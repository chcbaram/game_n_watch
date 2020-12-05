/*
 * battery.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */




#include "battery.h"
#include "adc.h"
#include "gpio.h"



#define BAT_ADC_MAX_COUNT     50


static int32_t bat_level = 0;
static int32_t bat_vol;
static uint8_t  adc_ch = 0;
static uint32_t bat_max = 410;
static uint32_t bat_min = 310;

static uint32_t adc_data[BAT_ADC_MAX_COUNT];


bool batteryInit(void)
{
  uint32_t i;

  for (i=0; i<BAT_ADC_MAX_COUNT; i++)
  {
    adc_data[i] = 0;
  }

  return true;
}

void batteryUpdate(void)
{
  static uint32_t pre_time;
  static uint32_t index = 0;
  static uint32_t last_level = 0;
  static bool is_started = false;
  uint32_t i;
  int32_t sum;
  int32_t value = 0;
  int32_t vol = 0;


  if (millis()-pre_time >= 10 && is_started == false)
  {
    pre_time = millis();


    if (is_started == false)
    {
      for (int i=0; i<BAT_ADC_MAX_COUNT; i++)
      {
        adc_data[index] = adcReadVoltage(adc_ch);
        index = (index + 1) % BAT_ADC_MAX_COUNT;
      }
      is_started = true;
    }
    else
    {
      adc_data[index] = adcReadVoltage(adc_ch);
      index = (index + 1) % BAT_ADC_MAX_COUNT;
    }


    sum = 0;
    for (i=0; i<BAT_ADC_MAX_COUNT; i++)
    {
      sum += adc_data[i];
    }

    bat_vol = sum/BAT_ADC_MAX_COUNT;
    vol   = constrain(bat_vol, bat_min, bat_max);

    value = map(vol, bat_min, bat_max, 0, 100);

    if (abs(value-last_level) > 5 || value == 100)
    {
      bat_level = value;
      last_level = value;
    }
  }
}

int32_t batteryGetLevel(void)
{
  return bat_level;
}

int32_t batteryGetVoltage(void)
{
  return bat_vol;
}

bool batteryIsCharging(void)
{
  if (gpioPinRead(4) == _DEF_HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

