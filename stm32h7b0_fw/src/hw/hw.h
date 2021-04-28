/*
 * hw.h
 *
 *  Created on: Nov 21, 2020
 *      Author: baram
 */

#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "hw_def.h"

#include "swtimer.h"
#include "led.h"
#include "uart.h"
#include "button.h"
#include "gpio.h"
#include "spi.h"
#include "lcd.h"
#include "pwr.h"
#include "adc.h"
#include "battery.h"
#include "image.h"


void hwInit(void);


#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_HW_H_ */
