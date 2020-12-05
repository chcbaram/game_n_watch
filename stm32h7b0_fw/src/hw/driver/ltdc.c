/*
 * ltdc.c
 *
 *  Created on: Dec 5, 2020
 *      Author: baram
 */




#include "ltdc.h"
#include "gpio.h"

#ifdef _USE_HW_LTDC


#define FRAME_BUF_ADDR        0x24000000



#define LCD_WIDTH             ((uint16_t)320)   /* LCD PIXEL WIDTH            */
#define LCD_HEIGHT            ((uint16_t)240)   /* LCD PIXEL HEIGHT           */


#define LCD_HSYNC             ((uint16_t)10)    /* Horizontal synchronization */
#define LCD_HBP               ((uint16_t)51)    /* Horizontal back porch      */
#define LCD_HFP               ((uint16_t)12)    /* Horizontal front porch     */


#define LCD_VSYNC             ((uint16_t)2)     /* Vertical synchronization   */
#define LCD_VBP               ((uint16_t)6)     /* Vertical back porch        */
#define LCD_VFP               ((uint16_t)8)     /* Vertical front porch       */



#define _USE_DOUBLE_BUFFER    1






void ltdcSetFrameBuffer(uint16_t* addr);



static LTDC_HandleTypeDef hltdc;
static volatile bool ltdc_request_draw = false;

static volatile uint16_t lcd_int_active_line;
static volatile uint16_t lcd_int_porch_line;


static volatile uint32_t  frame_index = 0;

#if _USE_DOUBLE_BUFFER
static uint16_t __attribute__((section(".lcd"))) __attribute__((aligned(64))) frame_buffer[2][HW_LCD_WIDTH * HW_LCD_HEIGHT];
static volatile bool is_double_buffer = true;

#else
static uint16_t __attribute__((section(".lcd"))) __attribute__((aligned(64))) frame_buffer[1][HW_LCD_WIDTH * HW_LCD_HEIGHT];
static volatile bool is_double_buffer = false;
#endif

uint16_t *ltdc_draw_buffer;






bool ltdcInit(void)
{
  bool ret = true;

  /* LTDC Initialization -------------------------------------------------------*/
  /* DeInit */
  HAL_LTDC_DeInit(&hltdc);

  /* Polarity configuration */
  /* Initialize the horizontal synchronization polarity as active low */
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  /* Initialize the vertical synchronization polarity as active low */
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  /* Initialize the data enable polarity as active low */
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  /* Initialize the pixel clock polarity as input pixel clock */
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IIPC;
  /* Timing configuration */
  /* The LCD AMPIRE 640x480 is selected */
  /* Timing configuration */
  hltdc.Init.HorizontalSync = (LCD_HSYNC - 1);
  hltdc.Init.VerticalSync = (LCD_VSYNC - 1);
  hltdc.Init.AccumulatedHBP = (LCD_HSYNC + LCD_HBP - 1);
  hltdc.Init.AccumulatedVBP = (LCD_VSYNC + LCD_VBP - 1);
  hltdc.Init.AccumulatedActiveH = (LCD_HEIGHT + LCD_VSYNC + LCD_VBP - 1);
  hltdc.Init.AccumulatedActiveW = (LCD_WIDTH + LCD_HSYNC + LCD_HBP - 1);
  hltdc.Init.TotalHeigh = (LCD_HEIGHT + LCD_VSYNC + LCD_VBP + LCD_VFP - 1);
  hltdc.Init.TotalWidth = (LCD_WIDTH + LCD_HSYNC + LCD_HBP + LCD_HFP - 1);


  /* Configure R,G,B component values for LCD background color */
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;

  hltdc.Instance = LTDC;


  /* Configure the LTDC */
  if(HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    /* Initialization Error */
    ret = false;
  }


  uint16_t *p_data;

  p_data = (uint16_t *)frame_buffer[0];
  for (int i=0; i<LCD_WIDTH*LCD_HEIGHT; i++)
  {
    p_data[i] = 0;
  }
#if _USE_DOUBLE_BUFFER
  p_data = (uint16_t *)frame_buffer[1];
  for (int i=0; i<LCD_WIDTH*LCD_HEIGHT; i++)
  {
    p_data[i] = 0;
  }
#endif


  ltdcLayerInit(LTDC_LAYER_1, (uint32_t)frame_buffer[frame_index]);
  //ltdcLayerInit(LTDC_LAYER_2, FRAME_OSD_ADDR);
  //ltdcSetAlpha(LTDC_LAYER_2, 0);

#if _USE_DOUBLE_BUFFER
  if (is_double_buffer == true)
  {
    ltdc_draw_buffer = frame_buffer[frame_index ^ 1];
  }
  else
  {
    ltdc_draw_buffer = frame_buffer[frame_index];
  }
#else
  ltdc_draw_buffer = frame_buffer[0];
#endif

  lcd_int_active_line = (LTDC->BPCR & 0x7FF) - 1;
  lcd_int_porch_line  = (LTDC->AWCR & 0x7FF) - 1;

  HAL_LTDC_ProgramLineEvent(&hltdc, lcd_int_active_line);
  __HAL_LTDC_ENABLE_IT(&hltdc, LTDC_IT_LI | LTDC_IT_FU);

  NVIC_SetPriority(LTDC_IRQn, 5);
  NVIC_EnableIRQ(LTDC_IRQn);



  ltdcRequestDraw();

  return ret;
}



void ltdcSetAlpha(uint16_t LayerIndex, uint32_t value)
{
  HAL_LTDC_SetAlpha(&hltdc, value, LayerIndex);
}


bool ltdcLayerInit(uint16_t LayerIndex, uint32_t Address)
{
  LTDC_LayerCfgTypeDef      pLayerCfg;
  bool ret = true;


  /* Layer1 Configuration ------------------------------------------------------*/

  /* Windowing configuration */
  /* In this case all the active display area is used to display a picture then :
     Horizontal start = horizontal synchronization + Horizontal back porch = 43
     Vertical start   = vertical synchronization + vertical back porch     = 12
     Horizontal stop = Horizontal start + window width -1 = 43 + 480 -1
     Vertical stop   = Vertical start + window height -1  = 12 + 272 -1      */
  if (LayerIndex == LTDC_LAYER_1)
  {
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = LCD_WIDTH;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = LCD_HEIGHT;
  }
  else
  {
    pLayerCfg.WindowX0 = (LCD_WIDTH-200)/2;
    pLayerCfg.WindowX1 = pLayerCfg.WindowX0 + 200;
    pLayerCfg.WindowY0 = (LCD_HEIGHT-200)/2;
    pLayerCfg.WindowY1 = pLayerCfg.WindowY0 + 200;
  }


  /* Pixel Format configuration*/
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;

  /* Start Address configuration : frame buffer is located at FLASH memory */
  pLayerCfg.FBStartAdress = Address;

  /* Alpha constant (255 == totally opaque) */
  pLayerCfg.Alpha = 255;

  /* Default Color configuration (configure A,R,G,B component values) : no background color */
  pLayerCfg.Alpha0 = 0; /* fully transparent */
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;

  /* Configure blending factors */
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;

  /* Configure the number of lines and number of pixels per line */
  pLayerCfg.ImageWidth  = LCD_WIDTH;
  pLayerCfg.ImageHeight = LCD_HEIGHT;


  /* Configure the Layer*/
  if(HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, LayerIndex) != HAL_OK)
  {
    /* Initialization Error */
    ret = false;
  }


  return ret;
}


void ltdcSetFrameBuffer(uint16_t* addr)
{
  LTDC_Layer1->CFBAR = (uint32_t)addr;

  /* Reload immediate */
  LTDC->SRCR = (uint32_t)LTDC_SRCR_IMR;
}


int32_t ltdcWidth(void)
{
  return LCD_WIDTH;
}

int32_t ltdcHeight(void)
{
  return LCD_HEIGHT;
}

uint32_t ltdcGetBufferAddr(uint8_t index)
{
  return  (uint32_t)frame_buffer[frame_index];
}

bool ltdcDrawAvailable(void)
{
  return !ltdc_request_draw;
}

void ltdcRequestDraw(void)
{
  ltdc_request_draw = true;
}

void ltdcSetDoubleBuffer(bool enable)
{
#if _USE_DOUBLE_BUFFER
  is_double_buffer = enable;

  if (enable == true)
  {
    ltdc_draw_buffer = frame_buffer[frame_index^1];
  }
  else
  {
    ltdc_draw_buffer = frame_buffer[frame_index];
  }
#endif
}

bool ltdcGetDoubleBuffer(void)
{
  return is_double_buffer;
}

uint16_t *ltdcGetFrameBuffer(void)
{
  return  ltdc_draw_buffer;
}

uint16_t *ltdcGetCurrentFrameBuffer(void)
{
  return  frame_buffer[frame_index];
}

extern void lcdTransferDoneISR(void);

void ltdcSwapFrameBuffer(void)
{
#if _USE_DOUBLE_BUFFER
  if (ltdc_request_draw == true)
  {
    ltdc_request_draw = false;

    frame_index ^= 1;

    ltdcSetFrameBuffer(frame_buffer[frame_index]);

    if (is_double_buffer == true)
    {
      ltdc_draw_buffer = frame_buffer[frame_index ^ 1];
    }
    else
    {
      ltdc_draw_buffer = frame_buffer[frame_index];
    }
    lcdTransferDoneISR();
  }
#else
  if (ltdc_request_draw == true)
  {
    ltdc_request_draw = false;

    ltdcSetFrameBuffer(frame_buffer[frame_index]);
    ltdc_draw_buffer = frame_buffer[frame_index];

    lcdTransferDoneISR();
  }
#endif
}









void LTDC_IRQHandler(void)
{
  HAL_LTDC_IRQHandler(&hltdc);
}


void HAL_LTDC_LineEvenCallback(LTDC_HandleTypeDef* hltdc)
{
  if (LTDC->LIPCR == lcd_int_active_line)
  {
    ltdcSwapFrameBuffer();
    HAL_LTDC_ProgramLineEvent(hltdc, lcd_int_active_line);
  }
  else
  {
    HAL_LTDC_ProgramLineEvent(hltdc, lcd_int_active_line);
  }
}



/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief LTDC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable the LTDC and DMA2D clocks */
  __HAL_RCC_LTDC_CLK_ENABLE();
  __HAL_RCC_DMA2D_CLK_ENABLE();

  /** @brief Toggle Sw reset of LTDC IP */
  __HAL_RCC_LTDC_FORCE_RESET();
  __HAL_RCC_LTDC_RELEASE_RESET();

  /** @brief Toggle Sw reset of DMA2D IP */
  __HAL_RCC_DMA2D_FORCE_RESET();
  __HAL_RCC_DMA2D_RELEASE_RESET();


  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  /**LTDC GPIO Configuration
  PC0     ------> LTDC_G2
  PA7     ------> LTDC_VSYNC
  PB0     ------> LTDC_R3
  PE13     ------> LTDC_DE
  PE15     ------> LTDC_R7
  PB10     ------> LTDC_G4
  PB11     ------> LTDC_G5
  PB14     ------> LTDC_CLK
  PD10     ------> LTDC_B3
  PC6     ------> LTDC_HSYNC
  PC7     ------> LTDC_G6
  PC9     ------> LTDC_G3
  PA8     ------> LTDC_R6
  PA9     ------> LTDC_R5
  PA10     ------> LTDC_B4
  PA11     ------> LTDC_R4
  PC10     ------> LTDC_R2
  PD2     ------> LTDC_B7
  PD3     ------> LTDC_G7
  PD6     ------> LTDC_B2
  PB5     ------> LTDC_B5
  PB8     ------> LTDC_B6
  */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_LTDC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_3|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_LTDC;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF12_LTDC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF11_LTDC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief LTDC MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hltdc: LTDC handle pointer
  * @retval None
  */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{

  /*##-1- Reset peripherals ##################################################*/
  /* Peripheral clock disable */
  __HAL_RCC_LTDC_CLK_DISABLE();

  /**LTDC GPIO Configuration
  PC0     ------> LTDC_G2
  PA7     ------> LTDC_VSYNC
  PB0     ------> LTDC_R3
  PE13     ------> LTDC_DE
  PE15     ------> LTDC_R7
  PB10     ------> LTDC_G4
  PB11     ------> LTDC_G5
  PB14     ------> LTDC_CLK
  PD10     ------> LTDC_B3
  PC6     ------> LTDC_HSYNC
  PC7     ------> LTDC_G6
  PC9     ------> LTDC_G3
  PA8     ------> LTDC_R6
  PA9     ------> LTDC_R5
  PA10     ------> LTDC_B4
  PA11     ------> LTDC_R4
  PC10     ------> LTDC_R2
  PD2     ------> LTDC_B7
  PD3     ------> LTDC_G7
  PD6     ------> LTDC_B2
  PB5     ------> LTDC_B5
  PB8     ------> LTDC_B6
  */
  HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9
                        |GPIO_PIN_10);

  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                        |GPIO_PIN_11);

  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_14
                        |GPIO_PIN_5|GPIO_PIN_8);

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_13|GPIO_PIN_15);

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_10|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6);

  /* LTDC interrupt Deinit */
  HAL_NVIC_DisableIRQ(LTDC_IRQn);
}


#endif
