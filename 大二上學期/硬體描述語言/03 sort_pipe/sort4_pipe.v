module reg8bit(input clk, rst, reg [7:0] enter, output reg[7:0] box);
    always @(posedge clk or posedge rst) begin
        if (rst) begin // reset all reg
		box <= 0;
        end else begin // sort item
		box <= enter;
        end
    end
endmodule
module sort4_pipe(input clk, input rst, input [7:0] x0, x1, x2, x3, output [7:0] y0, y1, y2, y3);
    task sort2; // using task since always can't use named module
        input [7:0] A, B;
        output [7:0] min, max;
        begin
            if (A < B) begin
                min = A;
                max = B;
            end else begin
                min = B;
                max = A;
            end
        end
    endtask

    reg [7:0] stage1_min0, stage1_max0, stage1_min1, stage1_max1;
    reg [7:0] stage2_min, stage2_max, stage2_mid0, stage2_mid1;

    wire [7:0] stage0_1, stage0_2, stage0_3, stage0_4;
    wire [7:0] stage3_min, stage3_mid0, stage3_mid1, stage3_max;

    reg8bit stage0_reg0(clk, rst, x0, stage0_1);
    reg8bit stage0_reg1(clk, rst, x1, stage0_2);
    reg8bit stage0_reg2(clk, rst, x2, stage0_3);
    reg8bit stage0_reg3(clk, rst, x3, stage0_4);

    always @(posedge clk or posedge rst) begin
        if (rst) begin // reset all reg
            stage1_min0 <= 0; stage1_max0 <= 0; stage1_min1 <= 0; stage1_max1 <= 0;
            stage2_min <= 0; stage2_max <= 0; stage2_mid0 <= 0; stage2_mid1 <= 0;
        end else begin // sort item
            sort2(stage0_1, stage0_2, stage1_min0, stage1_max0);
            sort2(stage0_3, stage0_4, stage1_min1, stage1_max1);

            sort2(stage1_min0, stage1_min1, stage2_min, stage2_mid0);
            sort2(stage1_max0, stage1_max1, stage2_mid1, stage2_max);
        end
    end

    reg8bit stage3_reg0(clk, rst, stage2_min, y0); // when posedge then activate 
    reg8bit stage3_reg1(clk, rst, stage2_mid0, y1);
    reg8bit stage3_reg2(clk, rst, stage2_mid1, y2);
    reg8bit stage3_reg3(clk, rst, stage2_max, y3);
endmodule

