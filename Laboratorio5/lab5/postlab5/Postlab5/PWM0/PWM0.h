/*
 * PWM0.h
 *
 * Created: 22/04/2024 19:34:48
 *  Author: josea
 */ 


#ifndef PWM0_H_
#define PWM0_H_


#include <avr/io.h>
#include <stdint.h>
//si invertido = 1, no invertido = 0, modo op =1
// otro modo op =2, canal A =1, canal b =2


/* configuracion para fastPWM
*/
void initFastPWM0(void);

//modos canales
void canal0(void);

#endif /* PWM0_H_ */