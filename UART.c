#include "UART.h"

	
void UART_Init(uint8_t UARTX,uint8_t length,uint16_t baud_rate){
	
	uint16_t clk_div=(int)(SYS_CLK/(baud_rate*16));		
	float32 fraction=(float)(SYS_CLK/(baud_rate*16))-clk_div;
	
	if(UARTX == '0'){

	SET_BIT(SYSCTL_RCGCUART_R,0);																        //ENABLE CLK FOR UART0
	SET_BIT(SYSCTL_RCGCGPIO_R,0);																				//ENABLE CLK FOR PORTA
	CLEAR_BIT(UART0_CTL_R,0);																		        //DISABLE UART0
	UART0_IBRD_R=clk_div;																								//SET BR
	UART0_FBRD_R=(int)(fraction*64+0.5);																//SET BR
	UART0_CC_R=0x0;																											//USE SYSTEM CLOCK
	UART0_LCRH_R=0;UART0_LCRH_R =((length-5)<<5);												//SET DATA SIZE
	SET_BIT(UART0_CTL_R,8);																							//ENABLE RX
	SET_BIT(UART0_CTL_R,9);																							//ENABLE TX
	SET_BIT(UART0_CTL_R,0);																							//ENABLE UART0
	SET_BIT(GPIO_PORTA_AFSEL_R,0);SET_BIT(GPIO_PORTA_AFSEL_R,1);				//ENABLE ALT FUN FOR PA0 & PA1
	GPIO_PORTA_PCTL_R=0x11;																							//DEFINE ALT FUN CODE PA0 & PA1
	SET_BIT(GPIO_PORTA_DEN_R,0);SET_BIT(GPIO_PORTA_DEN_R,1);						//ENABLE DIGITAL FOR PA0 & PA1
  CLEAR_BIT(GPIO_PORTA_AMSEL_R,0);CLEAR_BIT(GPIO_PORTA_AMSEL_R,1);		//DISABLE ANALOG FOR PA0 & PA1	*/
	}
	else if(UARTX=='1'){
	uint16_t dummy;	
	SET_BIT(SYSCTL_RCGCUART_R,1);																				//ENABLE CLK FOR UART1
	SET_BIT(SYSCTL_RCGCGPIO_R,1);																				//ENABLE CLK FOR PORTB
	dummy = SYSCTL_RCGCGPIO_R;																					//CLK IS STABLE
	CLEAR_BIT(UART1_CTL_R,0);																						//DISABLE UART1
	UART1_IBRD_R= clk_div;														  								//SET BR
	UART1_FBRD_R=(int)(fraction*64+0.5);																//SET BR
	UART1_CC_R=0x0;																											//USE SYSTEM CLOCK
	UART1_LCRH_R =0X60;													            						//SET DATA SIZE
	SET_BIT(UART1_CTL_R,8);																							//ENABLE UART1
	SET_BIT(UART1_CTL_R,9);																							//ENABLE RX	
	SET_BIT(UART1_CTL_R,0);																							//ENABLE TX
	SET_BIT(GPIO_PORTB_AFSEL_R,0);SET_BIT(GPIO_PORTB_AFSEL_R,1);				//ENABLE ALT FUN FOR PB0 & PB1
	GPIO_PORTB_PCTL_R=0x11;																							//DEFINE ALT FUN CODE PB0 & PB1
	SET_BIT(GPIO_PORTB_DEN_R,0);SET_BIT(GPIO_PORTB_DEN_R,1);						//ENABLE DIGITAL FOR PB0 & PB1
  CLEAR_BIT(GPIO_PORTB_AMSEL_R,0);CLEAR_BIT(GPIO_PORTB_AMSEL_R,1);		//DISABLE ANALOG FOR PB0 & PB1
	}



}


void UART_Send_Char(uint8_t character,uint8_t UARTX){
	if(UARTX=='0'){while(BIT_IS_SET(UART0_FR_R,5)){};UART0_DR_R=character;}
	else if(UARTX=='1'){while(BIT_IS_SET(UART1_FR_R,5)){};UART1_DR_R=character;}
	else if(UARTX=='2'){while(BIT_IS_SET(UART2_FR_R,5)){};UART2_DR_R=character;}
	else if(UARTX=='3'){while(BIT_IS_SET(UART3_FR_R,5)){};UART3_DR_R=character;}
	else if(UARTX=='4'){while(BIT_IS_SET(UART4_FR_R,5)){};UART4_DR_R=character;}
	else if(UARTX=='5'){while(BIT_IS_SET(UART5_FR_R,5)){};UART5_DR_R=character;}
	else if(UARTX=='6'){while(BIT_IS_SET(UART6_FR_R,5)){};UART6_DR_R=character;}
	else if(UARTX=='7'){while(BIT_IS_SET(UART7_FR_R,5)){};UART7_DR_R=character;}
}

uint8_t UART_Receive_Char(uint8_t UARTX){
	uint8_t data;
	if(UARTX=='0')		 {while(BIT_IS_SET(UART0_FR_R,4)){};data=UART0_DR_R;}
	else if(UARTX=='1'){while(BIT_IS_SET(UART1_FR_R,4)){};data=UART1_DR_R;}
	else if(UARTX=='2'){while(BIT_IS_SET(UART2_FR_R,4)){};data=UART2_DR_R;}
	else if(UARTX=='3'){while(BIT_IS_SET(UART3_FR_R,4)){};data=UART3_DR_R;}
	else if(UARTX=='4'){while(BIT_IS_SET(UART4_FR_R,4)){};data=UART4_DR_R;}
	else if(UARTX=='5'){while(BIT_IS_SET(UART5_FR_R,4)){};data=UART5_DR_R;}
	else if(UARTX=='6'){while(BIT_IS_SET(UART6_FR_R,4)){};data=UART6_DR_R;}
	else if(UARTX=='7'){while(BIT_IS_SET(UART7_FR_R,4)){};data=UART7_DR_R;}
return data;
}

void UART_Send_String(const uint8_t *Str , uint8_t UARTX)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		UART_Send_Char(Str[i],UARTX);
		i++;
	}
}

void UART_Receive_String(uint8_t *Str,uint8_t UARTX)
{
	uint8_t i = 0;
	Str[i] = UART_Receive_Char(UARTX);
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_Receive_Char(UARTX);
	}
	Str[i] = '\0';
}