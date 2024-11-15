module num_to_seg(num, led4, led3, led2, led1);
    input [31:0] num;
    output reg led4, led3, led2, led1;
    always @(num)
    begin
        case(num) 
            0:begin
                led4 = 0;
                led3 = 0;
                led2 = 0;
                led1 = 0;
            end
            1: begin
                led4 = 0;
                led3 = 0;
                led2 = 1;
                led1 = 1;
            end
            2: begin
                led4 = 1;
                led3 = 0;
                led2 = 0;
                led1 = 1;
            end
            3: begin
                led4 = 0;
                led3 = 1;
                led2 = 1;
                led1 = 0;
            end
        endcase
    end
endmodule
// 0000
// 0011
// 1001
// 0110