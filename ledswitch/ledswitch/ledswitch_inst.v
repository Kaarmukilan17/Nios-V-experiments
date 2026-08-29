	ledswitch u0 (
		.clk_clk                               (<connected-to-clk_clk>),                               //                            clk.clk
		.reset_reset_n                         (<connected-to-reset_reset_n>),                         //                          reset.reset_n
		.led_pio_external_connection_export    (<connected-to-led_pio_external_connection_export>),    //    led_pio_external_connection.export
		.switch_pio_external_connection_export (<connected-to-switch_pio_external_connection_export>)  // switch_pio_external_connection.export
	);

