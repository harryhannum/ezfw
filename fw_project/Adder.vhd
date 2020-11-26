-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY VectorAdder IS 
GENERIC(N: integer := 32);
PORT(
    a   		: IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    b			: IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    sum_out		: OUT STD_LOGIC_VECTOR(N DOWNTO 0)
);
END VectorAdder;

ARCHITECTURE Arch OF VectorAdder IS
BEGIN
    sum_out <= std_logic_vector(('0' & unsigned(a)) + unsigned(b));
END Arch;