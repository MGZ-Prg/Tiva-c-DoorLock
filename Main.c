#include "UART.h"
#include "GPIO.h"
void SystemInit(){}
	
int main(void)
{

uint8_t Char = '0';
UART_Init('1',8,9600);
pinMode(PortF,P1,Output);
	pinMode(PortF,P2,Output);
	pinMode(PortF,P3,Output);
while(1){
Char = UART_Receive_Char('1');
if(Char =='F')
{
	digitalWrite(PortF,P1,1);
	digitalWrite(PortF,P2,0);
	digitalWrite(PortF,P3,0);
}
else if(Char =='R')
{
	digitalWrite(PortF,P1,0);
	digitalWrite(PortF,P2,1);
	digitalWrite(PortF,P3,0);

}
else if(Char =='B')
{
	digitalWrite(PortF,P1,0);
	digitalWrite(PortF,P2,0);
	digitalWrite(PortF,P3,1);
}
else
{
	digitalWrite(PortF,P1,0);
	digitalWrite(PortF,P2,0);
	digitalWrite(PortF,P3,0);
}


}

}

