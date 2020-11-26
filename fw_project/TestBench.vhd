-- LC
-- Code your testbench here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY TestBench IS
END TestBench;

ARCHITECTURE Arch OF TestBench IS
    signal multiplier	: STD_LOGIC_VECTOR(31 DOWNTO 0);
    signal multiplicand : STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    signal activate 	: std_logic;
	signal clock		: std_logic;
	signal valid		: std_logic;
    
    signal result		: STD_LOGIC_VECTOR(63 DOWNTO 0);
BEGIN
	clock <= not clock after 10 ns;

	TL_E : entity work.TopLevel(Arch)
    	PORT MAP (multiplier, multiplicand, activate, clock, valid, result);
    
    process
	begin
    	report "Start";
		for i in 15 downto 0 loop
			multiplier <= std_logic_vector(to_unsigned(i,32));
			for j in 15 downto 0 loop
				multiplicand <= std_logic_vector(to_unsigned(j,32));
				activate <= '0', '1' after 5 ns, '0' after 40 ns;
				wait for 50 ns;
				wait until valid = '1';
                assert (to_integer(unsigned(result)) = (i * j)) report "Wrong Result" severity NOTE;
                report "The value of 'result' is " & integer'image((to_integer(unsigned(result))));
                report "The value of 'i * j' is " & integer'image(i * j);
				wait for 50 ns;
			end loop;
		end loop;
        wait for 500 ns;
	end process;
END Arch;