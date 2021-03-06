#include "pins.h"

//GENERAL
void unlock_gpios(){
    GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTD_CR_R   = 1 << 7;

    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R   = 1 << 0;
}

void delay_ms(int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++) { }
}

void delay_us (int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < 1600; j++){ }
    }
}

void enable_pulse(void) {
    ENABLE;
    delay_ms(10000);
    ENABLE;
}

void update_menu1(int coxao){
    switch (coxao){
        case 1:
            write_lcd("  CHOOSE A LED  <-      1     ->");
            break;
        case 2:
            write_lcd("  CHOOSE A LED  <-      2     ->");
            break;
        case 3:
            write_lcd("  CHOOSE A LED  <-      3     ->");
            break;
        case 4:
            write_lcd("  CHOOSE A LED  <-      4     ->");
            break;
    }
}

void update_menu2(int coxao2){
    switch (coxao2){
        case 1:
            write_lcd(" CHOOSE A MODE  <-    PWM     ->");
            break;
        case 2:
            write_lcd(" CHOOSE A MODE  <-    PIS     ->");
            break;
    }
}

void update_menu3(int coxao3, int cont){
    char lcd_text[31];
    switch (coxao3){
        case 1:
            sprintf(lcd_text, "PWM -> %d", cont);
            write_lcd(lcd_text);
            break;
        case 2:
            sprintf(lcd_text, "PIS -> %d", cont);
            write_lcd(lcd_text);
            break;
    }
}

void set_pwm_pis(int pwm[4], int pis[4]){
    int var;
    for (var = 0; var < 4; ++var) {
        if (pwm[var] == 0){
             switch(var){
                case 0:
                    init_pis0(pis[0]);
                    break;
                case 1:
                    init_pis1(pis[1]);
                    break;
                case 2:
                    init_pis2(pis[2]);
                    break;
                case 3:
                    init_pis3(pis[3]);
                    break;
            }
        } else {
            switch(var){
                case 0:
                    init_pwm0(pwm[0]);
                    break;
                case 1:
                    init_pwm1(pwm[1]);
                    break;
                case 2:
                    init_pwm2(pwm[2]);
                    break;
                case 3:
                    init_pwm3(pwm[3]);
                    break;
            }
        }
    }
}

//LCD
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
       // dire��o dos pinos
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
       delay_ms(100000);

       write_lcd("WE ARE ALMOST    THERE !? ");
       delay_ms(100000);
       write_lcd("DONE! LETS GO!");
       delay_ms(200000);
}

//PWM
void setup_pwm() {
    //Habilita fun��o alternativa dos PF1 - PF2
    GPIO_PORTF_AFSEL_R |= (1 << 1) | (1 << 2);
    delay_ms(20000);
    //Definir que a fun��o alternativa � PWM
    GPIO_PORTF_PCTL_R  |= GPIO_PCTL_PF1_M1PWM5 | GPIO_PCTL_PF2_M1PWM6;
    delay_ms(20000);
    //Habilita digitalmente os pinos
    GPIO_PORTF_DEN_R    |= (1 << 1) | (1 << 2);
    delay_ms(20000);

    //Habilita fun��o alternativa dos PE4 - PE5
    GPIO_PORTE_AFSEL_R |= (1 << 4) | (1 << 5);
    delay_ms(20000);
    //Definir que a fun��o alternativa � PWM
    GPIO_PORTE_PCTL_R  |= GPIO_PCTL_PE4_M1PWM2 | GPIO_PCTL_PE5_M0PWM5;
    delay_ms(20000);
    //Habilita digitalmente os pinos
    GPIO_PORTE_DEN_R   |=  (1 << 4) | (1 << 5);
    delay_ms(20000);

    //Ativa o m�dulo de PWM 0 e 1
    SYSCTL_RCGCPWM_R   |= (1 << 0) | (1 << 1);
    delay_ms(20000);
}

void init_pwm0 (int percent) {
    //N�vel baixo em LOAD / N�vel alto em CMPA
    PWM1_2_GENB_R |= 0xC08;
    delay_us(200);
    //Valor da frequencia do PWM, em ciclos de clock
    PWM1_2_LOAD_R |= 1600; //1/[(62,5*10^-9) * (10*10^3)] = 1600
    delay_us(200);
    //Valor da porcentagem do PWM, em ciclos de clock
    if (percent == 1) {
        PWM1_2_CMPB_R = 0;
        delay_us(200);
    } else {
        PWM1_2_CMPB_R |= (1600 * percent) / 100;
        delay_us(200);
    }
    //Ativa o controle do elemento 0 do PWM1
    PWM1_2_CTL_R  |= (1 << 0);
    delay_us(200);
    //Inicializa o PWM1 - Gerador 2
    PWM1_ENABLE_R |= (1 << 5);

    delay_us(200);
}

void init_pwm1 (int percent) {
    //N�vel baixo em LOAD / N�vel alto em CMPA
    PWM1_3_GENA_R |= 0x0C8;
    delay_us(200);
    //Valor da frequencia do PWM, em ciclos de clock
    PWM1_3_LOAD_R |= 1600; //1/[(62,5*10^-9) * (10*10^3)] = 1600
    delay_us(200);
    //Valor da porcentagem do PWM, em ciclos de clock
    if(percent == 1) {
        PWM1_3_CMPA_R = 0;
        delay_us(200);
    } else {
        PWM1_3_CMPA_R |= (1600 * percent) / 100;
        delay_us(200);
    }
    //Ativa o controle do elemento 0 do PWM1
    PWM1_3_CTL_R |= (1 << 0);
    delay_us(200);
    //Inicializa o PWM1 - Gerador 3
    PWM1_ENABLE_R |= (1 << 6);
    delay_us(200);
}

void init_pwm2 (int percent) {
    //N�vel baixo em LOAD / N�vel alto em CMPA
    PWM1_1_GENA_R |= 0x0C8;
    delay_us(200);
    //Valor da frequencia do PWM, em ciclos de clock
    PWM1_1_LOAD_R |= 1600; //1/[(62,5*10^-9) * (10*10^3)] = 1600
    delay_us(200);
    //Valor da porcentagem do PWM, em ciclos de clock
    if(percent == 1) {
        PWM1_1_CMPA_R = 0;
        delay_us(200);
    } else {
        PWM1_1_CMPA_R |= (1600 * percent) / 100;
        delay_us(200);
    }
    //Ativa o controle do elemento 0 do PWM1
    PWM1_1_CTL_R |= (1 << 0);
    delay_us(200);
    //Inicializa o PWM1 - Gerador 1
    PWM1_ENABLE_R |= (1 << 2);
    delay_us(200);
}

void init_pwm3 (int percent) {
    //N�vel baixo em LOAD / N�vel alto em CMPA
    PWM0_2_GENB_R |= 0xC08;
    delay_us(200);
    //Valor da frequencia do PWM, em ciclos de clock
    PWM0_2_LOAD_R |= 1600; //1/[(62,5*10^-9) * (10*10^3)] = 1600
    delay_us(200);
    //Valor da porcentagem do PWM, em ciclos de clock
    if(percent == 1) {
        PWM0_2_CMPB_R = 0;
        delay_us(200);
    } else {
        PWM0_2_CMPB_R |= (1600 * percent) / 100;
        delay_us(200);
    }
    //Ativa o controle do elemento 0 do PWM1
    PWM0_2_CTL_R |= (1 << 0);
    delay_us(200);
    //Inicializa o PWM0 - Gerador 2
    PWM0_ENABLE_R |= (1 << 5);
    delay_us(200);
}

//EEPROM
unsigned long init_EEPROM(void){
    volatile unsigned long delay;
    unsigned long status;
    // Habilita clock no eeprom
    SYSCTL_RCGCEEPROM_R |= 0x1;
    // Espera umpoquinho
    delay = SYSCTL_RCGC2_R;
    // Verifica se podemos mexer na eeprom
    while(EEPROM_EEDONE_R == 0x1){};
    // Verifica o status da eeprom
    status = EEPROM_EESUPP_R;
    if(status & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY)){
        EEPROM_EESUPP_R = EEPROM_EESUPP_START;
        while(EEPROM_EEDONE_R == 0x1){};
        status = EEPROM_EESUPP_R;
        if(status & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY)){
            return(EEPROM_ERROR);
        } else {
            return(EEPROM_REBOOT);
        }
    }
    EEPROM_EEBLOCK_R = 0x2;             // select block 1
    EEPROM_EEOFFSET_R = 0x0;            // select offset 0
    EEPROM_EEPROT_R &= ~0x0F;           // allow write and read
    return(EEPROM_SUCCESS);
}


void write_EEPROM(unsigned char block, unsigned char offset, unsigned int *data){
    //Verifica se a eeprom esta OK
    while(EEPROM_EEDONE_R == 0x1){};
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
    EEPROM_EERDWR_R = *data;
    //Verifica se a eeprom esta OK
    while(EEPROM_EEDONE_R == 0x1){};
}


unsigned long read_EEPROM(unsigned char block, unsigned char offset){
    //Verifica se a eeprom esta OK
    while(EEPROM_EEDONE_R == 0x1){};
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
    //Verifica se a eeprom esta OK
    while(EEPROM_EEDONE_R == 0x1){};
    return EEPROM_EERDWR_R;
}

//INTERRUPTION
void setup_nvic(void) {
    NVIC_ST_CTRL_R      = 0x00;                       //Desligando a NVIC para configura��o
    NVIC_ST_RELOAD_R    = 8000000;                    //Setando o tempo da NVIC
    NVIC_ST_CURRENT_R   = 0;                          //Inicializando a NVIC em 0
    //NVIC_ST_CTRL_R      = 0x07;                       //Ligando a NVIC
    NVIC_EN0_R          = SYSCTL_RCGC2_GPIOD;         //habilita inten do portA-C-D
}

void setup_portD(void) {
    GPIO_PORTD_DIR_R    = (0 << 2) | (0 << 3) | (0 << 7);
    GPIO_PORTD_RIS_R    = 0x00;
    GPIO_PORTD_PDR_R    = btn_plus | btn_enter | btn_minus;
    GPIO_PORTD_IS_R     = 0x00;                                 //Define sensibilidade do bot�o - 0 borda - 1 sinal continuo
    GPIO_PORTD_IEV_R    = 0x00;                                 //Define evento - 0 descida | baixo - 1 subida | alto
    GPIO_PORTD_IBE_R    = 0x00;                                 //Define inten por ambas as bordas
    GPIO_PORTD_IM_R     = btn_plus | btn_enter | btn_minus;     //Habilita inten no pino
    GPIO_PORTD_DEN_R    = btn_plus | btn_enter | btn_minus;
}

void clicked_btn(void) {
    delay_us(20);

    if((GPIO_PORTA_RIS_R & btn_plus) == btn_plus) {
        write_lcd("mais pressionado coroi");
    }

    if((GPIO_PORTA_RIS_R & btn_minus) == btn_minus) {
        write_lcd("menos pressionado coroi");
    }

    if((GPIO_PORTA_RIS_R & btn_enter) == btn_enter) {
        write_lcd("enter pressionado coroi");
    }

    GPIO_PORTD_ICR_R |= btn_plus | btn_enter | btn_minus;
}

//PIS
void init_pis0(int internal){
    int contInt = 0;
    while(contInt < internal) {
        init_pwm0(1);
//        GPIO_PORTF_DATA_R = LED0;
        delay_us(internal);
//        GPIO_PORTF_DATA_R = ~LED0;
        init_pwm0(99);
        delay_us(internal);
        init_pwm0(1);
        delay_us(internal);

        contInt++;
    }
}

void init_pis1(int internal){
    int contInt = 0;
    while(contInt < internal) {
        init_pwm1(1);
//        GPIO_PORTF_DATA_R = LED0;
        delay_us(internal);
//        GPIO_PORTF_DATA_R = ~LED0;
        init_pwm1(99);
        delay_us(internal);
        init_pwm1(1);
        delay_us(internal);

        contInt++;
    }
}

void init_pis2(int internal){
    int contInt = 0;
    while(contInt < internal) {
        init_pwm2(1);
//        GPIO_PORTF_DATA_R = LED0;
        delay_us(internal);
//        GPIO_PORTF_DATA_R = ~LED0;
        init_pwm2(99);
        delay_us(internal);
        init_pwm2(1);
        delay_us(internal);

        contInt++;
    }
}

void init_pis3(int internal){
    int contInt = 0;
    // pura pregui�a de configurar e desconfigurar o pwm hehehe
    while(contInt < internal) {
        init_pwm3(1);
//        GPIO_PORTF_DATA_R = LED0;
        delay_us(internal);
//        GPIO_PORTF_DATA_R = ~LED0;
        init_pwm3(99);
        delay_us(internal);
        init_pwm3(1);
        delay_us(internal);

        contInt++;
    }
}
