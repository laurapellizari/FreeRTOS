#ifndef drvLed_h
    #define drvLed_h
    #include "dd_types.h"

    //lista de fun��es do driver
    enum {
        LED_SET,LED_FLIP, LED_END
    };

    //fun��o de acesso ao driver
    driver* getLedDriver(void);

#endif // drvGenerico_h

