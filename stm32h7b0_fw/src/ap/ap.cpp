/*
 * ap.cpp
 *
 *  Created on: Nov 21, 2020
 *      Author: baram
 */




#include "ap.h"




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


  pre_time = millis();
  while(1)
  {
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


      lcdPrintf(0,  0, white, "%d ms", show_data[0]);
      lcdPrintf(0, 16, white, "%d fps", show_data[1]);
      lcdPrintf(0, 32, white, "%d ms", show_data[2]);

      for (int i=0; i<BUTTON_MAX_CH; i++)
      {
        lcdPrintf(i*8, 48, white, "%d", buttonGetPressed(i));
      }

      lcdPrintfRect(0, 0, LCD_WIDTH, LCD_HEIGHT, red, 2, LCD_ALIGN_H_CENTER | LCD_ALIGN_V_BOTTOM,  "게임앤워치 보드");

      lcdDrawFillRect(x, 62, 30, 30, red);
      lcdDrawFillRect(lcdGetWidth()-x, 92, 30, 30, green);
      lcdDrawFillRect(x + 30, 122, 30, 30, blue);

      draw_time = millis()-pre_time_draw;

      x += 2;

      x %= lcdGetWidth();
      y %= lcdGetHeight();

      lcdRequestDraw();
    }
  }
}
