LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY reg32_avalon_interface IS
    PORT (
        clock, resetn : IN STD_LOGIC;
        address : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        read, write, chipselect : IN STD_LOGIC;
        writedata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        byteenable : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        readdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
END reg32_avalon_interface;

ARCHITECTURE Structure OF reg32_avalon_interface IS
    SIGNAL local_byteenableA0 : STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL local_byteenableA1 : STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL local_byteenableA2 : STD_LOGIC_VECTOR(3 DOWNTO 0);

    SIGNAL local_byteenableB0 : STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL local_byteenableB1 : STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL local_byteenableB2 : STD_LOGIC_VECTOR(3 DOWNTO 0);

    SIGNAL  to_reg, 
            from_regA0, from_regA1, from_regA2, 
            from_regB0, from_regB1, from_regB2,
            from_regC0, from_regC1, from_regC2
            : STD_LOGIC_VECTOR(31 DOWNTO 0);




    COMPONENT reg32
        PORT (
            clock, resetn : IN STD_LOGIC;
            D : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
            byteenable : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
            Q : OUT STD_LOGIC_VECTOR(31 DOWNTO 0) 
        );
    END COMPONENT;


    component matrixMultiplier is
        generic(
          BITS : integer := 8;
          SIZE_N : integer := 3
       );
       
      port (
            SIGNAL matA   : in std_logic_vector( SIZE_N * SIZE_N  * BITS - 1 downto 0);
            SIGNAL matB   : in std_logic_vector( SIZE_N * SIZE_N  * BITS - 1 downto 0);
            SIGNAL matRes : out std_logic_vector(SIZE_N * SIZE_N  * BITS - 1 downto 0)
            
      );
    end component matrixMultiplier;
    
BEGIN

    
    local_byteenableA0 <= byteenable WHEN (chipselect = '1' AND write = '1' AND address = "0000") else "0000";
    local_byteenableA1 <= byteenable WHEN (chipselect = '1' AND write = '1' AND address = "0001") else "0000";
    local_byteenableA2 <= byteenable WHEN (chipselect = '1' AND write = '1' AND address = "0010") else "0000";

    local_byteenableB0 <= byteenable WHEN (chipselect = '1' AND write = '1' AND address = "0011") else "0000";
    local_byteenableB1 <= byteenable WHEN (chipselect = '1' AND write = '1' AND address = "0100") else "0000";
    local_byteenableB2 <= byteenable WHEN (chipselect = '1' AND write = '1' AND address = "0101") else "0000";

    to_reg <= writedata;
    



    readdata <=     from_regA0       when address = "0000" else 
                    from_regA1       when address = "0001" else 
                    from_regA2       when address = "0010" else 

                    from_regB0       when address = "0011" else 
                    from_regB1       when address = "0100" else 
                    from_regB2       when address = "0101" else 
                    
                    from_regC0       when address = "0110" else 
                    from_regC1       when address = "0111" else 
                    from_regC2       when address = "1000" else
					(others => '0'); 



        mat: matrixMultiplier port map(
            matA => from_regA0 & from_regA1 & from_regA2(31 downto 24),
            matB => from_regB0 & from_regB1 & from_regB2(31 downto 24),  
            matRes(71 downto 40) => from_regC0,
            matRes(39 downto 8) => from_regC1,
            matRes(7 downto 0) => from_regC2(31 downto 24)
        ) ;

        

    reg_instanceA0 : reg32
    PORT MAP(
        clock, resetn, to_reg, local_byteenableA0, from_regA0
    );
    
    reg_instanceA1 : reg32
    PORT MAP(
        clock, resetn, to_reg, local_byteenableA1, from_regA1
    );

    reg_instanceA2 : reg32
    PORT MAP(
        clock, resetn, to_reg, local_byteenableA2, from_regA2
    );

    reg_instanceB0 : reg32
    PORT MAP(
        clock, resetn, to_reg, local_byteenableB0, from_regB0
    );

    reg_instanceB1 : reg32
    PORT MAP(
        clock, resetn, to_reg, local_byteenableB1, from_regB1
    );

    reg_instanceB2 : reg32
    PORT MAP(
        clock, resetn, to_reg, local_byteenableB2, from_regB2
    );





END Structure;
