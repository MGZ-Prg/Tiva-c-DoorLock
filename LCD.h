#ifndef LCD_controller_H_
#define LCD_controller_H_

#include "stdint.h"
#include "inc/tm4c123gh6pm.h"

#define LCD_DATA_PORT PortB
#define LCD_D0 P0
#define LCD_D1 P1
#define LCD_D2 P2
#define LCD_D3 P3
#define LCD_D4 P4
#define LCD_D5 P5
#define LCD_D6 P6
#define LCD_D7 P7

#define LCD_CONTROL_PORT  PortD

#define LCD_RD  P0
#define LCD_WR  P1
#define LCD_RS  P2
#define LCD_CS  P3
#define LCD_RST P6


#define WHITE      0xFFFF
#define BLACK      0x0000
#define BLUE       0x001F
#define BRED       0XF81F
#define GRED       0XFFE0
#define GBLUE      0X07FF
#define RED        0xF800
#define MAGENTA    0xF81F
#define GREEN      0x07E0
#define CYAN       0x7FFF
#define YELLOW     0xFFE0
#define BROWN      0XBC40
#define BRRED      0XFC07
#define GRAY       0X8430
#define DARKBLUE   0X01CF
#define LIGHTBLUE  0X7D7C
#define GRAYBLUE   0X5458
#define LIGHTGREEN 0X841F
#define LGRAY      0XC618
#define LGRAYBLUE  0XA651
#define LBBLUE     0X2B12

#ifdef __cplusplus
extern "C" {
#endif
void LCD_GPIO_Init(void);
void LCD_RESET(void);
void LCD_Init(void);
void LCD_SetWindows(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void LCD_WR_REG (uint8_t command );
void LCD_WR_DATA (uint8_t data);
void fillscreen(uint16_t color);
void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color);
void Draw_Circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
#ifdef __cplusplus
}
#endif
#endif
