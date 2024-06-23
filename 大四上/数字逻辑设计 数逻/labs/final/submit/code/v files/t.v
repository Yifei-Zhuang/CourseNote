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
  // 使能按钮
  assign BTNX4 = 0;
  // 四个方向
  parameter LEFT=2'b00, DOWN=2'b01, UP=2'b10, RIGHT=2'b11;
  // 游戏状态
  parameter INIT=3'b000, CHECK=3'b001, WAIT=3'b010, UPDATEDIRECTION=3'b011, PROMOTE = 3'b100, FAIL = 3'b101;
  // 最大难度
  parameter MAX_LEVEL = 10;
  // 默认倒计时时间
  parameter DEFAULT_COUNT_DOWN = 15;
  // T的横线部分宽度
  parameter THICKNESS = 20;
  // VGA显示行数
  parameter ROWS = 640;
  // VGA显示列数
  parameter COLS = 480;
  // T的横线部分长度
  parameter SINGLE_LENGTH = 100;

  // 游戏状态
  reg [2:0] state;
  initial begin
	state <= INIT;
  end
	
  // 前一个500ms的按钮信息
  reg [3:0] previous_btn;
  // 生成随机方向
  wire [1:0] random_direction;
  // VGA显示的方向
  reg [1:0] real_direction; 
  // 按下按钮对应的方向
  wire [3:0] button_direction; 
  // 当前按错/超时的次数
  reg [3:0] error_count;
  // 当前按对次数
  reg [3:0] success_count;
  // 当前难度等级
  reg [3:0] current_level;   
  // 倒计时时间
  reg [15:0] countdown; 
  // 按钮防抖动
  wire [3:0]btn_pbd;
  // 时钟信号
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
			// 如果当前是左方向，那么绘制一个红色的左T
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
			// 如果当前是上方向，那么绘制一个绿色的T
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
			// 如果当前是下方向，那么绘制一个绿色的倒T
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
			// 如果当前是右方向，那么绘制一个红色的右T
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
			// 其余区域，填充黑色
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
		  // 执行初始化工作
        current_level <= 0;
        success_count <= 0;
        error_count <= 0;
        countdown <= DEFAULT_COUNT_DOWN;
        real_direction <= LEFT;
        state <= WAIT;
      end
      WAIT:begin
		  // 存储前一时刻的BTN
        previous_btn <= btn_pbd;
		  // 如果按钮按下，进入CHECK逻辑
        if(btn_pbd < previous_btn) begin
          state <= CHECK;
        end
		  // 如果倒计时不是0，自减即可
			if (countdown > 0) begin
				countdown <= countdown - 1;
			end else begin
		  // 倒计时为0，此次按钮失败，进入失败逻辑
				state <= FAIL;
			end
      end
      CHECK: begin
        // 检查按钮方向和VGA显示的方向是否一致
        if (
			(real_direction == LEFT && button_direction == 4'b1000) || 
			(real_direction == DOWN && button_direction == 4'b0100)   || 
			(real_direction == UP && button_direction == 4'b0010) || 
			(real_direction == RIGHT && button_direction == 4'b0001)
		  ) begin
		    // 更新成功次数
          success_count <= success_count + 1;
			 // 达到阈值，那么进入PROMOTE状态（提升难度）
          if (success_count == 10 && current_level <= MAX_LEVEL) begin
				state <= PROMOTE;
          end else begin
			 // 没有达到阈值，那么更新方向即可
				state <= UPDATEDIRECTION;
			 end
        end else begin
		    // 按错按钮了，进入失败逻辑
			 state <= FAIL;
        end
      end
      UPDATEDIRECTION:begin
		   // 更新当前方向，即将Random_gen生成的随机方向写入real_direction
			// 这里可以看到，倒计时和难度是负相关的，也就是难度越高，倒计时时间越短，留给每次按钮的时间越短
			// 本项目使用此方式实现难度提升
			if(current_level + current_level < DEFAULT_COUNT_DOWN) begin	
				countdown <= DEFAULT_COUNT_DOWN - current_level - current_level;
			end else begin
				countdown <= 1;
			end
        real_direction <= random_direction;
		  // 等待下次按钮信号
        state <= WAIT;
      end
		PROMOTE: begin
			 // 提升难度
			 current_level <= current_level + 1;
			 success_count <= 0;
			 error_count <= 0;
			 state <= UPDATEDIRECTION;
		end 
		FAIL: begin
			// 失败次数大于3，本次游戏结束，重新进入初始化逻辑
			if (error_count >= 3) begin
            state <= INIT;
          end else begin
			   // 失败次数没有大于3，那么更新失败次数，然后更新状态为UPDATEDIRECTION
            error_count <= error_count + 1;
            state <= UPDATEDIRECTION;
          end
		end
		endcase
  end
  // 将倒计时显示在4位7段数码管上
  disp_num d0(.clk(clk),.HEXS(countdown),.LES(4'b0000),.points(4'b0000),.rst(1'b0),.AN(AN),.SEGMENT(SEGMENT));
	
  // 8位七段数码管显示{5872,{当前难度},{当前错误次数},{当前成功次数},{当前方向}}，其中，5872是我的学号
  SSeg7_Dev m3(.clk(clk), .flash(1'b0), .Hexs({16'b0101_1000_0111_0010,current_level,error_count,success_count,2'b00,real_direction}), .LES(8'b0000_0000),
					  .point(8'b0000_0000), .rst(1'b0), .Start(clkdiv[20]), .seg_clk(seg_clk),
					  .seg_clrn(seg_clrn), .SEG_PEN(SEG_PEN), .seg_sout(seg_sout),.SW0(SSeg_SW0));

endmodule