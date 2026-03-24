 /*
 ------------------------------------------------------------
 Discente: Getúlio Victor 
 
 ELTD12A - Eletrônica Digital II
 
 Projeto Direcionado - Controlador de Mistura
 
------------------------ Requisitos--------------------------
Levar em consideraçao:

 1) Volume Atual da Mistura

 2) Nivel de concentraçao atual de um dos liquidos que a compoe

 3) Nivel de concetracao pretendido para esse mesmo liquido

---------- ---------------Funçoes do CKT----------------------

 1) Comandar a injeçao de cada um dos liquidos na mistura

 2) A açao do misturador

 3) despejo da mistura
---------------------------------------------------------------
*/
 
module mistura(L,M,C,D,A,B,R,E);

	input L; // Sensor de nível para o limite de volume (1, nível atingido) 
	input M; // Sensor de nível mínimo para acionar o misturador (1, nível atingido)
	input [6:0] C; // Percentual de concentração corrente para o líquido A (valores decimais de 0 a 100) 
	input [6:0] D; // Percentual de concentração-alvo para o líquido A (valores decimais de 0 a 100)

	output reg A; // Acionamento da válvula para injeção do líquido A (abertura em nível 1)
	output reg B; // Acionamento da válvula para injeção do líquido B (abertura em nível 1)
	output reg R; // Acionamento do misturador (ativo em nível 1).
	output reg E; // Acionamento da válvula de escoamento (abertura em nível 1)
	
	
	always@(*)
	begin
	
		if (C < D)
		begin
			A = 1'b1; //insere liquido A
			B = 1'b0;
		end
		
		else if (C > D)
		begin
			A = 1'b0;
			B = 1'b1; //insere liquido B
		end
		
		if (C == D)
		begin
			
			if(L != 1'b1) //insere os liquidos A e B ate atingir o limite
			begin
				A = 1'b1;
				B = 1'b1;
			
			
				if(D == 7'd100) //caso a concentracao esteja em 100 mas nao atingiu o limite insere o liquido A
					begin
						A = 1'b1;
						B = 1'b0;
					end
				
				else if (D == 7'd0) //caso a concentracao esteja em 0 e o limite nao foi atingido, insere o liquido B
					begin
						A = 1'b0;
						B = 1'b1;
					end	
			
			end						
		
			else
			begin
					A = 1'b0; //cessa a insercao de liquidos
					B = 1'b0; 
			end
		
		
		end
			
		
	end
		
			always @(*) E = (L & (A | B)); //Despejar a mistura, precisa que  haja a insercao do liquido A ou B e que o limite tenha sido atingido
	
			always @(*) R = (M & (A | B)); //Rotacionar o misturador, precisamos do nivel minimo para realizar a mistura, e que haja insercao do liquido A ou B
	
	
endmodule 
