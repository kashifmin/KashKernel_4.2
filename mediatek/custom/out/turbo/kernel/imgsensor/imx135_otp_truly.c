/*************************************************************************************************
imx135_otp.c
---------------------------------------------------------
OTP Application file From Truly for imx135
2013.01.14
---------------------------------------------------------
NOTE:
The modification is appended to initialization of image sensor. 
After sensor initialization, use the function , and get the id value.
bool otp_wb_update(BYTE zone)
and
bool otp_lenc_update(BYTE zone), 
then the calibration of AWB and LSC will be applied. 
After finishing the OTP written, we will provide you the golden_rg and golden_bg settings.
**************************************************************************************************/

#include <linux/videodev2.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <linux/delay.h>  
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <asm/atomic.h>
#include <linux/slab.h>

#include "kd_camera_hw.h"
#include "kd_imgsensor.h"
#include "kd_imgsensor_define.h"
#include "kd_imgsensor_errcode.h"

#include "imx135mipiraw_Sensor_truly.h"
#include "imx135mipiraw_Camera_Sensor_para_truly.h"
#include "imx135mipiraw_CameraCustomized_truly.h"

//#include "imx135_otp.h"
extern int iReadReg(u16 a_u2Addr, u8 * a_puBuff, u16 i2cId);
extern int iWriteReg(u16 a_u2Addr, u32 a_u4Data, u32 a_u4Bytes, u16 i2cId);

static BYTE imx135_byteread_cmos_sensor(kal_uint32 addr)
{
	kal_uint16 get_byte=0;
    iReadReg((u16)addr ,(u8*)&get_byte, IMX135MIPI_WRITE_ID);
    return get_byte;
}

static void imx135_wordwrite_cmos_sensor(u16 addr, u32 para){
    iWriteReg((u16)addr, (u32)para, 2, IMX135MIPI_WRITE_ID);
}

static void imx135_bytewrite_cmos_sensor(u16 addr, u32 para){
    iWriteReg((u16)addr, (u32)para, 1, IMX135MIPI_WRITE_ID);
}

#define USHORT             unsigned short
#define BYTE               unsigned char
#define Sleep(ms)          mdelay(ms)
#define TRULY_ID           0x01 // Jiangde 02---> 01
#define TRULY_ID2          0x02 // Jiangde

enum LENS
{
	LARGEN_LENS = 1,
	KT_LENS,
	KM_LENS,
	GENIUS_LENS,
	SUNNY_LENS,
	OTHER_LENS,
};
enum DRIVER_IC
{
	DONGWOOK = 1,
	ADI,
	ASM,
	ROHM,
	OTHER_IC,
};
enum VCM
{
	TDK = 1,
	MISTUMIS,
	SIKAO,
	MWT,
	ALPS,
	OTHER_VCM,
};
#define VALID_OTP          0x40

#define GAIN_DEFAULT       0x0100
#define GAIN_GREEN1_ADDR   0x020E
#define GAIN_BLUE_ADDR     0x0212
#define GAIN_RED_ADDR      0x0210
#define GAIN_GREEN2_ADDR   0x0214

USHORT golden_r;
USHORT golden_gr;
USHORT golden_gb;
USHORT golden_b;

USHORT current_r;
USHORT current_gr;
USHORT current_gb;
USHORT current_b;

kal_uint32 r_ratio;
kal_uint32 b_ratio;

bool g_b_lsc_read = 0;
BYTE lsc_data[64 * 8] ={0}; // Jiangde global

//kal_uint32	golden_r = 0, golden_gr = 0, golden_gb = 0, golden_b = 0;
//kal_uint32	current_r = 0, current_gr = 0, current_gb = 0, current_b = 0;
/*************************************************************************************************
* Function    :  start_read_otp
* Description :  before read otp , set the reading block setting  
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  0, reading block setting err
                 1, reading block setting ok 
**************************************************************************************************/
static bool start_read_otp(BYTE zone)
{
	BYTE val = 0;
	int i;
	imx135_bytewrite_cmos_sensor(0x3B02, zone);   //PAGE
	imx135_bytewrite_cmos_sensor(0x3B00, 0x01);
	Sleep(5);
	for(i=0;i<100;i++)
	{
		val = imx135_byteread_cmos_sensor(0x3B01);
		if((val & 0x01) == 0x01)
			break;
		Sleep(2);
	}
	if(i == 100)
	{
		printk("[truly] Read Page %d Err!\n", zone); // print log
		return 0;
	}
	return 1;
}


/*************************************************************************************************
* Function    :  get_otp_flag
* Description :  get otp WRITTEN_FLAG  
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE], if 0x40 , this type has valid otp data, otherwise, invalid otp data
**************************************************************************************************/
static BYTE get_otp_flag(BYTE zone)
{
	BYTE flag = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	flag = imx135_byteread_cmos_sensor(0x3B04);
	printk("[truly] get_otp_flag, Flag:0x%02x \n",flag );
    
	flag = flag & 0xc0;
	printk("[truly] get_otp_flag, Flag & 0xc0 = 0x%02x \n",flag );
	return flag;
}

/*************************************************************************************************
* Function    :  get_otp_date
* Description :  get otp date value    
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f    
**************************************************************************************************/
static bool get_otp_date(BYTE zone) 
{
	BYTE year  = 0;
	BYTE month = 0;
	BYTE day   = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	year  = imx135_byteread_cmos_sensor(0x3B06);
	month = imx135_byteread_cmos_sensor(0x3B07);
	day   = imx135_byteread_cmos_sensor(0x3B08);
    printk("[truly] OTP date=%02d.%02d.%02d(YYMMDD)\n", year,month,day);
	return 1;
}


/*************************************************************************************************
* Function    :  get_otp_module_id
* Description :  get otp MID value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : module ID data , TRULY ID is 0x0001            
**************************************************************************************************/
static BYTE get_otp_module_id(BYTE zone)
{
	BYTE module_id = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	module_id = imx135_byteread_cmos_sensor(0x3B05);
	printk("[truly] OTP_Module ID: 0x%02x.\n",module_id);
	return module_id;
}


/*************************************************************************************************
* Function    :  get_otp_lens_id
* Description :  get otp LENS_ID value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : LENS ID data             
**************************************************************************************************/
static BYTE get_otp_lens_id(BYTE zone)
{
	BYTE lens_id = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	lens_id = imx135_byteread_cmos_sensor(0x3B09);
	printk("[truly] OTP_Lens ID: 0x%02x.\n",lens_id);
	return lens_id;
}


/*************************************************************************************************
* Function    :  get_otp_vcm_id
* Description :  get otp VCM_ID value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : VCM ID data             
**************************************************************************************************/
static BYTE get_otp_vcm_id(BYTE zone)
{
	BYTE vcm_id = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	vcm_id = imx135_byteread_cmos_sensor(0x3B0A);
	printk("[truly] OTP_VCM ID: 0x%02x.\n",vcm_id);
	return vcm_id;	
}


/*************************************************************************************************
* Function    :  get_otp_driver_id
* Description :  get otp driver id value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                 other value : driver ID data             
**************************************************************************************************/
static BYTE get_otp_driver_id(BYTE zone)
{
	BYTE driver_id = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	driver_id = imx135_byteread_cmos_sensor(0x3B0B);
	printk("[truly] OTP_Driver ID: 0x%02x.\n",driver_id);
	return driver_id;
}

/*************************************************************************************************
* Function    :  get_light_id
* Description :  get otp environment light temperature value 
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f
* Return      :  [BYTE] 0 : OTP data fail 
                        other value : driver ID data     
			            BIT0:D65(6500K) EN
						BIT1:D50(5100K) EN
						BIT2:CWF(4000K) EN
						BIT3:A Light(2800K) EN
**************************************************************************************************/
static BYTE get_light_id(BYTE zone)
{
	BYTE light_id = 0;
	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}
	light_id = imx135_byteread_cmos_sensor(0x3B0C);
	printk("[truly] OTP_Light ID: 0x%02x.\n",light_id);
	return light_id;
}

/*************************************************************************************************
* Function    :  get_lsc_flag
* Description :  get LSC WRITTEN_FLAG  
* Return      :  [BYTE], if 0x40 , this type has valid lsc data, otherwise, invalid otp data
**************************************************************************************************/
static BYTE get_lsc_flag()
{
	BYTE flag = 0;
	if(!start_read_otp(0x0B))
	{
		printk("[truly] Start read Page 0x0B Fail!\n");
		return 0;
	}
	flag = imx135_byteread_cmos_sensor(0x3B43);
	flag = flag & 0xc0;
	printk("[truly] Flag:0x%02x\n",flag );
	return flag;
}

/*************************************************************************************************
* Function    :  otp_lenc_update
* Description :  Update lens correction 
* Return      :  [bool] 0 : OTP data fail 
                        1 : otp_lenc update success            
**************************************************************************************************/
static bool otp_lenc_update()
{
	BYTE lsc_flag;
	int i, j;
	BYTE temp1, temp2;

	lsc_flag = get_lsc_flag();
	lsc_flag = lsc_flag & 0xC0;
	if(lsc_flag == 0xC0 || lsc_flag == 0x80 ) // Jiangde how about 0x80 ?
	{
		printk("[truly] lsc data invalid\n");
		return 0;
	}
	else if(lsc_flag == 0x00)
	{
		printk("[truly] no lsc data\n");
		return 0;
	}

    // BYTE lsc_data[64 * 8] ={0}; // Jiangde global

	for(i=0;i<8;i++)
	{
		if(!start_read_otp(0x04+i))
		{
			printk("[truly] Start read Page %d Fail!\n", 0x04+i);
			return 0;
		}
		for(j=0;j<64;j++) // Jiangde i<64 --> j<64
     		lsc_data[i*64+j] = imx135_byteread_cmos_sensor(0x3B04+j);
	}

    g_b_lsc_read = 1;
	printk("[truly] read lsc finished\n");
    return 1;

    /*
	for(i=0;i<504;i++) //LSC SIZE is 504 BYTES
		imx135_bytewrite_cmos_sensor(0x4800+i, lsc_data[i]);

	//Enable LSC
	temp1 = imx135_byteread_cmos_sensor(0x0700);
	temp2 = imx135_byteread_cmos_sensor(0x3A63);
	temp1 = temp1 | 0x01;
	temp2 = temp2 | 0x01;
	imx135_bytewrite_cmos_sensor(0x0700, temp1);
	imx135_bytewrite_cmos_sensor(0x3A63, temp2);

	printk("[truly] Update lsc finished\n");
	*/
	return 1;
}

/*************************************************************************************************
* Function    :  wb_gain_set
* Description :  Set WB ratio to register gain setting  512x
* Parameters  :  [int] r_ratio : R ratio data compared with golden module R
                       b_ratio : B ratio data compared with golden module B
* Return      :  [bool] 0 : set wb fail 
                        1 : WB set success            
**************************************************************************************************/

static bool wb_gain_set()
{
	USHORT R_GAIN;
	USHORT B_GAIN;
	USHORT Gr_GAIN;
	USHORT Gb_GAIN;
	USHORT G_GAIN;
		
	if(!r_ratio || !b_ratio)
	{
		printk("[truly] OTP WB ratio Data Err!\n");
		return 0;
	}

	if(r_ratio >= 512 )
	{
		if(b_ratio>=512) 
		{
			R_GAIN = (USHORT)(GAIN_DEFAULT * r_ratio / 512);						
			G_GAIN = GAIN_DEFAULT;
			B_GAIN = (USHORT)(GAIN_DEFAULT * b_ratio / 512);
		}
		else
		{
			R_GAIN =  (USHORT)(GAIN_DEFAULT*r_ratio / b_ratio );
			G_GAIN = (USHORT)(GAIN_DEFAULT*512 / b_ratio );
			B_GAIN = GAIN_DEFAULT; 
		}
	}
	else                      
	{
		if(b_ratio >= 512)
		{
			R_GAIN = GAIN_DEFAULT;
			G_GAIN = (USHORT)(GAIN_DEFAULT*512 /r_ratio);		
			B_GAIN =  (USHORT)(GAIN_DEFAULT*b_ratio / r_ratio );
		} 
		else 
		{
			Gr_GAIN = (USHORT)(GAIN_DEFAULT*512/ r_ratio );						
			Gb_GAIN = (USHORT)(GAIN_DEFAULT*512/b_ratio );						
			if(Gr_GAIN >= Gb_GAIN)						
			{						
				R_GAIN = GAIN_DEFAULT;						
				G_GAIN = (USHORT)(GAIN_DEFAULT *512/ r_ratio );						
				B_GAIN =  (USHORT)(GAIN_DEFAULT*b_ratio / r_ratio );						
			} 
			else
			{						
				R_GAIN =  (USHORT)(GAIN_DEFAULT*r_ratio  / b_ratio);						
				G_GAIN = (USHORT)(GAIN_DEFAULT*512 / b_ratio );						
				B_GAIN = GAIN_DEFAULT;
			}
		}        
	}

	printk("[truly] OTP_golden_r=%d,golden_gr=%d,golden_gb=%d,golden_b=%d \n",golden_r,golden_gr,golden_gb,golden_b);
	printk("[truly] OTP_current_r=%d,current_gr=%d,current_gb=%d,current_b=%d \n",current_r,current_gr,current_gb,current_b);
	printk("[truly] OTP_r_ratio=%d,b_ratio=%d \n",r_ratio,b_ratio);
 
	imx135_wordwrite_cmos_sensor(GAIN_RED_ADDR, R_GAIN);		
	imx135_wordwrite_cmos_sensor(GAIN_BLUE_ADDR, B_GAIN);     
	imx135_wordwrite_cmos_sensor(GAIN_GREEN1_ADDR, G_GAIN); //Green 1 default gain 1x		
	imx135_wordwrite_cmos_sensor(GAIN_GREEN2_ADDR, G_GAIN); //Green 2 default gain 1x
	printk("[truly] OTP WB Update Finished! \n");
	return 1;
}

/*************************************************************************************************
* Function    :  get_otp_wb
* Description :  Get WB data    
* Parameters  :  [BYTE] zone : OTP PAGE index , 0x00~0x0f      
**************************************************************************************************/
static bool get_otp_wb(BYTE zone)
{
	BYTE temph = 0;
	BYTE templ = 0;
	golden_r = 0, golden_gr = 0, golden_gb = 0, golden_b = 0;
	current_r = 0, current_gr = 0, current_gb = 0, current_b = 0;

	if(!start_read_otp(zone))
	{
		printk("[truly] Start read Page %d Fail!\n", zone);
		return 0;
	}

	temph = imx135_byteread_cmos_sensor(0x3B18);  
	templ = imx135_byteread_cmos_sensor(0x3B19);   
	golden_r  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B1A);
	templ = imx135_byteread_cmos_sensor(0x3B1B);
	golden_gr  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B1C);
	templ = imx135_byteread_cmos_sensor(0x3B1D);
	golden_gb  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B1E);
	templ = imx135_byteread_cmos_sensor(0x3B1F);
	golden_b  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B10);  
	templ = imx135_byteread_cmos_sensor(0x3B11);   
	current_r  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B12);
	templ = imx135_byteread_cmos_sensor(0x3B13);
	current_gr  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B14);
	templ = imx135_byteread_cmos_sensor(0x3B15);
	current_gb  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	temph = imx135_byteread_cmos_sensor(0x3B16);
	templ = imx135_byteread_cmos_sensor(0x3B17);
	current_b  = (USHORT)templ + (((USHORT)temph & 0x03) << 8);

	return 1;
}


/*************************************************************************************************
* Function    :  otp_wb_update
* Description :  Update WB correction 
* Return      :  [bool] 0 : OTP data fail 
                        1 : otp_WB update success            
**************************************************************************************************/
static bool otp_wb_update(BYTE zone)
{
	USHORT golden_g, current_g;


	if(!get_otp_wb(zone))  // get wb data from otp
	{
		printk("[truly] Get OTP WB data Err!\n");
		return 0;
	}

	golden_g = (golden_gr + golden_gb) / 2;
	current_g = (current_gr + current_gb) / 2;

	if(!golden_g || !current_g || !golden_r || !golden_b || !current_r || !current_b)
	{
		printk("[truly] WB update Err !\n");
		return 0;
	}

	r_ratio = 512 * golden_r * current_g /( golden_g * current_r );
	b_ratio = 512 * golden_b * current_g /( golden_g * current_b );

	// wb_gain_set(); Jiangde --

	printk("[truly] WB update finished! \n");

	return 1;
}

/*************************************************************************************************
* Function    :  otp_update()
* Description :  update otp data from otp , it otp data is valid, 
                 it include get ID and WB update function  
* Return      :  [bool] 0 : update fail
                        1 : update success
**************************************************************************************************/
static bool otp_update()
{
	BYTE zone = 0x01;
	BYTE FLG  = 0x00;
	BYTE MID = 0x00, LENS_ID= 0x00, VCM_ID= 0x00;
	int i;

	for(i=0;i<3;i++)
	{
		FLG = get_otp_flag(zone);
		if(FLG == VALID_OTP)
    		break;
		else
	    	zone++;
	}
	if(i==3)
	{
		printk("[truly] No OTP Data or OTP data is invalid!!!\n");
		return 0;
	}

	MID =     get_otp_module_id(zone);
	LENS_ID = get_otp_lens_id(zone);
	VCM_ID =  get_otp_vcm_id(zone);

    get_otp_date(zone);
    get_light_id(zone);
    printk("[truly] MID=0x%02x, LENS_ID=0x%02x, VCM_ID=0x%02x, zone=%d",
        MID, LENS_ID, VCM_ID, zone);
    
	if(MID != TRULY_ID && MID != TRULY_ID2) //Select 
	{
		printk("[truly] No Truly Module !!!!\n");
		return 0;
	}
	otp_wb_update(zone);
	
	if(!otp_lenc_update())
	{
		printk("[truly] Update LSC Err\n");
		return 0;
	}

	return 1;	
}


// BEGIN <20130708> <truly OTP> Jiangde
int update_lens_truly(){
    int i, j;
	BYTE temp1, temp2;

	printk("[truly] in update_lens_truly\n");
    if (0 == g_b_lsc_read) {
    	printk("[truly] update_lens_truly -- g_b_lsc_read=0 , error !!!\n");
        return 0;
    }
    
	for(i=0;i<504;i++) //LSC SIZE is 504 BYTES
		imx135_bytewrite_cmos_sensor(0x4800+i, lsc_data[i]);

	//Enable LSC
	temp1 = imx135_byteread_cmos_sensor(0x0700);
	temp2 = imx135_byteread_cmos_sensor(0x3A63);
	temp1 = temp1 | 0x01;
	temp2 = temp2 | 0x01;
	imx135_bytewrite_cmos_sensor(0x0700, temp1);
	imx135_bytewrite_cmos_sensor(0x3A63, temp2);

	printk("[truly] out update_lens_truly, OK\n");
    return 1;
}


int update_awb_gain_truly()
{
    printk("[truly] in update_awb_gain_truly\n");
    wb_gain_set();
    printk("[truly] out update_awb_gain_truly, OK\n");
}


int read_otp_lenc_truly(){

	BYTE zone = 0x01;
	BYTE FLG  = 0x00;
	BYTE MID = 0x00, LENS_ID= 0x00, VCM_ID= 0x00;
	int i;

    printk("[truly] in read_otp_lenc_truly\n");
	for(i=0;i<3;i++)
	{
		FLG = get_otp_flag(zone);
		if(FLG == VALID_OTP)
    		break;
		else
	    	zone++;
	}
	if(i==3)
	{
		printk("[truly] No OTP Data or OTP data is invalid, error !!!\n");
		return 0;
	}

	MID =     get_otp_module_id(zone);
	LENS_ID = get_otp_lens_id(zone);
	VCM_ID =  get_otp_vcm_id(zone);

    get_otp_date(zone);
    get_light_id(zone);
    printk("[truly] ModuleID=0x%02x, LENS_ID=0x%02x, VCM_ID=0x%02x, zone=%d\n",
        MID, LENS_ID, VCM_ID, zone);
    
	if(MID != TRULY_ID && MID != TRULY_ID2) //Select 
	{
		printk("[truly] No Truly Module, error !!!!\n");
		return 0;
	}
	
	if(!otp_lenc_update())
	{
		printk("[truly] Update LSC Err\n");
		return 0;
	}

    printk("[truly] out read_otp_lenc_truly, OK\n");
	return 1;	
}


int read_otp_wb_truly(){
	BYTE zone = 0x01;
	BYTE FLG  = 0x00;
	BYTE MID = 0x00, LENS_ID= 0x00, VCM_ID= 0x00;
	int i;

    printk("[truly] in read_otp_wb_truly\n");
	for(i=0;i<3;i++)
	{
		FLG = get_otp_flag(zone);
		if(FLG == VALID_OTP)
    		break;
		else
	    	zone++;
	}
	if(i==3)
	{
		printk("[truly] No OTP Data or OTP data is invalid, error !!!\n");
		return 0;
	}

	MID =     get_otp_module_id(zone);
	LENS_ID = get_otp_lens_id(zone);
	VCM_ID =  get_otp_vcm_id(zone);

    get_otp_date(zone);
    get_light_id(zone);
    printk("[truly] ModuleID=0x%02x, LENS_ID=0x%02x, VCM_ID=0x%02x, zone=%d\n",
        MID, LENS_ID, VCM_ID, zone);
    
	if(MID != TRULY_ID && MID != TRULY_ID2) //Select 
	{
		printk("[truly] No Truly Module, error !!!!\n");
		return 0;
	}
	otp_wb_update(zone);

    printk("[truly] out read_otp_wb_truly, OK\n");
	return 1;	
}


bool is_truly_cm9010(void){
	BYTE zone = 0x01;
	BYTE FLG  = 0x00;
	BYTE MID = 0x00, LENS_ID= 0x00, VCM_ID= 0x00;
	int i;

    printk("[truly] in is_truly_cm9010\n");
	for(i=0; i<3; i++)
	{
		FLG = get_otp_flag(zone);
		if(FLG == VALID_OTP)
    		break;
		else
	    	zone++;
	}
	if(i==3)
	{
		printk("[truly] No OTP Data or OTP data is invalid, error !!!\n");
		return 0;
	}

	MID =     get_otp_module_id(zone);
	LENS_ID = get_otp_lens_id(zone);
	VCM_ID =  get_otp_vcm_id(zone);

    get_otp_date(zone);
    get_light_id(zone);
    printk("[truly] ModuleID=0x%02x, LENS_ID=0x%02x, VCM_ID=0x%02x, zone=%d\n",
        MID, LENS_ID, VCM_ID, zone);
    
	if(MID != TRULY_ID && MID != TRULY_ID2) //Select 
	{
		printk("[truly] No Truly Module, error !!!!\n");
		return 0;
	}

    printk("[truly] out is_truly_cm9010, OK\n");
    return 1;
}

// END <20130708> <truly OTP> Jiangde
