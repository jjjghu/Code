module counter_loop(clk, rst, count);
    input clk, rst;
    output reg [5:0] count;
    parameter [5:0] MX = 30;
    always@(posedge clk or posedge rst)
    begin
        if(rst)
        begin
            count = 0;
        end
        else
        begin
            // 0~30
            if(count == MX)
            begin
                count = 0;
            end
            else
                count = count + 1;
        end
    end
endmodule