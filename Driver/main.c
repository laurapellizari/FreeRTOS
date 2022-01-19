#include "config.h"
#include <pic18f4520.h>
#include "kernel.h"
#include "timer.h"
#include "bits.h"
#include "ssd.h"
#include "dd_types.h"
#include "drv_lcd.h"
#include "drv_keypad.h"

static int count = 0;
static int second = 0;
static int minute = 0;
static int hour = 0;

driver* lcd;
driver* keypad; 

//interrupt setup
void __interrupt ISR (void){
  //TIMER0: Overflow
  if (bitTst(INTCON, 2)){
    // 1mS
    TMR0H = (63535 >> 8);
    TMR0L = (63535 & 0x00FF);

    KernelClock();

    //limpa a flag
    bitClr(INTCON, 2);
  }
}

char disp (void){
  lcd->funcoes[LCD_CMD](0x80);
  lcd->funcoes[LCD_DATA](48 + (hour/10));
  lcd->funcoes[LCD_DATA](48 + (hour%10));
  lcd->funcoes[LCD_DATA](':');
  lcd->funcoes[LCD_DATA](48 + (minute/10));
  lcd->funcoes[LCD_DATA](48 + (minute%10));
  lcd->funcoes[LCD_DATA](':');
  lcd->funcoes[LCD_DATA](48 + (second/10));
  lcd->funcoes[LCD_DATA](48 + (second%10));
  return REPEAT;
}


char time (void){
  count++;
  second = count%60;
  minute = (count/60)%60;
  hour = count/3600;
  return REPEAT;
}

char db (void){
    keypad->funcoes[KP_DB](0); 
    return REPEAT;
}

char press(void){
    
   unsigned int *value;
   unsigned int x;
   value = &x;
   
   keypad->funcoes[KP_READ](&value); 
    if (*value == 2){//increase hour 
        count++;
        if (hour > 23){
            hour = 0;
        }
    }
    if (*value == 32){//increase minute 
        count++;
        if (minute > 59){
            minute = 0;
        }
    }
    if (*value == 512){//increase second
        count++;
        if (second > 59){
            second = 0;
        }
    }
    if (*value == 1){//decrease hour 
        count--;
        if (hour > 23){
            hour = 23;
        }
    }
    if (*value == 16){//decrease minute 
        count--;
        if (minute > 60){
            minute = 60;
        }
    }
    if (*value == 256){//decrease second 
        count--;
        if (second > 60){
            second = 60;
        }
    }    
   return REPEAT;
}


void main (void){
  lcd = getLcdDriver();
  keypad = getKeypadDriver();
  
  lcd->initFunc(0);
  keypad->initFunc(1);
  
  process p1 = {disp, 1000, 0};
  process p2 = {time, 1000, 1};
  process p3 = {db, 2, 4};
  process p4 = {press, 10, 3};
  
  timerInit();
  kernelInit();

  kernelAddProc(&p1);
  kernelAddProc(&p2);
  kernelAddProc(&p3);
  kernelAddProc(&p4);
  
  //interrupt start
  bitClr(RCON, 7); // desabilita IPEN ( modo de compatibilidade )
  bitSet(INTCON, 5); // liga a interrupção para o timer 0
  bitSet(INTCON, 7); // habilita todas as interrupções globais
  bitSet(INTCON, 6); // habilita todas as interrupções de perifericos

  kernelLoop();
}
