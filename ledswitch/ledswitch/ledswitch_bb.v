
module ledswitch (
	clk_clk,
	reset_reset_n,
	led_pio_external_connection_export,
	switch_pio_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[3:0]	led_pio_external_connection_export;
	input	[3:0]	switch_pio_external_connection_export;
endmodule
