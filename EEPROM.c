#include "EEPROM.h"
int i=0;
unsigned int eepromRead(uint16_t block,uint8_t offset)
{
				EEPROM_EEBLOCK_R |=block;
	      EEPROM_EEOFFSET_R |=offset;
				//uint32_t result = EEPROM_EERDWR_R;
	      return EEPROM_EERDWR_R;
}
void eepromInit(void)
{
		SYSCTL_RCGCEEPROM_R |=0x1;
		//SysCtlDelay(6);
	    i=0;	
	   while(i<=6)
		  {i++;}
		while( (EEPROM_EEDONE_R & 0x01) == 1){}
			
		while( (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY) == 1)
		{
				EEPROM_EESUPP_R |= 0x1;
		}
		
		SYSCTL_SREEPROM_R |= 0x1;
		
		//SysCtlDelay(6);	
	  i=0;
		while(i<=3)
		 {i++;}
		
		while( (EEPROM_EEDONE_R & 0x01) == 1){}
			
				while( (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY) == 1)
		{
				EEPROM_EESUPP_R |= 0x01;
		}
}


void eepromWrite(uint16_t block,uint8_t offset,uint32_t data)
{
				EEPROM_EEBLOCK_R |=block;
	      EEPROM_EEOFFSET_R |=offset;
				EEPROM_EERDWR_R = data;      
}