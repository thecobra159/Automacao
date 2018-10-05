/*
 * fucntions.h
 *
 *  Created on: 4 de out de 2018
 *      Author: thecobra
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "tm4c123gh6pm.h"
#include "pins.h"

void main(void);

void unlock_gpios(void);

//LCD
void delay_ms(int n);
void enable_pulse(void);
void cmd_lcd(unsigned char c, int index);
void write_lcd(char *c);
void config_lcd(void);

//PWM
void setup_pwm(void);
void init_pwm0 (int percent);
void init_pwm1 (int percent);
void init_pwm2 (int percent);
void init_pwm3 (int percent);

//EEPROM
unsigned long init_EEPROM(void);
void write_EEPROM(unsigned char block, unsigned char offset, unsigned int *data);
unsigned long read_EEPROM(unsigned char block, unsigned char offset);

//INTERRUPTION
void setup_nvic(void);
void setup_portD(void);
void clicked_btn(void);


#endif /* FUNCTIONS_H_ */
