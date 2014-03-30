
#include "tpd_custom_ft5316_5p.h"
static struct tinno_ts_data *g_pts = NULL ;
static struct task_struct * focaltech_update_thread;

extern ssize_t tp_write_m_byte(u8 cmd, u8 *writeData,U16 len);

//edit by Magnum 2012-2-2
static int  fts_ctpm_auto_clb(void)
{
	uint8_t  command = 0xFC;
	uint8_t  calib_buf=0x00;
	u8 uc_temp;
	u8 i ;   
	TPD_DEBUG("[FTS] start auto CLB.\n");
	msleep(200);
	i2c_smbus_write_byte_data(ft5316_i2c_client, 0x00, 0x40);

	msleep(100);   //make sure already enter factory mode
	i2c_smbus_write_byte_data(ft5316_i2c_client, 0x02, 0x04);

	msleep(300);
	for(i=0;i<100;i++)
	{
		command = 0x00;
		i2c_master_send(ft5316_i2c_client,&command,1);
		i2c_master_recv(ft5316_i2c_client, &calib_buf, 1);
		if ( ((calib_buf&0x70)>>4) == 0x0)  //return to normal mode, calibration finish
		{
		    break;
		}
		msleep(200);
		TPD_DEBUG("[FTS] waiting calibration %d\n",i);
	}
	TPD_DEBUG("[FTS] calibration OK.\n");
	msleep(300);
	i2c_smbus_write_byte_data(ft5316_i2c_client, 0x00, 0x40);
	msleep(100);   //make sure already enter factory mode
	i2c_smbus_write_byte_data(ft5316_i2c_client, 0x02, 0x05);
	msleep(300);
	i2c_smbus_write_byte_data(ft5316_i2c_client, 0x00, 0x00);
	msleep(300);
	TPD_DEBUG("[FTS] store CLB result OK.\n");
	return 0;
}

#ifdef CONFIG_TOUCHSCREEN_FT5X05_SUPPORT_ISP
static inline int _lock(atomic_t *excl)
{
	if (atomic_inc_return(excl) == 1) {
		return 0;
	} else {
		atomic_dec(excl);
		return -1;
	}
}

static inline void _unlock(atomic_t *excl)
{
	atomic_dec(excl);
}

static ssize_t fts_isp_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{	
	//ret = copy_to_user(buf,&acc, sizeof(acc));
	TPD_DEBUG("");
	return -EIO;
}

static ssize_t fts_isp_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	int rc = 0;
	struct tinno_ts_data *ts = file->private_data;
	const char __user *start = buf;
	TPD_DEBUG("count = %d \r\n", count);
	
	if ( count > ISP_FLASH_SIZE ){
		TPD_DEBUG("isp code is too long.");
		return -EDOM;
	}

	if ( copy_from_user(ts->isp_pBuffer, start, count) ){
		TPD_DEBUG("i2c_transfer failed(%d)", rc);
		return -EACCES;
	}

//	rc = i2c_master_send(ts->client, ts->isp_pBuffer, count);
	rc = tp_write_m_byte(0,ts->isp_pBuffer,count);
	if (rc == 0) {
		TPD_DEBUG("i2c_transfer failed(%d)", rc);
	} 

	return rc;
}

static int fts_isp_open(struct inode *inode, struct file *file)
{
	struct tinno_ts_data *ts = file->private_data;
    
	TPD_DEBUG("try to open isp.");

/*	
	if ( atomic_read( &g_pts->ts_sleepState ) ){
		TPD_DEBUG("TP is in sleep state, please try again latter.");
		return -EAGAIN;
	}
*/
	if (_lock(&g_pts->isp_opened)){
		TPD_DEBUG("isp is already opened.");
		return -EBUSY;
	}

	mutex_lock(&tp_mutex);
	if (tpd_status == 0)
	{    
	    tinno_tp_power_on();
	}	
	file->private_data = g_pts;

	g_pts->isp_pBuffer = (uint8_t *)kmalloc(ISP_FLASH_SIZE, GFP_KERNEL);
	if ( NULL == g_pts->isp_pBuffer ){
		_unlock ( &g_pts->isp_opened );
		TPD_DEBUG("no memory for isp.");
		return -ENOMEM;
	}
	tpd_status = 0;
    mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
//Ivan 6573    MT6516_IRQMask(MT6516_TOUCH_IRQ_LINE);
	wake_lock(&g_pts->wake_lock);

	TPD_DEBUG("isp open success.");
	return 0;
}

static int fts_isp_close(struct inode *inode, struct file *file)
{
	struct tinno_ts_data *ts = file->private_data;
	
	TPD_DEBUG("try to close isp.");
/*	
	if ( !atomic_read( &g_pts->isp_opened ) ){
		TPD_DEBUG("no opened isp.");
		return -ENODEV;
	}
*/

	kfree(ts->isp_pBuffer);
	ts->isp_pBuffer = NULL;
/*	
	if ( atomic_read( &ts->ts_opened ) ){//don't dec the counter
		if (ts->use_irq){
			enable_irq(ts->client->irq);
		}
		else{
			hrtimer_start(&ts->timer, ktime_set(1, 0), HRTIMER_MODE_REL);
		}
		TPD_DEBUG("open the opened touch device.");
	}
*/	
		mutex_unlock(&tp_mutex);
		tpd_status = 1;
		//Ivan 6573	MT6516_IRQUnmask(MT6516_TOUCH_IRQ_LINE);    
		mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);  
		file->private_data = NULL;
		_unlock ( &ts->isp_opened );
		wake_unlock(&ts->wake_lock);
		TPD_DEBUG("close isp success!");
		return 0;
}

static int fts_switch_to_update(struct i2c_client *client)
{
	int ret = 0;
	uint8_t  command = 0xFC;
	uint8_t arrCommand[] = {0x55, 0xaa};
	
	TPD_DEBUG("");
    
//	mutex_lock(&tp_mutex);
	
	/*write 0xaa to register 0xfc*/
	ret = i2c_smbus_write_byte_data(client, command, 0xAA);
	if (ret < 0) {
		TPD_DEBUG("write 0xaa to register 0xfc failed\n");
		goto err;
	}
	msleep(50);
	/*write 0x55 to register 0xfc*/
	ret = i2c_smbus_write_byte_data(client, command, 0x55);
	if (ret < 0) {
		TPD_DEBUG("write 0x55 to register 0xfc failed\n");
		goto err;
	}
	msleep(40);
	ret = i2c_master_send(client, arrCommand, sizeof(arrCommand));
	if (ret < sizeof(arrCommand)) {
		TPD_DEBUG("i2c_transfer failed 5(%d)\n", ret);
	} 
	ret = 0;
	isUpgrade = 1;
err:
//	mutex_unlock(&tp_mutex);
	return ret;
}


static int fts_mode_switch(struct tinno_ts_data *ts, int iMode)
{
	int ret = 0;
	
	TPD_DEBUG("iMode=%d\n", iMode);
	
	if ( FTS_MODE_OPRATE == iMode ){
	}
	else if (FTS_MODE_UPDATE == iMode){
		ret = fts_switch_to_update(ts->client);
	}
	else if (FTS_MODE_SYSTEM == iMode){
	}
	else{
		TPD_DEBUG("unsupport mode %d\n", iMode);
	}
	return ret;
}

//edit by Magnum 2012-7-18
//static int fts_isp_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
static int fts_isp_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	struct tinno_ts_data *ts = file->private_data;
	int flag;
	int rc = 0;
	uint8_t  command = 0xFC;
	uint8_t  checksum,calib_buf;
	
	if ( !atomic_read( &g_pts->isp_opened ) ){
		TPD_DEBUG("no opened isp.\n");
		return -ENODEV;
	}
	
	/* check cmd */
	if(_IOC_TYPE(cmd) != TOUCH_IO_MAGIC)	
	{
		TPD_DEBUG("cmd magic type error\n");
		return -EINVAL;
	}
	if(_IOC_NR(cmd) > FT5X05_IOC_MAXNR)
	{
		TPD_DEBUG("cmd number error\n");
		return -EINVAL;
	}

	if(_IOC_DIR(cmd) & _IOC_READ)
		rc = !access_ok(VERIFY_WRITE,(void __user*)arg, _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_WRITE)
		rc = !access_ok(VERIFY_READ, (void __user*)arg, _IOC_SIZE(cmd));
	if(rc)
	{
		TPD_DEBUG("cmd access_ok error\n");
		return -EINVAL;
	}

	switch (cmd) {
	case FT5X05_IOCTL_SWITCH_TO:
		TPD_DEBUG("Try to switch to update mode!(%lu)\n", arg);
		rc = fts_mode_switch(ts, (int)arg);
		if(rc)
		{
			TPD_DEBUG("switch to update mode error\n");
			return -EIO;
		}
		break;
	case FT5X05_IOCTL_WRITE_PROTECT:
		TPD_DEBUG("Try to set write protect mode!(%lu)\n", arg);
#if defined(FT5X06_FIRMWAIR_VERSION_D)
		rc = -EINVAL;
		break;
#endif
		if ( 0 == arg ){/*write enable*/
			rc = i2c_smbus_write_byte(ts->client, 0x06);
		}
		else{/*write disable*/
			rc = i2c_smbus_write_byte(ts->client, 0x04);
		}
		if (rc < 0) {
			TPD_DEBUG("set period active failed\n");
		}
		break;
	case FT5X05_IOCTL_ERASE:
		TPD_DEBUG("Try to erase flash!\n");
#if defined(FT5X06_FIRMWAIR_VERSION_C)
		rc = i2c_smbus_write_byte(ts->client, 0x60);
#elif defined(FT5X06_FIRMWAIR_VERSION_D)
		rc = i2c_smbus_write_byte(ts->client, 0x61);
#endif
		if (rc < 0) {
			TPD_DEBUG("erase failed\n");
			break;
		}
		msleep(1500);
		break;
	case FT5X05_IOCTL_GET_STATUS:
		TPD_DEBUG("Try to get status!\n");
//		flag = i2c_smbus_read_byte_data(ts->client, 0x05);
		command = 0x05;
		i2c_master_send(ts->client,&command,1);
		i2c_master_recv(ts->client, &flag, 1);
		
		if (flag < 0) {
			TPD_DEBUG("read check status failed\n");
		}
		TPD_DEBUG("status=%d!", flag);
		if(copy_to_user(argp,&flag,sizeof(int))!=0)
		{
			TPD_DEBUG(KERN_INFO "copy_to_user error\n");
			rc = -EFAULT;
		}
		break;
	case FT5X05_IOCTL_GET_CHECKSUM:
		TPD_DEBUG("Try to get checksum!\n");

//		flag = i2c_smbus_read_byte_data(ts->client, 0xCC);
		command = 0xCC;
		i2c_master_send(ts->client,&command,1);
		i2c_master_recv(ts->client, &checksum, 1);
		
//		if (checksum < 0) {
//			TPD_DEBUG("read checksum failed\n");
//		}
		flag = checksum;
		TPD_DEBUG("checksum=%x!\n", checksum);
		if(copy_to_user(argp,&flag,sizeof(int))!=0)
		{
			TPD_DEBUG(KERN_INFO "copy_to_user error\n");
			rc = -EFAULT;
		}
		break;
	case FT5X05_IOCTL_RESET:
		TPD_DEBUG("Try to reset TP!\n");
		rc = i2c_smbus_write_byte(ts->client, 0x07);
		if (rc < 0) {
			TPD_DEBUG("reset failed\n");
		}
	        fts_ctpm_auto_clb();
		isUpgrade = 0;
		tinno_ts_get_fw_version();
		ft5316_tpd_reset();
		break;
	case FT5X05_IOCTL_GET_TPID:
		{
			uint8_t arrCommand[] = {0x90, 0x00, 0x00, 0x00};

			TPD_DEBUG("Try to get TPID!\n");
			rc = i2c_master_send(ts->client, arrCommand, sizeof(arrCommand));
			if (rc < sizeof(arrCommand)) {
				TPD_DEBUG("i2c_master_send failed(%d)\n", rc);
			} 

			rc = i2c_master_recv(ts->client, arrCommand, 2);
			if (rc < 2) {
				TPD_DEBUG("i2c_master_recv failed(%d)\n", rc);
			} 

			flag = (( int )arrCommand[0] << 8) | (( int )arrCommand[1]);
			
			TPD_DEBUG("TPID=0x%X!\n", flag);
			if(copy_to_user(argp,&flag,sizeof(int))!=0)
			{
				TPD_DEBUG(KERN_INFO "copy_to_user error\n");
				rc = -EFAULT;
			}
			break;
		}
	case FT5X05_IOCTL_GET_VENDORID:
            {
               char readbyte[2] = {0xA8};
               char vendor_id;
               int err;
           
                // Read FW Version.
                //	fw_version = i2c_smbus_read_byte_data(i2c_client, 0xA6);
                readbyte[0] = 0xA8;
                i2c_master_send(ft5316_i2c_client,&readbyte[0],1);
                err = i2c_master_recv(ft5316_i2c_client, &vendor_id, 1);

                if (vendor_id < 0 || err < 0){
                	TPD_DEBUG("i2c_smbus_write_byte_data failed.\n");
                    return 0;
                }

                TPD_DEBUG("Magnum vendor_id=0x%X \n", vendor_id);

                if(copy_to_user(argp,&vendor_id,sizeof(char))!=0)
                {
                    TPD_DEBUG(KERN_INFO "copy_to_user error\n");
                    rc = -EFAULT;
                }
                break;
            }
	default:
		TPD_DEBUG("invalid command %d\n", _IOC_NR(cmd));
		rc = -EINVAL;
		break;
	}

	return rc;
}


static const struct file_operations fts_isp_fops = {
	.owner = THIS_MODULE,
	.read = fts_isp_read,
	.write = fts_isp_write,
	.open = fts_isp_open,
	.release = fts_isp_close,
	.unlocked_ioctl = fts_isp_ioctl,
};

 struct miscdevice fts_isp_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fts_isp",
	.fops = &fts_isp_fops,
};


 void magnum_fts_isp_register(struct i2c_client *client)
  {
  	TPD_DEBUG("////////////////////magnum_fts_isp_register\n");
	struct tinno_ts_data *ts;
	int err,ret;
	
	ts = kzalloc(sizeof(*ts), GFP_KERNEL);
	if (ts == NULL) {
		ret = -ENOMEM;
		goto err_detect_failed;
	}

	wake_lock_init(&ts->wake_lock, WAKE_LOCK_SUSPEND, "fts_tp_isp");
	ts->client = client;
	err = misc_register(&fts_isp_device);
	if (err) {
		TPD_DEBUG(KERN_ERR "fts_isp_device device register failed\n");
		goto exit_misc_device_register_failed;
	}else{
		g_pts = ts;
	}
	return;

err_detect_failed:
	kfree(ts);
	return;	
	
exit_misc_device_register_failed:
	wake_lock_destroy(&ts->wake_lock);
  }

  void fts_isp_deregister(struct i2c_client *client)
  {
	  misc_deregister(&fts_isp_device);
	  wake_lock_destroy(&g_pts->wake_lock);
	  g_pts = NULL;
  }
  
#endif

#ifdef TP_AUTO_UPGRADE
#define    FTS_PACKET_LENGTH       2// 128
static int factory_panel_id = 0;

static int focal_count = 0;
static int match_focal_index = -1;
static struct Focaltech_firmware focal_firmware[5];
static char BYD_FW[] =
{
	#include "ft5316_5p/ctp_firmware/byd_app_d.h"
};

/*static char NANBO_FW[]=
{
	#include "ft5316_5p/ctp_firmware/nanbo_app_d.h"
};*/
//const unsigned char * g_touch_bin;// = BYD_FW;

static void add_focaltech(const char * temp_focal, int len)
{
	if(focal_count == 5){
		TPD_DEBUG("Magnum there are have being 5 focaltech firmware,cat not add \n");	
		return;	
	}
	TPD_DEBUG("focal_count == %d\n",focal_count);
//	focal_firmware[focal_count].ctp_buffer = (char *)malloc(sizeof(char)*len+1);
	if(len < 1){
		TPD_DEBUG("focal_firmware length must bigger than == %d!!!!!!!!!!!!!!!\n",len);
		return; 
	}	
	focal_firmware[focal_count].ctp_buffer = (uint8_t *)kmalloc(len, GFP_KERNEL);
	memcpy(focal_firmware[focal_count].ctp_buffer,temp_focal,len);
	focal_firmware[focal_count].length = len;
	TPD_DEBUG("length == %d\n",len);
	TPD_DEBUG("byd ver == 0x%x\n",focal_firmware[focal_count].ctp_buffer[len-2]);
	focal_count++;
}

//match the firmware by vendor_version
static void  get_firmware(char ver)
{	
	TPD_DEBUG("Magnum object firmare version == 0x%x\n",ver);
	if(focal_count == 0)
		return;
	int i = 0;	
	int temp_len = 0;
	for(i;i<focal_count;i++){
		temp_len = focal_firmware[i].length;
		//if( get_fts_ctpm_vendor(focal_firmware[i].ctp_buffer,temp_len) == ver)
		if(focal_firmware[i].ctp_buffer[temp_len-1] == ver)
		{
			TPD_DEBUG("Find the match firmware index ==  %d\n",i);
			match_focal_index = i;
			return ;	
		}
		else
			TPD_DEBUG("Find next one \n");
	}
	TPD_DEBUG("Find the match firmware FAIL FAIL........\n");
	return ;
}

static char get_fts_ctpm_ver(char* CTPM_FW,int length)
{
	unsigned int ui_sz;
	ui_sz = length;//sizeof(CTPM_FW);
	printk("CTPM_FW length == 0x%x\n",ui_sz);
	if (ui_sz > 2)
	{
		return CTPM_FW[ui_sz - 2];
	}
	else
	{
		//TBD, error handling?
		return 0xff; //default value
	}
}

static  char get_fts_ctpm_vendor(char* CTPM_FW,int length)
{
	unsigned int ui_sz;
	ui_sz = length;//sizeof(CTPM_FW);
	printk("CTPM_FW length == 0x%x\n",ui_sz);
	if (ui_sz > 2)
	{
		return CTPM_FW[ui_sz - 1];
	}
	else
	{
		//TBD, error handling?
		return 0xff; //default value
	}
}

static void add_all_firmware()
{
	int len = sizeof(BYD_FW);
	add_focaltech(BYD_FW,len);
	
}

static ssize_t mt6573_dma_write_m_byte(unsigned char*returnData_va, u32 returnData_pa, int  len)
{
	int     ret=0;
	ft5316_i2c_client->addr = (ft5316_i2c_client->addr & I2C_MASK_FLAG) | I2C_DMA_FLAG;
	if (len > 0){
		ret = i2c_master_send(ft5316_i2c_client, returnData_pa, len);
		if (ret < 0) {
			TPD_DEBUG(KERN_ERR"xxxxfocal write data error!! xxxx\n");
			return 0;
		}
	}
	//	ft5316_i2c_client->addr = ft5316_i2c_client->addr & I2C_MASK_FLAG;
	//TPD_DEBUG("xxxxwrite transfer ok!!!!!!xxxx\n");
	return 1;
}

static u8 cmd_write(u8 btcmd,u8 btPara1,u8 btPara2,u8 btPara3,u8 num)
{
	u8 write_cmd[4] = {0};
//	i2c_client->addr = i2c_client->addr & I2C_MASK_FLAG;
	write_cmd[0] = btcmd;
	write_cmd[1] = btPara1;
	write_cmd[2] = btPara2;
	write_cmd[3] = btPara3;
//	i2c_client->addr = i2c_client->addr & I2C_MASK_FLAG;
	return i2c_master_send(ft5316_i2c_client, write_cmd, num);
}

static int  read_factory_id_from_boot()
{
	unsigned char reg_val[3] = {0};
	int i = 0;

	int  packet_number;
	int  j;
	int  temp;
	int  length;
	unsigned char  packet_buf[FTS_PACKET_LENGTH + 6];
	unsigned char  auc_i2c_write_buf[10];
	unsigned char bt_ecc;
	int      i_ret;
	int rc;  int ret;int err;
	TPD_DEBUG("=====================fts_ctpm_fw_upgrade======================\n");
	/*********Step 1:Reset  CTPM    timing here is important !!!!!!!*****/  
	uint8_t  command = 0xFC;
	uint8_t arrCommand[] = {0x55, 0xaa};
	
	TPD_DEBUG("");
	
	/*write 0xaa to register 0xfc*/
	ret = i2c_smbus_write_byte_data(ft5316_i2c_client, command, 0xAA);
	if (ret < 0) {
		TPD_DEBUG("write 0xaa to register 0xfc failed\n");
		//goto err;
	}
	msleep(50);
	/*write 0x55 to register 0xfc*/
	ret = i2c_smbus_write_byte_data(ft5316_i2c_client, command, 0x55);
	if (ret < 0) {
		TPD_DEBUG("write 0x55 to register 0xfc failed\n");
		//goto err;
	}
	msleep(40);   
	ret = i2c_master_send(ft5316_i2c_client, arrCommand, sizeof(arrCommand));
	if (ret < sizeof(arrCommand)) {
		TPD_DEBUG("i2c_transfer failed 5(%d)\n", ret);
	} 
	
	TPD_DEBUG("[FT520X] Step 2: Enter upgrade mode\n");
	
	/*********Step 3:check READ-ID***********************/    
	for( i = 0; i < 5; i++ ) {
			//i2c_client->addr = i2c_client->addr & I2C_MASK_FLAG;
			uint8_t arrCommand[] = {0x90, 0x00, 0x00, 0x00};

			TPD_DEBUG("Try to get TPID!\n");
			rc = i2c_master_send(ft5316_i2c_client, arrCommand, sizeof(arrCommand));
			if (rc < sizeof(arrCommand)) {
				TPD_DEBUG("i2c_master_send failed(%d)\n", rc);
			} 

			rc = i2c_master_recv(ft5316_i2c_client, arrCommand, 2);
			if (rc < 2) {
				TPD_DEBUG("i2c_master_recv failed(%d)\n", rc);
			} 

		//	flag = (( int )arrCommand[0] << 8) | (( int )arrCommand[1]);
			TPD_DEBUG("[FT520X] Step 3: CTPM ID,ID1 = 0x%x,ID2 = 0x%x\n",arrCommand[0],arrCommand[1]);
			//byte_read(reg_val,2);
			//0x7903 :ft5x06,ft5306 .  0x7907: ft5316
			if (arrCommand[0] == 0x79 && arrCommand[1] == 0x7)
			{
				TPD_DEBUG("[FT520X] Step 3: CTPM ID,ID1 = 0x%x,ID2 = 0x%x\n",reg_val[0],reg_val[1]);
				break;
			}
			else
			{
				TPD_DEBUG("[FT520X] Step 3: check Read ID Error!!\n");
				//return 2;
				//i_is_new_protocol = 1;
			}
	}
	if ( i == 5){
//		perror("\n CHECK-ID error!");
		TPD_DEBUG("CHECK-ID error!\n");
		return 2;
	}
	uint8_t factoryCommand[6] = {0x03, 0x00,0x78,0x00};
	TPD_DEBUG("Try to get FACTORY ID!\n");
	rc = i2c_master_send(ft5316_i2c_client, factoryCommand, 4);
	if (rc < sizeof(arrCommand)) {
		TPD_DEBUG("i2c_master_send failed(%d)\n", rc);
	} 

	rc = i2c_master_recv(ft5316_i2c_client, factoryCommand, 6);
	if (rc < 2) {
		TPD_DEBUG("i2c_master_recv failed(%d)\n", rc);
	} 
	 TPD_DEBUG("[FTS] old setting: uc_i2c_addr = 0x%x, uc_io_voltage = %d, uc_panel_factory_id = 0x%x\n",
	 			factoryCommand[0],  factoryCommand[2], factoryCommand[4]);
	 factory_panel_id = factoryCommand[4];
	 cmd_write(0x07,0x00,0x00,0x00,1);
	 msleep(200);
	 return  factory_panel_id;

			
}

// get the vendor id , then get the match firmware for tp_auto_upgrade
//  return value:    1      do upgrade.
//			      -1,   no match firmware
//			      -2,  read_factory_id_from ctp ic bootloader error.
//			     -3 ,   panel_version is newest. do not need upgrade.
static int  get_match_firmware()
{
	add_all_firmware();
	if(vendor_version == 0)
	{
		read_factory_id_from_boot();
		if(factory_panel_id == 0)
		{	
			TPD_DEBUG("read_factory_id_from_boot ERR !!\n");
			return -2;
		}
		get_firmware(factory_panel_id);	
		return 1;
	}
	else
	{
		get_firmware(vendor_version);
		char object_panel = get_fts_ctpm_ver(focal_firmware[match_focal_index].ctp_buffer,focal_firmware[match_focal_index].length);
		TPD_DEBUG("read object panel version  == 0x%x !!\n",object_panel);
		if(panel_version < object_panel){
			TPD_DEBUG("read object panel version  == 0x%x !!\n",object_panel);
			return 1;
		}
		else{
			TPD_DEBUG("++++++++++++++++++++read object panel version  == 0x%x !!\n",object_panel);
			return -3;
		}	
	}
}

//return value :     0 : sucess    ,    else :  fail.
static int  fts_ctpm_fw_upgrade(unsigned char* pbt_buf, int dw_lenth)
{
	unsigned char reg_val[3] = {0};
	int i = 0;

	int  packet_number;
	int  j;
	int  temp;
	int  length;
	unsigned char  packet_buf[FTS_PACKET_LENGTH + 6];
	unsigned char  auc_i2c_write_buf[10];
	unsigned char bt_ecc;
	int      i_ret;
	int rc;  int ret;int err;
	TPD_DEBUG("=====================fts_ctpm_fw_upgrade======================\n");
	/*********Step 1:Reset  CTPM    timing here is important !!!!!!!*****/  
	uint8_t  command = 0xFC;
	uint8_t arrCommand[] = {0x55, 0xaa};
	
	TPD_DEBUG("");
	
	/*write 0xaa to register 0xfc*/
	#if 0
	ret = i2c_smbus_write_byte_data(ft5316_i2c_client, command, 0xAA);
	if (ret < 0) {
		TPD_DEBUG("write 0xaa to register 0xfc failed\n");
		//goto err;
	}
	msleep(50);
	/*write 0x55 to register 0xfc*/
	ret = i2c_smbus_write_byte_data(ft5316_i2c_client, command, 0x55);
	if (ret < 0) {
		TPD_DEBUG("write 0x55 to register 0xfc failed\n");
		//goto err;
	}
	msleep(40);   
	#endif
	ft5316_tpd_reset();
	isUpgrade = 1;
	ret = i2c_master_send(ft5316_i2c_client, arrCommand, sizeof(arrCommand));
	if (ret < sizeof(arrCommand)) {
		TPD_DEBUG("i2c_transfer failed 5(%d)\n", ret);
	} 
	
	TPD_DEBUG("[FT520X] Step 2: Enter upgrade mode\n");
	
	/*********Step 3:check READ-ID***********************/    
	for( i = 0; i < 5; i++ ) {
			//i2c_client->addr = i2c_client->addr & I2C_MASK_FLAG;
			uint8_t arrCommand[] = {0x90, 0x00, 0x00, 0x00};

			TPD_DEBUG("Try to get TPID!\n");
			rc = i2c_master_send(ft5316_i2c_client, arrCommand, sizeof(arrCommand));
			if (rc < sizeof(arrCommand)) {
				TPD_DEBUG("i2c_master_send failed(%d)\n", rc);
			} 

			rc = i2c_master_recv(ft5316_i2c_client, arrCommand, 2);
			if (rc < 2) {
				TPD_DEBUG("i2c_master_recv failed(%d)\n", rc);
			} 

		//	flag = (( int )arrCommand[0] << 8) | (( int )arrCommand[1]);
			TPD_DEBUG("[FT520X] Step 3: CTPM ID,ID1 = 0x%x,ID2 = 0x%x\n",arrCommand[0],arrCommand[1]);
			//byte_read(reg_val,2);
			//0x7903 :ft5x06,ft5306 .  0x7907: ft5316
			if (arrCommand[0] == 0x79 && arrCommand[1] == 0x7)
			{
				TPD_DEBUG("[FT520X] Step 3: CTPM ID,ID1 = 0x%x,ID2 = 0x%x\n",reg_val[0],reg_val[1]);
				break;
			}
			else
			{
				TPD_DEBUG("[FT520X] Step 3: check Read ID Error!!\n");
				//return 2;
				//i_is_new_protocol = 1;
			}
	}
	if ( i == 5){
//		perror("\n CHECK-ID error!");
		TPD_DEBUG("CHECK-ID error!\n");
		return 2;
	}

	/*********Step 4:erase app*******************************/
	cmd_write(0x61,0x00,0x00,0x00,1);

	msleep(1500);
	//cmd_write(0x63, 0x00, 0x00, 0x00, 1);
	//msleep(100);
	TPD_DEBUG("[FT520X] Step 4: erase. \n");

	/*********Step 5:write firmware(FW) to ctpm flash*********/
	bt_ecc = 0;
	TPD_DEBUG("[FT520X] Step 5: start upgrade. \n");
	dw_lenth = dw_lenth - 8;
	TPD_DEBUG("####Packet length = %d\n", dw_lenth);
	packet_number = (dw_lenth) / FTS_PACKET_LENGTH;
	length = FTS_PACKET_LENGTH;
	TPD_DEBUG("Number of packet to write = %d; Packet len = %d\n",packet_number,length);
	packet_buf[0] = 0xbf;
	packet_buf[1] = 0x00;
	for (j=0;j<packet_number;j++)
	{
		temp = j * length;
		packet_buf[2] = (u8)(temp>>8);
		packet_buf[3] = (u8)temp;
		
		packet_buf[4] = (u8)(length>>8);
		packet_buf[5] = (u8)length;

		for (i=0;i<FTS_PACKET_LENGTH;i++)
		{
			packet_buf[6+i] = pbt_buf[j*FTS_PACKET_LENGTH + i]; 
			bt_ecc ^= packet_buf[6+i];
		}
	//	TPD_DEBUG("CTP write number == %d\n",j);
		tp_write_m_byte(0,packet_buf,length+6);
	//	mt6573_dma_write_m_byte(tpDMABuf_va, tpDMABuf_pa, FTS_PACKET_LENGTH + 6);
		udelay(100);
	/*	if ((j * FTS_PACKET_LENGTH % 1024) == 0)
		{
			TPD_DEBUG("[FT520X] upgrade the 0x%x th byte.\n", ((unsigned int)j) * FTS_PACKET_LENGTH);
		}
		*/
	}

	if ((dw_lenth) % FTS_PACKET_LENGTH > 0)
	{
		temp = packet_number * FTS_PACKET_LENGTH;
		packet_buf[2] = (u8)(temp>>8);
		packet_buf[3] = (u8)temp;

		temp = (dw_lenth) % FTS_PACKET_LENGTH;
		packet_buf[4] = (u8)(temp>>8);
		packet_buf[5] = (u8)temp;

		for (i=0;i<temp;i++)
		{
			packet_buf[6+i] = pbt_buf[ packet_number*FTS_PACKET_LENGTH + i]; 
			bt_ecc ^= packet_buf[6+i];
		}

	//	mt6573_dma_write_m_byte(tpDMABuf_va, tpDMABuf_pa,temp+6);    
	//		i2c_client->addr = i2c_client->addr & I2C_MASK_FLAG;
		tp_write_m_byte(0, packet_buf, temp+6);

		udelay(100);
	}

	//send the last six byte
	for (i = 0; i<6; i++)
	{
		packet_buf[0] = 0xbf;
		packet_buf[1] = 0x00;
		temp = 0x6ffa + i;
		packet_buf[2] = (u8)(temp>>8);
		packet_buf[3] = (u8)temp;
		temp =1;
		packet_buf[4] = (u8)(temp>>8);
		packet_buf[5] = (u8)temp;
		packet_buf[6] = pbt_buf[ dw_lenth + i]; 
		bt_ecc ^= packet_buf[6];

		i2c_master_send(ft5316_i2c_client, packet_buf, 7);    

		udelay(100);
	}

	/*********Step 6: read out checksum***********************/
	/*send the operation head*/
//	reg_val[0] = 0x01;
	cmd_write(0xcc,0x00,0x00,0x00,1);
//	i2c_client->addr = i2c_client->addr & I2C_MASK_FLAG;
	i2c_master_recv(ft5316_i2c_client, &reg_val, 1);
	TPD_DEBUG("[FT520X] Step 6:  ecc read 0x%x, new firmware 0x%x. \n", reg_val[0], bt_ecc);
	if(reg_val[0] != bt_ecc)
	{
		TPD_DEBUG("5 check sum error!!\n");
		return 5;
	}

	/*********Step 7: reset the new FW***********************/
	cmd_write(0x07,0x00,0x00,0x00,1);
	TPD_DEBUG("[FT520X] Step 7: reset the new FW. \n");
	
	/*********Step 8: calibration TP ***********************/
	msleep(300);          //延时100ms
	return 0;
}

static int fts_ctpm_fw_upgrade_with_i_file(void)
{
	char*     pbt_buf = NULL;
	int i_ret;

	TPD_DEBUG("=========FW upgrade========================\n");
	if(match_focal_index < 0){
		TPD_DEBUG("No Match firmware to be upgrade ......\n");
		return  -1;
	}
	//=========FW upgrade========================*/
	pbt_buf = focal_firmware[match_focal_index].ctp_buffer;//CTPM_FW;
	/*call the upgrade function*/
	i_ret =  fts_ctpm_fw_upgrade(pbt_buf,focal_firmware[match_focal_index].length);
	if (i_ret != 0)
	{
      		 TPD_DEBUG("[FTS] upgrade failed i_ret = %d.\n", i_ret);
 	 }
 	else
   	{
       		fts_ctpm_auto_clb();  //start auto CLB
       		tinno_ts_get_fw_version();
		if(panel_version>0){
				TPD_DEBUG("[FTS] upgrade successfully,after upgrade : bufff= 0x%X \n", panel_version);
		}
		else
			TPD_DEBUG(KERN_ERR"XXXXXXXXXXtp upgrade error!!\nXXXXXXXXXXX");				
  	 }
	isUpgrade = 0;
   return i_ret;
}

static  int update_firmware_thread(void *priv)
{
	TPD_DEBUG("[Focaltech] enter update_firmware_thread\n");
	fts_ctpm_fw_upgrade_with_i_file();
	kthread_should_stop();
	return NULL;
}

int focaltech_auto_upgrade(void)
{
	int err;
	if(get_match_firmware() == 1)//fts_ctpm_get_upg_ver() != panel_version)
	{
		focaltech_update_thread = kthread_run(update_firmware_thread, 0, TPD_DEVICE);
		if (IS_ERR(focaltech_update_thread)) {
		        err = PTR_ERR(focaltech_update_thread);
		        TPD_DEBUG(TPD_DEVICE " failed to create update_firmware_thread thread: %d\n", err);
		    }
	}
	else 
		TPD_DEBUG("Do not excute auto upgrade ..\n");
	return err;
}
#endif

