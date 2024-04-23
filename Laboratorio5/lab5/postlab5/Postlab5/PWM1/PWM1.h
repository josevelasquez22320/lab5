/*
 * PWM1.h
 *
 * Created: 15/04/2024 01:16:14 a. m.
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>
#include <stdint.h>
//si invertido = 1, no invertido = 0, modo op =1
// otro modo op =2, canal A =1, canal b =2


/* configuracion para fastPWM
*/
void initFastPWM1(uint8_t modoPWM, uint16_t prescaler);

//modos canales
void canal(uint8_t setCH, uint8_t invertido);

//modo 1 y 2
void valorTOP(uint16_t top);

/*conversion de servo manipular valores*/
void salidaservo(uint16_t pot, uint8_t chaselect);


#endif 