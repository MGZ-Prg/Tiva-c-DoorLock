#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "common_macros.h"
#include "GPIO.h"
void eepromInit(void);
void eepromWrite(uint16_t block,uint8_t offset,uint32_t data);
unsigned int eepromRead(uint16_t block,uint8_t offset);
