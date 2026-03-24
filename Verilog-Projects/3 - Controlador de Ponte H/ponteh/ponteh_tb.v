`timescale 1 ps/ 1 ps
module ponteh_tb();

	reg CLK, FR;
	reg [1:0] RGT, [1:0] VLR;

	wire SA, SH;

	ponteh mod(CLK, RGT, VLR, FR, SA,SH);
	
	initial
	begin
		#10000000  $finish;
	end
	
	//FR
	always
	begin
		FR = 1'b0;
		FR = #10000 1'b1;
		#10000;
	end 

	//CLK
	always
	begin
		CLK = 1'b0;
		CLK = #50000 1'b1;
		#50000;
	end 

	//RGT[1]
	initial
	begin
		RGT[1] = 1'b0;
		RGT[1] = #240000 1'b1;
		RGT[1] = #110000 1'b0;
		RGT[1] = #300000 1'b1;
		RGT[1] = #160000 1'b0;
	end 

	//RGT[0]
	initial
	begin
		RGT[0] = 1'b0;
		RGT[0] = #120000 1'b1;
		RGT[0] = #120000 1'b0;
		RGT[0] = #310000 1'b1;
		RGT[0] = #100000 1'b0;
	end 

	//VLR[1]
	initial
	begin
		VLR[1] = 1'b0;
		VLR[1] = #240000 1'b1;
		VLR[1] = #110000 1'b0;
		VLR[1] = #90000 1'b1;
		VLR[1] = #110000 1'b0;
	end 

	//VLR[0]
	initial
	begin
		VLR[0] = 1'b1;
		VLR[0] = #110000 1'b0;
		VLR[0] = #440000 1'b1;
		VLR[0] = #120000 1'b0;
	end 
	
endmodule 