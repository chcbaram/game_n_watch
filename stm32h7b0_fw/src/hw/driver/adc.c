/*
 * adc.c
 *
 *  Created on: Dec 6, 2020
 *      Author: baram
 */




#include "adc.h"
#include "gpio.h"
#ifdef _USE_HW_CMDIF
#include "cmdif.h"
#endif


typedef struct
{
  bool                    is_init;
  ADC_HandleTypeDef      *hADCx;
  uint32_t                adc_channel;
  uint16_t                adc_data;
} adc_tbl_t;



static adc_tbl_t adc_tbl[ADC_MAX_CH];

static ADC_HandleTypeDef hADC1;
static ADC_ChannelConfTypeDef  sConfig;


#ifdef _USE_HW_CMDIF
static void adcCmdif(void);
#endif


bool adcInit(void)
{
  uint32_t i;
  uint32_t ch;



  for (i=0; i<ADC_MAX_CH; i++)
  {
    adc_tbl[i].is_init = false;
    adc_tbl[i].adc_data = 0;
  }


  hADC1.Instance                      = ADC1;
  hADC1.Init.ClockPrescaler           = ADC_CLOCK_ASYNC_DIV64;
  hADC1.Init.Resolution               = ADC_RESOLUTION_12B;
  hADC1.Init.ScanConvMode             = ADC_SCAN_DISABLE;
  hADC1.Init.EOCSelection             = ADC_EOC_SINGLE_CONV;
  hADC1.Init.LowPowerAutoWait         = DISABLE;
  hADC1.Init.ContinuousConvMode       = DISABLE;
  hADC1.Init.NbrOfConversion          = 1;
  hADC1.Init.DiscontinuousConvMode    = DISABLE;
  hADC1.Init.ExternalTrigConv         = ADC_SOFTWARE_START;
  hADC1.Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hADC1.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hADC1.Init.Overrun                  = ADC_OVR_DATA_PRESERVED;
  hADC1.Init.LeftBitShift             = ADC_LEFTBITSHIFT_NONE;
  hADC1.Init.OversamplingMode         = DISABLE;

  if (HAL_ADC_Init(&hADC1) != HAL_OK)
  {
    return false;
  }

  /* Run the ADC calibration in single-ended mode */
  if (HAL_ADCEx_Calibration_Start(&hADC1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
  {
    /* Calibration Error */
    return false;
  }


  // BAT_ADC
  ch = 0;
  adc_tbl[ch].is_init     = true;
  adc_tbl[ch].hADCx       = &hADC1;
  adc_tbl[ch].adc_channel = ADC_CHANNEL_4;


  sConfig.Channel       = adc_tbl[ch].adc_channel;
  sConfig.Rank          = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime  = ADC_SAMPLETIME_810CYCLES_5;
  sConfig.SingleDiff    = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber  = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hADC1, &sConfig) != HAL_OK)
  {
    return 0;
  }
  delay(2);

  HAL_ADC_Start(&hADC1);
  HAL_ADC_PollForConversion(&hADC1, 10);
  adc_tbl[0].adc_data = HAL_ADC_GetValue(adc_tbl[0].hADCx);


#ifdef _USE_HW_CMDIF
  cmdifAdd("adc", adcCmdif);
#endif

  return true;
}

bool adcUpdate(void)
{
  static uint32_t pre_time = 0;

  if (millis()-pre_time >= 10)
  {
    pre_time = millis();

    adc_tbl[0].adc_data = HAL_ADC_GetValue(adc_tbl[0].hADCx);

    HAL_ADC_Start(&hADC1);
  }

  return true;
}

uint32_t adcRead(uint8_t ch)
{
  uint32_t adc_value;

  if (adc_tbl[ch].is_init != true)
  {
    return 0;
  }


  adc_value = adc_tbl[ch].adc_data;

  return adc_value;
}

uint32_t adcRead8(uint8_t ch)
{
  return 0;
}

uint32_t adcRead10(uint8_t ch)
{
  return 0;
}

uint32_t adcRead12(uint8_t ch)
{
  return 0;
}

uint32_t adcRead16(uint8_t ch)
{
  return 0;
}

uint32_t adcReadVoltage(uint8_t ch)
{
  return adcConvVoltage(ch, adcRead(ch));
}

uint32_t adcReadCurrent(uint8_t ch)
{

  return adcConvCurrent(ch, adcRead(ch));
}

uint32_t adcConvVoltage(uint8_t ch, uint32_t adc_value)
{
  uint32_t ret = 0;
  float calc_data;

  switch(ch)
  {
    case 0:
      calc_data  = (float)adc_value / 4095.0;
      calc_data  = calc_data * 1.9 * 11.05;
      calc_data += 0.005;
      ret  = (uint32_t)(calc_data * 100);
      break;
  }

  return ret;
}

uint32_t adcConvCurrent(uint8_t ch, uint32_t adc_value)
{
  return 0;
}

uint8_t  adcGetRes(uint8_t ch)
{
  return 0;
}




void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  if(adcHandle->Instance==ADC1)
  {
    /* ADC1 clock enable */
    __HAL_RCC_ADC12_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PC4     ------> ADC1_INP4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }
}


void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
  if(adcHandle->Instance==ADC1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_ADC12_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC4     ------> ADC1_INP4
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4);
  }
}



#ifdef _USE_HW_CMDIF
//-- adcCmdif
//
void adcCmdif(void)
{
  bool ret = true;


  if (cmdifGetParamCnt() == 1)
  {
    if (cmdifHasString("show", 0) == true)
    {
      while(cmdifRxAvailable() == 0)
      {
        for (int i=0; i<ADC_MAX_CH; i++)
        {
          cmdifPrintf("%04d ", adcRead(i));
        }
        cmdifPrintf("\r\n");
        delay(50);
      }
    }
    else
    {
      ret = false;
    }
  }
  else if (cmdifGetParamCnt() == 2)
  {
    if (cmdifHasString("show", 0) == true && cmdifHasString("voltage", 1) == true)
    {
      while(cmdifRxAvailable() == 0)
      {
        for (int i=0; i<ADC_MAX_CH; i++)
        {
          uint32_t adc_data;

          adc_data = adcReadVoltage(i);

          cmdifPrintf("%d.%d ", adc_data/10, adc_data%10);
        }
        cmdifPrintf("\r\n");
        delay(50);
      }
    }
    else
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }


  if (ret == false)
  {
    cmdifPrintf( "adc show\n");
    cmdifPrintf( "adc show voltage\n");
  }
}
#endif
