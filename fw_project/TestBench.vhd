-- LC
-- Code your testbench here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY TestBench IS
GENERIC(
	N: integer := 32;
    POW: integer := 5
);
END TestBench;

ARCHITECTURE Arch OF TestBench IS
    signal multiplier	: STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    signal multiplicand : STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    
    signal activate 	: std_logic := '0';
	signal clock 		: std_logic := '0';
	signal valid		: std_logic := '0';
    
    signal result		: STD_LOGIC_VECTOR(2*N-1 DOWNTO 0);
BEGIN
	clock <= not clock after 20 ns;

	TL_E : entity work.TopLevel(Arch)
    	GENERIC MAP (N, POW)
    	PORT MAP (multiplier, multiplicand, result, activate, clock, valid);
    
    process
	begin
    	report "Start";
        
		for i in 1 to 10 loop
			multiplier <= std_logic_vector(to_unsigned(i,N));

			for j in 1 to 10 loop
				multiplicand <= std_logic_vector(to_unsigned(j,N));
                
				activate <= '0', '1' after 5 ns, '0' after 40 ns;
				wait for 50 ns;
				wait until valid = '1';
                                
                report "i: " & integer'image(i);
                report "j: " & integer'image(j);
                report "i * j: " & integer'image(i * j);
                report "result: " & integer'image((to_integer(unsigned(result))));
                
                assert to_integer(unsigned(result)) = (i * j) report "Wrong Result";
                
				wait for 50 ns;
			end loop;
		end loop;
        
        report "End";
        wait;
	end process;
END Arch;