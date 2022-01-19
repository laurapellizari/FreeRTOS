#include "kernel.h"
#include <pic18f4520.h>
#include "drv_keypad.h"
#include "keypad.h"

static driver myself;
static ptrFuncDrv my_funcs[KP_END];


char debounce (void) {
    kpDebounce();
    return SUCCESS;
}
char read (void * parameters){
    *((unsigned int *) parameters) = kpRead();
    return SUCCESS;
}
char initKp(void *parameters) {
    kpInit();
    myself.id = (char) parameters;
    return SUCCESS;
}
driver* getKeypadDriver(void) {
    myself.initFunc = initKp;
    my_funcs[KP_DB] = debounce;
    my_funcs[KP_READ] = read;
    myself.funcoes = my_funcs;
    return &myself;
}


