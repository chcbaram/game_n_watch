/*
 * pwr.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */




#include "pwr.h"
#include "lcd.h"
#include "button.h"



bool pwrInit(void)
{
  uint32_t pre_time;

  pre_time = millis();
  while(millis()-pre_time < 500)
  {
    if (buttonGetPressed(_DEF_HW_BTN_POWER) != true)
    {
      break;
    }
  }

  return true;
}

void pwrEnterDeepSleep(void)
{
  // Enable wakup by PIN1, the power button
  HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1_LOW);

  lcdDeInit();

  delay(500);

  HAL_PWR_EnterSTANDBYMode();

  HAL_NVIC_SystemReset();

  // Execution stops here, this function will not return
  while(1)
  {
    __NOP();
  }
}

bool pwrUpdate(void)
{
  if (buttonGetRepeatCount(_DEF_HW_BTN_POWER) == 1)
  {
    pwrEnterDeepSleep();
  }

  return true;
}
