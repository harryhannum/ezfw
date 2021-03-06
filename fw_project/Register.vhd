-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY ShiftableRegister IS 
GENERIC(N: integer := 32);
PORT(
    input   		: IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    output  		: OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    
    clock   		: IN STD_LOGIC;
    load    		: IN STD_LOGIC;
    clear   		: IN STD_LOGIC;

	shift         	: IN STD_LOGIC;
    rotation_value 	: IN STD_LOGIC
);
END ShiftableRegister;

ARCHITECTURE Arch OF ShiftableRegister IS
	signal internal : STD_LOGIC_VECTOR(N-1 DOWNTO 0);
BEGIN
    process(clock)
    begin
    	if rising_edge(clock) then
        	if clear = '1' then
            	internal <= (others => '0');
            elsif load = '1' then
                internal <= input;
            elsif shift = '1' then
            	internal <= rotation_value & internal(N-1 downto 1);
            end if;
        end if;
    end process;
    
    output <= internal;
END Arch;