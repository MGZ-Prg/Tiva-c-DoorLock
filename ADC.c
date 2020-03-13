#include "ADC.h"
#include "GPIO.h"
void adc_Init(ADC adc,AIN ain)
{
	PORT port;
	AIN_P ain_p;
	if(ain == AIN10 ||ain == AIN9 )
	{
		ain_p = 4;
	}
	else if(ain == AIN11 ||ain == AIN8 )
	{
		ain_p = 5;  //
	}
	else if(ain == AIN7 ||ain == AIN3 )
	{
		ain_p = 0;
	}
	else if(ain == AIN6 ||ain == AIN2 )
	{
		ain_p = 1;
	}
	else if(ain == AIN5 ||ain == AIN1 )
	{
		ain_p = 2;
	}
	else if(ain == AIN4 ||ain == AIN0 )
	{
		ain_p = 3;
	}
	
	
	
	if(ain == AIN0 ||ain == AIN1 ||ain == AIN2 ||ain == AIN3 ||ain == AIN8 ||ain == AIN9 )
	{
		port = PortE;
	}
	else if(ain == AIN4|| ain == AIN5|| ain == AIN6|| ain == AIN7)
	{
		port = PortD;
	}
	else if(ain == AIN10|| ain == AIN11)
	{
		port = PortB;
	}
	
	
	analogPinInit(port, ain_p);
	
	
	if(adc == ADC0)
	{
		
		SET_BIT(SYSCTL_RCGC0_R,16); //ENABLING CLOCK & power for adc 
		while( BIT_IS_CLEAR( SYSCTL_PRADC_R , 0) ) {}  //waiting until it is enabled
		SET_BIT(SYSCTL_RCGCADC_R,0);		// enabling adc it self
			
		CLEAR_BIT(SYSCTL_RCGC0_R,8); // setting sampling rate to 1 M samples per sec ,it needs two bits 8,9
		CLEAR_BIT(SYSCTL_RCGC0_R,9);
			
		SET_BIT(ADC0_SSPRI_R,12);   //Changing sequencers priorities seq 3 will have highest priority
		SET_BIT(ADC0_SSPRI_R,13); 			
		CLEAR_BIT(ADC0_SSPRI_R,8);
		SET_BIT(ADC0_SSPRI_R,9);
		CLEAR_BIT(ADC0_SSPRI_R,5);
		SET_BIT(ADC0_SSPRI_R,4);
		CLEAR_BIT(ADC0_SSPRI_R,0);
		CLEAR_BIT(ADC0_SSPRI_R,1);
			
		CLEAR_BIT(ADC0_ACTSS_R,3);  //Disabeling sequensor 3
			
		CLEAR_BIT(ADC0_EMUX_R,12);  // start converstion is intiated by processor(software)
		CLEAR_BIT(ADC0_EMUX_R,13);
		CLEAR_BIT(ADC0_EMUX_R,14);			
		CLEAR_BIT(ADC0_EMUX_R,15);
		
		ADC0_SSMUX0_R =ain; // selecting channel 
		
		
		CLEAR_BIT(ADC0_SSCTL3_R,3);  // NO temp sensor
		SET_BIT(ADC0_SSCTL3_R,2);   // end bit enabled
		SET_BIT(ADC0_SSCTL3_R,1);   // a bit is set when conversion ends
		CLEAR_BIT(ADC0_SSCTL3_R,0);  // differential input is diabled
		
		SET_BIT(ADC0_ACTSS_R,3);  // activating sequencer 3
	}
	else if(adc == ADC1)
	{
		
		SET_BIT(SYSCTL_RCGC0_R,17); //ENABLING CLOCK & power for adc
		while( BIT_IS_CLEAR( SYSCTL_PRADC_R , 1) ) {} //waiting until it is enabled
		SET_BIT(SYSCTL_RCGCADC_R,1);  //enabling adc it self
			
		CLEAR_BIT(SYSCTL_RCGC0_R,10);  // setting sampling rate to 1 M samples per sec ,it needs two bits 10,11
		CLEAR_BIT(SYSCTL_RCGC0_R,11);
			
		SET_BIT(ADC1_SSPRI_R,12);  //Changing sequencers priorities seq 3 will have highest priority
		SET_BIT(ADC1_SSPRI_R,13);
		CLEAR_BIT(ADC1_SSPRI_R,8);
		SET_BIT(ADC1_SSPRI_R,9);
		CLEAR_BIT(ADC1_SSPRI_R,5);
		SET_BIT(ADC1_SSPRI_R,4);
		CLEAR_BIT(ADC1_SSPRI_R,0);
		CLEAR_BIT(ADC1_SSPRI_R,1);
			
		CLEAR_BIT(ADC1_ACTSS_R,3);    //Disabeling sequensor 3
			
		CLEAR_BIT(ADC1_EMUX_R,12);  // start converstion is intiated by processor(software)
		CLEAR_BIT(ADC1_EMUX_R,13);
		CLEAR_BIT(ADC1_EMUX_R,14);			
		CLEAR_BIT(ADC1_EMUX_R,15);
			
		ADC1_SSMUX0_R =ain; // selecting channel 
			
		CLEAR_BIT(ADC1_SSCTL3_R,3);  // NO temp sensor
		SET_BIT(ADC1_SSCTL3_R,2);  // end bit enabled
		SET_BIT(ADC1_SSCTL3_R,1);	// a bit is set when conversion ends
		CLEAR_BIT(ADC1_SSCTL3_R,0); // differential input is diabled
		
		
		SET_BIT(ADC1_ACTSS_R,3);  // activating sequencer 3
		
		
	}
}


uint16_t analogRead(ADC adc)
{
	int x=6;
	uint16_t result ;
	if(adc == ADC0)
	{
		SET_BIT(ADC0_PSSI_R,3);

		while(BIT_IS_CLEAR(ADC0_RIS_R ,3)){}
		result = ADC0_SSFIFO3_R;
		SET_BIT(ADC0_ISC_R,3);
		
	}
	else if(adc == ADC1)
	{
		SET_BIT(ADC1_PSSI_R,3);
		//		while(x--){}
		while(BIT_IS_CLEAR(ADC1_RIS_R ,3)){}
		result = ADC1_SSFIFO3_R;
		SET_BIT(ADC1_ISC_R,3);
		
	}
	return result;
}
