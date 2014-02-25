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

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_ov8827raw.h"
#include "camera_info_ov8827raw.h"
#include "camera_custom_AEPlinetable.h"

const NVRAM_CAMERA_ISP_PARAM_STRUCT CAMERA_ISP_DEFAULT_VALUE =
{{
    //Version
    Version: NVRAM_CAMERA_PARA_FILE_VERSION,

    //SensorId
    SensorId: SENSOR_ID,
    ISPComm:{
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    	}
    },
    ISPPca: {
        #include INCLUDE_FILENAME_ISP_PCA_PARAM
    },
    ISPRegs:{
        #include INCLUDE_FILENAME_ISP_REGS_PARAM
    },
    ISPMfbMixer:{{
        {//00: MFB mixer for ISO 100
            0x00000000, 0x00000000
        },
        {//01: MFB mixer for ISO 200
            0x00000000, 0x00000000
        },
        {//02: MFB mixer for ISO 400
            0x00000000, 0x00000000
        },
        {//03: MFB mixer for ISO 800
            0x00000000, 0x00000000
        },
        {//04: MFB mixer for ISO 1600
            0x00000000, 0x00000000
        },
        {//05: MFB mixer for ISO 2400
            0x00000000, 0x00000000
        },
        {//06: MFB mixer for ISO 3200
            0x00000000, 0x00000000
    }
    }},
    ISPCcmPoly22:{
        72050, // i4R_AVG
        14181, // i4R_STD
        91475, // i4B_AVG
        23921, // i4B_STD
        { // i4P00[9]
          4767500,   -1717500,   -490000,   -675000,   3250000,   -15000 ,  42500,  -2067500, 4585000
        },
        { // i4P10[9]
            -383533,  440317,     -56784,  43170 ,     98401,  -141572,    -110628,     776268,   -665640
        },
        { // i4P01[9]
            -745882 ,  843085 ,  -97203 ,  -80028,  33383,    46645 ,    -179947,  211280,   -31332
        },
        { // i4P20[9]
            0,  -0,   0,  -0,   0,  -0, 0,  -0,  0
        },
        { // i4P11[9]
                     0,  -0,   0,  -0,   0,  -0, 0,  -0,  0
        },
        { // i4P02[9]
                     0,  -0,   0,  -0,   0,  -0, 0,  -0,  0
        }        
    }
}};

const NVRAM_CAMERA_3A_STRUCT CAMERA_3A_NVRAM_DEFAULT_VALUE =
{
    NVRAM_CAMERA_3A_FILE_VERSION, // u4Version
    SENSOR_ID, // SensorId

    // AE NVRAM
    {
        // rDevicesInfo
        {
            1144,   // u4MinGain, 1024 base =  1x
            10240,  // u4MaxGain, 16x
            100,     // u4MiniISOGain, ISOxx
            128,    // u4GainStepUnit, 1x/8
            26355,     // u4PreExpUnit
            30,     // u4PreMaxFrameRate
            17763,     // u4VideoExpUnit
            30,     // u4VideoMaxFrameRate
            512,   // u4Video2PreRatio, 1024 base = 1x
            17763,     // u4CapExpUnit
            23,     // u4CapMaxFrameRate
            512,   // u4Cap2PreRatio, 1024 base = 1x
            24,      // u4LensFno, Fno = 2.8
            350     // u4FocusLength_100x
         },
         // rHistConfig
        {
            2,   // u4HistHighThres
            40,  // u4HistLowThres
            2,   // u4MostBrightRatio
            1,   // u4MostDarkRatio
            160, // u4CentralHighBound
            20,  // u4CentralLowBound
            {240, 230, 220, 210, 200}, // u4OverExpThres[AE_CCT_STRENGTH_NUM]
            {75, 108, 128, 148, 170},  // u4HistStretchThres[AE_CCT_STRENGTH_NUM]
            {18, 22, 26, 30, 34}       // u4BlackLightThres[AE_CCT_STRENGTH_NUM]
        },
        // rCCTConfig
        {
            TRUE,            // bEnableBlackLight
            TRUE,            // bEnableHistStretch
            FALSE,           // bEnableAntiOverExposure
            TRUE,            // bEnableTimeLPF
            FALSE,            // bEnableCaptureThres
            FALSE,            // bEnableVideoThres
            FALSE,            // bEnableStrobeThres
            47,                // u4AETarget
            47,                // u4StrobeAETarget

            50,                // u4InitIndex
            4,                 // u4BackLightWeight
            5,                // u4HistStretchWeight
            4,                 // u4AntiOverExpWeight
            2,                 // u4BlackLightStrengthIndex
            2,                 // u4HistStretchStrengthIndex
            2,                 // u4AntiOverExpStrengthIndex
            2,                 // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8}, // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM]
            90,                // u4InDoorEV = 9.0, 10 base
            0,               // i4BVOffset delta BV = -2.3
            64,    // u4PreviewFlareOffset
            64,    // u4CaptureFlareOffset
            5,                 // u4CaptureFlareThres
            64,                 // u4VideoFlareOffset 
            5,                 // u4VideoFlareThres
            64,                 // u4StrobeFlareOffset
            2,                 // u4StrobeFlareThres
            160,    // u4PrvMaxFlareThres
            0,                 // u4PrvMinFlareThres
            160,    // u4VideoMaxFlareThres
            0,                 // u4VideoMinFlareThres            
            18,                // u4FlatnessThres              // 10 base for flatness condition.
            66                 // u4FlatnessStrength
         } 
    },

    // AWB NVRAM
    {
    	// AWB calibration data
    	{
    		// rUnitGain (unit gain: 1.0 = 512)
    		{
    			0,	// i4R
    			0,	// i4G
    			0	// i4B
    		},
    		// rGoldenGain (golden sample gain: 1.0 = 512)
    		{
	            0,	// i4R
	            0,	// i4G
	            0	// i4B
            },
    		// rTuningUnitGain (Tuning sample unit gain: 1.0 = 512)
    		{
	            0,	// i4R
	            0,	// i4G
	            0	// i4B
            },
            // rD65Gain (D65 WB gain: 1.0 = 512)
            {
                870,    // i4R
                512,    // i4G
                583    // i4B
            }
    	},
    	// Original XY coordinate of AWB light source
    	{
           // Strobe
            {
                60,    // i4X
                -336    // i4Y
            },
            // Horizon
            {
                -354,    // i4X
                -324    // i4Y
            },
            // A
            {
                -242,    // i4X
                -316    // i4Y
            },
            // TL84
            {
                -120,    // i4X
                -322    // i4Y
            },
            // CWF
            {
                -79,    // i4X
                -394    // i4Y
            },
            // DNP
            {
                22,    // i4X
                -293    // i4Y
            },
            // D65
            {
                148,    // i4X
                -244    // i4Y
    		},
		// DF
		{
                94,    // i4X
                -340    // i4Y
    		}
    	},
    	// Rotated XY coordinate of AWB light source
    	{
		    // Strobe
		    {
                -5,    // i4X
                -341    // i4Y
            },
            // Horizon
            {
                -409,    // i4X
                -250    // i4Y
            },
            // A
            {
                -298,    // i4X
                -264    // i4Y
            },
            // TL84
            {
                -179,    // i4X
                -293    // i4Y
            },
            // CWF
            {
                -153,    // i4X
                -371    // i4Y
            },
            // DNP
            {
                -35,    // i4X
                -291    // i4Y
            },
            // D65
            {
                98,    // i4X
                -268    // i4Y
            },
		// DF
		{
                27,    // i4X
                -351    // i4Y
    		}
    	},
	// AWB gain of AWB light source
	{
            // Strobe 
            {
                874,    // i4R
                512,    // i4G
                744    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                534,    // i4G
                1337    // i4B
            },
            // A 
            {
                566,    // i4R
                512,    // i4G
                1091    // i4B
            },
            // TL84 
            {
                673,    // i4R
                512,    // i4G
                932    // i4B
            },
            // CWF 
            {
                785,    // i4R
                512,    // i4G
                971    // i4B
            },
            // DNP 
            {
                784,    // i4R
                512,    // i4G
                739    // i4B
            },
            // D65 
            {
                870,    // i4R
                512,    // i4G
                583    // i4B
		},
		// DF
		{
                922,    // i4R
                512,    // i4G
                714    // i4B
		}
	},
    	// Rotation matrix parameter
    	{
            11,    // i4RotationAngle
            251,    // i4Cos
            49    // i4Sin
        },
    	// Daylight locus parameter
    	{
            -186,    // i4SlopeNumerator
    		128	// i4SlopeDenominator
    	},
    	// AWB light area
    	{
		    // Strobe:FIXME
		    {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
		    },
    		// Tungsten
    		{
            -200,    // i4RightBound
            -1000,    // i4LeftBound
            -180,    // i4UpperBound
            -307    // i4LowerBound
    		},
    		// Warm fluorescent
    		{
            -200,    // i4RightBound
            -1000,    // i4LeftBound
            -307,    // i4UpperBound
            -427    // i4LowerBound
    		},
    		// Fluorescent
    		{
            -95,    // i4RightBound
            -200,    // i4LeftBound
            -197,    // i4UpperBound
            -332    // i4LowerBound
            },
            // CWF
            {
            -95,    // i4RightBound
            -200,    // i4LeftBound
            -332,    // i4UpperBound
            -421    // i4LowerBound
            },
            // Daylight
            {
            123,    // i4RightBound
            -95,    // i4LeftBound
            -188,    // i4UpperBound
            -338    // i4LowerBound
            },
            // Shade
            {
            483,    // i4RightBound
            123,    // i4LeftBound
            -188,    // i4UpperBound
            -348    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            123,    // i4RightBound
            -95,    // i4LeftBound
            -338,    // i4UpperBound
            -421    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            483,    // i4RightBound
            -879,    // i4LeftBound
            0,    // i4UpperBound
            -427    // i4LowerBound
            },
            // Daylight
            {
            148,    // i4RightBound
            -95,    // i4LeftBound
            -188,    // i4UpperBound
            -338    // i4LowerBound
            },
            // Cloudy daylight
            {
            248,    // i4RightBound
            73,    // i4LeftBound
            -188,    // i4UpperBound
            -338    // i4LowerBound
            },
            // Shade
            {
            348,    // i4RightBound
            73,    // i4LeftBound
            -188,    // i4UpperBound
            -338    // i4LowerBound
            },
            // Twilight
            {
            -95,    // i4RightBound
            -245,    // i4LeftBound
            -188,    // i4UpperBound
            -338    // i4LowerBound
            },
            // Fluorescent
            {
            148,    // i4RightBound
            -279,    // i4LeftBound
            -218,    // i4UpperBound
            -421    // i4LowerBound
            },
            // Warm fluorescent
            {
            -198,    // i4RightBound
            -398,    // i4LeftBound
            -218,    // i4UpperBound
            -421    // i4LowerBound
            },
            // Incandescent
            {
            -198,    // i4RightBound
            -398,    // i4LeftBound
            -188,    // i4UpperBound
            -338    // i4LowerBound
            },
            // Gray World
            {
            5000,    // i4RightBound
            -5000,    // i4LeftBound
            5000,    // i4UpperBound
            -5000    // i4LowerBound
		    }
    	},
        // PWB default gain	
        {
            // Daylight
            {
            804,    // i4R
            512,    // i4G
            645    // i4B
            },
            // Cloudy daylight
            {
            924,    // i4R
            512,    // i4G
            526    // i4B
            },
            // Shade
            {
            974,    // i4R
            512,    // i4G
            486    // i4B
            },
            // Twilight
            {
            652,    // i4R
            512,    // i4G
            882    // i4B
            },
            // Fluorescent
            {
            793,    // i4R
            512,    // i4G
            800    // i4B
            },
            // Warm fluorescent
            {
            618,    // i4R
            512,    // i4G
            1158    // i4B
            },
            // Incandescent
            {
            565,    // i4R
            512,    // i4G
            1090    // i4B
            },
            // Gray World
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        // AWB preference color	
        {
            // Tungsten
            {
            0,    // i4SliderValue
            6126    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            0,    // i4SliderValue
            5532    // i4OffsetThr
            },
            // Shade
            {
            0,    // i4SliderValue
            1346    // i4OffsetThr
            },
            // Daylight WB gain
            {
            755,    // i4R
            512,    // i4G
            721    // i4B
		},
		// Preference gain: strobe
		{
			512,	// i4R
			512,	// i4G
			512	// i4B
		},
		// Preference gain: tungsten
		{
            500,    // i4R
            512,    // i4G
            512    // i4B
		},
		// Preference gain: warm fluorescent
		{
            512,    // i4R
            512,    // i4G
            512    // i4B
		},
		// Preference gain: fluorescent
		{
            512,    // i4R
            512,    // i4G
            512    // i4B
		},
		// Preference gain: CWF
		{
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
		},
		// Preference gain: shade
		{
			512,	// i4R
			512,	// i4G
			512	    // i4B
		},
		// Preference gain: daylight fluorescent
		{
			512,	// i4R
			512,	// i4G
			512	    // i4B
    		}
    	},
        {// CCT estimation
            {// CCT
			    2300,	// i4CCT[0]
    			2850,	// i4CCT[1]
    			4100,	// i4CCT[2]
    			5100,	// i4CCT[3]
    			6500	// i4CCT[4]
    		},
            {// Rotated X coordinate
                -507,    // i4RotatedXCoordinate[0]
                -396,    // i4RotatedXCoordinate[1]
                -277,    // i4RotatedXCoordinate[2]
                -133,    // i4RotatedXCoordinate[3]
    			0	// i4RotatedXCoordinate[4]
    		}
    	}
    },
	{0}
};

#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;


namespace NSFeature {
template <>
UINT32
SensorInfoSingleton_T::
impGetDefaultData(CAMERA_DATA_TYPE_ENUM const CameraDataType, VOID*const pDataBuf, UINT32 const size) const
{
    UINT32 dataSize[CAMERA_DATA_TYPE_NUM] = {sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT),
                                             sizeof(NVRAM_CAMERA_3A_STRUCT),
                                             sizeof(NVRAM_CAMERA_SHADING_STRUCT),
                                             sizeof(NVRAM_LENS_PARA_STRUCT),
                                             sizeof(AE_PLINETABLE_T)};

    if (CameraDataType > CAMERA_DATA_AE_PLINETABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
    {
        return 1;
    }

    switch(CameraDataType)
    {
        case CAMERA_NVRAM_DATA_ISP:
            memcpy(pDataBuf,&CAMERA_ISP_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_3A:
            memcpy(pDataBuf,&CAMERA_3A_NVRAM_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_3A_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_SHADING:
            memcpy(pDataBuf,&CAMERA_SHADING_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_SHADING_STRUCT));
            break;
        case CAMERA_DATA_AE_PLINETABLE:
            memcpy(pDataBuf,&g_PlineTableMapping,sizeof(AE_PLINETABLE_T));
            break;
        default:
            break;
    }
    return 0;
}};  //  NSFeature


