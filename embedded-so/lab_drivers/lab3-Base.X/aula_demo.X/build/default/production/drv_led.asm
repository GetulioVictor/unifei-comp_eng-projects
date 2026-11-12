;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.6.0 #9615 (MINGW64)
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4520
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_getLedDriver
	global	_changePORTD
	global	_inverte
	global	_initGenerico

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
WREG	equ	0xfe8
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1

udata_drv_led_0	udata
_myself	res	7

udata_drv_led_1	udata
_my_funcs	res	6

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_drv_led__getLedDriver	code
_getLedDriver:
;	.line	21; drv_led.c	driver* getLedDriver(void) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
;	.line	22; drv_led.c	myself.initFunc = initGenerico;
	MOVLW	LOW(_initGenerico)
	BANKSEL	(_myself + 4)
	MOVWF	(_myself + 4), B
	MOVLW	HIGH(_initGenerico)
	BANKSEL	(_myself + 5)
	MOVWF	(_myself + 5), B
	MOVLW	UPPER(_initGenerico)
	BANKSEL	(_myself + 6)
	MOVWF	(_myself + 6), B
;	.line	23; drv_led.c	my_funcs[LED_SET] = changePORTD;
	MOVLW	LOW(_changePORTD)
	BANKSEL	_my_funcs
	MOVWF	_my_funcs, B
	MOVLW	HIGH(_changePORTD)
	BANKSEL	(_my_funcs + 1)
	MOVWF	(_my_funcs + 1), B
	MOVLW	UPPER(_changePORTD)
	BANKSEL	(_my_funcs + 2)
	MOVWF	(_my_funcs + 2), B
;	.line	24; drv_led.c	my_funcs[LED_FLIP] = inverte;
	MOVLW	LOW(_inverte)
	BANKSEL	(_my_funcs + 3)
	MOVWF	(_my_funcs + 3), B
	MOVLW	HIGH(_inverte)
	BANKSEL	(_my_funcs + 4)
	MOVWF	(_my_funcs + 4), B
	MOVLW	UPPER(_inverte)
	BANKSEL	(_my_funcs + 5)
	MOVWF	(_my_funcs + 5), B
;	.line	25; drv_led.c	myself.funcoes = my_funcs;
	MOVLW	HIGH(_my_funcs)
	MOVWF	r0x01
	MOVLW	LOW(_my_funcs)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x00, W
	BANKSEL	(_myself + 1)
	MOVWF	(_myself + 1), B
	MOVF	r0x01, W
	BANKSEL	(_myself + 2)
	MOVWF	(_myself + 2), B
	MOVF	r0x02, W
	BANKSEL	(_myself + 3)
	MOVWF	(_myself + 3), B
;	.line	26; drv_led.c	return &myself;
	MOVLW	HIGH(_myself)
	MOVWF	r0x01
	MOVLW	LOW(_myself)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVFF	r0x02, PRODH
	MOVFF	r0x01, PRODL
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_drv_led__initGenerico	code
_initGenerico:
;	.line	16; drv_led.c	char initGenerico(void *parameters) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
;	.line	17; drv_led.c	TRISD = 0x00;
	LFSR	0x00, 0xf95
	MOVLW	0x00
	MOVWF	INDF0
;	.line	18; drv_led.c	myself.id = (char) parameters;
	MOVF	r0x00, W
	BANKSEL	_myself
	MOVWF	_myself, B
;	.line	19; drv_led.c	return SUCCESS;
	CLRF	WREG
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_drv_led__inverte	code
_inverte:
;	.line	11; drv_led.c	char inverte(void * parameters){
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	13; drv_led.c	PORTD = ~PORTD;
	LFSR	0x00, 0xf83
	MOVFF	INDF0, r0x00
	COMF	r0x00, F
	LFSR	0x00, 0xf83
	MOVFF	r0x00, INDF0
;	.line	14; drv_led.c	return SUCCESS;
	CLRF	WREG
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_drv_led__changePORTD	code
_changePORTD:
;	.line	7; drv_led.c	char changePORTD(void *parameters) {
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
;	.line	8; drv_led.c	PORTD = (char) parameters;
	LFSR	0x00, 0xf83
	MOVFF	r0x00, INDF0
;	.line	9; drv_led.c	return SUCCESS;
	CLRF	WREG
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  324 (0x0144) bytes ( 0.25%)
;           	  162 (0x00a2) words
; udata size:	   13 (0x000d) bytes ( 1.02%)
; access size:	    3 (0x0003) bytes


	end
