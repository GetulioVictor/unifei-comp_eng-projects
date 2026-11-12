#include "drv_lcd.h"
#include "lcd.h"         
#include "kernel.h"

static driver myself;
static ptrFuncDrv my_funcs[LCD_END];

char lcd_init_display(void *parameters) {
    Lcd_Init();
    return SUCCESS;
}

char lcd_write_string(void *parameters) {
    Lcd_Write_String((char *)parameters);
    return SUCCESS;
}

char lcd_set_cursor(void *parameters) {
    char *pos = (char *)parameters;
    Lcd_Set_Cursor(pos[0], pos[1]);
    return SUCCESS;
}

char lcd_clear(void *parameters) {
    Lcd_Clear();
    return SUCCESS;
}

char initLcd(void *parameters) {
    myself.id = (char)parameters;
    Lcd_Init();
    return SUCCESS;
}

driver* getLcdDriver(void) {
    myself.initFunc = initLcd;
    my_funcs[LCD_INIT_DISPLAY] = lcd_init_display;
    my_funcs[LCD_WRITE_STRING]  = lcd_write_string;
    my_funcs[LCD_SET_CURSOR]    = lcd_set_cursor;
    my_funcs[LCD_CLEAR]         = lcd_clear;
    myself.funcoes = my_funcs;
    return &myself;
}