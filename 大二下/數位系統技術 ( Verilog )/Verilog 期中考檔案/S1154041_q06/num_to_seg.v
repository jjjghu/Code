module num_to_seg(num, seg, seg_dpt);
    input [3:0] num;
    output reg [6:0] seg;
    output reg seg_dpt;
    always @(num)
    begin
        case(num)
            0: {seg, seg_dpt} = {7'b1111110, 1'b1}; // 0
            1: {seg, seg_dpt} = {7'b1111101, 1'b1}; // 1
            2: {seg, seg_dpt} = {7'b1111011, 1'b1}; // 2
            3: {seg, seg_dpt} = {7'b1110111, 1'b1}; // 3
            4: {seg, seg_dpt} = {7'b1101111, 1'b1}; // 4
            5: {seg, seg_dpt} = {7'b1011111, 1'b1}; // 5
            default: {seg, seg_dpt} = {7'b1000000, 1'b0}; // error
        endcase
    end
endmodule
