/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#include "tpd_custom_ft5316_5p.h"
#ifdef  TP_AUTO_UPGRADE   
extern int focaltech_auto_upgrade(void);
#endif

extern struct tpd_device *tpd;
struct mutex tp_mutex;
static u8 tpd_down_state=0;
static int down_x=0;
static int down_y=0;
int isUpgrade = 0; // 1:show that TP is upgrading ...edit by Magnum  2012-7-19 
char panel_version = 0;
char vendor_version= 0 ;
int tpd_status = 0; // 0: tp suspend . 1: tp working 
struct i2c_client * ft5316_i2c_client = NULL;
extern void tinno_tp_power_on(void);
extern  void tinno_tp_power_off(void);
extern  void ft5316_tpd_reset(void);
extern  void fts_isp_deregister(struct i2c_client *client);
extern  void magnum_fts_isp_register(struct i2c_client *client);
static struct task_struct *thread = NULL;

static int tpd_flag=0;
static int inTouchKey = 0;
static int tpd_downMode = 0; // 1:touchmode, 2:virtual key in touch mode, 0 : default and up event
static int tpd_init_skip = 0;
extern char phonestate;

//edit by Magnum 2012-8-31 ctp up Questions
static int x_history[TINNO_TOUCH_TRACK_IDS+1];
static int y_history[TINNO_TOUCH_TRACK_IDS+1];
static int tpd_dcount = 0;

static const struct i2c_device_id ft5316_i2c_id[] = {{"ft5316",0},{}};
static struct i2c_board_info __initdata ft5316_i2c_tpd={ I2C_BOARD_INFO("ft5316", (TPD_SLAVE_ADDR>>1))};

static struct tpd_driver_t tpd_device_driver = {
		.tpd_device_name = "FT5316",
		.tpd_local_init = tpd_local_init,
		.suspend = tpd_suspend,
		.resume = tpd_resume,
#ifdef TPD_HAVE_BUTTON
		.tpd_have_button = 1,
#else
		.tpd_have_button = 0,
#endif		
		.tpd_x_res = TPD_CUST_RES_X,
		.tpd_y_res = TPD_CUST_RES_Y,	//including button area
	        .tpd_get_fw_version = tpd_get_fw_version_stored,
	        .tpd_get_vendor_version = tpd_get_vendor_version_stored,  //edit by Magnum 2012-7-10
};

struct i2c_driver tpd_i2c_driver = {
    .driver = {
	    .name = "ft5316_5p",//.name = TPD_DEVICE,
    },    
    .probe = tpd_i2c_probe,
    .remove = __devexit_p(tpd_remove),
    .detect = tpd_i2c_detect,
    .id_table = ft5316_i2c_id,
//    .address_data = &addr_data,
};

static int tpd_i2c_detect(struct i2c_client *client, int kind, struct i2c_board_info *info)
{
	TPD_DEBUG("tpd_i2c_detect\n");
	strcpy(info->type, "ft5316");
	return 0;
}

static int __devexit tpd_remove(struct i2c_client *client) 
{
	TPD_DEBUG("TPD removed\n");
	return 0;
}
 

int tpd_local_init(void) 
{
	int i;
	tp_boot_mode = get_boot_mode();
	// Software reset mode will be treated as normal boot
	if(tp_boot_mode==3) tp_boot_mode = NORMAL_BOOT;
	TPD_DEBUG("tpd_local_init boot mode = %d\n",tp_boot_mode);  
	if(i2c_add_driver(&tpd_i2c_driver)!=0)
	    TPD_DEBUG("unable to add i2c driver.\n");

	if(tpd_load_status == 0) 
	{
		TPD_DMESG("ft5206 add error touch panel driver.\n");
		i2c_del_driver(&tpd_i2c_driver);
		return -1;
	}
	
#ifdef TPD_HAVE_BUTTON     
	if (FACTORY_BOOT == tp_boot_mode)
	{
	for (i = 0; i < TPD_KEY_COUNT ; i++)
	    tpd_keys_local[i] = TPD_KEYSFACTORY[i];
	}

	tpd_button_setting(TPD_KEY_COUNT, tpd_keys_local, tpd_keys_dim_local);// initialize tpd button data
#endif   
	 
#if (defined(TPD_WARP_START) && defined(TPD_WARP_END))    
	TPD_DO_WARP = 1;
	memcpy(tpd_wb_start, tpd_wb_start_local, TPD_WARP_CNT*4);
	memcpy(tpd_wb_end, tpd_wb_start_local, TPD_WARP_CNT*4);
#endif 

#if (defined(TPD_HAVE_CALIBRATION) && !defined(TPD_CUSTOM_CALIBRATION))
	memcpy(tpd_calmat, tpd_calmat_local, 8*4);
	memcpy(tpd_def_calmat, tpd_def_calmat_local, 8*4);	
#endif  
	TPD_DMESG("end %s, %d\n", __FUNCTION__, __LINE__);  
	tpd_type_cap = 1;	
	return 0;
}

 int tpd_get_fw_version_stored()
{
    return panel_version;
}

 int tpd_get_vendor_version_stored()
{
     return vendor_version;
}

static void tpd_down(int x, int y, int id) {
    if(tpd_status)
    {
		TPD_DEBUG("tpd_down!\n");
	 if(RECOVERY_BOOT != get_boot_mode())
	   {
		    input_report_key(tpd->dev, BTN_TOUCH, 1);
		    input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 128);
		    input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
		    input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
		    input_report_abs(tpd->dev, ABS_MT_TRACKING_ID, id-1); 
		    input_mt_sync(tpd->dev);
		    tpd_down_state=1;
		    down_x=x;
		    down_y=y;
	     }
	    if (FACTORY_BOOT == get_boot_mode()|| RECOVERY_BOOT == get_boot_mode())
	    {   
	        //tpd_button(x, y, 1); 
		     int i ;
		     for(i=0;i< TPD_KEY_COUNT;i++) 
			{
	            if( (x >= (tpd_keys_dim_local[i][0] - tpd_keys_dim_local[i][2]/2)) && (x <=(tpd_keys_dim_local[i][0]+tpd_keys_dim_local[i][2]/2))
					&&(y >=	(tpd_keys_dim_local[i][1]-tpd_keys_dim_local[i][3]/2)) &&(y <=(tpd_keys_dim_local[i][1]+tpd_keys_dim_local[i][3]/2)) )
	            {
	            	
	            	TPD_DEBUG("tpd down value ==%d \n",tpd_keys_local[i]);
					input_report_key(tpd->dev, tpd_keys_local[i], 1);
				}
		    }  
		}
    }
}

static void tpd_up(int x, int y,int *count) {
    if(tpd_status){
	    TPD_DEBUG("tpd_up!\n");
	   if(RECOVERY_BOOT != get_boot_mode())
	   {
		    input_report_key(tpd->dev, BTN_TOUCH, 0);
		    input_mt_sync(tpd->dev);	    
	             tpd_down_state=0;
	             down_x=0;
	             down_y=0;
	   	}
		 if (FACTORY_BOOT == get_boot_mode()|| RECOVERY_BOOT == get_boot_mode())
		{   
		     	 int i ;
			     for(i=0;i< TPD_KEY_COUNT;i++) 
				{
		          if( (x >= (tpd_keys_dim_local[i][0] - tpd_keys_dim_local[i][2]/2)) && (x <=(tpd_keys_dim_local[i][0]+tpd_keys_dim_local[i][2]/2))
					&&(y >=	(tpd_keys_dim_local[i][1]-tpd_keys_dim_local[i][3]/2)) &&(y <=(tpd_keys_dim_local[i][1]+tpd_keys_dim_local[i][3]/2)) )
		            {
		            	TPD_DEBUG("tpd up value ==%d \n",tpd_keys_local[i]);
						input_report_key(tpd->dev, tpd_keys_local[i], 0);
					}
			    }  
		    }  
       }
}

#ifdef CONFIG_HAS_EARLYSUSPEND

/* platform device functions */
void tpd_suspend(struct early_suspend *h)
{
	TPD_DEBUG("[mtk-tpd] Suspend++.\n");
	if(isUpgrade ==1)
	{
	    TPD_DEBUG("Magnum tp is Upgrading.....\r\n");
		return;
	}
	mt65xx_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
	if(tpd_down_state){
	    tpd_up(down_x,down_y,NULL);
	//Ivan        input_report_abs(tpd->dev, ABS_MT_TRACKING_ID, 0);
	    input_sync(tpd->dev);
	    msleep(200);
	}
	tpd_status = 0;
	tinno_tp_power_off();
	TPD_DEBUG("[mtk-tpd] Suspend--.tpd_down_state=%d\n",tpd_down_state);
	if (ft5316_i2c_client == NULL)
		return;
}


void tpd_resume(struct early_suspend *h) 
{
	TPD_DEBUG("TP tpd_resume\n");
	if (ft5316_i2c_client == NULL)
		return;

	//    if (atomic_read( &g_pts->isp_opened ))
	//	return;

	TPD_DEBUG("[mtk-tpd] Resume++.\n");
	tinno_tp_power_on();
	int err = 0;
    	int i=0;
	for(i=0;i<5;i++){
	   err = tinno_check_focaltech();
	   if(err)
	        break;
	    tinno_tp_power_off();
	    tinno_tp_power_on();
	}
	if (err ==0)
	    TPD_DEBUG("tinno_init_panel ****************************************************power on failed.\n");

	tpd_init_skip = 1;
	tpd_status = 1;
	//Ivan 6573    MT6516_IRQUnmask(MT6516_TOUCH_IRQ_LINE); 
	mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);  
	TPD_DEBUG("[mtk-tpd] Resume--.\n");  
}
#endif

static int tpd_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id) 
{
	int err = 0;
	TPD_DEBUG("ft5316 tpd_i2c_probe\n");
	if (ft5316_i2c_client != NULL)
	return 1;

	ft5316_i2c_client = client;
	TPD_DEBUG("ft5316_i2c_client addr ==== %X \n", ft5316_i2c_client->addr);
	tinno_tp_power_off();
	tinno_tp_power_on();

	int i = 0;
	while(i++ <5){
		err=tinno_ts_get_fw_version();
		TPD_DEBUG("Product  version ==== %X \n", panel_version);
		if(err > 0)
			break;
		else
			continue;
	}
	if ( err < 0 ){
	    TPD_DEBUG("Product  version %X is invalid.\n", panel_version);
	    goto err_detect_failed;
	}

	tpd_load_status = 1;
	
	  

    /* added in android 2.2, for configuring EINT2 */
    mt_set_gpio_mode(TPIO_EINT, GPIO_CTP_EINT_PIN_M_EINT);
    mt_set_gpio_pull_enable(TPIO_EINT, GPIO_PULL_ENABLE);
    mt_set_gpio_pull_select(TPIO_EINT,GPIO_PULL_UP);
    mt65xx_eint_set_sens(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_SENSITIVE);
    mt65xx_eint_set_hw_debounce(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_CN);
    mt65xx_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, CUST_EINT_TOUCH_PANEL_DEBOUNCE_EN, CUST_EINT_TOUCH_PANEL_POLARITY, tpd_eint_interrupt_handler, 1);    
    mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);

    mutex_init(&tp_mutex);	
#ifdef CONFIG_TOUCHSCREEN_FT5X05_SUPPORT_ISP
	magnum_fts_isp_register(ft5316_i2c_client);

#endif/*CONFIG_TOUCHSCREEN_FT5X05_SUPPORT_ISP*/
    tpd_status = 1;
  thread = kthread_run(touch_event_handler, 0, TPD_DEVICE);
	    if (IS_ERR(thread)) { 
	        err = PTR_ERR(thread);
	        TPD_DEBUG(TPD_DEVICE " failed to create kernel thread: %d\n", err);
    }

    //edit by Magnum 2012-12-25
#ifdef  TP_AUTO_UPGRADE
		focaltech_auto_upgrade();
#endif

    TPD_DEBUG("tpd_i2c_probe OK\n");	
   
    return 0;

err_detect_failed:
    TPD_DEBUG("tpd_i2c_probe ERROR\n");
    ft5316_i2c_client = NULL;
    tinno_tp_power_off();
   return 1;
}


static void tpd_eint_interrupt_handler(void) {
    TPD_DEBUG_PRINT_INT; tpd_flag=1; wake_up_interruptible(&waiter);
}

int tinno_ts_parse_data(struct touch_info *cinfo, struct touch_info *sinfo, uint8_t buffer[])
{
	int iInvalidTrackIDs = 0;
	fts_report_data_t report_data = {0};
	tinno_ts_point touch_point[TINNO_TOUCH_TRACK_IDS];
	int iTouchID, i,iKeyCode;

	memset(touch_point, FTS_INVALID_DATA, sizeof(touch_point));
	memcpy(&report_data, buffer, FTS_PROTOCOL_LEN);

	cinfo->count = 0;

	cinfo->pt[0].z = FTS_EF_RESERVED;
	cinfo->pt[1].z = FTS_EF_RESERVED;
	//edit by Magnum 2012-8-6
	cinfo->pt[2].z = FTS_EF_RESERVED;
	cinfo->pt[3].z = FTS_EF_RESERVED;
	cinfo->pt[4].z = FTS_EF_RESERVED;

#ifdef TPD_USE_VIRTUAL_KEY
    if (tp_boot_mode == RECOVERY_BOOT || tp_boot_mode == FACTORY_BOOT)
    {
    	//edit by Magnum 2012-9-20: make only one point in Recovery & Factory mode.
    	if (report_data.fingers > 0 && report_data.fingers < 2 )
		    tpd_dcount = 1;
		else
		    tpd_dcount = 0;
    }
    else
    {
		 tpd_dcount=((report_data.xy_data[0].event_flag  != FTS_EF_RESERVED)?1:0)+
               ((report_data.xy_data[1].event_flag  != FTS_EF_RESERVED)?1:0);	
    }
#else
       tpd_dcount=((report_data.xy_data[0].event_flag  != FTS_EF_RESERVED)?1:0)+
               ((report_data.xy_data[1].event_flag  != FTS_EF_RESERVED)?1:0);
#endif
       if(tpd_dcount){		
		for ( i=0; i < TINNO_TOUCH_TRACK_IDS; i++ ){
			if (report_data.xy_data[i].event_flag != FTS_EF_RESERVED) {
				iTouchID = report_data.xy_data[i].touch_id;
				if ( iTouchID >= TINNO_TOUCH_TRACK_IDS )
				{
					TPD_DEBUG("Invalied Track ID(%d)!\n", iTouchID);
					iInvalidTrackIDs++;
					continue;
				}
				cinfo->pt[i].x = report_data.xy_data[i].x_h << 8 | report_data.xy_data[i].x_l;
				cinfo->pt[i].y = report_data.xy_data[i].y_h << 8 | report_data.xy_data[i].y_l;
				cinfo->pt[i].z = report_data.xy_data[i].event_flag;	
				cinfo->pt[i].id = report_data.xy_data[i].touch_id;		
				TPD_DEBUG("iTpuchID ==%d, Point ID == %d, x == %d , y == %d ,z ==%d\n!",iTouchID, cinfo->pt[iTouchID].id,cinfo->pt[iTouchID].x,cinfo->pt[iTouchID].y,cinfo->pt[iTouchID].z );
				cinfo->count++;						//Two fingers touched

				//edit by Magnum 2012-8-31 ctp up question
				x_history[i] = cinfo->pt[iTouchID].x;
               			y_history[i] = cinfo->pt[iTouchID].y;
				
			}
		}
//		cinfo->count = 	i;						//Two fingers touched		
		if ( TINNO_TOUCH_TRACK_IDS == iInvalidTrackIDs ){
			TPD_DEBUG("All points are Invalied, Ignore the interrupt!");
			return 1; 
		}
	}

	if (1==report_data.fingers)
	{
        if (cinfo->pt[0].y > TPD_BUTTON_HEIGHT)
        {
              // cinfo->count = 3;
              inTouchKey = 1;
        } 
		else 
			 inTouchKey = 0;  
     }
    if (0==report_data.fingers)
        cinfo->count = 0 ; //0xFF;		//Release
	    
	return 0;
}

int tpd_gettouchinfo(struct touch_info *cinfo, struct touch_info *sinfo) 
{
	int ret;
	uint8_t start_reg = 0x00;
	char buffer[40];
	//	memset(buffer, 0xFF, 16);
	memset(buffer, 0xFF, FTS_PROTOCOL_LEN);
	TPD_DEBUG("Magnum FTS_PROTOCOL_LEN ===%d\n",FTS_PROTOCOL_LEN);

	mutex_lock(&tp_mutex);

	start_reg = 0x02;
	ret = i2c_master_send(ft5316_i2c_client,&start_reg,1);
	ret = i2c_master_recv(ft5316_i2c_client, &buffer[2], 5);
	
	if (buffer[2] > 1)
	{
	    start_reg = 9;
	    ret = i2c_master_send(ft5316_i2c_client,&start_reg,1);
	    ret = i2c_master_recv(ft5316_i2c_client, &buffer[9], 4);
	} 
	//edit by Magnum 2012-8-6
	if (buffer[9] > 1)
	{
	    start_reg = 0x0f;
	    ret = i2c_master_send(ft5316_i2c_client,&start_reg,1);
	    ret = i2c_master_recv(ft5316_i2c_client, &buffer[15], 4);
	} 
	if (buffer[15] > 1)
	{
	    start_reg = 0x15;
	    ret = i2c_master_send(ft5316_i2c_client,&start_reg,1);
	    ret = i2c_master_recv(ft5316_i2c_client, &buffer[21], 4);
	} 
	if (buffer[21] > 1)
	{
	    start_reg = 0x1b;
	    ret = i2c_master_send(ft5316_i2c_client,&start_reg,1);
	    ret = i2c_master_recv(ft5316_i2c_client, &buffer[27], 4);
	} 
//	ret = i2c_master_recv(i2c_client, &buffer[0],8 );
	//ret = i2c_master_recv(i2c_client, &buffer[8],8 );	
	//ret = i2c_master_recv(i2c_client, &buffer[16],8 );	
	//ret = i2c_master_recv(i2c_client, &buffer[24],8 );	
	//ret = i2c_master_recv(i2c_client, &buffer[32],1 );	
	

	mutex_unlock(&tp_mutex);

	if (ret < 0) {
	    TPD_DEBUG("i2c_transfer failed");
		return 1;							//Error
	}

	TPD_DEBUG("[%x %x %x ]\n",buffer[0],buffer[1],buffer[2]);			
    	int i = 0;int j =3;
	for(i;i<4;i++){
      		 TPD_DEBUG("[%x %x %x %x ]\n",buffer[j],buffer[j+1],buffer[j+2],buffer[j+3],buffer[j+4]);
	   	j = j+6;
	}
				
    	ret = tinno_ts_parse_data(cinfo, sinfo, buffer);
	return ret;
}


static int touch_event_handler(void *unused) {
    struct sched_param param = { .sched_priority = RTPM_PRIO_TPD };
    struct touch_info cinfo, sinfo;
    int pending = 0;
    struct i2c_client * i2c_client  =  ft5316_i2c_client ;
    TPD_DEBUG("touch_event_handler\n");
	
    cinfo.pending=0;
    sched_setscheduler(current, SCHED_RR, &param);
    do {
//Ivan added for testing
		if (tpd_status == 1){
		    mt65xx_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM); // possibly to lose event?
         	 }
	        set_current_state(TASK_INTERRUPTIBLE);
	        if (!kthread_should_stop()) 
		{
	        //    TPD_DEBUG_CHECK_NO_RESPONSE;
	            do {
	                if(pending) wait_event_interruptible_timeout(waiter, tpd_flag!=0, HZ/10);
	                else wait_event_interruptible_timeout(waiter,tpd_flag!=0, HZ*2);
	            } while(0);
	            if(tpd_flag==0 && !pending) continue; // if timeout for no touch, then re-wait.
	            if(tpd_flag!=0 && pending>0)  pending=0;
	            tpd_flag=0;
	            TPD_DEBUG_SET_TIME;
	        }
	        set_current_state(TASK_RUNNING);
	        
	        if(!pending) if(tpd_gettouchinfo(&cinfo, &sinfo)) continue; 
	        if(pending>1) { pending--; continue; }
		//Ivan ++
		if (tpd_init_skip) {tpd_init_skip = 0; continue; }
		TPD_DEBUG("cinfo->count == %d!\n", cinfo.count);
		if(cinfo.count > 0)
		{
			int i;
			for ( i=0; i < cinfo.count; i++ )
			{
				TPD_DEBUG("cinfo->count == %d!\n", cinfo.count);
				TPD_DEBUG("Point ID == %d, x == %d , y == %d ,z ==%d\n!",cinfo.pt[i].id,cinfo.pt[i].x,cinfo.pt[i].y,cinfo.pt[i].z );
				tpd_down(cinfo.pt[i].x, cinfo.pt[i].y, cinfo.pt[i].id);
			}
			input_sync(tpd->dev);
		}
		else
		{
			TPD_DEBUG("TPD up x == %d , y == %d\n!",x_history[cinfo.count], y_history[cinfo.count]);
			tpd_up(x_history[cinfo.count], y_history[cinfo.count], 0);		
			input_sync(tpd->dev);
		}    
    } while (!kthread_should_stop());
    return 0;
}

static int tpd_i2c_remove(struct i2c_client *client) {
	i2c_unregister_device(client);
	TPD_DEBUG("[mtk-tpd] touch panel i2c device is removed.\n");
	input_unregister_device(tpd->dev);
	input_unregister_device(tpd->kpd);

#ifdef CONFIG_TOUCHSCREEN_FT5X05_SUPPORT_ISP
	fts_isp_deregister(ft5316_i2c_client);//misc_deregister(&fts_isp_device);
	
#endif		
	return 0;
}

/* called when loaded into kernel */
static int __init tpd_driver_init(void) {
	TPD_DEBUG("MediaTek FT5316 touch panel driver init\n");
	i2c_register_board_info(TPD_I2C_NUMBER, &ft5316_i2c_tpd, 1);    
	if(tpd_driver_add(&tpd_device_driver) < 0)
	TPD_DMESG("add generic driver failed\n");
	return 0;
}

/* should never be called */
static void __exit tpd_driver_exit(void) {
    TPD_DMESG("MediaTek FT5316 touch panel driver exit\n");
    //input_unregister_device(tpd->dev);
    tpd_driver_remove(&tpd_device_driver);
}

module_init(tpd_driver_init);
module_exit(tpd_driver_exit);

