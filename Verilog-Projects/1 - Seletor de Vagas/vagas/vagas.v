module vagas(VE, VD, P, V, L, B);

	input [3:0] VE; // Bloco E
	input [3:0] VD; // Bloco D
	input P; // Preferencia  E = 0 D = 1
	
	output reg [1:0] V; //Numero da Vaga
	output reg L; // Indica Vaga Livre
	output reg B; //Bloco a ser usado E = 0 D = 1
	
	reg E, D; 		// 
	reg [2:0] SE; //Numero da vaga do Bloco E 
								//3 bits - 1° preferencia 2° e 3° - Vaga
	reg [2:0] SD; //Numero da Vaga do Bloco D
	reg [2:0] i;  //3 bits - 1° preferencia 2° e 3° - Vaga
	
	always @(*)
	begin	
		E = 0;
		D = 0;
		L = 0;
		
		//Verificacao se a vaga esta livre
		for(i = 0; i < 4; i = i + 1)
		begin
			if (VE[i] == 0)
				E = 1;
				//L = 1;
			if (VD[i] == 0)
				D = 1;
				//L = 1;
		end
		
		//logica para o Bloco que esta sendo utilizado
		
		B = 0;
		
		// Bloco E
		if (P == 0 && E == 1)
			B = 0;
		if (P == 0 && E == 0 && D == 1)
			B = 1;
		if (P == 1 && D == 1)
			B = 1;
		if (P == 1 && D == 0 && E == 1)
			B = 0;
		
		//selecao	
		if (B == 0)
		begin
			for (i = 0; i < 4; i = i + 1)
				begin
				 if (VE[i] == 0)
				 begin
					V = i; // manda o numero da vaga para a saida
					L = 1; // a vaga esta livre
				 end
				end
		end
		
		else
		begin
		
			for (i = 0; i < 4; i = i + 1)
				begin
				 if (VD[i] == 0)
				 begin
					V = i; // manda o numero da vaga para a saida
					L = 1; // a vaga esta livre
				 end
				end
		end
		
	end
 endmodule 