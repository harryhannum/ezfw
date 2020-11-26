-- LC
-- Code your design here
library IEEE;
use IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY MultiplierManager IS 
GENERIC(N: integer := 5);
PORT(
	clock   				: IN STD_LOGIC;
	current_multiplied_bit 	: IN STD_LOGIC;
    activate   				: IN STD_LOGIC;
    
    init_ff    		: OUT STD_LOGIC;
    shift_request   : OUT STD_LOGIC;
    add_request		: OUT STD_LOGIC;
    valid			: OUT STD_LOGIC
);
END MultiplierManager;

ARCHITECTURE Arch OF MultiplierManager IS
	type States is (Start, Selection, Adding, Shifting, Finish);
    
    signal state : States := Finish;
    signal step_counter : unsigned(N-1 downto 0);
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
                	if (step_counter = 2**N - 1) then
						state <= Finish;
					else
						state <= Selection;
					end if;
			end case;
		end if;
	end process;
    
    process(clock)
	begin
		if rising_edge(clock) then
			if state = Start then
				step_counter <= to_unsigned(0, N);
			elsif state = Shifting then
				step_counter <= step_counter + 1;
			end if;
		end if;
	end process;
END Arch;