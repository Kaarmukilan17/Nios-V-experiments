
module pushbutton (
	clk_clk,
	reset_reset_n,
	button_pio_external_connection_export,
	led_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[3:0]	button_pio_external_connection_export;
	output	[3:0]	led_external_connection_export;
endmodule
