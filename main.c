#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "pins.h"
#include "functions.h"

/**
 * main.c
 */
void main(void) {

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOA | SYSCTL_RCGC2_GPIOB | SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOE | SYSCTL_RCGC2_GPIOF;

    unlock_gpios();
    config_lcd();

    setup_nvic();
    setup_portD();

    setup_pwm();
    init_pwm0(25);
    delay_ms(20000);
    init_pwm1(50);
    delay_ms(20000);
    init_pwm2(75);
    delay_ms(20000);
    init_pwm3(99);

    while(1) {
//        write_lcd("  CHOOSE A LED  <-      1     ->");
//        delay_ms(100000);
    }

}
