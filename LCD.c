
#include "LCD.h"
#include "GPIO.h"
void delay_1ms(void)
	{
		NVIC_ST_CTRL_R =0;  
		NVIC_ST_RELOAD_R =0x000003E80 ;
		NVIC_ST_CURRENT_R = 0;
		NVIC_ST_CTRL_R = 0x05;
		while((NVIC_ST_CTRL_R &0x0010000) == 0){}
	}
	void delay(uint32_t delay)
	{
			while(delay--)
				delay_1ms();
	}
void LCD_GPIO_Init(void)
{
//Init the GPIOs for LCD

	// DATA PINS
	
	  pinMode(LCD_DATA_PORT, LCD_D0, Output);	  
	  pinMode(LCD_DATA_PORT, LCD_D1, Output);
	  pinMode(LCD_DATA_PORT, LCD_D2, Output);
	  pinMode(LCD_DATA_PORT, LCD_D3, Output);
	  pinMode(LCD_DATA_PORT, LCD_D4, Output);	  
	  pinMode(LCD_DATA_PORT, LCD_D5, Output);
	  pinMode(LCD_DATA_PORT, LCD_D6, Output);
	  pinMode(LCD_DATA_PORT, LCD_D7, Output);
	  
	// CONTROL PINS
	
	  pinMode(LCD_CONTROL_PORT, LCD_RST, Output);	  
	  pinMode(LCD_CONTROL_PORT, LCD_CS , Output);
	  pinMode(LCD_CONTROL_PORT, LCD_WR , Output);
	  pinMode(LCD_CONTROL_PORT, LCD_RD , Output);
	  pinMode(LCD_CONTROL_PORT, LCD_RS , Output);
}
void LCD_RESET(void)
{
	delay(50);
	digitalWrite(LCD_CONTROL_PORT,LCD_RST, 0);
	delay(150);	
	digitalWrite(LCD_CONTROL_PORT,LCD_RST, 1);
	delay(50);
}
void LCD_WR_REG (uint8_t command)
{
   digitalPortWrite(LCD_DATA_PORT,command);     // writing command
   digitalWrite(LCD_CONTROL_PORT,LCD_CS, 0); 
   digitalWrite(LCD_CONTROL_PORT,LCD_RS, 0);  // RESET command pin to LOW                  
   digitalWrite(LCD_CONTROL_PORT,LCD_WR, 0);  // RESET write data pin    
   digitalWrite(LCD_CONTROL_PORT,LCD_WR, 1);  // Set write pin to HIGh
   digitalWrite(LCD_CONTROL_PORT,LCD_RS, 1);  // set command pin to HIGH
   digitalWrite(LCD_CONTROL_PORT,LCD_CS, 1);
 }

void LCD_WR_DATA (uint8_t data)
{
  digitalPortWrite(LCD_DATA_PORT,data);
  digitalWrite(LCD_CONTROL_PORT,LCD_CS, 0);
  digitalWrite(LCD_CONTROL_PORT,LCD_WR, 0);
  digitalWrite(LCD_CONTROL_PORT,LCD_WR, 1);
  digitalWrite(LCD_CONTROL_PORT,LCD_CS, 1);
  
}  

void LCD_SetWindows(uint16_t  x1, uint16_t  y1,uint16_t  x2,uint16_t  y2)
{	
	LCD_WR_REG(0x2A);   //COLADDR_SET
	LCD_WR_DATA(x1>>8);
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2>>8);
	LCD_WR_DATA(x2);
	
	LCD_WR_REG(0x2B);  //PAGE_ADDR_SET
	LCD_WR_DATA(y1>>8);
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2>>8);
	LCD_WR_DATA(y2);
	

} 


void fillscreen(uint16_t  color)
{
	unsigned int i;
	LCD_SetWindows(0, 0, 480, 320);
	LCD_WR_REG(0x2C);
	for (i = 0; i < 320*480; i++)
	{
			LCD_WR_DATA(color >> 8);
			LCD_WR_DATA(color);
	}
}
void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_SetWindows(x, y, x, y);
	LCD_WR_REG(0x2C);
	LCD_WR_DATA(color >> 8);
	LCD_WR_DATA(color);
}

void Draw_Circle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{
	int16_t f = 1 - radius;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * radius;
	int16_t x1= 0;
	int16_t y1= radius;

	Draw_Pixel(x, y+radius,color);
 	Draw_Pixel(x, y-radius,color);
	Draw_Pixel(x+radius, y,color);
	Draw_Pixel(x-radius, y,color);

	while (x1<y1) 
	{
    	if (f >= 0) 
		{
      		y1--;
      		ddF_y += 2;
      		f += ddF_y;
    	}
    	x1++;
    	ddF_x += 2;
    	f += ddF_x;
  
		Draw_Pixel(x + x1, y + y1,color);
    	Draw_Pixel(x - x1, y + y1,color);
		Draw_Pixel(x + x1, y - y1,color);
		Draw_Pixel(x - x1, y - y1,color);
		Draw_Pixel(x + y1, y + x1,color);
		Draw_Pixel(x - y1, y + x1,color);
		Draw_Pixel(x + y1, y - x1,color);
		Draw_Pixel(x - y1, y - x1,color);
 	}
}
void LCD_Init(void)
{
     LCD_GPIO_Init();
      LCD_RESET();
  
		 LCD_WR_REG(0x01); //Soft Reset
		 
		 delay(150); // .kbv will power up with ONLY reset, sleep out, display on
		 
		 LCD_WR_REG(0x28); //Display Off
		 
		 LCD_WR_REG(0x3A); //Pixel read=565, write=565.
		 LCD_WR_DATA(0x55); 
		 
		 LCD_WR_REG(0xF9);
		 LCD_WR_DATA(0x00);
		 LCD_WR_DATA(0x08);
		 
		 LCD_WR_REG(0xB7); 
		 LCD_WR_DATA(0x07);
		 
		  LCD_WR_REG(0xB1); 
		 LCD_WR_DATA(0xB0); 
		 LCD_WR_DATA(0x10);

		 LCD_WR_REG(0x36); 
		 LCD_WR_DATA(0xA8);		

		 LCD_WR_REG(0x3A); 
		 LCD_WR_DATA(0x55);			 
		 
		 LCD_WR_REG(0xC0); //Power Control 1 [0E 0E]
		 LCD_WR_DATA(0x19);
		 LCD_WR_DATA(0x1A);
		 
		 LCD_WR_REG(0xC1); //Power Control 2 [43 00]
		 LCD_WR_DATA(0x45);
		 LCD_WR_DATA(0x00);
		 
		 LCD_WR_REG(0xC2); //Power Control 3 [33]
		 LCD_WR_DATA(0x33);
		 
		 LCD_WR_REG(0xC5); //VCOM  Control 1 [00 40 00 40]
		 LCD_WR_DATA(0x00);
		 LCD_WR_DATA(0x28);
		 
		 LCD_WR_REG(0xB1);//Sets the frame frequency of full color normal mode
		 LCD_WR_DATA(0x90);//0XB0 =70HZ, <=0XB0.0xA0=62HZ
		 LCD_WR_DATA(0x11);
		 
		 LCD_WR_REG(0xB4); //Inversion Control [00]
		 LCD_WR_DATA(0x02);
		 
		 LCD_WR_REG(0xB6); // Display Function Control [02 02 3B]
		 LCD_WR_DATA(0x00);
		 LCD_WR_DATA(0x42);
		 LCD_WR_DATA(0x3B);
		 
		 LCD_WR_REG(0xB7);
		 LCD_WR_DATA(0x07);
		 
		 LCD_WR_REG(0xE0); // 3.2 TM  3.2 Inch Initial Code not bad
		 LCD_WR_DATA(0x0F);
		 LCD_WR_DATA(0x21);
		 LCD_WR_DATA(0x1C);
		 LCD_WR_DATA(0x0B);
		 LCD_WR_DATA(0x0E);
		 LCD_WR_DATA(0x08);		
		 LCD_WR_DATA(0x49);
		 LCD_WR_DATA(0x98);		
		 LCD_WR_DATA(0x38);
		 LCD_WR_DATA(0x09);		 
		 LCD_WR_DATA(0x11);
		 LCD_WR_DATA(0x03);
		 LCD_WR_DATA(0x14);		 
		 LCD_WR_DATA(0x10);
		 LCD_WR_DATA(0x00);

		 LCD_WR_REG(0xE1);
		 LCD_WR_DATA(0x0F);
		 LCD_WR_DATA(0x2F);
		 LCD_WR_DATA(0x2B);
		 LCD_WR_DATA(0x0C);
		 LCD_WR_DATA(0x0E);
		 LCD_WR_DATA(0x06);		
		 LCD_WR_DATA(0x47);
		 LCD_WR_DATA(0x76);		
		 LCD_WR_DATA(0x37);
		 LCD_WR_DATA(0x07);		 
		 LCD_WR_DATA(0x11);
		 LCD_WR_DATA(0x04);
		 LCD_WR_DATA(0x23);		 
		 LCD_WR_DATA(0x1E);
		 LCD_WR_DATA(0x00);
		 
		 LCD_WR_REG(0xF1);
		 LCD_WR_DATA(0x36);
		 LCD_WR_DATA(0x04);
		 LCD_WR_DATA(0x00);
		 LCD_WR_DATA(0x3C);
		 LCD_WR_DATA(0x0F);
		 LCD_WR_DATA(0x0F);
		 LCD_WR_DATA(0xA4);
		 LCD_WR_DATA(0x02);

		 LCD_WR_REG(0xF2);
		 LCD_WR_DATA(0x18);
		 LCD_WR_DATA(0xA3);
		 LCD_WR_DATA(0x12);
		 LCD_WR_DATA(0x02);
		 LCD_WR_DATA(0x32);
		 LCD_WR_DATA(0x12);
		 LCD_WR_DATA(0xFF);
		 LCD_WR_DATA(0x32);
		 LCD_WR_DATA(0x00);

		 LCD_WR_REG(0xF4);
		 LCD_WR_DATA(0x40);
		 LCD_WR_DATA(0x00);
		 LCD_WR_DATA(0x08);
		 LCD_WR_DATA(0x91);
		 LCD_WR_DATA(0x04);
		 
		 LCD_WR_REG(0xF8);
		 LCD_WR_DATA(0x21);
		 LCD_WR_DATA(0x04);
		 
		 LCD_WR_REG(0x11); //Sleep Out

		 delay(120);
		 LCD_WR_REG(0x29);//Display On
		   
       /* _lcd_capable = (1<<1) | (1<<0) | (1<<10); //Red 3.5", Blue 3.5"
		_lcd_rev = ((_lcd_capable & (1<<12)) != 0);
    setRotation(0);             //PORTRAIT
    invertDisplay(false);*/
}
