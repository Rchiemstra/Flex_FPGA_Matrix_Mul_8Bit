LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY matrixMultiplier_8bit IS

    PORT (
		CLOCK_50 : IN STD_LOGIC;
		KEY : IN std_logic
			
     );
END matrixMultiplier_8bit;




ARCHITECTURE Structure OF matrixMultiplier_8bit IS
	    component RTOS is
        port (
            clk_clk       : in std_logic := 'X'; -- clk
            reset_reset_n : in std_logic := 'X'  -- reset_n
        );
    end component RTOS;
	 
BEGIN


    u0 : component RTOS
        port map (
            clk_clk       => CLOCK_50,       --   clk.clk
            reset_reset_n => KEY  			-- reset.reset_n
        );

		  
END Structure;