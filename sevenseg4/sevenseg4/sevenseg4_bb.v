
module sevenseg4 (
	clk_clk,
	reset_reset_n,
	hex0_pio_external_connection_export,
	hex1_pio_external_connection_export,
	hex2_pio_external_connection_export,
	hex3_pio_external_connection_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[6:0]	hex0_pio_external_connection_export;
	output	[6:0]	hex1_pio_external_connection_export;
	output	[6:0]	hex2_pio_external_connection_export;
	output	[6:0]	hex3_pio_external_connection_export;
endmodule
