
module pushbutton (
	button_pio_external_connection_export,
	clk_clk,
	led_external_connection_export,
	reset_reset_n);	

	input	[2:0]	button_pio_external_connection_export;
	input		clk_clk;
	output	[2:0]	led_external_connection_export;
	input		reset_reset_n;
endmodule
