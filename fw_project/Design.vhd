-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;

ENTITY TopLevel IS PORT(
    multiplier	 : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    multiplicand : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    activate 	 : in std_logic;
	clock		 : in std_logic;
	valid		 : out std_logic;
    
    result		 : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
);
END TopLevel;

ARCHITECTURE Arch OF TopLevel IS
BEGIN
    sum_out <= ('0' & a) + ('0' & b);
END Arch;

ARCHITECTURE Arch OF TopLevel IS
	signal shifting_multiplicand	: std_logic_vector (31 downto 0);
	signal shifting_multiplier		: std_logic_vector (31 downto 0);
    
	signal progressive_result		: std_logic_vector (32 downto 0);
	signal adder_result				: std_logic_vector (32 downto 0);
    
	signal init_ff 		 : std_logic;
	signal shift_request : std_logic;
	signal add_request 	 : std_logic;
BEGIN
	Manager : entity work.MultiplierManager(Arch)
    	PORT MAP (clock, shifting_multiplier(0), activate, init_ff, shift_request, add_request, valid);
    
    Adder : entity work.VectorAdder(Arch)
    	PORT MAP (adder_result(31 downto 0), shifting_multiplicand, progressive_result);

	Multiplicand : entity work.ShiftableRegister(Arch)
    	GENERIC MAP (31)
    	PORT MAP (multiplicand, shifting_multiplicand, clock, init_ff, '0', '0', '0');
        
	Multiplier : entity work.ShiftableRegister(Arch)
    	GENERIC MAP (31)
    	PORT MAP (multiplier, shifting_multiplier, clock, init_ff, shift_request, '0', adder_result(0));
	
    Progression : entity work.ShiftableRegister(Arch)
    	GENERIC MAP (32)
    	PORT MAP (progressive_result(31 downto 0), adder_result, clock, 
        		  add_request, shift_request, init_ff, '0');
    
    result <= adder_result(31 downto 0) & shifting_multiplier;
END Arch;