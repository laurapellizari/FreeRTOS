#ifndef drvKeypad_h
    #define drvKeypad_h
    #include "dd_types.h"

    //lista de fun��es do driver
    enum {
        KP_READ, KP_DB, KP_END
    };

    //fun��o de acesso ao driver
    driver* getKeypadDriver(void);

#endif // drvGenerico_h

