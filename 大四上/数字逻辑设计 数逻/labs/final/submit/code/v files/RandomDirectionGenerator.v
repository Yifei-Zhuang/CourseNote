`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:08:42 12/06/2023 
// Design Name: 
// Module Name:    RandomDirectionGenerator 
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
// ��ģ�����������������
module RandomDirectionGenerator(
	input wire clk,
  // �µķ���
  output reg [1:0] direction);
  integer i;
  initial begin
      i = 0;
  end
  always @(posedge clk) begin
	 i <= i + 1;
    // ���·���
    direction <= i % 4;
  end

endmodule
