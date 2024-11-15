module S1154041_q01(sw3, sw2, sw1, seg3, seg2, seg1);
    input sw3, sw2, sw1;
    output [6:0] seg3, seg2, seg1;
    wire [31:0] n3, n2, n1;
    switch_to_num stn(sw3, sw2, sw1, n3, n2, n1);
    num_to_seg nts3(n3, seg3);
    num_to_seg nts2(n2, seg2);
    num_to_seg nts1(n1, seg1);
endmodule