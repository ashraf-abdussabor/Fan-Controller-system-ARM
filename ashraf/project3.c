/*
 * project3.c
 *
 *  Created on: Oct 8, 2022
 *      Author: ashraf abdelsabor
 */


#include"gpio.h"
#include "lcd.h"
#include "ADC.h"
#include "dc_motor.h"
#include "common_macros.h"
#include "pwm_timer0.h"
#include "lm35_sensor.h"
boolean FAN_STATE = 0;


void lcd_print(uint8 temperature ,boolean FAN_STATE)
{

	LCD_moveCursor(1,0);
	LCD_displayString("Temp = ");
	if (temperature >= 100)
	{
		LCD_intgerToString(temperature);
		LCD_displayCharacter('c');
	}
	else
	{
	LCD_intgerToString(temperature);
	LCD_displayCharacter(' ');
	LCD_displayCharacter('c');
	}
	LCD_moveCursor(0,0);
	if (FAN_STATE == 0)
	{
		LCD_displayString("Fan Is OFF");
	}
	else
	{
		LCD_displayString("Fan Is ON");
		LCD_displayCharacter(' ');
	}

}

int main()
{
	LCD_init();
	LCD_displayCharacter('A');
	uint8 temperature=0;
	uint8 speed=0 ;


	ADC_ConfigType adc_config;
	adc_config.ref_volt=INTERNAL;
	adc_config.prescaler=DIVISION_BY_8;
	ADC_init(&adc_config);

	LCD_init();
	LCD_displayCharacter(temperature);

	DcMotor_Init();

	while(1)
	{
		temperature= LM35_getTemperature();
		LCD_moveCursor(0,4);

		if (temperature < 30) {
			DcMotor_Rotate(DC_MOTOR_STOP, speed);


			FAN_STATE = 0;
			lcd_print(temperature, FAN_STATE);
		}

		else if ((temperature >= 30) && (temperature < 60)) {
			speed = 25;
			DcMotor_Rotate(DC_MOTOR_CW, speed);
			FAN_STATE = 1;
			lcd_print(temperature, FAN_STATE);
		}

		else if ((temperature >= 60) && (temperature < 90)) {
			speed = 50;
			DcMotor_Rotate(DC_MOTOR_CW, speed);
			FAN_STATE = 1;
			lcd_print(temperature, FAN_STATE);
		}

		else if ((temperature >= 90) && (temperature < 120)) {
			speed = 75;
			DcMotor_Rotate(DC_MOTOR_CW, speed);
			FAN_STATE = 1;
			lcd_print(temperature, FAN_STATE);
		}
		else if (temperature >= 120) {
			speed = 100;
			DcMotor_Rotate(DC_MOTOR_CW, speed);
			FAN_STATE = 1;
			lcd_print(temperature, FAN_STATE);
		}
	}

}
