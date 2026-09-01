
module sevenseg (
	clk_clk,
	reset_reset_n,
	pio_0_external_connection_export,
	hex0_pio_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	input	[3:0]	pio_0_external_connection_export;
	output	[6:0]	hex0_pio_external_connection_export;
endmodule
