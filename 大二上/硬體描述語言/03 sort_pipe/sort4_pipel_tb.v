module sort4_pipel_tb;
    reg [7:0] x0, x1, x2, x3;
    wire [7:0] y0, y1, y2, y3;
    reg clk = 0, rst = 0;
    reg [5:0] index = 0;
    reg [7:0] counter=0;
    reg flag = 1;


    reg [7:0] test[0:31]; 

    always #20 clk = ~clk; 

    sort4_pipe sorter(clk, rst, x0, x1, x2, x3, y0, y1, y2, y3);

    initial begin
        test[0] = 8'd38; test[1] = 8'd94; test[2] = 8'd61; test[3] = 8'd50;
        test[4] = 8'd24; test[5] = 8'd15; test[6] = 8'd82; test[7] = 8'd65;
        test[8] = 8'd89; test[9] = 8'd20; test[10] = 8'd63; test[11] = 8'd51;
        test[12] = 8'd72; test[13] = 8'd24; test[14] = 8'd36; test[15] = 8'd77;
        test[16] = 8'd50; test[17] = 8'd69; test[18] = 8'd13; test[19] = 8'd30;
        test[20] = 8'd23; test[21] = 8'd60; test[22] = 8'd30; test[23] = 8'd11;
        test[24] = 8'd45; test[25] = 8'd54; test[26] = 8'd22; test[27] = 8'd56;
        test[28] = 8'd71; test[29] = 8'd42; test[30] = 8'd90; test[31] = 8'd89;
        #500 $finish;
    end
    always @(posedge clk) begin
        {x0, x1, x2, x3} <= {test[index], test[index+1], test[index+2], test[index+3]};
        $display("Time: %t, Input X: %d %d %d %d, Output Y: %d %d %d %d", $time, x0, x1, x2, x3, y0, y1, y2, y3);
        index <= index + 4;
        if (index >= 32) index <= 0;
        if (y0 <= y1 && y1 <= y2 && y2 <= y3) begin
            $display("Time: %3d ns, Pass!", $time); 
        end else begin
            $display("Time: %3d ns, Fail!", $time);
        end
    end
endmodule
