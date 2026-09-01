	component sevenseg4 is
		port (
			clk_clk                             : in  std_logic                    := 'X'; -- clk
			reset_reset_n                       : in  std_logic                    := 'X'; -- reset_n
			hex0_pio_external_connection_export : out std_logic_vector(6 downto 0);        -- export
			hex1_pio_external_connection_export : out std_logic_vector(6 downto 0);        -- export
			hex2_pio_external_connection_export : out std_logic_vector(6 downto 0);        -- export
			hex3_pio_external_connection_export : out std_logic_vector(6 downto 0)         -- export
		);
	end component sevenseg4;

	u0 : component sevenseg4
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                        reset.reset_n
			hex0_pio_external_connection_export => CONNECTED_TO_hex0_pio_external_connection_export, -- hex0_pio_external_connection.export
			hex1_pio_external_connection_export => CONNECTED_TO_hex1_pio_external_connection_export, -- hex1_pio_external_connection.export
			hex2_pio_external_connection_export => CONNECTED_TO_hex2_pio_external_connection_export, -- hex2_pio_external_connection.export
			hex3_pio_external_connection_export => CONNECTED_TO_hex3_pio_external_connection_export  -- hex3_pio_external_connection.export
		);

