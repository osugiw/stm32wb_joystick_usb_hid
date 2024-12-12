/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/USB_Device/App/usb_device.c
  * @author  MCD Application Team
  * @brief   This file implements the USB Device
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"

/* USER CODE BEGIN Includes */
#include "main.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
__IO uint32_t remotewakeupon = 0;
extern PCD_HandleTypeDef hpcd_USB_FS;
uint8_t HID_Buffer[4];
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
extern void SystemClockConfig_Resume(void);
void USBD_Clock_Config(void);
void GetPointerData(uint8_t *pbuf, joystick_dir _dir);
/* USER CODE END PFP */

extern void Error_Handler(void);
/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;
extern USBD_DescriptorsTypeDef HID_Desc;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */
/**
  * @brief USB Clock Configuration
  * @retval None
  */
void USBD_Clock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_CRSInitTypeDef RCC_CRSInitStruct= {0};

  /* Enable HSI48 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }
  /*Configure the clock recovery system (CRS)**********************************/

  /*Enable CRS Clock*/
  __HAL_RCC_CRS_CLK_ENABLE();

  /* Default Synchro Signal division factor (not divided) */
  RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;

  /* Set the SYNCSRC[1:0] bits according to CRS_Source value */
  RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;

  /* HSI48 is synchronized with USB SOF at 1KHz rate */
  RCC_CRSInitStruct.ReloadValue =  __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;

  /* Set the TRIM[5:0] to the default value */
  RCC_CRSInitStruct.HSI48CalibrationValue = RCC_CRS_HSI48CALIBRATION_DEFAULT;

  /* Start automatic synchronization */
  HAL_RCCEx_CRSConfig (&RCC_CRSInitStruct);
}
/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/**
  * @brief  Gets Pointer Data X
  * @param  pbuf: Pointer to report
  * @retval None
  */
void GetPointerData(uint8_t * pbuf, joystick_dir _dir)
{
  int8_t x = 0, y = 0;

  if (_dir == JOYSTICK_RIGHT){
	  x = +CURSOR_STEP;
  }
  else if(_dir == JOYSTICK_LEFT){
	  x = -CURSOR_STEP;
  }
  else if (_dir == JOYSTICK_UP){
	  y = -CURSOR_STEP;
  }
  else if (_dir == JOYSTICK_DOWN){
	  y = +CURSOR_STEP;
  }
  else if (_dir == JOYSTICK_UP_LEFT){
	  x = -CURSOR_STEP;
	  y = -CURSOR_STEP;
  }
  else if (_dir == JOYSTICK_DOWN_LEFT){
  	  x = -CURSOR_STEP;
  	  y = +CURSOR_STEP;
  }
  else if (_dir == JOYSTICK_UP_RIGHT){
  	  x = +CURSOR_STEP;
  	  y = -CURSOR_STEP;
  }
  else if (_dir == JOYSTICK_DOWN_RIGHT){
  	  x = +CURSOR_STEP;
  	  y = +CURSOR_STEP;
  }


  pbuf[0] = 0;
  pbuf[1] = x;
  pbuf[2] = y;
  pbuf[3] = 0;
}

/**
  * @brief  Joystick control Function
  *         Handle joystick ADC input to control the mouse through USB Device
  * @param  None
  * @retval None
  */
void JoystickControl(void)
{
	if ((((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_remote_wakeup == 1) && (((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_state == USBD_STATE_SUSPENDED))
	{
		if ((&hpcd_USB_FS)->Init.low_power_enable)
		{
			HAL_ResumeTick();
			SystemClockConfig_Resume();
		}
		/* Activate Remote wakeup */
		HAL_PCD_ActivateRemoteWakeup((&hpcd_USB_FS));

		/* Remote wakeup delay */
		HAL_Delay(10);

		/* Disable Remote wakeup */
		HAL_PCD_DeActivateRemoteWakeup((&hpcd_USB_FS));

		/* change state to configured */
		((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_state = USBD_STATE_CONFIGURED;

		/* Change remote_wakeup feature to 0 */
		((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_remote_wakeup = 0;
		remotewakeupon = 1;
	}
	else if (((USBD_HandleTypeDef *) hpcd_USB_FS.pData)->dev_state == USBD_STATE_CONFIGURED){
		// Vertical
		if(joystick_X >= THR_MOVE_1AXIS_MIN && joystick_X <= THR_MOVE_1AXIS_MAX){
		  // Up
		  if (joystick_Y < THR_MOVE_UP)
		  {
			  flagDir = JOYSTICK_UP;
			  GetPointerData(HID_Buffer, JOYSTICK_UP);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		  // Down
		  else if (joystick_Y > THR_MOVE_DOWN)
		  {
			  flagDir = JOYSTICK_DOWN;
			  GetPointerData(HID_Buffer, JOYSTICK_DOWN);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		}

		// Horizontal
		if(joystick_Y >= THR_MOVE_1AXIS_MIN && joystick_Y <= THR_MOVE_1AXIS_MAX)
		{
		  // Left
		  if (joystick_X < THR_MOVE_LEFT)
		  {
			  flagDir = JOYSTICK_LEFT;
			  GetPointerData(HID_Buffer, JOYSTICK_LEFT);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		  // Right
		  else if (joystick_X > THR_MOVE_RIGHT)
		  {
			  flagDir = JOYSTICK_RIGHT;
			  GetPointerData(HID_Buffer, JOYSTICK_RIGHT);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		}

		// Quadrant 1 and 4
		if(joystick_X >= THR_MOVE_Q14_X){
		  // Up-right
		  if(joystick_Y <= THR_MOVE_Q1_Y){
			  flagDir = JOYSTICK_UP_RIGHT;
			  GetPointerData(HID_Buffer, JOYSTICK_UP_RIGHT);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		  // Down-right
		  else if(joystick_Y >= THR_MOVE_Q4_Y){
			  flagDir = JOYSTICK_DOWN_RIGHT;
			  GetPointerData(HID_Buffer, JOYSTICK_DOWN_RIGHT);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		}

		// Quadrant 2 and 3
		if(joystick_X <= THR_MOVE_Q23_X){
		  // Up-left
		  if(joystick_Y <= THR_MOVE_Q2_Y){
			  flagDir = JOYSTICK_UP_LEFT;
			  GetPointerData(HID_Buffer, JOYSTICK_UP_LEFT);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		  // Down-left
		  else if(joystick_Y >= THR_MOVE_Q3_Y){
			  flagDir = JOYSTICK_DOWN_LEFT;
			  GetPointerData(HID_Buffer, JOYSTICK_DOWN_LEFT);
			  USBD_HID_SendReport(&hUsbDeviceFS, HID_Buffer, 4);
		  }
		}
	}
}

/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void MX_USB_Device_Init(void)
{
  /* USER CODE BEGIN USB_Device_Init_PreTreatment */
  /* USB Clock Initialization */
   USBD_Clock_Config();
  /* USER CODE END USB_Device_Init_PreTreatment */

  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &HID_Desc, DEVICE_FS) != USBD_OK) {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_HID) != USBD_OK) {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Device_Init_PostTreatment */

  /* USER CODE END USB_Device_Init_PostTreatment */
}

/**
  * @}
  */

/**
  * @}
  */

