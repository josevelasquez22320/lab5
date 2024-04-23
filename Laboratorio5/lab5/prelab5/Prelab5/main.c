/*;UNIVERSIDAD DEL VALLE DE GUATEMALA
;IE2023: PROGRAMACIÓN DE MICROCONTROLADORES
;Lab2.asm
;AUTOR: Jose Andrés Velásquez Gacía
;PROYECTO: prelab5
;HARDWARE: ATMEGA328P
;CREADO: 22/02/2024
;ÚLTIMA MODIFICACIÓN: 22/02/2024 23:36*/

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "PWM1/PWM1.h"
#include "PWM0/PWM0.h"
uint8_t contador =0;

void initADC(void);

int main(void)
{
	cli();
	DDRB |= (1 << PORTB2) ;		//PB6 Salida
	DDRC = 0;		//puestoc entradas
	DDRD |= (1 << PORTD5);		//PB6 salida


	
	initFastPWM0();
	canal0();
	TCCR0B = 0x02;
	
	initFastPWM1(2, 8);
	canal(2, 0);
	canal(1,0);
	valorTOP(39999);
	
	//modulo ADC lect y mux 
	initADC();
	sei();
	ADCSRA |= (1 << ADSC);//in lec
	while (1)
	{
		//soilo lo hace
		
		
	}
}



//esperar conversion entre a interrupcion 
void initADC(void){
	ADMUX = 0;
	//Vref = AVcc = 5Vs
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	ADMUX |= (1 << ADLAR);	
	
	ADCSRA = 0;
	ADCSRA |= (1 << ADEN);	//on ADC
	ADCSRA |= (1 << ADIE);	//int
	
	//pres 128 > 125kHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	DIDR0 |= (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);	//PC0 desabilita 
}

//que canal lo quiero
ISR (ADC_vect){
	//mostrar valor ADC
	//apaga bandera
	ADCSRA |= (1 << ADIF);	
	if (contador == 0){
		contador = 1;
		ADMUX = (ADMUX & 0xF0);
		salidaservo(ADCH, 1);
	}
