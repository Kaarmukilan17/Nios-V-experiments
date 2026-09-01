	component pushbutton is
		port (
			button_pio_external_connection_export : in  std_logic_vector(2 downto 0) := (others => 'X'); -- export
			clk_clk                               : in  std_logic                    := 'X';             -- clk
			led_external_connection_export        : out std_logic_vector(2 downto 0);                    -- export
			reset_reset_n                         : in  std_logic                    := 'X'              -- reset_n
		);
	end component pushbutton;

	u0 : component pushbutton
		port map (
			button_pio_external_connection_export => CONNECTED_TO_button_pio_external_connection_export, -- button_pio_external_connection.export
			clk_clk                               => CONNECTED_TO_clk_clk,                               --                            clk.clk
			led_external_connection_export        => CONNECTED_TO_led_external_connection_export,        --        led_external_connection.export
			reset_reset_n                         => CONNECTED_TO_reset_reset_n                          --                          reset.reset_n
		);

