#ifndef drvLcd_h
    #define drvLcd_h
    #include "dd_types.h"

    //lista de fun��es do driver
    enum {
        LCD_DATA, LCD_CMD, LCD_END
    };

    //fun��o de acesso ao driver
    driver* getLcdDriver(void);

#endif // drvGenerico_h

