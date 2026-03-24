/*
Discente: Getúlio Victor
Disciplina: ELTD12A - Eletrônica Digital II
Projeto: Controlador Ponte H
*/

/*
-------------Requisitos--------------
1) Registros de Operação
	- OPE (Operação)
	- DIV (Divisor de Frequência)
	- CMO (Modulação)
2) Divisor de Frequência
3) Modulação
4) Geração das Saídas
*/

/*
-------Observações-------------------
 Divisor de Frequência
	Entradas: FR e DIV
	Saída: Fo
 Modulação
 	Entradas: Fo e CMO
 	Saída: Am
 Geração das Saídas
 	Entradas: Am, Fo e OPE
 	Saídas: SA e SH
*/

module ponteh(CLK, RGT, VLR, FR, SA,SH);

	input CLK; // Sinal de sincronismo para se configurar a operação do circuito
	input [1:0] RGT; //Sinal de especificação de registro de operação do circuito
	input [1:0] VLR; //Sinal de especificação de valor de registro de operação do circuito
	input FR; //Sinal de sincronismo de referência para a acionamentos das saídas
	output SA; //Controle dos pares de saída que geram rotação no sentido anti-horário
	output SH; //Controle dos pares de saída que geram rotação no sentido horário
	
	reg [1:0]OPE;
	reg [1:0]DIV;
	reg [1:0]CMO;
	
	wire Am, Fo;

	//Seleciona qual registro deve ser utilizado
	always@(posedge CLK) 
	begin
		if (RGT == 2'b00)
			OPE = VLR;
		else if (RGT == 2'b01)
			DIV = VLR;
		else if (RGT == 2'b10)
			CMO = VLR;
	end
	
	divisor mod1(DIV, FR, Fo);
	modulacao mod2(Fo, CMO, Am);
	saidas mod3(Am, Fo, OPE, SA, SH);
	
endmodule

//-------Divisor de Frequência----
module divisor(DIV,FR,Fo);
	input [1:0] DIV;
	input FR;
	output reg Fo;
	reg fr2, fr4, fr8;

	always@(posedge FR)
	begin
	 fr2 = ~fr2;
	end
	
	always@(posedge fr2)
	begin
	 fr4 = ~fr4;
	end
	
	always@(posedge fr4)
	begin
	 fr8 = ~fr8; //Fo
	end
	
	always@(*)
		begin
			case(DIV)
				2'b00: Fo = FR;
				2'b01: Fo = fr2;
				2'b10: Fo = fr4;
				2'b11: Fo = fr8;
			endcase
		end
		
endmodule

//--------Modulação----------------
module modulacao(Fo,	CMO, Am);
	input [1:0] CMO;
	input Fo;
	
	reg [1:0] count;
	output reg Am;
	reg am25, am50, am75;
	

	always @(posedge Fo)
	begin
	
		count = count + 2'h1;
		
		am25 = (count < 1);
		am50 = (count < 2);
		am75 = (count < 3);
		
	end
	
	always @(*)
	begin
	
		case (CMO)
			2'd0: Am = am25;
			2'd1: Am = am50;
			2'd2: Am = am75;
			2'd3: Am = 1;
		endcase
		
	end
	
endmodule

//--------Geração das Saídas-------
module saidas(Am, Fo, OPE, SA, SH);

	input Am;
	input Fo;
	input [1:0]OPE;
	output reg SA, SH;
	
	always@(posedge Fo)
	begin
		case(OPE)
			2'b01:
				begin
					SA = (Am && Fo);
					SH = 1'b0;
				end
			2'b10:
				begin
					SA = 1'b0;
					SH = (Am && Fo);
				end
			default:
				begin
					SA = 1'b0;
					SH = 1'b0;
				end
		endcase
			
	end


endmodule 
