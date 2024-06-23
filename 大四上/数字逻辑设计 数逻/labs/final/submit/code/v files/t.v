`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:08:57 12/07/2023 
// Design Name: 
// Module Name:    t 
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
module t(
  input wire clk, 
  input wire rst,
  input wire clrn, 
  input wire SSeg_SW0,
  input wire [3:0] BTN,
  output wire BTNX4,
  output wire [3:0] AN,
  output wire [7:0] SEGMENT,
  output wire seg_clk,
  output wire seg_sout,
  output wire SEG_PEN,
  output wire seg_clrn,
  output wire VS,
  output wire HS,
  output wire [3:0]r,g,b
    );
  // ʹ�ܰ�ť
  assign BTNX4 = 0;
  // �ĸ�����
  parameter LEFT=2'b00, DOWN=2'b01, UP=2'b10, RIGHT=2'b11;
  // ��Ϸ״̬
  parameter INIT=3'b000, CHECK=3'b001, WAIT=3'b010, UPDATEDIRECTION=3'b011, PROMOTE = 3'b100, FAIL = 3'b101;
  // ����Ѷ�
  parameter MAX_LEVEL = 10;
  // Ĭ�ϵ���ʱʱ��
  parameter DEFAULT_COUNT_DOWN = 15;
  // T�ĺ��߲��ֿ��
  parameter THICKNESS = 20;
  // VGA��ʾ����
  parameter ROWS = 640;
  // VGA��ʾ����
  parameter COLS = 480;
  // T�ĺ��߲��ֳ���
  parameter SINGLE_LENGTH = 100;

  // ��Ϸ״̬
  reg [2:0] state;
  initial begin
	state <= INIT;
  end
	
  // ǰһ��500ms�İ�ť��Ϣ
  reg [3:0] previous_btn;
  // �����������
  wire [1:0] random_direction;
  // VGA��ʾ�ķ���
  reg [1:0] real_direction; 
  // ���°�ť��Ӧ�ķ���
  wire [3:0] button_direction; 
  // ��ǰ����/��ʱ�Ĵ���
  reg [3:0] error_count;
  // ��ǰ���Դ���
  reg [3:0] success_count;
  // ��ǰ�Ѷȵȼ�
  reg [3:0] current_level;   
  // ����ʱʱ��
  reg [15:0] countdown; 
  // ��ť������
  wire [3:0]btn_pbd;
  // ʱ���ź�
  wire clk_1ms;
  wire[31:0] clkdiv;
  
  clkdiv c(.clk(clk), .rst(1'b0), .clkdiv(clkdiv));
  
	reg [11:0] vga_data;
	wire [9:0] col_addr;
	wire [8:0] row_addr;
	wire rdn;
	vgac v0(.vga_clk(clkdiv[1]),.clrn(clrn),.d_in(vga_data),.row_addr(row_addr),.col_addr(col_addr),.r(r),.g(g),.b(b),.hs(HS),.vs(VS));
	
	always@(posedge clk)begin
		if(!rdn)begin
			// �����ǰ��������ô����һ����ɫ����T
			if(real_direction == LEFT) begin
				if(row_addr <= 370 && 
					row_addr >= 170 && 
					col_addr >= 170 && 
					col_addr <= 190)begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'h0;
							vga_data[3:0] <= 4'hf;
				end else if(
					row_addr <= 260 && row_addr >= 240 && 
					col_addr <= 390 && col_addr >= 190
				) begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'h0;
							vga_data[3:0] <= 4'hf;
				end else begin
					vga_data[11:8] <= 4'h0;
					vga_data[7:4] <= 4'h0;
					vga_data[3:0] <= 4'h0;
				end
			// �����ǰ���Ϸ�����ô����һ����ɫ��T
			end else if(real_direction == UP) begin
				if(row_addr <= 190 && 
					row_addr >= 170 && 
					col_addr >= 270 && 
					col_addr <= 370) begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'hf;
							vga_data[3:0] <= 4'h0;
				end else if(
					row_addr <= 290 && row_addr >= 190 && 
					col_addr <= 330 && col_addr >= 310
				) begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'hf;
							vga_data[3:0] <= 4'h0;
				end else begin
					vga_data[11:8] <= 4'h0;
					vga_data[7:4] <= 4'h0;
					vga_data[3:0] <= 4'h0;
				end
			// �����ǰ���·�����ô����һ����ɫ�ĵ�T
			end else if(real_direction == DOWN) begin
				if(row_addr <= 310 && 
					row_addr >= 290 && 
					col_addr >= 270 && 
					col_addr <= 370) begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'hf;
							vga_data[3:0] <= 4'h0;
				end else if(
					row_addr <= 290&& row_addr >= 190 && 
					col_addr <= 330 && col_addr >= 310
				) begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'hf;
							vga_data[3:0] <= 4'h0;
				end else begin
					vga_data[11:8] <= 4'h0;
					vga_data[7:4] <= 4'h0;
					vga_data[3:0] <= 4'h0;
				end
			// �����ǰ���ҷ�����ô����һ����ɫ����T
			end else if(real_direction == RIGHT) begin
				if(row_addr <= 290 && 
					row_addr >= 190 && 
					col_addr >= 370 && 
					col_addr <= 390)begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'h0;
							vga_data[3:0] <= 4'hf;
				end else if(
					row_addr <= 250 && row_addr >= 230 && 
					col_addr <= 370 && col_addr >= 270
				) begin
							vga_data[11:8] <= 4'h0;
							vga_data[7:4] <= 4'h0;
						 	vga_data[3:0] <= 4'hf;
				end else begin
					vga_data[11:8] <= 4'h0;
					vga_data[7:4] <= 4'h0;
					vga_data[3:0] <= 4'h0;
				end
			// ������������ɫ
			end else begin
				vga_data[11:8] <= 4'hf;
				vga_data[7:4] <= 4'hf;
				vga_data[3:0] <= 4'hf;
			end
		end
	end
	
  pbdebounce p0(.clk_1ms(clkdiv[17]), .button(BTN[0]), .pbreg(btn_pbd[0]));
  pbdebounce p1(.clk_1ms(clkdiv[17]), .button(BTN[1]), .pbreg(btn_pbd[1]));
  pbdebounce p2(.clk_1ms(clkdiv[17]), .button(BTN[2]), .pbreg(btn_pbd[2]));
  pbdebounce p3(.clk_1ms(clkdiv[17]), .button(BTN[3]), .pbreg(btn_pbd[3]));
	
	RandomDirectionGenerator random_gen (
	  .clk(clkdiv[25]),
     .direction(random_direction)
	);

  ButtonCheck buttonCheck (
    .btn(btn_pbd),
    .parseResult(button_direction)
  ); 
  always @(posedge clkdiv[23]) begin
    if(rst) begin
      state <= INIT;
    end
    case(state)
      INIT:begin 
		  // ִ�г�ʼ������
        current_level <= 0;
        success_count <= 0;
        error_count <= 0;
        countdown <= DEFAULT_COUNT_DOWN;
        real_direction <= LEFT;
        state <= WAIT;
      end
      WAIT:begin
		  // �洢ǰһʱ�̵�BTN
        previous_btn <= btn_pbd;
		  // �����ť���£�����CHECK�߼�
        if(btn_pbd < previous_btn) begin
          state <= CHECK;
        end
		  // �������ʱ����0���Լ�����
			if (countdown > 0) begin
				countdown <= countdown - 1;
			end else begin
		  // ����ʱΪ0���˴ΰ�ťʧ�ܣ�����ʧ���߼�
				state <= FAIL;
			end
      end
      CHECK: begin
        // ��鰴ť�����VGA��ʾ�ķ����Ƿ�һ��
        if (
			(real_direction == LEFT && button_direction == 4'b1000) || 
			(real_direction == DOWN && button_direction == 4'b0100)   || 
			(real_direction == UP && button_direction == 4'b0010) || 
			(real_direction == RIGHT && button_direction == 4'b0001)
		  ) begin
		    // ���³ɹ�����
          success_count <= success_count + 1;
			 // �ﵽ��ֵ����ô����PROMOTE״̬�������Ѷȣ�
          if (success_count == 10 && current_level <= MAX_LEVEL) begin
				state <= PROMOTE;
          end else begin
			 // û�дﵽ��ֵ����ô���·��򼴿�
				state <= UPDATEDIRECTION;
			 end
        end else begin
		    // ����ť�ˣ�����ʧ���߼�
			 state <= FAIL;
        end
      end
      UPDATEDIRECTION:begin
		   // ���µ�ǰ���򣬼���Random_gen���ɵ��������д��real_direction
			// ������Կ���������ʱ���Ѷ��Ǹ���صģ�Ҳ�����Ѷ�Խ�ߣ�����ʱʱ��Խ�̣�����ÿ�ΰ�ť��ʱ��Խ��
			// ����Ŀʹ�ô˷�ʽʵ���Ѷ�����
			if(current_level + current_level < DEFAULT_COUNT_DOWN) begin	
				countdown <= DEFAULT_COUNT_DOWN - current_level - current_level;
			end else begin
				countdown <= 1;
			end
        real_direction <= random_direction;
		  // �ȴ��´ΰ�ť�ź�
        state <= WAIT;
      end
		PROMOTE: begin
			 // �����Ѷ�
			 current_level <= current_level + 1;
			 success_count <= 0;
			 error_count <= 0;
			 state <= UPDATEDIRECTION;
		end 
		FAIL: begin
			// ʧ�ܴ�������3��������Ϸ���������½����ʼ���߼�
			if (error_count >= 3) begin
            state <= INIT;
          end else begin
			   // ʧ�ܴ���û�д���3����ô����ʧ�ܴ�����Ȼ�����״̬ΪUPDATEDIRECTION
            error_count <= error_count + 1;
            state <= UPDATEDIRECTION;
          end
		end
		endcase
  end
  // ������ʱ��ʾ��4λ7���������
  disp_num d0(.clk(clk),.HEXS(countdown),.LES(4'b0000),.points(4'b0000),.rst(1'b0),.AN(AN),.SEGMENT(SEGMENT));
	
  // 8λ�߶��������ʾ{5872,{��ǰ�Ѷ�},{��ǰ�������},{��ǰ�ɹ�����},{��ǰ����}}�����У�5872���ҵ�ѧ��
  SSeg7_Dev m3(.clk(clk), .flash(1'b0), .Hexs({16'b0101_1000_0111_0010,current_level,error_count,success_count,2'b00,real_direction}), .LES(8'b0000_0000),
					  .point(8'b0000_0000), .rst(1'b0), .Start(clkdiv[20]), .seg_clk(seg_clk),
					  .seg_clrn(seg_clrn), .SEG_PEN(SEG_PEN), .seg_sout(seg_sout),.SW0(SSeg_SW0));

endmodule