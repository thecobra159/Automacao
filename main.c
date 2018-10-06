#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "pins.h"
#include "functions.h"

/**
 * main.c
 */
void main(void) {
    int option_menu = 1;

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOE | SYSCTL_RCGC2_GPIOF;

    GPIO_PORTD_DIR_R    = (0 << 2) | (0 << 3);
    GPIO_PORTD_DEN_R    = (1 << 2) | (1 << 3);
    GPIO_PORTD_DATA_R   = 0x00;

    GPIO_PORTA_DIR_R    = (0 << 2);
    GPIO_PORTA_DEN_R    = (1 << 2);
    GPIO_PORTA_DATA_R   = 0x00;

    unlock_gpios();
    config_lcd();

    /*setup_nvic();
    setup_portD();*/

    setup_pwm();
    init_pwm0(25);
    delay_ms(20000);
    init_pwm1(50);
    delay_ms(20000);
    init_pwm2(75);
    delay_ms(20000);
    init_pwm3(99);

    write_lcd("  CHOOSE A LED  <-      1     ->");
    int menu = 1;
    int cont = 0;
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
                    if (option_menu == 2) {
                        option_menu = 1;
                    } else {
                        option_menu++;
                    }
                    update_menu2(option_menu);
                }

                if( (GPIO_PORTA_DATA_R & btn_minus) == btn_minus){
                    delay_us(20);
                    if (option_menu == 2) {
                        option_menu = 1;
                    } else {
                        option_menu--;
                    }
                    update_menu2(option_menu);
                }

                if( (GPIO_PORTD_DATA_R & btn_enter) == btn_enter){
                    delay_us(20);
                    write_lcd("   NEW MENU   ");
                    //update_menu3(option_menu);
                    menu = 2;
                }
                break;
            /*case 3:
                if( (GPIO_PORTD_DATA_R & btn_plus) == btn_plus){
                    delay_us(20);
                    if (cont <= 99)
                        cont = 99;
                    else
                        cont++;
                    update_menu3(cont);
                }

                if( (GPIO_PORTA_DATA_R & btn_minus) == btn_minus){
                    delay_us(20);
                    if (option_menu == 2) {
                        option_menu = 1;
                    } else {
                        option_menu--;
                    }
                    update_menu2(option_menu);
                }

                if( (GPIO_PORTD_DATA_R & btn_enter) == btn_enter){
                    delay_us(20);
                    write_lcd("   NEW MENU   ");
                    update_menu1(option_menu);
                    menu = 1;
                }
                break;*/
        }
    }
}
