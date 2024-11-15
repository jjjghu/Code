module num_to_led(num, led1, led2, led3, led4);
    input [1:0] num;
    output reg led1, led2, led3, led4;

    always @(num) begin
        case(num)
            2'b00: {led1, led2, led3, led4} = 4'b0000; // 0
            2'b01: {led1, led2, led3, led4} = 4'b0011; // 3
            2'b10: {led1, led2, led3, led4} = 4'b1001; // 6
            2'b11: {led1, led2, led3, led4} = 4'b0110; // 9
            default: {led1, led2, led3, led4} = 4'b1111; // error
        endcase
    end
endmodule
