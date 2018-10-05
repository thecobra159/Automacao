/*
 * pins.h
 *
 *  Created on: 3 de out de 2018
 *      Author: thecobra
 */

#ifndef PINS_H_
#define PINS_H_

#include "tm4c123gh6pm.h"
#include <inttypes.h>

//GENERAL
#define ENABLE GPIO_PORTA_DATA_R ^= (1 << 6)
#define EEPROM_SUCCESS       0
#define EEPROM_REBOOT        1
#define EEPROM_ERROR         2
#define EEPROM_EESUPP_START  0x00000001  // Start Erase

//LCD
#define RS          (1 << 5)    //PA5
#define EN          (1 << 6)    //PA6

#define DB0         (1 << 0)    //PB0
#define DB1         (1 << 1)    //PB1
#define DB2         (1 << 2)    //PB2
#define DB3         (1 << 3)    //PB3
#define DB4         (1 << 4)    //PB4
#define DB5         (1 << 5)    //PB5
#define DB6         (1 << 6)    //PB6
#define DB7         (1 << 7)    //PB7

//PWM
#define LED0        (1 << 1)    //PF1   PWM 5 MODULO 1
#define LED1        (1 << 2)    //PF2   PWM 6 MODULO 1
#define LED2        (1 << 4)    //PE4   PWM 2 MODULO 1
#define LED3        (1 << 5)    //PE5   PWM 5 MODULO 0

//BUTTONS
#define btn_plus    (1 << 2)    //PD2
#define btn_enter   (1 << 3)    //PD3
#define btn_minus   (1 << 7)    //PD7

#endif /* PINS_H_ */
