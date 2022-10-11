/*
 * ADC.h
 *
 *  Created on: Oct 7, 2022
 *      Author: ashraf abdelsabor
 *      ADC driver atmega16 , 1mhz
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define polling_OR_INTERRUPT 0     /*if polling set this = 0 , interrupt = 1*/

#if((polling_OR_INTERRUPT != 0) && (polling_OR_INTERRUPT != 1))

#error "please choose interrupt or polling"

#endif

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	/*choose your reference voltage (AVCC= 5 V , INTERNAL = 2.56V , EXTERNAL  */
	EXTERNAL_AREF , AVCC ,REVERSED , INTERNAL
}ADC_REFERENCE_VOLTAGE;

typedef enum
{
	/*choose input channel from ADC0 to ADC7*/
	ADC0 ,ADC1 ,ADC2 ,ADC3 ,ADC4 ,ADC5 ,ADC6 , ADC7
}ADC_CHANNEL ;

typedef enum
{
	/*choose prescaler  division factor*/
	DIVISION_BY_2 = 1 ,DIVISION_BY_4 ,DIVISION_BY_8 ,DIVISION_BY_16 ,DIVISION_BY_32 ,
	DIVISION_BY_64 ,DIVISION_BY_128
}ADC_PRESCALER ;

typedef enum
{
	/*choose trigger source*/
	FREE_RUNNING_MODE , ANALOG_COMPARATOR , EXTERNAL_INTERRUPT_REQUEST0,
	TIMER_COUNTER0_COMPARE_MATCH , TIMER_COUNTER0_OVERFLOW , TIMER_COUNTER0_COMPARE_MATCH_B ,
	TIMER_COUNTER1_OVERFLOW , TIMER_COUNTER1_CAPTURE_EVENT
}ADC_TRIGGER_SOURCE;

typedef enum
{
	RIGHT_ADJUST_RESULT , LEFT_ADJUST_RESULT
}ADC_ADJUST_RESULT;

typedef struct{
	ADC_REFERENCE_VOLTAGE ref_volt;
	ADC_PRESCALER prescaler;
	ADC_ADJUST_RESULT result_Adjust ;
	ADC_TRIGGER_SOURCE triger_Source;
	}ADC_ConfigType;


/*******************************************************************************
 *                               functions                             *
 *******************************************************************************/
void ADC_init(const ADC_ConfigType *Config_Ptr);
uint16 ADC_readChannel(ADC_CHANNEL channel_num);

#endif /* ADC_H_ */
