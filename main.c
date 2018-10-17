#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "pins.h"
#include "functions.h"

/**
 * main.c
 */
void main(void) {
    int option_menu = 1;
    int option_menu2 = 1;
    int menu = 1;
    int cont = 0;
    int PWM[4] = 0;
    int PIS[4] = 0;

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOE | SYSCTL_RCGC2_GPIOF;

    while(1) {
        switch (menu) {
            case 1:
                if( (GPIO_PORTD_DATA_R & btn_plus) == btn_plus){
                        delay_us(20);
                        if (option_menu == 4) {
                            option_menu = 1;
                        } else {
                            option_menu++;
                        }
                        update_menu1(option_menu);
                    }

                    if( (GPIO_PORTA_DATA_R & btn_minus) == btn_minus){
                        delay_us(20);
                        if (option_menu == 1) {
                            option_menu = 4;
                        } else {
                            option_menu--;
                        }
                        update_menu1(option_menu);
                    }

                    if( (GPIO_PORTD_DATA_R & btn_enter) == btn_enter){
                        delay_us(20);
                        write_lcd("   NEW MENU   ");
                        update_menu2(option_menu);
                        menu = 2;
                    }
                    break;
            case 2:
                if( (GPIO_PORTD_DATA_R & btn_plus) == btn_plus){
                    delay_us(20);
                    if (option_menu2 == 2) {
                        option_menu2 = 1;
                    } else {
                        option_menu2++;
                    }
                    update_menu2(option_menu2);
                }

                if( (GPIO_PORTA_DATA_R & btn_minus) == btn_minus){
                    delay_us(20);
                    if (option_menu2 == 2) {
                        option_menu2 = 1;
                    } else {
                        option_menu2--;
                    }
                    update_menu2(option_menu2);
                }

                if( (GPIO_PORTD_DATA_R & btn_enter) == btn_enter){
                    delay_us(20);
                    write_lcd("   NEW MENU   ");
                    update_menu3(option_menu2, cont);
                    menu = 3;
                }
                break;
            case 3:
                if( (GPIO_PORTD_DATA_R & btn_plus) == btn_plus){
                    delay_us(20);
                    if (cont > 99)
                        cont = 1;
                    else
                        cont++;
                    update_menu3(option_menu2, cont);
                }

                if( (GPIO_PORTA_DATA_R & btn_minus) == btn_minus){
                    delay_us(20);
                    if (cont < 1)
                        cont = 99;
                    else
                        cont--;
                    update_menu3(option_menu2, cont);
                }

                if( (GPIO_PORTD_DATA_R & btn_enter) == btn_enter){
                    delay_us(20);
                    switch (option_menu2) {
                        case 1:
                            PWM[option_menu-1] = cont;
                            PIS[option_menu-1] = 0;
                            break;
                        case 2:
                            PWM[option_menu-1] = 0;
                            PIS[option_menu-1] = cont;
                            break;
                    }
                    menu = 1;
                    cont = 0;
                    set_pwm_pis(PWM, PIS);
                    update_menu1(option_menu);
                }
                break;
        }
    }
}
