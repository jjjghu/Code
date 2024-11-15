module clkUpdate(sw2, sw1, clkSelect, clkFast, clkMedium, clkSlow);
	input sw2, sw1, clkFast, clkMedium, clkSlow;
	output reg clkSelect;
    always @(sw2 or sw1)
    begin
        if(sw2 == 0 && sw1 == 0)
            clkSelect = clkSlow;
        else if(sw2 == 1 && sw1 == 0)
            clkSelect = clkMedium;
        else if(sw2 == 1 && sw1 == 1)
            clkSelect = clkFast;
        else
            clkSelect = clkSelect;
    end
 endmodule