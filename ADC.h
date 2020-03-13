#ifndef ADC_H
#define ADC_H
#include "GPIO.h"
typedef enum {
	ADC0,ADC1
}ADC;
void adc_Init(ADC adc,AIN ain);
uint16_t analogRead(ADC adc);
#endif
