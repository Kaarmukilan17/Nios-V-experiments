	component sevenseg is
		port (
			clk_clk                             : in  std_logic                    := 'X';             -- clk
			reset_reset_n                       : in  std_logic                    := 'X';             -- reset_n
			pio_0_external_connection_export    : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			hex0_pio_external_connection_export : out std_logic_vector(6 downto 0)                     -- export
		);
	end component sevenseg;

	u0 : component sevenseg
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                        reset.reset_n
			pio_0_external_connection_export    => CONNECTED_TO_pio_0_external_connection_export,    --    pio_0_external_connection.export
			hex0_pio_external_connection_export => CONNECTED_TO_hex0_pio_external_connection_export  -- hex0_pio_external_connection.export
		);

