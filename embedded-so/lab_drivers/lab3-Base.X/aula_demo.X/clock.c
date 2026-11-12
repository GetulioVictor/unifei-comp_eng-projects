#include "kernel.h"
#include "drv_lcd.h"

static unsigned char segundos = 0;
static unsigned char minutos  = 0;
static unsigned char horas    = 0;

static driver *lcd;

/* Processo 1: conta o tempo
   Deve ser chamado/agendado a cada 1 segundo pelo kernel */
void process_clock_count(void) {
    segundos++;
    if (segundos >= 60) {
        segundos = 0;
        minutos++;
    }
    if (minutos >= 60) {
        minutos = 0;
        horas++;
    }
    if (horas >= 24) {
        horas = 0;
    }
}

/* Processo 2: exibe o horario no LCD
   Deve ser chamado/agendado a cada 1 segundo pelo kernel */
void process_clock_display(void) {
    char buf[9];          /* "HH:MM:SS\0" */
    char pos[2] = {1, 1}; /* linha 1, coluna 1 */

    /* monta string manualmente (sem sprintf) */
    buf[0] = '0' + horas   / 10;
    buf[1] = '0' + horas   % 10;
    buf[2] = ':';
    buf[3] = '0' + minutos / 10;
    buf[4] = '0' + minutos % 10;
    buf[5] = ':';
    buf[6] = '0' + segundos / 10;
    buf[7] = '0' + segundos % 10;
    buf[8] = '\0';

    /* reposiciona cursor na mesma posicao para nao precisar limpar */
    lcd->funcoes[LCD_SET_CURSOR](pos);
    lcd->funcoes[LCD_WRITE_STRING](buf);
}

void clock_init(void) {
    lcd = getLcdDriver();
    lcd->initFunc((void *)0);
}