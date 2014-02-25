 
#include "tpd.h"
#include <linux/interrupt.h>
#include <cust_eint.h>
#include <linux/i2c.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/rtpm_prio.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>

#include <linux/time.h>
#include <linux/delay.h>


#include <linux/rtpm_prio.h>

#include <linux/wakelock.h>

#include <asm/uaccess.h>

#include <linux/dma-mapping.h>
#include <linux/vmalloc.h>

#include "cust_gpio_usage.h"
#include "tpd_custom_ft5406.h"

#if 1 // defined(MT6577)
#include <mach/mt_pm_ldo.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_boot.h>
#elif defined(MT6575)
#include <mach/mt6575_pm_ldo.h>
#include <mach/mt6575_typedefs.h>
#include <mach/mt6575_boot.h>
#elif defined(CONFIG_ARCH_MT6573)
#include <mach/mt6573_boot.h>
#endif

#include "cust_gpio_usage.h"



extern struct tpd_device *tpd;
 
static DECLARE_WAIT_QUEUE_HEAD(waiter);
static void tpd_eint_interrupt_handler(void);
 extern void mt65xx_eint_unmask(unsigned int line);
 extern void mt65xx_eint_mask(unsigned int line);
 extern void mt65xx_eint_set_hw_debounce(kal_uint8 eintno, kal_uint32 ms);
 extern kal_uint32 mt65xx_eint_set_sens(kal_uint8 eintno, kal_bool sens);
 extern void mt65xx_eint_registration(kal_uint8 eintno, kal_bool Dbounce_En,
									  kal_bool ACT_Polarity, void (EINT_FUNC_PTR)(void),
									  kal_bool auto_umask);
static int __devinit tpd_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int tpd_detect(struct i2c_client *client, struct i2c_board_info *info);
static int __devexit tpd_remove(struct i2c_client *client);
static int touch_event_handler(void *unused);
 
#define TPD_OK 0

//LINE<JIRA_ID><DATE20130402><add for focaltech debug>zenghaihui
#if 1 // def FTS_CTL_IIC
#include "focaltech_ctl.h"
#endif

#ifdef TPD_HAVE_BUTTON 

static int tpd_keys_local[TPD_KEY_COUNT] = TPD_KEYS;
static int tpd_keys_dim_local_BYD[TPD_KEY_COUNT][4] = TPD_KEYS_DIM_BYD;
static int tpd_keys_dim_local_NB[TPD_KEY_COUNT][4] = TPD_KEYS_DIM_NB;

//LINE<JIRA_ID><DATE20130107><ftm set key>zenghaihui
static const int TPD_KEYSFACTORY[TPD_KEY_COUNT] =  {KEY_F1, KEY_F2, KEY_F3};


//LINE<JIRA_ID><DATE20130320><BUG_INFO>zenghaihui
kal_uint8 g_pre_tp_charger_flag = 0;
kal_uint8 g_tp_charger_flag = 0;
kal_uint8 g_need_refresh_tp_flag = 0;


static void tinno_update_tp_button_dim(int panel_vendor)
{
//LINE<JIRA_ID><DATE20130107><ftm set key>zenghaihui        
int i;
#ifdef TPD_HAVE_BUTTON     
        if (FACTORY_BOOT == get_boot_mode())
        {
        for (i = 0; i < TPD_KEY_COUNT ; i++)
            tpd_keys_local[i] = TPD_KEYSFACTORY[i];
        }
#endif   
      

	if ( FTS_CTP_VENDOR_NANBO == panel_vendor ){
		tpd_button_setting(TPD_KEY_COUNT, tpd_keys_local, tpd_keys_dim_local_NB);
	}else{
		tpd_button_setting(TPD_KEY_COUNT, tpd_keys_local, tpd_keys_dim_local_BYD);
	}
}
 
#endif

static tinno_ts_data *g_pts = NULL;
static volatile	int tpd_flag;

//FT5406DQ9
#define DRIVER_NAME "ft5406"

//LINE<JIRA_ID><DATE20130101><BUG_INFO>zenghaihui
//char tpd_desc[50];
//int tpd_fw_version;

//LINE <S8111B & S8201 TP> <DATE20121220> <S8111B & S8201 TP> zhangxiaofei
#define GPIO_CTP_WAKE_PIN 0xff			//GPIO_CTP_EN_PIN      //GPIO187

static const struct i2c_device_id ft5x06_tpd_id[] = {{DRIVER_NAME,0},{}};

/* This is not use after Android 4.0
static const struct i2c_device_id tpd_id[] = {{TPD_DEVICE,0},{}};
unsigned short force[] = {TPD_I2C_GROUP_ID, TPD_I2C_SLAVE_ADDR2, I2C_CLIENT_END, I2C_CLIENT_END}; 
static const unsigned short * const forces[] = { force, NULL };
static struct i2c_client_address_data addr_data = { 
	.forces = forces, 
};
*/

//BEGIN <S8111B & S8201 TP> <DATE20121220> <S8111B & S8201 TP> zhangxiaofei
	static struct i2c_board_info __initdata ft5x06_i2c_tpd[]={ 
					{I2C_BOARD_INFO(DRIVER_NAME, TPD_I2C_SLAVE_ADDR2)}
				};			
//END <S8111B & S8201 TP> <DATE20121220> <S8111B & S8201 TP> zhangxiaofei

static struct i2c_driver tpd_i2c_driver = {
	.driver = {
		 .name = DRIVER_NAME,
		 //.owner = THIS_MODULE,
	},
	.probe = tpd_probe,
	.remove = __devexit_p(tpd_remove),
	.id_table = ft5x06_tpd_id,
	.detect = tpd_detect,
	//.address_data = &addr_data,
};

static  void tpd_down(tinno_ts_data *ts, int x, int y, int pressure, int trackID) 
{
	CTP_DBG("x=%03d, y=%03d, pressure=%03d, ID=%03d", x, y, pressure, trackID);

	input_report_key(tpd->dev, BTN_TOUCH, 1);
       input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 20);
	input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
	input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);

	input_report_abs(tpd->dev, ABS_MT_TRACKING_ID, trackID);

	input_mt_sync(tpd->dev);


	if (FACTORY_BOOT == get_boot_mode() || RECOVERY_BOOT == get_boot_mode()) {   
		tpd_button(x, y, 1);  
	}	 
	//TPD_DOWN_DEBUG_TRACK(x,y);
 }
 
static  int tpd_up(tinno_ts_data *ts, int x, int y, int pressure, int trackID) 
{
        CTP_DBG("x=%03d, y=%03d, ID=%03d", x, y, trackID);
        //input_report_abs(tpd->dev, ABS_PRESSURE, 0);
        input_report_key(tpd->dev, BTN_TOUCH, 0);
        //input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 0);
        //input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
        //input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
        //input_report_abs(tpd->dev, ABS_MT_TRACKING_ID, trackID);
        input_mt_sync(tpd->dev);
        
        //TPD_UP_DEBUG_TRACK(x,y);
        if (FACTORY_BOOT == get_boot_mode() || RECOVERY_BOOT == get_boot_mode()) {   
            tpd_button(x, y, 0); 
        }     
        
        return 0;
 }


 static void tpd_dump_touchinfo(tinno_ts_data *ts)
 {
 	uint8_t *pdata = ts->buffer;
	CTP_DBG("0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x  0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x  0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x  0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x  0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x  0x%02x 0x%02x 0x%02x 0x%02x"
		"   0x%02x 0x%02x  0x%02x 0x%02x"
              , 
	      pdata[0],   pdata[1],  pdata[2],   
	      pdata[3],   pdata[4],  pdata[5],   pdata[6],  pdata[7], pdata[8],   
	      pdata[9],  pdata[10], pdata[11], pdata[12], pdata[13], pdata[15], 
	      pdata[15], pdata[16], pdata[17], pdata[18], pdata[19], pdata[20], 
	      pdata[21], pdata[22], pdata[23], pdata[24], pdata[25], pdata[26],
    pdata[27],   pdata[28],  pdata[29],   pdata[30],  pdata[31], pdata[32],   
    pdata[33],  pdata[34], pdata[35], pdata[36], pdata[37], pdata[38], 
    pdata[39], pdata[40], pdata[41], pdata[42], pdata[43], pdata[44], 
    pdata[45], pdata[46], pdata[47], pdata[48], pdata[49], pdata[50],
    pdata[51], pdata[52], pdata[53], pdata[54], pdata[55], pdata[56], 
    pdata[57], pdata[58], pdata[59], pdata[60]); 


 }
 
 static int tpd_touchinfo(tinno_ts_data *ts, tinno_ts_point *touch_point)
 {
	int i = 0;
	int iInvalidTrackIDs = 0;
	int iTouchID, iSearchDeep;
	uint8_t *p_data_buf = (uint8_t *)ts->buffer;
    
	int status, touch_num;
	int offset;
	int points;

	if ( tpd_read_touchinfo(ts) ){
		CTP_DBG("Read touch information error. \n");
		return -EAGAIN; 
	}

    

	if (TINNO_TOUCH_TRACK_IDS == 5) {
		touch_num = p_data_buf[2] & 0x07;
	} else {
		touch_num = p_data_buf[2] & 0x0f;//0x03;
	}

    
    CTP_DBG("touch_num is %d\n", touch_num);

    tpd_dump_touchinfo(ts);
    
    if (touch_num == 0)
    {
        ts->pcount = 0;
        ts->last_point_num = 0;
        return 0;
    }


    CTP_DBG("ts->last_point_num is %d\n", ts->last_point_num);
    
	points = touch_num;
	if (ts->last_point_num > touch_num) {
		touch_num = ts->last_point_num;
	}
	ts->last_point_num = points;


	if ( touch_num > TINNO_TOUCH_TRACK_IDS ){
		CTP_DBG("fingers is %d\n", touch_num);
		touch_num = TINNO_TOUCH_TRACK_IDS;
	}

	iSearchDeep = 0;

    if (get_boot_mode() == RECOVERY_BOOT || get_boot_mode() == FACTORY_BOOT)
    {
        if ( 1 == touch_num )
        {   
            iSearchDeep = 1;
        }
        else
        {      
            iSearchDeep = 0;
        }
    }
    else
    {
	iSearchDeep = touch_num;
    }

    ts->pcount = 0;

    offset = 0;
    
    if ( iSearchDeep )
    {
        for ( i=0; i < touch_num; i++ )
        {
            iTouchID = p_data_buf[5 + offset] >> 4;
            status = p_data_buf[3  + offset] >> 6;

            if ( iTouchID >= TINNO_TOUCH_TRACK_IDS )
            {
                CTP_DBG("i = %d: Invalied Track ID(%d)\n!", i, iTouchID);
                iInvalidTrackIDs++;
            }
            else if(1 == status)
            {
                CTP_DBG("i = %d: TP Up event status ==%d\n!", i, status);
            }
            else
            {
                touch_point[i].x = (s16)(p_data_buf[3 + offset] & 0x0F) << 8 | (s16)p_data_buf[4 + offset];
                touch_point[i].y = (s16)(p_data_buf[5 + offset] & 0x0F) << 8 | (s16)p_data_buf[6 + offset];

                touch_point[i].touch_id = iTouchID;
                touch_point[i].status = status;
                
                ts->pcount++;
                
                CTP_DBG("i = %d, iTouchID ==%d, x == %d , y == %d , status ==%d\n!", i, touch_point[i].touch_id, touch_point[i].x, touch_point[i].y, touch_point[i].status);
            }

            offset += 6;

        }

    }

    
    CTP_DBG("touch_num = %d, ts->pcount = %d \n", touch_num, ts->pcount);
    
    if (0==touch_num)
    {
            ts->pcount = 0 ; //0xFF;		//Release
    }
    
    if (ts->pcount > touch_num)
    {
            ts->pcount = touch_num;
    }
    
    return 0;

 };

 static int touch_event_handler(void *para)
 {
 	int i;
	tinno_ts_point touch_point[TINNO_TOUCH_TRACK_IDS];
	struct sched_param param = { .sched_priority = RTPM_PRIO_TPD };
	tinno_ts_data *ts = (tinno_ts_data *)para;
	sched_setscheduler(current, SCHED_RR, &param);
	
	do {
		set_current_state(TASK_INTERRUPTIBLE); 
		wait_event_interruptible(waiter, tpd_flag!=0);
		tpd_flag = 0;
		memset(touch_point, FTS_INVALID_DATA, sizeof(touch_point));
		set_current_state(TASK_RUNNING);

            
            //LINE<JIRA_ID><DATE20130320><BUG_INFO>zenghaihui
            if(g_tp_charger_flag != g_pre_tp_charger_flag)
            {
                g_pre_tp_charger_flag = g_tp_charger_flag;
                g_need_refresh_tp_flag = 1;
            }

            if(g_need_refresh_tp_flag)
            {
                g_need_refresh_tp_flag = 0;
                fts_ft5316_switch_charger_status(g_tp_charger_flag);
            }
        
        
		if (!tpd_touchinfo(ts, &touch_point)) {

			if(ts->pcount > 0)
			{
				for ( i=0; i < ts->pcount; i++ )
				{
					tpd_down(ts, touch_point[i].x, touch_point[i].y, touch_point[i].pressure, touch_point[i].touch_id);//<20120714><for multi-touch id>wangyanhui
				}
				input_sync(tpd->dev);
			}
			else
			{
				tpd_up(ts, touch_point[0].x, touch_point[0].y, touch_point[0].pressure, touch_point[0].touch_id);
				input_sync(tpd->dev);
			}
            
            
		}
		
		mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM); 
	}while(!kthread_should_stop());
	mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM); 
	return 0;
 }
 
static int tpd_detect (struct i2c_client *client, struct i2c_board_info *info) 
{
	strcpy(info->type, TPD_DEVICE);	
	return 0;
}
 
static void tpd_eint_interrupt_handler(void)
{
	if ( 0 == tpd_load_status ){
		return;
	}
	tpd_flag = 1;
	wake_up_interruptible(&waiter);
}

void fts_5x06_hw_reset(void)
{
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
	mdelay(1);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
	mdelay(15);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
	mdelay(1);
}

static void fts_5x06_hw_init(void)
{
	//make sure the WakeUp is high before it enter power on mode, 
	mt_set_gpio_mode(GPIO_CTP_WAKE_PIN, 0x00);
	mt_set_gpio_dir(GPIO_CTP_WAKE_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_WAKE_PIN, GPIO_OUT_ONE);
	msleep(2);  
	
	//Power On CTP
#if 1 // def MT6577
	hwPowerOn(MT65XX_POWER_LDO_VGP5, VOL_2800, "touch"); 
#else
	mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
	mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ONE);
#endif
	msleep(2);  
	
	//Reset CTP
	mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
	mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
	msleep(30);
}

static char *fts_get_vendor_name(int vendor_id)
{
	switch(vendor_id){
		case FTS_CTP_VENDOR_BYD:		return "BYD";			break;
		case FTS_CTP_VENDOR_TRULY:		return "TRULY";		break;
		case FTS_CTP_VENDOR_NANBO:		return "NANBO";		break;
		case FTS_CTP_VENDOR_BAOMING:	return "BAOMING";	break;
		case FTS_CTP_VENDOR_JIEMIAN:		return "JIEMIAN";		break;
		case FTS_CTP_VENDOR_YEJI:		return "YEJI";			break;
		case FTS_CTP_VENDOR_DEFAULT:	return "DEFAULT";		break;
		default:							return "UNKNOWN";	break;
	}
	return "UNKNOWN";
}

 static int __devinit tpd_probe(struct i2c_client *client, const struct i2c_device_id *id)
 {	 
	int retval = TPD_OK;
	int panel_version = 0;
	int panel_vendor = 0;
	int iRetry = 3;
	tinno_ts_data *ts;
	int ret = 0;
	
	if ( tpd_load_status ){
		printk("[ft5x06] %s:Already probed a TP, needn't to probe any more!",__func__);
		return -1;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev,"need I2C_FUNC_I2C");
		ret = -ENODEV;
		goto err_check_functionality_failed;
	}

	ts = kzalloc(sizeof(tinno_ts_data), GFP_KERNEL);
	if (ts == NULL) {
		ret = -ENOMEM;
		goto err_alloc_data_failed;
	}
	
	printk("[ft5x06] %s:TPD enter tpd_probe ts=0x%p, TPD_RES_X=%d, TPD_RES_Y=%d, addr=0x%x\n", __func__, ts, TPD_RES_X, TPD_RES_Y, client->addr);
	memset(ts, 0, sizeof(tinno_ts_data));
	g_pts = ts;

	client->timing = I2C_MASTER_CLOCK;
	ts->client = client;
	ts->start_reg = 0x00;
	atomic_set( &ts->ts_sleepState, 0 );
	mutex_init(&ts->mutex);

	i2c_set_clientdata(client, ts);

	fts_5x06_hw_init();
	msleep(120);
	
	fts_iic_init(ts);

	if ( fts_5x06_isp_init(ts) ){
		goto err_isp_register;
	}

	while (iRetry) {
		ret = ft5x06_get_vendor_version(ts, &panel_vendor, &panel_version);
		if ( panel_version < 0 || panel_vendor<0 || ret<0 ){
			printk("[ft5x06] %s: Product version is %d\n", __func__, panel_version);
			fts_5x06_hw_reset();
		}else{
            printk("[ft5x06] %s: panel_vendor =%x, panel_version=%x\n", __func__, panel_vendor, panel_version);
			break;
		}
		iRetry--;
		msleep(15);  
	} 
	if ( panel_version < 0 || panel_vendor<0 || ret<0 ){
		goto err_get_version;
	}
#ifdef TPD_HAVE_BUTTON 
	tinno_update_tp_button_dim(panel_vendor);
#endif
#ifdef CONFIG_TOUCHSCREEN_FT5X05_DISABLE_KEY_WHEN_SLIDE
	if ( fts_keys_init(ts) ){
		fts_keys_deinit();
		goto err_get_version;
	}
#endif
	
	mt_set_gpio_mode(GPIO_CTP_EINT_PIN, GPIO_CTP_EINT_PIN_M_EINT);
	mt_set_gpio_dir(GPIO_CTP_EINT_PIN, GPIO_DIR_IN);
	mt_set_gpio_pull_enable(GPIO_CTP_EINT_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_CTP_EINT_PIN, GPIO_PULL_UP);
 
 	mt65xx_eint_set_sens(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_SENSITIVE);
	mt65xx_eint_set_hw_debounce(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_CN);
	mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_TOUCH_PANEL_POLARITY, tpd_eint_interrupt_handler, 0); 
 
	ts->thread = kthread_run(touch_event_handler, ts, TPD_DEVICE);
	 if (IS_ERR(ts->thread)){ 
		  retval = PTR_ERR(ts->thread);
		  printk("[ft5x06] %s: failed to create kernel thread: %d\n", __func__, retval);
			goto err_start_touch_kthread;
	}

	tpd_load_status = 1;
	mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM); 
	
	printk("[ft5x06] %s:Touch Panel Device(%s) Probe PASS\n", __func__, fts_get_vendor_name(panel_vendor));
//#if defined (TINNO_ANDROID_S9091) || defined (TINNO_ANDROID_S8121) || defined(TINNO_ANDROID_S8111B)
#if 1
{
	extern char tpd_desc[50];
	extern int tpd_fw_version;
	sprintf(tpd_desc, "%s", fts_get_vendor_name(panel_vendor));
	tpd_fw_version = panel_version;
}
#endif

//LINE<JIRA_ID><DATE20130402><add for focaltech debug>zenghaihui
#ifdef FTS_CTL_IIC
        if (ft_rw_iic_drv_init(client) < 0)
            dev_err(&client->dev, "%s:[FTS] create fts control iic driver failed\n",
                    __func__);
#endif

    //LINE<JIRA_ID><DATE20130320><add charger flag>zenghaihui
    g_need_refresh_tp_flag = 1;
    
	return 0;
   
err_start_touch_kthread:
	mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM); 
err_get_version:
err_isp_register:
  #ifdef CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP
	hwPowerDown(MT65XX_POWER_LDO_VGP5, "touch"); 
  #endif	
	fts_5x06_isp_exit();
	mutex_destroy(&ts->mutex);
	g_pts = NULL;
	kfree(ts);
err_alloc_data_failed:
err_check_functionality_failed:
	printk("[ft5x06] %s:Touch Panel Device Probe FAIL\n", __func__);
	return -1;
 }

 static int __devexit tpd_remove(struct i2c_client *client)
{
	CTP_DBG("TPD removed\n");
    
//LINE<JIRA_ID><DATE20130402><add for focaltech debug>zenghaihui
#ifdef FTS_CTL_IIC
	ft_rw_iic_drv_exit();
#endif

	return 0;
}
 
 static int tpd_local_init(void)
{
	TPD_DMESG("Focaltech FT5x06 I2C Touchscreen Driver (Built %s @ %s)\n", __DATE__, __TIME__);
	if(i2c_add_driver(&tpd_i2c_driver)!=0)
	{
		TPD_DMESG("unable to add i2c driver.\n");
		return -1;
	}
#ifdef TPD_HAVE_BUTTON     
		tinno_update_tp_button_dim(FTS_CTP_VENDOR_NANBO);
#endif   
	TPD_DMESG("end %s, %d\n", __FUNCTION__, __LINE__);  
	tpd_type_cap = 1;
	return 0; 
}

static void tpd_resume(struct early_suspend *h)
{
	if ( g_pts ){
		CTP_DBG("TPD wake up\n");
		if (atomic_read(&g_pts->isp_opened)){
			CTP_DBG("isp is already opened.");
			return;
		}

#ifdef CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP
		fts_5x06_hw_init();
#else //!CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP
		mt_set_gpio_mode(GPIO_CTP_WAKE_PIN, GPIO_CTP_WAKE_PIN_M_GPIO);
		mt_set_gpio_dir(GPIO_CTP_WAKE_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_CTP_WAKE_PIN, GPIO_OUT_ZERO);
		msleep(1);  
		mt_set_gpio_mode(GPIO_CTP_WAKE_PIN, GPIO_CTP_WAKE_PIN_M_GPIO);
		mt_set_gpio_dir(GPIO_CTP_WAKE_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_CTP_WAKE_PIN, GPIO_OUT_ONE);
#endif//CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP
		mutex_unlock(&g_pts->mutex);//Lock on suspend
		mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);  

		atomic_set( &g_pts->ts_sleepState, 0 );
        
        //LINE<JIRA_ID><DATE20130320><add charger flag>zenghaihui
        g_need_refresh_tp_flag = 1;
        
	}
 }
 

static void tpd_suspend(struct early_suspend *h)
 {
	int ret = 0;
	int iRetry = 5;
	const char data = 0x3;
 
	if ( g_pts ){
		 CTP_DBG("TPD enter sleep\n");
		if (atomic_read(&g_pts->isp_opened)){
			CTP_DBG("isp is already opened.");
			return;
		}

		 mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
		mutex_lock(&g_pts->mutex);//Unlock on resume
		 
#ifdef CONFIG_TOUCHSCREEN_FT5X05_DISABLE_KEY_WHEN_SLIDE
		fts_5x06_key_cancel();
#endif

#ifdef CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP
	mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
	mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
	msleep(2);
#if 1 // def MT6577
		hwPowerDown(MT65XX_POWER_LDO_VGP5, "touch"); 
#else
		mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
		mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
		mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ZERO);
#endif	
#else //!CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP
		//make sure the WakeUp is high before it enter sleep mode, 
		//otherwise the touch can't be resumed.
		//mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
		//mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
		//mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ONE);
		//msleep(1);  

		while (iRetry) {
			ret = i2c_smbus_write_i2c_block_data(g_pts->client, 0xA5, 1, &data);  //TP enter sleep mode
			if ( ret < 0 ){
				TPD_DMESG("Enter sleep mode is %d\n", ret);
#if 1 // def MT6577
				hwPowerDown(MT65XX_POWER_LDO_VGP5, "touch"); 
#else
				mt_set_gpio_mode(GPIO_CTP_EN_PIN, GPIO_CTP_EN_PIN_M_GPIO);
				mt_set_gpio_dir(GPIO_CTP_EN_PIN, GPIO_DIR_OUT);
				mt_set_gpio_out(GPIO_CTP_EN_PIN, GPIO_OUT_ZERO);
#endif	
				msleep(2);  
				fts_5x06_hw_init();
			}else{
				break;
			}
			iRetry--;
			msleep(100);  
		} 
#endif//CONFIG_TOUCHSCREEN_POWER_DOWN_WHEN_SLEEP

		atomic_set( &g_pts->ts_sleepState, 1 );
	}
 } 



//LINE<JIRA_ID><DATE20130422><add multi tp>zenghaihui
extern int get_fw_version_ext(void);
extern char tpd_desc[50];
int ft5x06_tpd_get_fw_version( void )
{
    return get_fw_version_ext();
}

void ft5x06_tpd_get_fw_vendor_name(char * fw_vendor_name)
{
    sprintf(fw_vendor_name, "%s", tpd_desc);
}

 
 static struct tpd_driver_t tpd_device_driver = {
	.tpd_device_name = DRIVER_NAME,
	.tpd_local_init = tpd_local_init,
	.suspend = tpd_suspend,
	.resume = tpd_resume,
#ifdef TPD_HAVE_BUTTON
	.tpd_have_button = 1,
#else
	.tpd_have_button = 0,
#endif	
    //LINE<JIRA_ID><DATE20130422><add multi tp>zenghaihui
    .tpd_get_fw_version = ft5x06_tpd_get_fw_version,
    .tpd_get_fw_vendor_name = ft5x06_tpd_get_fw_vendor_name,
 };
 
 /* called when loaded into kernel */
 static int __init tpd_driver_init(void) 
 {
	printk("MediaTek FT5x06 touch panel driver init\n");
	i2c_register_board_info(TPD_I2C_GROUP_ID, &ft5x06_i2c_tpd, sizeof(ft5x06_i2c_tpd)/sizeof(ft5x06_i2c_tpd[0]));
	if(tpd_driver_add(&tpd_device_driver) < 0)
		TPD_DMESG("add FT5x06 driver failed\n");
	return 0;
 }
 
 /* should never be called */
 static void __exit tpd_driver_exit(void) 
{
	TPD_DMESG("MediaTek FT5x06 touch panel driver exit\n");
	//input_unregister_device(tpd->dev);
	tpd_driver_remove(&tpd_device_driver);
}
 
 module_init(tpd_driver_init);
 module_exit(tpd_driver_exit);
 EXPORT_SYMBOL(g_tp_charger_flag);
