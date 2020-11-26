-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;

ENTITY VectorAdder IS PORT(
    a   		: IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    b			: IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    sum_out		: OUT STD_LOGIC_VECTOR(32 DOWNTO 0)
);
END VectorAdder;

ARCHITECTURE Arch OF VectorAdder IS
BEGIN
    sum_out <= ('0' & a) + ('0' & b);
END Arch;