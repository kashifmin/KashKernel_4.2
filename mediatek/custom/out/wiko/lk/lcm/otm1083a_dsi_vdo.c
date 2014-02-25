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

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#define LCM_ID_HX8394 (0x94)

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

static unsigned int lcm_esd_test = FALSE;      ///only for ESD test

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))

#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)   


#define   LCM_DSI_CMD_MODE							0


static void init_lcm_registers(void)
{
	unsigned int data_array[16];  
	//SSD2825_Gen_write_1A_1P(0x00,0x00);

	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_3P(0xff,0x12,0x83,0x01);	//EXTC=1
	data_array[0] = 0x00043902;                          
        data_array[1] = 0x018312ff;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x80);	            //Orise mode enable
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008000;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_2P(0xff,0x12,0x83);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x008312ff;                 
        dsi_set_cmdq(data_array, 2, 1);

//-------------------- panel setting ------------------------------------//

	//SSD2825_Gen_write_1A_1P(0x00,0x80);             //TCON Setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008000;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_9P(0xc0,0x00,0x64,0x00,0x0f,0x11,0x00,0x64,0x0f,0x11);
	data_array[0] = 0x000a3902;                          
        data_array[1] = 0x006400c0; 
        data_array[2] = 0x6400110f;
        data_array[3] = 0x0000110f;                
        dsi_set_cmdq(data_array, 4, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x90);             //Panel Timing Setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_6P(0xc0,0x00,0x55,0x00,0x01,0x00,0x04);   //Charge time setting,gate and source 
	data_array[0] = 0x00073902;                          
        data_array[1] = 0x005500c0; 
        data_array[2] = 0x00040001;                
        dsi_set_cmdq(data_array, 3, 1);

    	//SSD2825_Gen_write_1A_1P(0x00,0xa4);             //source pre.
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a400;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc0,0x00);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000000c0;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb3);             //Interval Scan Frame: 0 frame, column inversion
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b300;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_2P(0xc0,0x00,0x50);        // 50 column, 00 1dot
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x005000c0;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x81);             //frame rate:60Hz
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008100;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc1,0x55);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000055c1;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x81);             //source bias 0.75uA
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008100;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc4,0x82);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000082c4;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x82);             //flash-orise add
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008200;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_1P(0xc4,0x02);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000002c4;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x90);             //clock delay for data latch 
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc4,0x49);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000049c4;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xc6);		//debounce 
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000c600;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xB0,0x03); 
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000003b0;                 
        dsi_set_cmdq(data_array, 2, 1);

//-------------------------------------- BOE Power IC-----------------------------------------

	//SSD2825_Gen_write_1A_1P(0x00,0x90);             //Mode-3
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_4P(0xf5,0x02,0x11,0x02,0x11);
	data_array[0] = 0x00053902;                          
        data_array[1] = 0x021102f5;
        data_array[2] = 0x00000011;                  
        dsi_set_cmdq(data_array, 3, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x90);             //3xVPNL
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc5,0x50);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000050c5;                   //50
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x94);             //2xVPNL
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009400;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc5,0x66);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000066c5;                 //66
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb2);             //VGLO1
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b200;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xf5,0x00,0x00);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x000000f5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb4);             //VGLO1_S
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b400;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xf5,0x00,0x00);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x000000f5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb6);             //VGLO2
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b600;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xf5,0x00,0x00);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x000000f5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb8);             //VGLO2_S
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b800;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xf5,0x00,0x00);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x000000f5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x94);  		//VCL on  
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009400;                 
        dsi_set_cmdq(data_array, 2, 1);
	
	//SSD2825_Gen_write_1A_1P(0xF5,0x02);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000002f5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xBA);  		//VSP on   	
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000ba00;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xF5,0x03);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000003f5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb2);             //C31 cap. not remove
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b200;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc5,0x40);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000040c5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb4);             //VGLO1/2 Pull low setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b400;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc5,0xc0);		//d[7] vglo1 d[6] vglo2 => 0: pull vss, 1: pull vgl
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000c0c5;                 
        dsi_set_cmdq(data_array, 2, 1);

//-------------------- power setting -----------------------------------//
	//SSD2825_Gen_write_1A_1P(0x00,0xa0);             //dcdc setting (PFM Fre)
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xc4,0x05,0x10,0x06,0x02,0x05,0x15,0x10,0x05,0x10,0x07,0x02,0x05,0x15,0x10);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x061005c4; 
        data_array[2] = 0x10150502;  
        data_array[3] = 0x02071005;  
        data_array[4] = 0x00101505;                  
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb0);             //clamp voltage setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xc4,0x00,0x00);         //VSP and VSN Change (5.6V,-5.6V)
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x000000c4;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x91);             //VGH=12V, VGL=-12V, pump ratio:VGH=6x, VGL=-5x
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009100;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xc5,0x19,0x50);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x005019c5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x00);             //GVDD=4.87V, NGVDD=-4.87V
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xd8,0xbc,0xbc);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x00bcbcd8;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb0);             //VDD_18V=1.6V, LVDSVDD=1.55V
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xc5,0x04,0xb8);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x00b804c5;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xbb);             //LVD voltage level setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000bb00;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xc5,0x80);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000080c5;                 
        dsi_set_cmdq(data_array, 2, 1);
//-------------------- control setting ---------------------------------------------------//

	//SSD2825_Gen_write_1A_1P(0x00,0x00);             //ID1
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0xd0,0x40);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000040d0;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x00);             //ID2, ID3
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_2P(0xd1,0x00,0x00);
	data_array[0] = 0x00033902;                          
        data_array[1] = 0x000000d1;                 
        dsi_set_cmdq(data_array, 2, 1);

	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a000;                 
        dsi_set_cmdq(data_array, 2, 1);	

	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000002c1;                 
        dsi_set_cmdq(data_array, 2, 1);			
//-------------------- GAMMA TUNING ------------------------------------------//

	//SSD2825_Gen_write_1A_1P(0x00,0x00);  
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);
          
	//SSD2825_Gen_write_1A_16P(0xE1,0x05,0x0E,0x14,0x0E,0x06,0x11,0x0B,0x0A,0x00,0x05,0x0A,0x03,0x0E,0x15,0x10,0x05);
	data_array[0] = 0x00113902;                          
        data_array[1] = 0x140e05e1;  
        data_array[2] = 0x0b11060e; 
        data_array[3] = 0x0a05000a; 
        data_array[4] = 0x10150e03; 
        data_array[5] = 0x00000005;                
        dsi_set_cmdq(data_array, 6, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x00);   
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);
         
	//SSD2825_Gen_write_1A_16P(0xE2,0x05,0x0E,0x14,0x0E,0x06,0x0F,0x0D,0x0c,0x04,0x07,0x0E,0x0B,0x10,0x15,0x10,0x05);	
	data_array[0] = 0x00113902;                          
        data_array[1] = 0x140e05e2;   
        data_array[2] = 0x0d0f060e;
        data_array[3] = 0x0e07040c;
        data_array[4] = 0x1015100b;
        data_array[5] = 0x00000005;              
        dsi_set_cmdq(data_array, 6, 1);

#if 0  //<20130531><new lcd do not set vcom>wangyanhui
	//SSD2825_Gen_write_1A_1P(0x00,0x00);      
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);
 
	//SSD2825_Gen_write_1A_1P(0xD9,0x73);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x000073d9;
        dsi_set_cmdq(data_array, 2, 1);
#endif
//-------------------- panel timing state control ------------------------------------------//
	//SSD2825_Gen_write_1A_1P(0x00,0x80);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_11P(0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x000c3902;                          
        data_array[1] = 0x000000cb;
        data_array[2] = 0x00000000; 
        data_array[3] = 0x00000000;                
        dsi_set_cmdq(data_array, 4, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x90);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_15P(0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x000000cb; 
        data_array[2] = 0x00000000;
        data_array[3] = 0x00000000;
        data_array[4] = 0x00000000;                
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xa0);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_15P(0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x000000cb;  
        data_array[2] = 0x00000000;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb0);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_15P(0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x000000cb;  
        data_array[2] = 0x00000000;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);


	//SSD2825_Gen_write_1A_1P(0x00,0xc0);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000c000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_15P(0xcb,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x050505cb;  
        data_array[2] = 0x00050505;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xd0);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000d000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_15P(0xcb,0x00,0x00,0x00,0x00,0x00,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x000000cb;  
        data_array[2] = 0x05050000;  
        data_array[3] = 0x05050505;  
        data_array[4] = 0x00000505;                 
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xe0);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000e000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xcb,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x05);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cb;  
        data_array[2] = 0x00000000;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x00050500;                 
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xf0);             //panel timing state control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000f000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_11P(0xcb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff);
	data_array[0] = 0x000c3902;                          
        data_array[1] = 0xffffffcb; 
        data_array[2] = 0xffffffff;  
        data_array[3] = 0xffffffff;                  
        dsi_set_cmdq(data_array, 4, 1);
//-------------------- panel pad mapping control --------------------//

	 //SSD2825_Gen_write_1A_1P(0x00,0x80);             //panel pad mapping control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008000;                 
        dsi_set_cmdq(data_array, 2, 1);

	 //SSD2825_Gen_write_1A_15P(0xcc,0x0a,0x0c,0x0e,0x10,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x0e0c0acc;  
        data_array[2] = 0x00040210;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);

	 //SSD2825_Gen_write_1A_1P(0x00,0x90);             //panel pad mapping control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	 //SSD2825_Gen_write_1A_15P(0xcc,0x00,0x00,0x00,0x00,0x00,0x2e,0x2d,0x09,0x0b,0x0d,0x0f,0x01,0x03,0x00,0x00);
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x000000cc;  
        data_array[2] = 0x2d2e0000;  
        data_array[3] = 0x0f0d0b09;  
        data_array[4] = 0x00000301;                 
        dsi_set_cmdq(data_array, 5, 1);

	 //SSD2825_Gen_write_1A_1P(0x00,0xa0);             //panel pad mapping control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a000;                 
        dsi_set_cmdq(data_array, 2, 1);

	 //SSD2825_Gen_write_1A_14P(0xcc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2e,0x2d);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cc;  
        data_array[2] = 0x00000000;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x002d2e00;                 
        dsi_set_cmdq(data_array, 5, 1);

	 //SSD2825_Gen_write_1A_1P(0x00,0xb0);             //panel pad mapping control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b000;                 
        dsi_set_cmdq(data_array, 2, 1);

	 //SSD2825_Gen_write_1A_15P(0xcc,0x0F,0x0D,0x0B,0x09,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00); 
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x0b0d0fcc;  
        data_array[2] = 0x00010309;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);

	 //SSD2825_Gen_write_1A_1P(0x00,0xc0);             //panel pad mapping control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000c000;                 
        dsi_set_cmdq(data_array, 2, 1);

	 //SSD2825_Gen_write_1A_15P(0xcc,0x00,0x00,0x00,0x00,0x00,0x2d,0x2e,0x10,0x0E,0x0C,0x0A,0x04,0x02,0x00,0x00); 
	data_array[0] = 0x00103902;                          
        data_array[1] = 0x000000cc;  
        data_array[2] = 0x2e2d0000;  
        data_array[3] = 0x0a0c0e10;  
        data_array[4] = 0x00000204;                 
        dsi_set_cmdq(data_array, 5, 1);

	 //SSD2825_Gen_write_1A_1P(0x00,0xd0);             //panel pad mapping control
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000d000;                 
        dsi_set_cmdq(data_array, 2, 1);

	 //SSD2825_Gen_write_1A_14P(0xcc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2d,0x2e); 
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cc;  
        data_array[2] = 0x00000000;  
        data_array[3] = 0x00000000;  
        data_array[4] = 0x002e2d00;                 
        dsi_set_cmdq(data_array, 5, 1);


//-------------------- panel timing setting --------------------//
	//SSD2825_Gen_write_1A_1P(0x00,0x80);             //panel VST setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008000;                 
        dsi_set_cmdq(data_array, 2, 1); 

	//SSD2825_Gen_write_1A_12P(0xce,0x8d,0x03,0x00,0x8c,0x03,0x00,0x8b,0x03,0x00,0x8a,0x03,0x00);
	data_array[0] = 0x000d3902;                          
        data_array[1] = 0x00038dce; 
        data_array[2] = 0x8b00038c;
        data_array[3] = 0x038a0003;
        data_array[4] = 0x00000000;                
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xa0);             //panel CLKA1/2 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xce,0x38,0x0b,0x04,0xfc,0x00,0x10,0x10,0x38,0x0a,0x04,0xfd,0x00,0x10,0x10);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x040b38ce; 
        data_array[2] = 0x101000fc;
        data_array[3] = 0xfd040a38;
        data_array[4] = 0x00101000;                
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb0);             //panel CLKA3/4 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b000;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_14P(0xce,0x38,0x09,0x04,0xfe,0x00,0x10,0x10,0x38,0x08,0x04,0xff,0x00,0x10,0x10);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x040938ce;  
        data_array[2] = 0x101000fe; 
        data_array[3] = 0xff040838; 
        data_array[4] = 0x00101000;                
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xc0);             //panel CLKb1/2 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000c000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xce,0x38,0x07,0x05,0x00,0x00,0x10,0x10,0x38,0x06,0x05,0x01,0x00,0x10,0x10);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x050738ce;   
        data_array[2] = 0x10100000; 
        data_array[3] = 0x01050638; 
        data_array[4] = 0x00101000;               
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xd0);             //panel CLKb3/4 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000d000;                 
        dsi_set_cmdq(data_array, 2, 1);
		
	//SSD2825_Gen_write_1A_14P(0xce,0x38,0x05,0x05,0x02,0x00,0x10,0x10,0x38,0x04,0x05,0x03,0x00,0x10,0x10);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x050538ce;
        data_array[2] = 0x10100002; 
        data_array[3] = 0x03050438; 
        data_array[4] = 0x00101000;                  
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x80);             //panel CLKc1/2 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00008000;                 
        dsi_set_cmdq(data_array, 2, 1);


	//SSD2825_Gen_write_1A_14P(0xcf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cf; 
        data_array[2] = 0x00000000;
        data_array[3] = 0x00000000;
        data_array[4] = 0x00000000;                
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x90);             //panel CLKc3/4 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xcf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cf;   
        data_array[2] = 0x00000000;
        data_array[3] = 0x00000000;
        data_array[4] = 0x00000000;              
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xa0);             //panel CLKd1/2 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xcf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cf; 
        data_array[2] = 0x00000000; 
        data_array[3] = 0x00000000; 
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);

#if 1
        data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000a400;                    //c1a0  -->02 huxh
        dsi_set_cmdq(data_array, 2, 1);

        data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000ffc1;                 
        dsi_set_cmdq(data_array, 2, 1);

        //Samsung_Gen_write_1A_1P(0x00,0xb2);             //power on clock switch
        //Samsung_Gen_write_1A_1P(0xc4,0x81);
        data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b200;                 
        dsi_set_cmdq(data_array, 2, 1);

        data_array[0] = 0x00023902;
        data_array[1] = 0x000081c4;
        dsi_set_cmdq(data_array, 2, 1);
		
        //Samsung_Gen_write_1A_1P(0x00,0x93);             //17MHz /
        //Samsung_Gen_write_1A_1P(0xc1,0x90);
        data_array[0] = 0x00023902;                          
        data_array[1] = 0x00009300;                 
        dsi_set_cmdq(data_array, 2, 1);

        data_array[0] = 0x00023902;                          
        data_array[1] = 0x000090c1;                 
        dsi_set_cmdq(data_array, 2, 1);
		
        //Samsung_Gen_write_1A_1P(0x00,0xb5);             //17MHz /
        //Samsung_Gen_write_1A_1P(0xc4,0x80);
        data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b500;                 
        dsi_set_cmdq(data_array, 2, 1);

        data_array[0] = 0x00023902;                          
        data_array[1] = 0x000080c4;                 
        dsi_set_cmdq(data_array, 2, 1);		
#endif



	//SSD2825_Gen_write_1A_1P(0x00,0xb0);             //panel CLKd3/4 setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b000;
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_14P(0xcf,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	data_array[0] = 0x000f3902;                          
        data_array[1] = 0x000000cf; 
        data_array[2] = 0x00000000; 
        data_array[3] = 0x00000000; 
        data_array[4] = 0x00000000;                 
        dsi_set_cmdq(data_array, 5, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xc0);             //panel ECLK setting, gate pre. ena.
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000c000;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_11P(0xcf,0x01,0x01,0x20,0x20,0x00,0x00,0x01,0x02,0x00,0x00,0x08);
	data_array[0] = 0x000c3902;                          
        data_array[1] = 0x200101cf;  
        data_array[2] = 0x01000020; 
        data_array[3] = 0x08000002;                
        dsi_set_cmdq(data_array, 4, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0xb5);             //TCON_GOA_OUT Setting
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x0000b500;                 
        dsi_set_cmdq(data_array, 2, 1);

	//SSD2825_Gen_write_1A_6P(0xc5,0x33,0xf1,0xff,0x33,0xf1,0xff);  //normal output with VGH/VGL
	data_array[0] = 0x00073902;                          
        data_array[1] = 0xfff133c5;  
        data_array[2] = 0x00fff133;                
        dsi_set_cmdq(data_array, 3, 1);

	//SSD2825_Gen_write_1A_1P(0x00,0x00);
	data_array[0] = 0x00023902;                          
        data_array[1] = 0x00000000;                 
        dsi_set_cmdq(data_array, 2, 1);
           
	//SSD2825_Gen_write_1A_3P(0xFF,0xFF,0xFF,0xFF);
	data_array[0] = 0x00043902;                          
        data_array[1] = 0xffffffff;                 
        dsi_set_cmdq(data_array, 2, 1);

	data_array[0] = 0x00351500; // TE
	dsi_set_cmdq(&data_array, 1, 1);

	
	data_array[0] = 0x00110500; // Sleep In
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(120);

	data_array[0] = 0x00290500; // Sleep In
	dsi_set_cmdq(&data_array, 1, 1);
	MDELAY(20);
}


// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{
		memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

       //1 SSD2075 has no TE Pin
		// enable tearing-free
		params->dbi.te_mode 				= LCM_DBI_TE_MODE_DISABLED;
		params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;

        #if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
        #else
		//params->dsi.mode   = SYNC_PULSE_VDO_MODE;
		params->dsi.mode   = BURST_VDO_MODE;
		//params->dsi.mode   = SYNC_EVENT_VDO_MODE; 
		
        #endif
	
		// DSI
		/* Command mode setting */
		//1 Three lane or Four lane
		params->dsi.LANE_NUM				= LCM_FOUR_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Highly depends on LCD driver capability.
		// Not support in MT6573
		params->dsi.packet_size=256;

		// Video mode setting		
		params->dsi.intermediat_buffer_num = 0;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		params->dsi.word_count=720*3;	

		params->dsi.vertical_sync_active				= 4;  //---3
		params->dsi.vertical_backporch					= 20; //---14
		params->dsi.vertical_frontporch					= 20;  //----8
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 

		params->dsi.horizontal_sync_active				= 10;		// 2;  //----2
		params->dsi.horizontal_backporch				= 150;			// 28; //----28
		params->dsi.horizontal_frontporch				= 150;			// 50; //----50
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;
		
#if 0
		params->dsi.vertical_sync_active				= 3;  //---3
		params->dsi.vertical_backporch					= 12; //---14
		params->dsi.vertical_frontporch					= 2;  //----8
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 

		params->dsi.horizontal_sync_active				= 26;		// 2;  //----2
		params->dsi.horizontal_backporch				= 146;			// 28; //----28
		params->dsi.horizontal_frontporch				= 146;			// 50; //----50
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;
#endif

        //	params->dsi.HS_PRPR=6;
	    params->dsi.LPX=8; 
		//params->dsi.HS_PRPR=5;
		//params->dsi.HS_TRAIL=13;

		// Bit rate calculation
		//1 Every lane speed
		params->dsi.pll_div1=	0;		// div1=0,1,2,3;div1_real=1,2,4,4 ----0: 546Mbps  1:273Mbps
		params->dsi.pll_div2=	1;		// div2=0,1,2,3;div1_real=1,2,4,4	
		params->dsi.fbk_div =	19;		//19;    // fref=26MHz, fvco=fref*(fbk_div+1)*2/(div1_real*div2_real)	
}

static void lcm_init(void)
{

	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(20);      

	init_lcm_registers();

}



static void lcm_suspend(void)
{
	unsigned int data_array[16];

	data_array[0] = 0x00100500; // Sleep In
	dsi_set_cmdq(&data_array, 1, 1);

	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(200);

}

static void lcm_resume(void)
{
   //1 do lcm init again to solve some display issue

	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(20);      

	init_lcm_registers();

}
         
#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);

	data_array[0]= 0x00290508; //HW bug, so need send one HS packet
	dsi_set_cmdq(&data_array, 1, 1);
	
	data_array[0]= 0x002c3909;
	dsi_set_cmdq(&data_array, 1, 0);

}
#endif

static unsigned int lcm_compare_id(void)
{
	unsigned int id0,id1,id=0;
	unsigned char buffer[2];
	unsigned int array[16];  
	return 1;
}

#if 1
static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_LK
	char  buffer[3];
	char  buffer1[3];
	char  buffer2[3];	
	char  buffer3[3];	
	int   array[4];

	if(lcm_esd_test)
	{
		lcm_esd_test = FALSE;
		return TRUE;
	}

	/// please notice: the max return packet size is 1
	/// if you want to change it, you can refer to the following marked code
	/// but read_reg currently only support read no more than 4 bytes....
	/// if you need to read more, please let BinHan knows.
	/*
			unsigned int data_array[16];
			unsigned int max_return_size = 1;
			
			data_array[0]= 0x00003700 | (max_return_size << 16);	
			
			dsi_set_cmdq(&data_array, 1, 1);
	*/

	array[0] = 0x00013708;
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0x0a, buffer, 1);
	
	array[0] = 0x00013708;
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0x0d, buffer1, 1);

	array[0] = 0x00013708;
	dsi_set_cmdq(array, 1, 1);
	read_reg_v2(0x0e, buffer2, 1);

	//array[0] = 0x00013708;
	//dsi_set_cmdq(array, 1, 1);
	//read_reg_v2(0x0b, buffer3, 1);
	//printk("%s, Kernel otm1083a  id0 = 0x%08x\n", __func__, buffer3[0]);
	
	printk("%s, Kernel otm1083a  id0 = 0x%08x  id1 = 0x%08x  id2 = 0x%08x\n", __func__, buffer[0], buffer1[0], buffer2[0]);	
	
	if(buffer[0]==0x9c && buffer1[0]==0x00 && buffer2[0] == 0x81)
	{
		return FALSE;
	}
	else
	{			 
		return TRUE;
	}
#endif

}

static unsigned int lcm_esd_recover(void)
{
	//lcm_init();
	#ifndef BUILD_LK
	//printk("%s, Kernel lcm_esd_recover\n", __func__);	
	#endif
	lcm_resume();

	return TRUE;
}
#endif

LCM_DRIVER otm1083a_dsi_vdo_lcm_drv = 
{
    .name			= "otm1083a_dsi_vdo",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id    = lcm_compare_id,
	.esd_check = lcm_esd_check,
	.esd_recover = lcm_esd_recover,
    #if (LCM_DSI_CMD_MODE)
    .update         = lcm_update,
    #endif
    };
