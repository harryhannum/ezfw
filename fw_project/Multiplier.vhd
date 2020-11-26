-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY MultiplierManager IS PORT(
	current_multiplied_bit 	: IN STD_LOGIC;
    
    clock   		: IN STD_LOGIC;
    activate   		: IN STD_LOGIC;
    
    init_ff    		: OUT STD_LOGIC;
    add_request		: OUT STD_LOGIC;
    shift_request   : OUT STD_LOGIC;
    valid			: OUT STD_LOGIC
);
END MultiplierManager;

ARCHITECTURE Arch OF MultiplierManager IS
	type States is (Start, Selection, Adding, Shifting, Finish);
    
    signal state : States := Finish;
    signal step_counter : unsigned(31 downto 0);
BEGIN
	init_ff <= '1' when state = Start else '0';
	add_request <= '1' when state = Adding else '0';
	shift_request <= '1' when state = Shifting else '0';
    valid <= '1' when state = Finish else '0';

	process(clock)
	begin
		if rising_edge(clock) then
			case state is
				when Finish => 
                	if activate = '1' then
						state <= Start;
					end if;
				
                when Start => 
                	step_counter <= to_unsigned(0, 32);
                	state <= Selection;
				
                when Selection => 
                	if (current_multiplied_bit = '1') then
						state <= Adding;
					else
						state <= Shifting;
					end if;
                    
				when Adding => 
                	state <= Shifting;
                    
				when Shifting => 
                	if (step_counter = 2**32 - 1) then
						state <= Finish;
					else
						state <= Selection;
					end if;
                    step_counter <= step_counter + 1; 
			end case;
		end if;
	end process;
END Arch;