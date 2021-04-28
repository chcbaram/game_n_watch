/*
 * ap.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: baram
 */




#include "ap.h"


IMAGE_RES_DEF(img_logo);


void apInit(void)
{
}

void apMain(void)
{
  uint32_t pre_time;
  uint16_t x = 0;
  uint16_t y = 0;
  uint32_t show_data[3] = {0, };
  uint32_t pre_time_draw;
  uint32_t draw_time = 0;

  image_t logo;
  int16_t img_x = 0;
  int16_t img_y = 0;

  logo = imageLoad(&img_logo);

  pre_time = millis();
  while(1)
  {
    adcUpdate();
    pwrUpdate();
    batteryUpdate();


    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      show_data[0] = lcdGetFpsTime();
      show_data[1] = lcdGetFps();
      show_data[2] = draw_time;
    }


    if (lcdDrawAvailable())
    {
      pre_time_draw = millis();
      lcdClearBuffer(black);


      lcdPrintf(0, 16*0, white, "LCD : %d ms, %d fps, %d ms", show_data[0], show_data[1], show_data[2]);
      lcdPrintf(0, 16*1, white, "BAT : %d, %dV, %d%%, CHG %d", adcRead(0), batteryGetVoltage(), batteryGetLevel(), batteryIsCharging());


      lcdPrintf(0, 16*3, white, "BTN : ");
      for (int i=0; i<BUTTON_MAX_CH; i++)
      {
        lcdPrintf(i*8+8*6, 16*3, white, "%d", buttonGetPressed(i));
      }
      lcdPrintf(0, 16*4, white, "PIN : ");
      for (int i=0; i<GPIO_MAX_CH; i++)
      {
        lcdPrintf(i*8+8*6, 16*4, white, "%d", gpioPinRead(i));
      }

      lcdPrintfRect(0, 0, LCD_WIDTH, LCD_HEIGHT, blue, 2, LCD_ALIGN_H_CENTER | LCD_ALIGN_V_BOTTOM,  "게임앤워치 보드");


      //lcdDrawFillRect(x, 62, 30, 30, red);
      //lcdDrawFillRect(lcdGetWidth()-x, 92, 30, 30, green);
      //lcdDrawFillRect(x + 30, 122, 30, 30, blue);

      int16_t speed = 5;

      if (buttonGetPressed(_DEF_HW_BTN_LEFT))  img_x -= speed;
      if (buttonGetPressed(_DEF_HW_BTN_RIGHT)) img_x += speed;
      if (buttonGetPressed(_DEF_HW_BTN_UP))    img_y -= speed;
      if (buttonGetPressed(_DEF_HW_BTN_DOWN))  img_y += speed;

      img_x = constrain(img_x, 0, lcdGetWidth());
      img_y = constrain(img_y, 0, lcdGetHeight());

      imageDraw(&logo, img_x, img_y);

      draw_time = millis()-pre_time_draw;

      x += 2;

      x %= lcdGetWidth();
      y %= lcdGetHeight();

      lcdRequestDraw();
    }
  }
}
