`timescale 1ms / 1ns

module ahb_pwm(
    input              I_ahb_clk,
    input              I_rst,

    input   [1:0]      I_ahb_htrans,
    input              I_ahb_hwrite,
    input   [31:0]     I_ahb_haddr,       //synthesis keep
    input   [2:0]      I_ahb_hsize,
    input   [2:0]      I_ahb_hburst,
    input   [3:0]      I_ahb_hprot,
    input              I_ahb_hmastlock,
    input   [31:0]     I_ahb_hwdata,      //synthesis keep
    output  reg [31:0] O_ahb_hrdata,      //synthesis keep
    output  wire[1:0]  O_ahb_hresp,
    output  reg        O_ahb_hready,
    output  [7:0]  	   pwmo

);

    reg        S_ahb_wr_trig;
    reg        S_ahb_wr_trig_1d;
    reg[31:0]  S_ahb_wr_addr;
    reg[31:0]  S_ahb_wr_data;

    reg        S_ahb_rd_trig;
    reg        S_ahb_rd_trig_1d;
    reg[31:0]  S_ahb_rd_addr;
    reg[31:0]  S_ahb_rd_data; 
    
// Registers
reg [31:00] clkdiv;
reg [31:00] period0;
reg [31:00] period1;
reg [31:00] period2;
reg [31:00] period3;
reg [31:00] period4;
reg [31:00] period5;
reg [31:00] period6;
reg [31:00] period7;
reg [31:00] duty0;
reg [31:00] duty1;
reg [31:00] duty2;
reg [31:00] duty3;
reg [31:00] duty4;
reg [31:00] duty5;
reg [31:00] duty6;
reg [31:00] duty7;
reg [7:0]	en;

    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            O_ahb_hready <= 1'b1;
        else
            if(I_ahb_htrans == 2'b10)
                O_ahb_hready <= 1'b0;
            else if(S_ahb_wr_trig_1d || S_ahb_rd_trig_1d)
                O_ahb_hready <= 1'b1;
            else
                O_ahb_hready <= O_ahb_hready;
    end

    
    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            S_ahb_wr_trig <= 1'b0;
        else
            if(I_ahb_htrans == 2'b10 && I_ahb_hwrite)
                S_ahb_wr_trig <= 1'b1;
            else
                S_ahb_wr_trig <= 1'b0;
    end

    always @(posedge I_ahb_clk) begin
        S_ahb_wr_trig_1d <= S_ahb_wr_trig;
    end

    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            S_ahb_wr_addr <= 'd0;
        else
            if(S_ahb_wr_trig)
                S_ahb_wr_addr <= I_ahb_haddr;
            else
                S_ahb_wr_addr <= S_ahb_wr_addr;
    end

    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            S_ahb_wr_data <= 'd0;
        else
            if(S_ahb_wr_trig)
                S_ahb_wr_data <= I_ahb_hwdata;
            else
                S_ahb_wr_data <= S_ahb_wr_data;
    end


    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            begin
                en  		<= 'd0;
                clkdiv		<= 'd0;     	
                period0 	<= 'd0;   
                period1  	<= 'd0;   
                period2  	<= 'd0;   
                period3  	<= 'd0;   
                period4  	<= 'd0;
                period5  	<= 'd0;   
                period6  	<= 'd0;   
                period7  	<= 'd0;   
				duty0  		<= 'd0;      	
				duty1  		<= 'd0;      	
				duty2 		<= 'd0;     	
                duty3 		<= 'd0;     	
                duty4 		<= 'd0;     	
                duty5 		<= 'd0;     	
                duty6 		<= 'd0;     	
                duty7 		<= 'd0;     	
            end
        else
            begin
                if(S_ahb_wr_trig_1d)
                    begin
                        case(S_ahb_wr_addr[7:0])
                            8'h00:  en  	  <= S_ahb_wr_data;  
                            8'h04:  clkdiv    <= S_ahb_wr_data;  
                            8'h08:  period0   <= S_ahb_wr_data;  
                            8'h0C:  period1   <= S_ahb_wr_data;  
                            8'h10:  period2   <= S_ahb_wr_data;  
                            8'h14:  period3   <= S_ahb_wr_data;  
                            8'h18:  period4   <= S_ahb_wr_data;  
                            8'h1C:  period5   <= S_ahb_wr_data;  
                            8'h20:  period6   <= S_ahb_wr_data;  
                            8'h24:  period7   <= S_ahb_wr_data;  
                            8'h28:  duty0  	  <= S_ahb_wr_data;  
                            8'h2C:  duty1  	  <= S_ahb_wr_data;  
                            8'h30:  duty2 	  <= S_ahb_wr_data;  
                            8'h34:  duty3 	  <= S_ahb_wr_data;  
                            8'h38:  duty4 	  <= S_ahb_wr_data;  
                            8'h3c:  duty5 	  <= S_ahb_wr_data;
                            8'h40:  duty6 	  <= S_ahb_wr_data; 
                            8'h44:  duty7 	  <= S_ahb_wr_data;
                        endcase
                    end
                else
                    begin
                        en  	 <= en  	;
                        clkdiv   <= clkdiv  ;
                        period0  <= period0 ;
                        period1  <= period1 ;
                        period2  <= period2 ;
                        period3  <= period3 ;
                        period4  <= period4 ;
                        period5  <= period5 ;
                        period6  <= period6 ;
                        period7  <= period7 ;
                        duty0  	 <= duty0  	;
                        duty1  	 <= duty1  	;
                        duty2 	 <= duty2 	;
                        duty3 	 <= duty3 	;
                        duty4 	 <= duty4 	;
                        duty5 	 <= duty5 	;
                        duty6 	 <= duty6 	;
                        duty7 	 <= duty7 	;

                    end
            end
    end



    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            S_ahb_rd_trig <= 1'b0;
        else
            if(I_ahb_htrans == 2'b10 && (!I_ahb_hwrite))
                S_ahb_rd_trig <= 1'b1;
            else
                S_ahb_rd_trig <= 1'b0;
    end

    always @(posedge I_ahb_clk) begin
        S_ahb_rd_trig_1d <= S_ahb_rd_trig;
    end

    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            S_ahb_rd_addr <= 'd0;
        else
            if(S_ahb_rd_trig)
                S_ahb_rd_addr <= I_ahb_haddr;
            else
                S_ahb_rd_addr <= S_ahb_rd_addr;
    end


    always @(posedge I_ahb_clk or posedge I_rst) begin
        if(I_rst)
            O_ahb_hrdata <= 'd0;
        else
            begin
                if(S_ahb_rd_trig_1d)
                    begin
                        case(S_ahb_rd_addr[7:0])
                            8'h00: O_ahb_hrdata  <=en  	    ;
                            8'h04: O_ahb_hrdata  <=clkdiv   ;
                            8'h08: O_ahb_hrdata  <=period0  ;
                            8'h0C: O_ahb_hrdata  <=period1  ;
                            8'h10: O_ahb_hrdata  <=period2  ;
                            8'h14: O_ahb_hrdata  <=period3  ;
                            8'h18: O_ahb_hrdata  <=period4  ;
                            8'h1C: O_ahb_hrdata  <=period5  ;
                            8'h20: O_ahb_hrdata  <=period6  ;
                            8'h24: O_ahb_hrdata  <=period7  ;
                            8'h28: O_ahb_hrdata  <=duty0    ;  
                            8'h2C: O_ahb_hrdata  <=duty1    ;  
                            8'h30: O_ahb_hrdata  <=duty2    ;  
                            8'h34: O_ahb_hrdata  <=duty3    ;  
                            8'h38: O_ahb_hrdata  <=duty4    ;  
                            8'h3c: O_ahb_hrdata  <=duty5    ;
                            8'h40: O_ahb_hrdata  <=duty6    ;
                            8'h44: O_ahb_hrdata  <=duty7    ; 
                        endcase
                    end
                else
                    O_ahb_hrdata <= O_ahb_hrdata;
            end
    end


/* Counter */

counter pwm0(.clk(I_ahb_clk), .clkdiv(clkdiv[3:0]  ), .period(period0), .duty(duty0), .state(pwmo[0]), .en(en[0]));
counter pwm1(.clk(I_ahb_clk), .clkdiv(clkdiv[7:4]  ), .period(period1), .duty(duty1), .state(pwmo[1]), .en(en[1]));
counter pwm2(.clk(I_ahb_clk), .clkdiv(clkdiv[11:8] ), .period(period2), .duty(duty2), .state(pwmo[2]), .en(en[2]));
counter pwm3(.clk(I_ahb_clk), .clkdiv(clkdiv[15:12]), .period(period3), .duty(duty3), .state(pwmo[3]), .en(en[3]));
counter pwm4(.clk(I_ahb_clk), .clkdiv(clkdiv[19:16]), .period(period4), .duty(duty4), .state(pwmo[4]), .en(en[4]));
counter pwm5(.clk(I_ahb_clk), .clkdiv(clkdiv[23:20]), .period(period5), .duty(duty5), .state(pwmo[5]), .en(en[5]));
counter pwm6(.clk(I_ahb_clk), .clkdiv(clkdiv[27:24]), .period(period6), .duty(duty6), .state(pwmo[6]), .en(en[6]));
counter pwm7(.clk(I_ahb_clk), .clkdiv(clkdiv[31:28]), .period(period7), .duty(duty7), .state(pwmo[7]), .en(en[7]));

endmodule


module counter(
    input clk,
    input [3:0] clkdiv,
    input en,
    input [31:0] period,
    input [31:0] duty,
    output reg   state
    ); 

// Registers
wire clk_div      ;
reg clk_div1      ;
reg clk_div2      ;

reg [4:0] contclk = 0;
reg [32:0] contper = 0;

	always @(posedge clk) begin
		if(en == 1)begin
			if (contclk == clkdiv) begin  //clkdiv+1 为分频系数
                contclk = 0;
                clk_div1 = ~clk_div1;
            end else begin 
                contclk = contclk+1;
                end
		end
	end

    always @(negedge clk) begin
        if(en == 1) begin
            if (contclk == (clkdiv)/2) begin
                clk_div2 = ~clk_div2;
            end
        end
    end

assign clk_div = clk_div1^clk_div2;

	always @(posedge clk_div) begin
		if(en == 1)begin
			if(contper >= period-1) begin // Period is registered in ms.
				contper = 0;
			end else begin
				contper = contper + 1;
			end
		end
	end

	always @(posedge clk_div) begin
		if(en == 1)begin
			if(contper <= duty-1)begin
				state = 1;
			end else begin
				state = 0;
			end
		end
	end


endmodule