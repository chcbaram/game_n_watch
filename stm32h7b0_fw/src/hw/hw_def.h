/*
 * hw_def.h
 *
 *  Created on: Nov 21, 2020
 *      Author: baram
 */

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"







#define _USE_HW_LED
#define      HW_LED_MAX_CH          3

#define _USE_HW_GPIO
#define      HW_GPIO_MAX_CH         4

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       10

#define _USE_HW_SWTIMER
#define      HW_SWTIMER_MAX_CH      8

#define _USE_HW_LCD
#define _USE_HW_LTDC
#define      HW_LCD_WIDTH           320
#define      HW_LCD_HEIGHT          240

#define _USE_HW_SPI
#define      HW_SPI_MAX_CH          1



#endif /* SRC_HW_HW_DEF_H_ */
