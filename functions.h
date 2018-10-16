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

//GENERAL
void main(void);
void unlock_gpios(void);
void delay_us (int n);
void update_menu1(int coxao);
void update_menu2(int coxao2);
void update_menu3(int coxao3, int cont);
void set_pwm_pis(int pwm[4], int pis[4]);

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

//PIS
void init_pis0(int internal);
void init_pis1(int internal);
void init_pis2(int internal);
void init_pis3(int internal);

#endif /* FUNCTIONS_H_ */
