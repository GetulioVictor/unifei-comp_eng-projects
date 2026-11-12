;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW64)
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4520
	radix	dec
	CONFIG	MCLRE=ON
	CONFIG	OSC=HS
	CONFIG	WDT=OFF
	CONFIG	LVP=OFF
	CONFIG	DEBUG=OFF
	CONFIG	WDTPS=1
	CONFIG	XINST=OFF


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_ISR
	global	_t1
	global	_main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	_kernelInit
	extern	_kernelAddProc
	extern	_kernelLoop
	extern	_KernelClock
	extern	_timerInit

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PRODL	equ	0xff3
PRODH	equ	0xff4


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1

udata_main_0	udata
_main_p1_1_16	res	7

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_main_ivec_0x1_ISR	code	0X000008
ivec_0x1_ISR:
	GOTO	_ISR

; I code from now on!
; ; Starting pCode block
S_main__main	code
_main:
;	.line	29; main.c	process p1 = {t1, 100, 0};
	MOVLW	LOW(_t1)
	BANKSEL	_main_p1_1_16
	MOVWF	_main_p1_1_16, B
	MOVLW	HIGH(_t1)
	BANKSEL	(_main_p1_1_16 + 1)
	MOVWF	(_main_p1_1_16 + 1), B
	MOVLW	UPPER(_t1)
	BANKSEL	(_main_p1_1_16 + 2)
	MOVWF	(_main_p1_1_16 + 2), B
	MOVLW	0x64
	BANKSEL	(_main_p1_1_16 + 3)
	MOVWF	(_main_p1_1_16 + 3), B
	BANKSEL	(_main_p1_1_16 + 4)
	CLRF	(_main_p1_1_16 + 4), B
	BANKSEL	(_main_p1_1_16 + 5)
	CLRF	(_main_p1_1_16 + 5), B
	BANKSEL	(_main_p1_1_16 + 6)
	CLRF	(_main_p1_1_16 + 6), B
;	.line	30; main.c	TRISD = 0x00;
	LFSR	0x00, 0xf95
	MOVLW	0x00
	MOVWF	INDF0
;	.line	31; main.c	timerInit();
	CALL	_timerInit
;	.line	35; main.c	kernelInit();
	CALL	_kernelInit
;	.line	36; main.c	kernelAddProc(&p1);
	MOVLW	HIGH(_main_p1_1_16)
	MOVWF	r0x01
	MOVLW	LOW(_main_p1_1_16)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_kernelAddProc
	MOVLW	0x03
	ADDWF	FSR1L, F
;	.line	40; main.c	BitClr(RCON, 7); // desabilita IPEN ( modo de compatibilidade )
	LFSR	0x00, 0xfd0
	MOVFF	INDF0, r0x00
	BCF	r0x00, 7
	LFSR	0x00, 0xfd0
	MOVFF	r0x00, INDF0
;	.line	41; main.c	BitSet(INTCON, 5); // liga a interrupção para o timer 0
	LFSR	0x00, 0xff2
	MOVFF	INDF0, r0x00
	BSF	r0x00, 5
	LFSR	0x00, 0xff2
	MOVFF	r0x00, INDF0
;	.line	42; main.c	BitSet(INTCON, 7); // habilita todas as interrupções globais
	LFSR	0x00, 0xff2
	MOVFF	INDF0, r0x00
	BSF	r0x00, 7
	LFSR	0x00, 0xff2
	MOVFF	r0x00, INDF0
;	.line	43; main.c	BitSet(INTCON, 6); // habilita todas as interrupções de perifericos
	LFSR	0x00, 0xff2
	MOVFF	INDF0, r0x00
	BSF	r0x00, 6
	LFSR	0x00, 0xff2
	MOVFF	r0x00, INDF0
;	.line	46; main.c	kernelLoop();
	CALL	_kernelLoop
	RETURN	

; ; Starting pCode block
S_main__t1	code
_t1:
;	.line	23; main.c	char t1(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	24; main.c	PORTD = PORTD + 1;
	LFSR	0x00, 0xf83
	MOVFF	INDF0, r0x00
	INCF	r0x00, F
	LFSR	0x00, 0xf83
	MOVFF	r0x00, INDF0
;	.line	25; main.c	return REPEAT;
	MOVLW	0x02
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_main__ISR	code
_ISR:
;	.line	9; main.c	void ISR(void) __interrupt 1 {
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	11; main.c	if (BitTst(INTCON, 2)) {
	LFSR	0x00, 0xff2
	MOVFF	INDF0, r0x00
	BTFSS	r0x00, 2
	BRA	_00107_DS_
;	.line	13; main.c	TMR0H = (45535 >> 8);
	LFSR	0x00, 0xfd7
	MOVLW	0xb1
	MOVWF	INDF0
;	.line	14; main.c	TMR0L = (45535 & 0x00FF);
	LFSR	0x00, 0xfd6
	MOVLW	0xdf
	MOVWF	INDF0
;	.line	16; main.c	KernelClock();
	CALL	_KernelClock
;	.line	19; main.c	BitClr(INTCON, 2);
	LFSR	0x00, 0xff2
	MOVFF	INDF0, r0x00
	BCF	r0x00, 2
	LFSR	0x00, 0xff2
	MOVFF	r0x00, INDF0
_00107_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	



; Statistics:
; code size:	  346 (0x015a) bytes ( 0.26%)
;           	  173 (0x00ad) words
; udata size:	    7 (0x0007) bytes ( 0.55%)
; access size:	    3 (0x0003) bytes


	end
