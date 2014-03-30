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

#ifndef TOUCHPANEL_H__
#define TOUCHPANEL_H__

#include <linux/i2c.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include "tpd.h"
#include <cust_eint.h>
#include <linux/rtpm_prio.h>
#include <linux/wakelock.h>
#include <asm/uaccess.h>
#include <linux/dma-mapping.h>
#include <linux/vmalloc.h>
#include "cust_gpio_usage.h"
#include <mach/mt_pm_ldo.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_boot.h>

/* Pre-defined definition */
#define TPD_USE_VIRTUAL_KEY
#define TPD_TYPE_CAPACITIVE
#define TPD_TYPE_RESISTIVE
#define TPD_POWER_SOURCE         MT65XX_POWER_LDO_VGP4
#define TPD_I2C_NUMBER           0
#define TPD_WAKEUP_TRIAL         60
#define TPD_WAKEUP_DELAY         100

#define TPD_DELAY                (2*HZ/100)
#define TPD_CUST_RES_X          	480
#define TPD_CUST_RES_Y           854
#define TPD_CALIBRATION_MATRIX  {962,0,0,0,1600,0,0,0};

//#define TPD_HAVE_CALIBRATION
#define TPD_HAVE_BUTTON
//#define TPD_HAVE_TREMBLE_ELIMINATION

//#define TPD_HAVE_POWER_ON_OFF

#define PRESSURE_FACTOR	10

#define TPD_BUTTON_HEIGHT		854
//#define TPD_KEY_COUNT           3
//#define TPD_KEYS                {KEY_HOME, KEY_MENU, KEY_BACK}
//#define TPD_KEYS_DIM            {{106,501,106,43},{212,501,106,43},{318,501,106,43}}
//Ivan (centerx,centery,width,height)
#define VIRTUAL_KEY_DEB_TIME	3
#define TPD_Y_OFFSET		0

#define TPD_KEY_COUNT           3
#define TPD_KEYS                {KEY_MENU,KEY_HOMEPAGE,KEY_BACK}

#define TPD_YMAX		915		//Truely, BYD = 516
#define TPD_BUTTON_SIZE_HEIGHT  (TPD_YMAX - TPD_BUTTON_HEIGHT - TPD_Y_OFFSET)
#define TPD_BUTTON_Y_CENTER   	(TPD_BUTTON_HEIGHT + (TPD_YMAX - TPD_BUTTON_HEIGHT)/2 + TPD_Y_OFFSET)

//TP virtual key customization

// |                                                                                                   |
// |                                                                                                   |  Touch Pad area ( H < 480)
//  ---------------------------------------------------------------------------------------------------
// |                                           TPD_Y_OFFSET                                            |  Virtual key area ( H > 480)
// |---------------------------------------------------------------------------------------------------
// |TPD_B1_FP | [TPD_B1_W] | TPD_B2_FP | [TPD_B2_W] | TPD_B3_FP | [TPD_B3_W] | TPD_B4_FP | [TPD_B4_W]  |  
// -----------------------------------------------------------------------------------------------------

#define TPD_B1_FP	0		//Button 1 pad space
#define TPD_B1_W	120		//Button 1 Width
#define TPD_B2_FP	80		//Button 2 pad space
#define TPD_B2_W	120		//Button 2 Width
#define TPD_B3_FP	80		//Button 3 pad space
#define TPD_B3_W	120		//Button 3 Width
#define TPD_B4_FP	0		//Button 4 pad space
#define TPD_B4_W	75		//Button 4 width
//#define TPD_KEYS_DIM            {{80,850,160,TPD_BUTTON_HEIGH},{240,850,160,TPD_BUTTON_HEIGH},{400,850,160,TPD_BUTTON_HEIGH}}


//-------------------------------------------------------------------------
#define TPD_BUTTON1_X_CENTER	TPD_B1_FP + TPD_B1_W/2
#define TPD_BUTTON2_X_CENTER	TPD_B1_FP + TPD_B1_W + TPD_B2_FP + TPD_B2_W/2
#define TPD_BUTTON3_X_CENTER	TPD_B1_FP + TPD_B1_W + TPD_B2_FP + TPD_B2_W + TPD_B3_FP + TPD_B3_W/2
#define TPD_BUTTON4_X_CENTER	TPD_B1_FP + TPD_B1_W + TPD_B2_FP + TPD_B2_W + TPD_B3_FP + TPD_B3_W + TPD_B4_FP + TPD_B4_W/2


#define TPD_KEYS_DIM            {{TPD_BUTTON1_X_CENTER, TPD_BUTTON_Y_CENTER, TPD_B1_W, TPD_BUTTON_SIZE_HEIGHT},	\
				 {TPD_BUTTON2_X_CENTER, TPD_BUTTON_Y_CENTER, TPD_B2_W, TPD_BUTTON_SIZE_HEIGHT},	\
				 {TPD_BUTTON3_X_CENTER, TPD_BUTTON_Y_CENTER, TPD_B3_W, TPD_BUTTON_SIZE_HEIGHT}}


/*--------------------------Const value , Macro Definition ----------------------------*/
#define TPD_SLAVE_ADDR 0x72	//ES980=0x72  //ES970=0x7E	//default = 0x70
#define CONFIG_TOUCHSCREEN_FT5X05_SUPPORT_ISP		
#define TP_AUTO_UPGRADE 	
extern struct i2c_client * ft5316_i2c_client ;
extern int isUpgrade ; // 1:show that TP is upgrading ...edit by Magnum  2012-7-19 
extern char panel_version ;
extern char vendor_version ;
extern int tpd_status ;

//extern struct tinno_ts_data *g_pts ;
extern struct mutex tp_mutex;
extern int tp_boot_mode;

#define FTS_PROTOCOL_LEN (sizeof(fts_report_data_t))
#define TINNO_TOUCH_TRACK_IDS (5)  //edit by Magnum 2012-8-6
#define FTS_INVALID_DATA (-1)

#define FTS_EF_DOWN (0)
#define FTS_EF_UP (1)
#define FTS_EF_CONTACT (2)
#define FTS_EF_RESERVED (3)

#define TPIO_RESET      GPIO_CTP_RST_PIN     //GPIO184
#define TPIO_WAKEUP     GPIO_CTP_PD_PIN      //GPIO187
#define TPIO_EINT		GPIO_CTP_EINT_PIN

static const int TPD_KEYSFACTORY[TPD_KEY_COUNT] =  {KEY_F1, KEY_F2, KEY_F3};

#ifdef TPD_HAVE_BUTTON 
static int tpd_keys_local[TPD_KEY_COUNT] = TPD_KEYS;
static int tpd_keys_dim_local[TPD_KEY_COUNT][4] = TPD_KEYS_DIM;
extern void tpd_button(unsigned int x, unsigned int y, unsigned int down);
#endif

#if (defined(TPD_WARP_START) && defined(TPD_WARP_END))
static int tpd_wb_start_local[TPD_WARP_CNT] = TPD_WARP_START;
static int tpd_wb_end_local[TPD_WARP_CNT]   = TPD_WARP_END;
#endif
#if (defined(TPD_HAVE_CALIBRATION) && !defined(TPD_CUSTOM_CALIBRATION))
static int tpd_calmat_local[8]     = TPD_CALIBRATION_MATRIX;
static int tpd_def_calmat_local[8] = TPD_CALIBRATION_MATRIX;
#endif




/*--------------------------Struct  Definition ----------------------------*/
typedef struct _tinno_ts_point{
	int x, y, z, id;
} tinno_ts_point;

struct touch_info {
    tinno_ts_point pt[TINNO_TOUCH_TRACK_IDS];
    int p, count, pending;
};

struct touch_elapse {
    int t1, t2, i;
    int buf[5];
};

#ifdef CONFIG_TOUCHSCREEN_FT5X05_SUPPORT_ISP
struct tinno_ts_data {
	struct wake_lock wake_lock;
	atomic_t isp_opened;
	uint8_t *isp_pBuffer;
	struct i2c_client *client;
};

#define ISP_FLASH_SIZE	0x8000 //32KB
#define FT5X06_FIRMWAIR_VERSION_D
 
#define FTS_MODE_OPRATE (0x00)
#define FTS_MODE_UPDATE (0x01)
#define FTS_MODE_SYSTEM (0x02)

#define TOUCH_IO_MAGIC ('F')
#define FT5X05_IOCTL_RESET 				_IO(TOUCH_IO_MAGIC, 0x00)
#define FT5X05_IOCTL_SWITCH_TO 		_IOW(TOUCH_IO_MAGIC, 0x01, int)
#define FT5X05_IOCTL_WRITE_PROTECT 	_IOW(TOUCH_IO_MAGIC, 0x02, int)
#define FT5X05_IOCTL_ERASE 				_IO(TOUCH_IO_MAGIC, 0x03)
#define FT5X05_IOCTL_GET_STATUS		_IOR(TOUCH_IO_MAGIC, 0x04, int)
#define FT5X05_IOCTL_GET_CHECKSUM		_IOR(TOUCH_IO_MAGIC, 0x05, int)
#define FT5X05_IOCTL_GET_TPID			_IOR(TOUCH_IO_MAGIC, 0x06, int)
#define FT5X05_IOCTL_GET_VENDORID		_IOR(TOUCH_IO_MAGIC, 0x07, int)
#define FT5X05_IOC_MAXNR				(0x08)


#endif

typedef struct {
	uint8_t	x_h: 4,
		reserved_1: 2,
		event_flag: 2;
	uint8_t	x_l;
	uint8_t	y_h: 4,
		touch_id: 4;
	uint8_t	y_l;
	uint8_t reserved_2;
	uint8_t reserved_3;
} xy_data_t;

typedef struct {
	uint8_t	reserved_1: 4,
		device_mode: 3,
		reserved_2: 1;
	uint8_t	gesture;
	uint8_t	fingers: 4,
		reserved_3: 4;
	xy_data_t	 xy_data[TINNO_TOUCH_TRACK_IDS];
} fts_report_data_t;

struct Focaltech_firmware
{
	//firmware buffer
       char * ctp_buffer;
 	int length;   
};

/*--------------------------Function Declaration ----------------------------*/
static void tpd_eint_interrupt_handler(void);
static int tpd_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int tpd_i2c_detect(struct i2c_client *client, int kind, struct i2c_board_info *info);
static int tpd_i2c_remove(struct i2c_client *client);
static int __devexit tpd_remove(struct i2c_client *client);
void tpd_suspend(struct early_suspend *h);
void tpd_resume(struct early_suspend *h) ;
int tpd_local_init(void);
int tpd_get_fw_version_stored();
int tpd_get_vendor_version_stored();
int tinno_ts_set_period_active(void);
int tinno_check_focaltech(void);
int tinno_ts_get_fw_version();
//static void tpd_up(int x, int y,int *count) ;
void tinno_tp_power_on(void);
void tinno_tp_power_off(void);
void ft5316_tpd_reset(void);

// TODO: should be moved into mach/xxx.h 
extern void mt65xx_eint_unmask(unsigned int line);
extern void mt65xx_eint_mask(unsigned int line);
extern void mt65xx_eint_set_hw_debounce(unsigned int eint_num, unsigned int ms);
extern unsigned int mt65xx_eint_set_sens(unsigned int eint_num, unsigned int sens);
extern void mt65xx_eint_registration(unsigned int eint_num, unsigned int is_deb_en, unsigned int pol, void (EINT_FUNC_PTR)(void), unsigned int is_auto_umask);

static DECLARE_WAIT_QUEUE_HEAD(waiter);
static int touch_event_handler(void *unused);

#endif /* TOUCHPANEL_H__ */
