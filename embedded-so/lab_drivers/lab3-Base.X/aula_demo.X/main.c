#include "config.h"
#include "pic18f4520.h"
#include "kernel.h"
#include "timer.h"


//interrupt setup

void ISR(void) __interrupt 1 {
    //TIMER0: Overflow
    if (BitTst(INTCON, 2)) {
        // 65535 ? 2*10.000 = 10mS
        TMR0H = (45535 >> 8);
        TMR0L = (45535 & 0x00FF);

        KernelClock();

        //limpa a flag
        BitClr(INTCON, 2);
    }
}

char t1(void) {
    PORTD = PORTD + 1;
    return REPEAT;
}

void main(void) {
    process p1 = {t1, 100, 0};
    process p_count   = {process_clock_count,  100, 0};
    process p_display = {process_clock_display, 100, 0};

    TRISD = 0x00;

    timerInit();
    clockInit();
    kernelInit();

    kernelAddProc(&p1);
    kernelAddProc(&p_count);
    kernelAddProc(&p_display);

    //interrupt start
    BitClr(RCON, 7); // desabilita IPEN ( modo de compatibilidade )
    BitSet(INTCON, 5); // liga a interrup��o para o timer 0
    BitSet(INTCON, 7); // habilita todas as interrup��es globais
    BitSet(INTCON, 6); // habilita todas as interrup��es de perifericos


    kernelLoop();
}
