#include "config.h"
#include <pic18f4520.h>
#include "kernel.h"
#include "timer.h"
#include "bits.h"
#include "ssd.h"
#include "lcd.h"

static char count = 0;
static int i = 0;
static int j = 0;

//interrupt setup

void __interrupt ISR(void) {
    //TIMER0: Overflow
    if (bitTst(INTCON, 2)) {
        // 65535 - 2*10.000 = 10mS
        TMR0H = (45535 >> 8);
        TMR0L = (45535 & 0x00FF);

        KernelClock();

        //limpa a flag
        bitClr(INTCON, 2);
    }
}

char ledInit(void){
    TRISD = 0x00;
    return SUCCESS;
}
char firstLeds(void) {
    i++;
    switch(i){
        case 1: PORTD |= 0x0F; break;
        case 2: PORTD &= 0xF0; break;
        case 10: i = 0; break;
        default: break;    
    }
    return REPEAT;
}

char lastLeds (void){
    j++;
    switch(j){
        case 1: PORTD |= 0xF0; break;
        case 2: PORTD &= 0x0F; break;
        case 20: j = 0; break;
        default: break;   
    }
     return REPEAT;
}

char update (void){
    ssdUpdate();
    return REPEAT;
}

char time (void){
    ssdDigit(         (count%10), 3);
    ssdDigit(     ((count/10)%6), 2);
    ssdDigit(    ((count/60)%10), 1);
    ssdDigit(   ((count/600)%10), 0);
    count++;
    return REPEAT; 
}

void interrupInit(void){
    //interrupt start
    bitClr(RCON, 7); // desabilita IPEN ( modo de compatibilidade )
    bitSet(INTCON, 5); // liga a interrupção para o timer 0
    bitSet(INTCON, 7); // habilita todas as interrupções globais
    bitSet(INTCON, 6); // habilita todas as interrupções de perifericos
}

void main(void) {
   
    process p1 = {ledInit, 1, 0, 0};
    process p2 = {firstLeds, 10, 0, 0};
    process p3 = {lastLeds, 10, 1, 0};
    process p4 = {update, 0.8, 0, 1};
    process p5 = {time, 100, 0, 0};
   
    lcdInit();
    timerInit();
    kernelInit();
    interrupInit();
    ssdInit(); 
    
    lcdCommand(0x80);
    
    for(int cont = 0; cont <10; cont++){
    lcdData(cont);
    }
 // Exercício 3
 //   kernelAddProc(&p1);
 //   kernelAddProc(&p2);
 //   kernelAddProc(&p3);
    
 // Exercício 4    
   // kernelAddProc(&p5);
  //  kernelAddProc(&p4);
    
    kernelLoop();
    
}
