/*
 * ADC.c
 *
 *  Created on: Oct 7, 2022
 *      Author: ashraf abdelsabor
 */
#include "avr/io.h" /* To use the ADC Registers */
#include "ADC.h"
#include "common_macros.h"


void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/* clear ADMUX and set reference voltage and result */
	ADMUX = 0;
	ADMUX =	((Config_Ptr->ref_volt) <<REFS0) | ((Config_Ptr->result_Adjust) <<ADLAR) ;

	/*set trigger source */
	SFIOR |=((Config_Ptr->triger_Source)<<ADTS0);

	/*ADEN to enable ADC
	 *ADATE trigger
	 *ADIE interrupt or polling
	 *ADPSE to set the prescaller
	 * */
	ADCSRA = 0;
	ADCSRA = (1<<ADEN) | (1<<ADATE) | ((Config_Ptr->prescaler)<<ADPS0);

#if (POLLING_OR_INTERRUPT==1)
	ADCSRA = ADCSRA | (1<<ADIE); //if interrupt define set this bit to 1
#endif
}

uint16 ADC_readChannel(ADC_CHANNEL channel_num)
{
	/*ADC read channel*/
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */

#if(POLLING_OR_INTERRUPT==0)
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
#endif
}




