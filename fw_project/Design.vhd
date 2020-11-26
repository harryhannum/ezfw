-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY TopLevel IS 
GENERIC(
	N: integer := 32;
    POW: integer := 5
);
PORT(
    multiplier	 : IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    multiplicand : IN STD_LOGIC_VECTOR(N-1 DOWNTO 0);
    result		 : OUT STD_LOGIC_VECTOR(2*N-1 DOWNTO 0);
    
    activate 	 : in std_logic;
	clock		 : in std_logic;
	valid		 : out std_logic
);
END TopLevel;

ARCHITECTURE Arch OF TopLevel IS
	signal shifting_multiplicand	: std_logic_vector (N-1 downto 0);
	signal shifting_multiplier		: std_logic_vector (N-1 downto 0);
    
	signal progressive_result		: std_logic_vector (N downto 0);
	signal adder_result				: std_logic_vector (N downto 0);
    
	signal init_ff 		 : std_logic;
	signal shift_request : std_logic;
	signal add_request 	 : std_logic;
BEGIN
	Manager_E : entity work.MultiplierManager(Arch)
    	GENERIC MAP (POW)
    	PORT MAP (clock, shifting_multiplier(0), activate, init_ff, shift_request, add_request, valid);
    
    Adder_E : entity work.VectorAdder(Arch)
    	GENERIC MAP (N)
    	PORT MAP (adder_result(N-1 downto 0), shifting_multiplicand, progressive_result);

	Multiplicand_E : entity work.ShiftableRegister(Arch)
    	GENERIC MAP (N)
    	PORT MAP (multiplicand, shifting_multiplicand, clock, init_ff, '0', '0', '0');
        
	Multiplier_E : entity work.ShiftableRegister(Arch)
    	GENERIC MAP (N)
    	PORT MAP (multiplier, shifting_multiplier, clock, init_ff, '0', shift_request, adder_result(0));
	
    Progression_E : entity work.ShiftableRegister(Arch)
    	GENERIC MAP (N+1)
    	PORT MAP (progressive_result, adder_result, clock, 
        		  add_request, init_ff, shift_request, '0');
    
    result <= adder_result(N-1 downto 0) & shifting_multiplier;
END Arch;