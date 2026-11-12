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
	global	_lcdCommand
	global	_lcdData
	global	_lcdInit
	global	_Delay40us
	global	_Delay2ms

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_lcd__lcdInit	code
_lcdInit:
;	.line	75; lcd.c	void lcdInit(void){
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
;	.line	77; lcd.c	BitClr(TRISE,RS);	//RS
	LFSR	0x00, 0xf96
	MOVFF	INDF0, r0x00
	BCF	r0x00, 0
	LFSR	0x00, 0xf96
	MOVFF	r0x00, INDF0
;	.line	78; lcd.c	BitClr(TRISE,EN);	//EN
	LFSR	0x00, 0xf96
	MOVFF	INDF0, r0x00
	BCF	r0x00, 1
	LFSR	0x00, 0xf96
	MOVFF	r0x00, INDF0
;	.line	79; lcd.c	BitClr(TRISE,RW);	//RW
	LFSR	0x00, 0xf96
	MOVFF	INDF0, r0x00
	BCF	r0x00, 2
	LFSR	0x00, 0xf96
	MOVFF	r0x00, INDF0
;	.line	80; lcd.c	TRISD = 0x00;		//dados
	LFSR	0x00, 0xf95
	MOVLW	0x00
	MOVWF	INDF0
;	.line	81; lcd.c	ADCON1 = 0b00001110;	//apenas
	LFSR	0x00, 0xfc1
	MOVLW	0x0e
	MOVWF	INDF0
;	.line	84; lcd.c	Delay2ms(); Delay2ms();	Delay2ms();	Delay2ms();	Delay2ms();
	CALL	_Delay2ms
	CALL	_Delay2ms
	CALL	_Delay2ms
	CALL	_Delay2ms
	CALL	_Delay2ms
;	.line	86; lcd.c	lcdCommand(0x38);	//8bits, 2 linhas, 5x8
	MOVLW	0x38
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
;	.line	87; lcd.c	Delay2ms();	Delay2ms();
	CALL	_Delay2ms
	CALL	_Delay2ms
;	.line	88; lcd.c	lcdCommand(0x38);	//8bits, 2 linhas, 5x8
	MOVLW	0x38
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
;	.line	89; lcd.c	Delay2ms();
	CALL	_Delay2ms
;	.line	90; lcd.c	lcdCommand(0x38);	//8bits, 2 linhas, 5x8
	MOVLW	0x38
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
;	.line	92; lcd.c	lcdCommand(0x38);	//8bits, 2 linhas, 5x8
	MOVLW	0x38
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
;	.line	93; lcd.c	lcdCommand(0x06);	//modo incremental
	MOVLW	0x06
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
;	.line	94; lcd.c	lcdCommand(0x0F);	//display e cursor on, com blink
	MOVLW	0x0f
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
;	.line	95; lcd.c	lcdCommand(0x01);	//limpar display
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_lcdCommand
	MOVF	POSTINC1, F
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_lcd__lcdData	code
_lcdData:
;	.line	59; lcd.c	void lcdData(unsigned char valor)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	61; lcd.c	BitSet(PORTE,RS);	//dados
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x01
	BSF	r0x01, 0
	LFSR	0x00, 0xf84
	MOVFF	r0x01, INDF0
;	.line	62; lcd.c	BitClr(PORTE,RW);	// habilita escrita
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x01
	BCF	r0x01, 2
	LFSR	0x00, 0xf84
	MOVFF	r0x01, INDF0
;	.line	65; lcd.c	PORTD = valor;
	LFSR	0x00, 0xf83
	MOVFF	r0x00, INDF0
;	.line	67; lcd.c	BitSet(PORTE,EN);   //Pulso no Enable
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x00
	BSF	r0x00, 1
	LFSR	0x00, 0xf84
	MOVFF	r0x00, INDF0
;	.line	68; lcd.c	BitClr(PORTE,EN);
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x00
	BCF	r0x00, 1
	LFSR	0x00, 0xf84
	MOVFF	r0x00, INDF0
;	.line	70; lcd.c	BitClr(PORTE,RS);	//deixa em nivel baixo por causa do display de 7 seg
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x00
	BCF	r0x00, 0
	LFSR	0x00, 0xf84
	MOVFF	r0x00, INDF0
;	.line	71; lcd.c	Delay40us();
	CALL	_Delay40us
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_lcd__lcdCommand	code
_lcdCommand:
;	.line	44; lcd.c	void lcdCommand(unsigned char cmd)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
;	.line	46; lcd.c	BitClr(PORTE,RS);	//comando
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x01
	BCF	r0x01, 0
	LFSR	0x00, 0xf84
	MOVFF	r0x01, INDF0
;	.line	47; lcd.c	BitClr(PORTE,RW);	// habilita escrita
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x01
	BCF	r0x01, 2
	LFSR	0x00, 0xf84
	MOVFF	r0x01, INDF0
;	.line	48; lcd.c	PORTD = cmd;
	LFSR	0x00, 0xf83
	MOVFF	r0x00, INDF0
;	.line	50; lcd.c	BitSet(PORTE,EN);   //Pulso no Enable
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x01
	BSF	r0x01, 1
	LFSR	0x00, 0xf84
	MOVFF	r0x01, INDF0
;	.line	51; lcd.c	BitClr(PORTE,EN);
	LFSR	0x00, 0xf84
	MOVFF	INDF0, r0x01
	BCF	r0x01, 1
	LFSR	0x00, 0xf84
	MOVFF	r0x01, INDF0
;	.line	52; lcd.c	if((cmd == 0x02)||(cmd == 0x01)){
	MOVF	r0x00, W
	XORLW	0x02
	BZ	_00123_DS_
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00124_DS_
_00123_DS_:
;	.line	53; lcd.c	Delay2ms();   
	CALL	_Delay2ms
	BRA	_00127_DS_
_00124_DS_:
;	.line	55; lcd.c	Delay40us();
	CALL	_Delay40us
_00127_DS_:
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_lcd__Delay2ms	code
_Delay2ms:
;	.line	34; lcd.c	void Delay2ms(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
;	.line	37; lcd.c	for(i=0; i < 50; i++)
	MOVLW	0x32
	MOVWF	r0x00
_00117_DS_:
;	.line	39; lcd.c	Delay40us();
	CALL	_Delay40us
	DECF	r0x00, W
	MOVWF	r0x01
	MOVFF	r0x01, r0x00
;	.line	37; lcd.c	for(i=0; i < 50; i++)
	MOVF	r0x01, W
	BNZ	_00117_DS_
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_lcd__Delay40us	code
_Delay40us:
;	.line	28; lcd.c	void Delay40us(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
;	.line	31; lcd.c	for(i=0; i < 25; i++); //valor aproximado
	MOVLW	0x19
	MOVWF	r0x00
_00108_DS_:
	DECF	r0x00, W
	MOVWF	r0x01
	MOVFF	r0x01, r0x00
	MOVF	r0x01, W
	BNZ	_00108_DS_
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  566 (0x0236) bytes ( 0.43%)
;           	  283 (0x011b) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    2 (0x0002) bytes


	end
