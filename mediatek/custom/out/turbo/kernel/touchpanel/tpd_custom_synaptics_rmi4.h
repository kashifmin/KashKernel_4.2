#ifndef TOUCHPANEL_H__
#define TOUCHPANEL_H__

/* Pre-defined definition */

/* Register */
//#define FD_ADDR_MAX    	0xE9
//#define FD_ADDR_MIN    	0xDD
//#define FD_BYTE_COUNT 	6

#define CUSTOM_MAX_WIDTH (1080)
#define CUSTOM_MAX_HEIGHT (1920)

//#define TPD_UPDATE_FIRMWARE

#define TPD_HAVE_BUTTON
#define TPD_KEY_COUNT           3
#define TPD_KEYS                { KEY_MENU, KEY_HOMEPAGE, KEY_BACK}


#define TPD_YMAX        (2075)
#define TPD_Y_OFFSET		30

#define TPD_B1_FP	80		//Button 1 pad space
#define TPD_B1_W	240		//Button 1 Width
#define TPD_B2_FP	90		//Button 2 pad space
#define TPD_B2_W	240		//Button 2 Width
#define TPD_B3_FP	120		//Button 3 pad space
#define TPD_B3_W	240		//Button 3 Width

#define TPD_BUTTON1_X_CENTER	(TPD_B1_FP + TPD_B1_W/2)
#define TPD_BUTTON2_X_CENTER	(TPD_B1_FP + TPD_B1_W + TPD_B2_FP + TPD_B2_W/2)
#define TPD_BUTTON3_X_CENTER	(TPD_B1_FP + TPD_B1_W + TPD_B2_FP + TPD_B2_W + TPD_B3_FP + TPD_B3_W/2)

#define TPD_BUTTON_SIZE_HEIGHT  (TPD_YMAX - CUSTOM_MAX_HEIGHT - TPD_Y_OFFSET)
#define TPD_BUTTON_Y_CENTER   	(CUSTOM_MAX_HEIGHT + TPD_Y_OFFSET + (TPD_YMAX - CUSTOM_MAX_HEIGHT - TPD_Y_OFFSET)/2)

#define TPD_KEYS_DIM		{{TPD_BUTTON1_X_CENTER, TPD_BUTTON_Y_CENTER, TPD_B1_W, TPD_BUTTON_SIZE_HEIGHT},	\
				 			{TPD_BUTTON2_X_CENTER, TPD_BUTTON_Y_CENTER, TPD_B2_W, TPD_BUTTON_SIZE_HEIGHT},	\
							{TPD_BUTTON3_X_CENTER, TPD_BUTTON_Y_CENTER, TPD_B3_W, TPD_BUTTON_SIZE_HEIGHT}}


#define TPD_POWER_SOURCE         MT65XX_POWER_LDO_VGP5
#define LCD_X           (1080)			//add by lishengli 20130514
#define LCD_Y           (1920)

#define TPD_UPDATE_FIRMWARE
//#define HAVE_TOUCH_KEY

//#define TPD_HAVE_CALIBRATION
//#define TPD_CALIBRATION_MATRIX  {2680,0,0,0,2760,0,0,0};
//#define TPD_WARP_START
//#define TPD_WARP_END

//#define TPD_RESET_ISSUE_WORKAROUND
//#define TPD_MAX_RESET_COUNT 3
//#define TPD_WARP_Y(y) ( TPD_Y_RES - 1 - y )
//#define TPD_WARP_X(x) ( x )




//LINE<JIRA_ID><DATE20130422><BUG_INFO>zenghaihui
#if 0
#define CTP_DBG(fmt, arg...) \
	printk("[CTP-S3202] %s (line:%d) :" fmt "\r\n", __func__, __LINE__, ## arg)
#else
#define CTP_DBG(fmt, arg...) do {} while (0)
#endif


#endif /* TOUCHPANEL_H__ */
