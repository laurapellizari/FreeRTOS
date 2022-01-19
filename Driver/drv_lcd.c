#include "kernel.h"
#include <pic18f4520.h>
#include "drv_lcd.h"
#include "lcd.h"

static driver myself;
static ptrFuncDrv my_funcs[LCD_END];

char cmd (void *parameters) {
    lcdCommand((char)parameters);
    return SUCCESS;
}
char data (void * parameters){
    lcdData((char) parameters);
    return SUCCESS;
}
char initLCD(void *parameters) {
    lcdInit();
    myself.id = (char) parameters;
    return SUCCESS;
}
driver* getLcdDriver(void) {
    myself.initFunc = initLCD;
    my_funcs[LCD_CMD] = cmd;
    my_funcs[LCD_DATA] = data;
    myself.funcoes = my_funcs;
    return &myself;
}


