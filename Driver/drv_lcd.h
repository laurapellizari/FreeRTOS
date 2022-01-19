#ifndef drvLcd_h
    #define drvLcd_h
    #include "dd_types.h"

    //lista de funções do driver
    enum {
        LCD_DATA, LCD_CMD, LCD_END
    };

    //função de acesso ao driver
    driver* getLcdDriver(void);

#endif // drvGenerico_h

