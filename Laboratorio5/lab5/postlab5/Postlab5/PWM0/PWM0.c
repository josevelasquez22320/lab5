/*
 * PWM0.c
 *
 * Created: 22/04/2024 19:36:23
 *  Author: josea
 */ 
//timer0
#include "PWM0.h"
void initFastPWM0(void){
		TCCR0A = 0;
		TCCR0B = 0;
		
		TCCR0A |= (1  << WGM00) | (1 << WGM01) ;//config
		
}

//modos canales
void canal0(void){
	TCCR0A |= (1 << COM0B1);//config canalB pd5
}

