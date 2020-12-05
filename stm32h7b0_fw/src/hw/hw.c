/*
 * hw.c
 *
 *  Created on: Nov 21, 2020
 *      Author: baram
 */




#include "hw.h"





void hwInit(void)
{
  bspInit();

  swtimerInit();
  ledInit();
  buttonInit();
  gpioInit();
  spiInit();
  lcdInit();
  pwrInit();
}
