
#include "tpd_custom_ft5316_5p.h"

 void ft5316_tpd_reset(void)
{
    mt_set_gpio_out(TPIO_RESET,1);				//output low  
    msleep(3);	
    mt_set_gpio_out(TPIO_RESET,0);				//output low
    msleep(3);
    mt_set_gpio_out(TPIO_RESET,1);				//output low  
    //msleep(50);	
    msleep(40);
}

 void tinno_tp_power_on(void)
{
    hwPowerOn(TPD_POWER_SOURCE, VOL_2800, "TP");     
    msleep(10);	
    
    mt_set_gpio_mode(TPIO_WAKEUP, 0x00);		//GPIO mode        
    mt_set_gpio_dir(TPIO_WAKEUP,1);
    mt_set_gpio_pull_enable(TPIO_WAKEUP, 1);	//external pull up???        
    mt_set_gpio_pull_select(TPIO_WAKEUP, GPIO_PULL_UP);	   
    
    mt_set_gpio_out(TPIO_WAKEUP,1);				//output high???
    msleep(5);	
    mt_set_gpio_mode(TPIO_RESET, 0x00);		//GPIO mode        
    mt_set_gpio_dir(TPIO_RESET,1);
    mt_set_gpio_pull_enable(TPIO_RESET, 1);	//external pull up???        
    mt_set_gpio_pull_select(TPIO_RESET, GPIO_PULL_UP);	   
    mt_set_gpio_out(TPIO_RESET,1);
    msleep(200);       
}    

 void tinno_tp_power_off(void)
{
    mt_set_gpio_mode(TPIO_WAKEUP, 0x00);		//GPIO mode        
    mt_set_gpio_dir(TPIO_WAKEUP,1);
    mt_set_gpio_pull_enable(TPIO_WAKEUP, 1);	//external pull up???        
    mt_set_gpio_pull_select(TPIO_WAKEUP, GPIO_PULL_DOWN);	       
    mt_set_gpio_out(TPIO_WAKEUP,0);

    msleep(10);        
    
    mt_set_gpio_mode(TPIO_RESET, 0x00);		//GPIO mode        
    mt_set_gpio_dir(TPIO_RESET,1);
    mt_set_gpio_pull_enable(TPIO_RESET, 1);	//external pull up???        
    mt_set_gpio_pull_select(TPIO_RESET, GPIO_PULL_DOWN);	   
    mt_set_gpio_out(TPIO_RESET,0);				//output low
    hwPowerDown(TPD_POWER_SOURCE, "TP");
    
    msleep(50); 
    
}    

ssize_t tp_write_m_byte(u8 cmd, u8 *writeData,U16 len)
{
//	TPD_DEBUG("tp_write_m_byte!! \n");
    char    write_data[8] = {0};
    int   i, ret=0;
    struct i2c_client * i2c_client = ft5316_i2c_client;
    if(len == 0) {
        TPD_DEBUG("[Error]TP Write Len should not be zero!! \n");
        return 0;
    }
    //Driver does not allow (single write length > 8)
    while(len > 8)
    {
        for (i = 0; i<7; i++){
            write_data[i] = *(writeData+i);    
        }
        ret = i2c_master_send(ft5316_i2c_client, write_data, 8);
        if (ret < 0) {
            TPD_DEBUG("[Error]TP reads data error!! \n");
            return 0;
        }
        writeData+=8;
        len -= 8;
    }
    if (len > 0){
        for (i = 0; i<len; i++){
            write_data[i] = *(writeData+i);    
        }
        ret = i2c_master_send(ft5316_i2c_client, write_data, len);
        if (ret < 0) {
            TPD_DEBUG("[Error]TP reads data error!! \n");
            return 0;
        }
    }

    return 1;
}

//return value:   2013-1-15
// <0  :  // the driver do not match the IC
// = 0 :  // IC has been upgraded fail.
// > 0 :  // IC work well.
//ABC
 int tinno_ts_get_fw_version()
{
	char readbyte[2] = {0xA6};
	char fw_version;
	int err;
	char vendor_id;
	readbyte[0] = 0xA8;
	TPD_DEBUG("ft5316_i2c_client addr ==== %X \n", ft5316_i2c_client->addr);
	 i2c_master_send(ft5316_i2c_client,&readbyte[0],1);
	 err = i2c_master_recv(ft5316_i2c_client, &vendor_id, 1);
	 TPD_DEBUG("++++++++++++Check IC return %d\n",err);
	 if(err<0)   // the driver do not match the IC
		return err;   
	 vendor_version = vendor_id;
	  TPD_DEBUG("Magnum vendor_id=0x%X \n", vendor_id);   
	 if (vendor_id == 0 || vendor_id == 0xa8 ){
	    TPD_DEBUG("i2c_read vendor version failed.\n");
	     return 0;
	  }
	  
	// Read FW Version.
	//	fw_version = i2c_smbus_read_byte_data(ft5316_i2c_client, 0xA6);
	readbyte[0] = 0xA6;
	i2c_master_send(ft5316_i2c_client,&readbyte[0],1);
	err = i2c_master_recv(ft5316_i2c_client, &fw_version, 1);
	if(err<0)   // the driver do not match the IC
		return err;   
	TPD_DEBUG("fw_version=0x%X \n", fw_version);
	panel_version = fw_version;
	if (fw_version == 0 ||fw_version == 0xa6 ){
		TPD_DEBUG("i2c_read panel version failed.\n");
	    return 0;
	}

	TPD_DEBUG("tpd_local_init boot mode = %d \n", tp_boot_mode);    
	return 1;
}


// get the report frequent 
int tinno_ts_set_period_active(void)
{
    char readbyte[2] = {0x88};	
	char rdata;
	int ret = 0;
	ret = i2c_smbus_write_byte_data(ft5316_i2c_client, 0x88, 6);/*6X10HZ*/
	readbyte[0] = 0x88;
	i2c_master_send(ft5316_i2c_client,&readbyte[0],1);
	i2c_master_recv(ft5316_i2c_client, &rdata, 1);
	if (rdata < 0) {
		TPD_DEBUG("get period active failed");
		goto err;
	}
	TPD_DEBUG("active period is %d \n", rdata);

	if (ret < 0) {
		TPD_DEBUG("set period active failed");
		goto err;
	}
	return 0;
err:
	return ret;
}

//edit by Magnum 2012-12-17  check ic work state 
//return value :  <0  :  // I2c commiucatie  fail
// 			   = 0 :  // IC has been upgraded fail.
//			   > 0 :  // IC work well.
 int tinno_check_focaltech(void)
{
	char readbyte[2] = {0xA3};
   	char fw_version;
    	int err;

	// Read FW Version.
//	fw_version = i2c_smbus_read_byte_data(ft5316_i2c_client, 0xA6);
	readbyte[0] = 0xA3;
	i2c_master_send(ft5316_i2c_client,&readbyte[0],1);
	err = i2c_master_recv(ft5316_i2c_client, &fw_version, 1);
	TPD_DEBUG("fw_version=0x%X \n", fw_version);
	if(err<0)   // I2c commiucatie  fail
		return err;
	if (fw_version == 0x0a){
		return 1;
	}
	TPD_DEBUG("i2c_smbus_write_byte_data failed.\n");
	 return 0;
	
}

