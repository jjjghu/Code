module num_to_seg(num, seg3, seg2, seg1);
    input [31:0] num;
    output reg [6:0] seg3, seg2, seg1;
    // 000 003 032 321 210 100 loop
    always @(num)
    begin
        case(num)
            0:begin
                seg3 = 7'b1000000; // 0
                seg2 = 7'b1000000; // 0
                seg1 = 7'b1000000; // 0
            end
            1: begin
                seg3 = 7'b1000000; // 0
                seg2 = 7'b1000000; // 0
                seg1 = 7'b0110000; // 3
            end
            2: begin
                seg3 = 7'b1000000; // 0
                seg2 = 7'b0110000; // 3
                seg1 = 7'b0100100; // 2
            end
            3: begin
                seg3 = 7'b0110000; // 3
                seg2 = 7'b0100100; // 2
                seg1 = 7'b1111001; // 1
            end
            4: begin
                seg3 = 7'b0100100; // 2
                seg2 = 7'b1111001; // 1
                seg1 = 7'b1000000; // 0
            end
            5: begin
                seg3 = 7'b1111001; // 1
                seg2 = 7'b1000000; // 0
                seg1 = 7'b1000000; // 0
            end
            default: begin
                seg3 = 7'b0111111; // 0
                seg2 = 7'b0111111; // 0
                seg1 = 7'b0111111; // 0
            end
        endcase
    end
endmodule