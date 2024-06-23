`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:54:57 12/06/2023 
// Design Name: 
// Module Name:    ButtonCheck 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ButtonCheck(
	// 按钮
	input wire [3:0]btn,
	// 解析当前按下的按钮对应的方向 btn[0] -> LEFT, btn[1] -> RIGHT, btn[2] -> UP, btn[3] -> DOWN
	output reg [3:0] parseResult
    );
	 
	 always @* begin
		parseResult[0] = (btn[0]) ? 1'b0 : 1'b1;
		parseResult[1] = (btn[1]) ? 1'b0 : 1'b1;
		parseResult[2] = (btn[2]) ? 1'b0 : 1'b1;
		parseResult[3] = (btn[3]) ? 1'b0 : 1'b1;
	end
	
endmodule
