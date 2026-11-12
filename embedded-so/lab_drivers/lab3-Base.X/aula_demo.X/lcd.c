// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: lcd.c
//            Biblioteca de manipulação do LCD
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------


#include "lcd.h"
#include "pic18f4520.h"

#define RS 0
#define EN 1
#define RW 2

void Delay40us(void)
{
	unsigned char i;
	for(i=0; i < 25; i++); //valor aproximado
}

void Delay2ms(void)
{
	unsigned char i;
	for(i=0; i < 50; i++)
	{
		Delay40us();
	}
}


void lcdCommand(unsigned char cmd)
{
	BitClr(PORTE,RS);	//comando
	BitClr(PORTE,RW);	// habilita escrita
	PORTD = cmd;

    BitSet(PORTE,EN);   //Pulso no Enable
	BitClr(PORTE,EN);
    if((cmd == 0x02)||(cmd == 0x01)){
       Delay2ms();   
    }else{
	   Delay40us();
    }
}

void lcdData(unsigned char valor)
{
	BitSet(PORTE,RS);	//dados
	BitClr(PORTE,RW);	// habilita escrita


	PORTD = valor;
	
    BitSet(PORTE,EN);   //Pulso no Enable
	BitClr(PORTE,EN);
    
	BitClr(PORTE,RS);	//deixa em nivel baixo por causa do display de 7 seg
	Delay40us();
}
 

void lcdInit(void){
	// configurações de direção dos terminais
	BitClr(TRISE,RS);	//RS
	BitClr(TRISE,EN);	//EN
	BitClr(TRISE,RW);	//RW
	TRISD = 0x00;		//dados
	ADCON1 = 0b00001110;	//apenas

    // garante inicialização do LCD (+-10ms)
	Delay2ms(); Delay2ms();	Delay2ms();	Delay2ms();	Delay2ms();
    //precisa enviar 4x pra garantir 8 bits
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    Delay2ms();	Delay2ms();
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    Delay2ms();
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    
    lcdCommand(0x38);	//8bits, 2 linhas, 5x8
    lcdCommand(0x06);	//modo incremental
    lcdCommand(0x0F);	//display e cursor on, com blink
    lcdCommand(0x01);	//limpar display
}
