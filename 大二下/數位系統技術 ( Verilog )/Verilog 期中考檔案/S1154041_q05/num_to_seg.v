module num_to_seg(num, seg1, seg2, seg3, seg1_dpt, seg2_dpt, seg3_dpt);
    input [5:0] num;
    output reg [6:0] seg1, seg2, seg3;
    output reg seg1_dpt, seg2_dpt, seg3_dpt;
    always @(num)
    begin
        case(num)
            0:begin
                    {seg1, seg1_dpt} = {7'b1000000, 1'b1};
                    {seg2, seg2_dpt} = {7'b1000000, 1'b1};
                    {seg3, seg3_dpt} = {7'b1000000, 1'b1}; 
            end
            1: {seg1, seg1_dpt} = {7'b1111001, 1'b1}; // 1
            2: {seg1, seg1_dpt} = {7'b0100100, 1'b1}; // 2
            3: {seg1, seg1_dpt} = {7'b0110000, 1'b1}; // 3
            4: {seg1, seg1_dpt} = {7'b0011001, 1'b1}; // 4

            5: {seg2, seg2_dpt} = {7'b1111001, 1'b1}; // 1
            6: {seg2, seg2_dpt} = {7'b0100100, 1'b1}; // 2
            7: {seg2, seg2_dpt} = {7'b0110000, 1'b1}; // 3
            8: {seg2, seg2_dpt} = {7'b0011001, 1'b1}; // 4
            9: {seg2, seg2_dpt} = {7'b0010010, 1'b1}; // 5

            10: {seg3, seg3_dpt} = {7'b1111001, 1'b1}; // 1
            11: {seg3, seg3_dpt} = {7'b0100100, 1'b1}; // 2
            12: {seg3, seg3_dpt} = {7'b0110000, 1'b1}; // 3
            13: {seg3, seg3_dpt} = {7'b0011001, 1'b1}; // 4
            14: {seg3, seg3_dpt} = {7'b0010010, 1'b1}; // 5
            15: {seg3, seg3_dpt} = {7'b0000010, 1'b1}; // 6

            16: {seg1, seg1_dpt} = {7'b0010010, 1'b1}; // 5
            17: {seg1, seg1_dpt} = {7'b0000010, 1'b1}; // 6
            18: {seg1, seg1_dpt} = {7'b1111000, 1'b1}; // 7
            19: {seg1, seg1_dpt} = {7'b0000000, 1'b1}; // 8
            20: {seg1, seg1_dpt} = {7'b0010000, 1'b1}; // 9
            21: {seg1, seg1_dpt} = {7'b1000000, 1'b1}; // 0

            22: {seg2, seg2_dpt} = {7'b0000010, 1'b1}; // 6
            23: {seg2, seg2_dpt} = {7'b1111000, 1'b1}; // 7
            24: {seg2, seg2_dpt} = {7'b0000000, 1'b1}; // 8
            25: {seg2, seg2_dpt} = {7'b0010000, 1'b1}; // 9
            26: {seg2, seg2_dpt} = {7'b1000000, 1'b1}; // 0

            27: {seg3, seg3_dpt} = {7'b1111000, 1'b1}; // 7
            28: {seg3, seg3_dpt} = {7'b0000000, 1'b1}; // 8
            29: {seg3, seg3_dpt} = {7'b0010000, 1'b1}; // 9
            30: {seg3, seg3_dpt} = {7'b1000000, 1'b1}; // 0
				
            default: {seg3, seg3_dpt} = {7'b1111111, 1'b1}; // error
        endcase
    end
endmodule
