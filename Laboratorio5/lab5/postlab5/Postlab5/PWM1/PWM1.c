/*
 * PWM1.c
 *
 * Created: 16/04/2024 10:15:04 a. m.
 */ 

#include "PWM1.h"

uint16_t topVal = 0;
uint16_t i, j;		//varablies

//(canal <- 1/2, invertido  1/0)
void canal(uint8_t setCH, uint8_t invertido){
	switch(setCH){
		case 1:
			if(invertido == 1){
				TCCR1A |= (1 << COM1A0) | (1 << COM1A1);	//channel A invertido
			}else{
				TCCR1A |= (1 << COM1A1);					//channel A no invertido
			}
		break;
		
		case 2:
			if(invertido == 1){
				TCCR1A |= (1 << COM1B0) | (1 << COM1B1);	//channelB invertido
			}else{
				TCCR1A |= (1 << COM1B1);					//channelB no invertido
			}
		break;
	}
}

/*configuracion para fastPWM
*/
void initFastPWM1(uint8_t modoPWM, uint16_t prescaler){	//initialize register timer1
	TCCR1A = 0;
	TCCR1B = 0;
	
	switch (prescaler)
	{
		case 8:
			TCCR1B |= (1 << CS11);					//prescaler 8
		break;
		
		case 1024:
			TCCR1B |= (1 << CS10) | (1 << CS12);	//prescaler 1024
		break;
	}
	
	//modo de opercion seleccionado
	switch (modoPWM)
	{
		case 1:
			//resolucion 10bits pwm
			TCCR1A |= (1 << WGM11) | (1 << WGM10);
			TCCR1B |= (1 << WGM12);
		break;
		
		case 2:
			//fast PWM con ICR1 en top
			TCCR1A |= (1 << WGM11);
			TCCR1B |= (1 << WGM12) | (1 << WGM13);
			topVal = 1;		
		break;
	}
	
}

//topValue, modo 2 confugurar valor periodo
void valorTOP(uint16_t top){
	if (topVal == 1)	{
		ICR1 = top;		
	}else{
		topVal = 0;
	}
}

//conversion de servos, valores cada cnal valor nesct
void salidaservo(uint16_t pot, uint8_t chaselect){
	
	switch(chaselect){
		case 1:
			i = ADCH;
			j = (200/12)*i+1000;
			OCR1A = j;
		break;
		
		case 2:
			i = ADCH;
			j = (200/12)*i+1000;
			OCR1B = j;
		break;
	}
}