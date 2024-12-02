/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           USB_Device/HID_Standalone/USB_Device/App/usb_device.h
  * @author         MCD Application Team
  * @brief          Header for usb_device.c file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx.h"
#include "stm32wbxx_hal.h"
#include "usbd_def.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/** @addtogroup USBD_OTG_DRIVER
  * @{
  */

/** @defgroup USBD_DEVICE USBD_DEVICE
  * @brief Device file for Usb otg low level driver.
  * @{
  */

/** @defgroup USBD_DEVICE_Exported_Variables USBD_DEVICE_Exported_Variables
  * @brief Public variables.
  * @{
  */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
typedef enum{
	JOYSTICK_IDLE,
	JOYSTICK_UP,
	JOYSTICK_DOWN,
	JOYSTICK_LEFT,
	JOYSTICK_UP_LEFT,
	JOYSTICK_DOWN_LEFT,
	JOYSTICK_RIGHT,
	JOYSTICK_UP_RIGHT,
	JOYSTICK_DOWN_RIGHT,
} joyStick_dir;


/* USER CODE END PV */

// Mouse Cursor Step
#define CURSOR_STEP     2


// 1 Axis thresholds
#define THR_MOVE_1AXIS_MIN 	480
#define THR_MOVE_1AXIS_MAX 	500
#define THR_MOVE_UP			400
#define THR_MOVE_DOWN		600
#define THR_MOVE_RIGHT		THR_MOVE_DOWN
#define THR_MOVE_LEFT		THR_MOVE_UP

// Multiple Axis Thresholds
#define THR_MOVE_Q14_X		900
#define THR_MOVE_Q1_Y		100
#define THR_MOVE_Q4_Y		900
#define THR_MOVE_Q23_X		100
#define THR_MOVE_Q2_Y		THR_MOVE_Q1_Y
#define THR_MOVE_Q3_Y		THR_MOVE_Q4_Y
/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN VARIABLES */

/* USER CODE END VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_DEVICE_Exported_FunctionsPrototype USBD_DEVICE_Exported_FunctionsPrototype
  * @brief Declaration of public functions for Usb device.
  * @{
  */

/** USB Device initialization function. */
void MX_USB_Device_Init(void);

/*
 * -- Insert functions declaration here --
 */
/* USER CODE BEGIN FD */
void GetPointerData(uint8_t *pbuf, joyStick_dir _dir);
void JoystickControl(void);
/* USER CODE END FD */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE__H__ */

