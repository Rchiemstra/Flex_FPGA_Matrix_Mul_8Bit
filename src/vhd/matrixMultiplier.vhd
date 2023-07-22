LIBRARY ieee;
USE ieee.std_logic_1164.ALL;



ENTITY matrixMultiplier IS
    generic(BITS : integer := 8;
        SIZE_N : integer := 3
    );
    port (
        matA   : in std_logic_vector( SIZE_N * SIZE_N * BITS - 1 downto 0);
        matB   : in std_logic_vector( SIZE_N * SIZE_N  * BITS - 1 downto 0);
        matRes : out std_logic_vector(SIZE_N * SIZE_N  * BITS - 1 downto 0)
    );
END matrixMultiplier;


ARCHITECTURE Behavior OF matrixMultiplier IS
    constant SIZE_NN : integer := SIZE_N * SIZE_N;

    component subMatrixMultiplier is
        generic(BITS : integer := BITS;
            SIZE_N : integer := SIZE_N); -- 
        Port (
            vecAbits : in std_logic_vector(SIZE_N * BITS - 1 downto 0);
            vecBbits : in std_logic_vector(SIZE_N * BITS - 1 downto 0);
            resOut : out std_logic_vector(BITS-1 downto 0)
        );
    end component;


    type matrixValuesArray is array (SIZE_N*SIZE_N-1 downto 0) of std_logic_vector(BITS-1 downto 0);
    signal matrixResults : matrixValuesArray; -- vector b
    
    type matrixRange is array (SIZE_N-1 downto 0) of std_logic_vector(SIZE_N * BITS-1 downto 0);
    signal rows_A : matrixRange;
    signal cols_B : matrixRange;
BEGIN

    
    rowsA_map:
       for I in 0 to SIZE_N-1 generate
        constant BITS_ROW : integer := SIZE_N * BITS;
    begin
        rows_A(I) <= matA( (I+1) * BITS_ROW-1 downto I * BITS_ROW);
       end generate rowsA_map;


    colsB_map_outer:
       for I in 0 to SIZE_N-1 generate

        colsB_map_inner:
        for J in 0 to SIZE_N-1 generate
            cols_B(I)( (J+1) * BITS-1 downto J * BITS ) <= matB(I*8 + (J*SIZE_N+1) * BITS-1 downto I*8 + (J*SIZE_N) * BITS);
        end generate colsB_map_inner;

       end generate colsB_map_outer;


    vecMul_gen_outer:
    for I in 0 to SIZE_N-1 generate
        
        vecMul_gen_inner:
        for J in 0 to SIZE_N-1 generate
            submatmul : subMatrixMultiplier Port map (rows_A(I), cols_B(J) , matrixResults(I*SIZE_N + J));
        end generate vecMul_gen_inner;

    end generate vecMul_gen_outer;


    out_res_map:
       for I in 0 to SIZE_NN-1 generate
        matRes(( I+1) * BITS - 1 downto I*BITS) <= matrixResults(I);
       end generate out_res_map;


END Behavior;