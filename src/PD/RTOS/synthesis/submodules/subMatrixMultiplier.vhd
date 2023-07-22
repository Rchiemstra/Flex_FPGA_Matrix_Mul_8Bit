LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.all;

ENTITY subMatrixMultiplier IS
	generic(BITS : integer := 8;
		SIZE_N : integer := 3); -- number of values in vector
	Port (
		vecAbits : in std_logic_vector(SIZE_N * BITS - 1 downto 0);
		vecBbits : in std_logic_vector(SIZE_N * BITS - 1 downto 0);
		resOut : out std_logic_vector(BITS-1 downto 0)
	);
END subMatrixMultiplier;


ARCHITECTURE Behavior OF submatrixMultiplier IS
	type signedArray is array (SIZE_N-1 downto 0) of signed(BITS-1 downto 0);

	signal vecAarray : signedArray; -- vector b
	signal vecBarray : signedArray; -- vector a

	signal res : signed (2 * BITS - 1 downto 0); -- vector result
BEGIN
 
	num_gen:
   	for I in 0 to SIZE_N-1 generate
		vecAarray(I) <= signed(vecAbits((I+1)*BITS -1 downto I*BITS));
		vecBarray(I) <= signed(vecBbits((I+1)*BITS -1 downto I*BITS));
   	end generate num_gen;

	res <= vecAarray(0) * vecBarray(0) + vecAarray(1) * vecBarray(1) + vecAarray(2) * vecBarray(2);

	resOut <= std_logic_vector(res(BITS - 1 downto 0));
END Behavior;