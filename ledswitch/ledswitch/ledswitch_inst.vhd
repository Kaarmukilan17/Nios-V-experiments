	component ledswitch is
		port (
			clk_clk                               : in  std_logic                    := 'X';             -- clk
			reset_reset_n                         : in  std_logic                    := 'X';             -- reset_n
			led_pio_external_connection_export    : out std_logic_vector(3 downto 0);                    -- export
			switch_pio_external_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X')  -- export
		);
	end component ledswitch;

	u0 : component ledswitch
		port map (
			clk_clk                               => CONNECTED_TO_clk_clk,                               --                            clk.clk
			reset_reset_n                         => CONNECTED_TO_reset_reset_n,                         --                          reset.reset_n
			led_pio_external_connection_export    => CONNECTED_TO_led_pio_external_connection_export,    --    led_pio_external_connection.export
			switch_pio_external_connection_export => CONNECTED_TO_switch_pio_external_connection_export  -- switch_pio_external_connection.export
		);

