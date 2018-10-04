#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "pins.h"
#include "functions.h"

#define ENABLE GPIO_PORTA_DATA_R ^= (1 << 6)

/**
 * main.c
 */
void main(void) {

    config_lcd();

}

void delay_ms(int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++) { }
}

void enable_pulse(void) {
    ENABLE;
    delay_ms(10000);
    ENABLE;
}

void cmd_lcd(unsigned char c, int index) {
    if (index == 0) {
        GPIO_PORTA_DATA_R = (0 << 0);
        delay_ms(400);
        GPIO_PORTB_DATA_R = (1 << 0);
        enable_pulse();
        GPIO_PORTB_DATA_R = (1 << 1);
        enable_pulse();
    }
    if (index == 16) {
        GPIO_PORTA_DATA_R = (0 << 0);
        delay_ms(400);
        GPIO_PORTB_DATA_R = (1 << 6) | (1 << 7);
        enable_pulse();
    }
    GPIO_PORTA_DATA_R = (1 << 5);
    delay_ms(400);
    GPIO_PORTB_DATA_R = c;
    enable_pulse();

}

void write_lcd(char *c) {
    uint8_t i;
    for (i = 0; c[i] != 0; i++)
        cmd_lcd(c[i], i);
}

void config_lcd(void) {
    // registradores
       SYSCTL_RCGCGPIO_R |= 1<<0 | 1<<1;

       //garante que tem 0
       GPIO_PORTB_DATA_R = 0x00;
       GPIO_PORTA_DATA_R = 0x00;
       // direção dos pinos
       GPIO_PORTA_DIR_R |= 1<<5 | 1<<6 | 1<<7;
       GPIO_PORTB_DIR_R |= 0xFF; // todos
       // Habilita os pinos
       GPIO_PORTB_DEN_R |= 0xFF; // todos
       GPIO_PORTA_DEN_R |= 1<<5 | 1<<6 | 1<<7;

       delay_ms(60500);
       // config 8 bits
       GPIO_PORTB_DATA_R = 1<<4 | 1<<5;

       delay_ms(100000);
       enable_pulse();

       delay_ms(20000);
       enable_pulse();

       delay_ms(20000);
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<2 | 1<<3 | 1<<4 | 1<<5;
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<3;
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<0;
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<0 | 1<<1 | 1<<2;
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<2 | 1<<3;
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<1 | 1<<2;
       enable_pulse();

       GPIO_PORTB_DATA_R = 1<<0;
       enable_pulse();

       write_lcd("INITIALIZING...  WAIT...  ");
}

void setup_pwm() {
    //Habilita função alternativa dos PF0 - PF1 - PF2 - PF3
    GPIO_PORTF_AFSEL_R = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
    //Definir que a função alternativa é PWM
    GPIO_PORTF_PCTL_R = 0x4444;
    //Habilita digitalmente os pinos
    GPIO_PORTF_DEN_R = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

    //Ativa o módulo de PWM 1
    SYSCTL_RCGCPWM_R = (1 << 1);
}

void init_pwm0 (int percent) {
    //Nível baixo em LOAD / Nível alto em CMPA
    PWM1_3_GENA_R = (1 << 3) | (1 << 6) | (1 << 7);
    //Valor da frequencia do PWM, em ciclos de clock
    PWM1_3_LOAD_R = 1600; //1/[(62,5*10^-9) * (10*10^3)] = 1600
    //Valor da porcentagem do PWM, em ciclos de clock
    PWM1_3_CMPA_R = (1600 * percent) / 100;
    //Ativa o controle do elemento 0 do PWM1
    PWM1_3_CTL_R = (1 << 1);
    //Inicializa o PWM1 - Gerador
    PWM1_ENABLE_R = (1 << 4);
}
