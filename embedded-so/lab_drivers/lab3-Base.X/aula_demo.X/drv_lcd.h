#ifndef DRV_LCD_H
#define DRV_LCD_H

#include "dd_types.h"

enum {
    LCD_INIT_DISPLAY,
    LCD_WRITE_STRING,
    LCD_SET_CURSOR,
    LCD_CLEAR,
    LCD_END
};

driver* getLcdDriver(void);

#endif 