/*
 * led.c
 *
 *  Created on: 2020. 11. 21.
 *      Author: baram
 */




#include "led.h"


#ifdef _USE_HW_LED

typedef struct
{
  GPIO_TypeDef* GPIOx;
  uint16_t      GPIO_Pin;
  GPIO_PinState on_state;
  GPIO_PinState off_state;
} led_tbl_t;


led_tbl_t led_tbl[LED_MAX_CH] =
    {
        {GPIOA, GPIO_PIN_4, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, GPIO_PIN_5, GPIO_PIN_SET, GPIO_PIN_RESET},
        {GPIOA, GPIO_PIN_6, GPIO_PIN_SET, GPIO_PIN_RESET},
    };





bool ledInit(void)
{
  uint32_t i;
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();


  /*Configure GPIO pins : PA4 PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  for (i=0; i<LED_MAX_CH; i++)
  {
    ledOff(i);
  }


  return true;
}

void ledOn(uint8_t ch)
{
  HAL_GPIO_WritePin(led_tbl[ch].GPIOx, led_tbl[ch].GPIO_Pin, led_tbl[ch].on_state);
}

void ledOff(uint8_t ch)
{
  HAL_GPIO_WritePin(led_tbl[ch].GPIOx, led_tbl[ch].GPIO_Pin, led_tbl[ch].off_state);
}

void ledToggle(uint8_t ch)
{
  HAL_GPIO_TogglePin(led_tbl[ch].GPIOx, led_tbl[ch].GPIO_Pin);
}

#else
void ledInit(void)
{

}
#endif
