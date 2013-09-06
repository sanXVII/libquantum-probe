#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <quantum.h>



/* Sum 2 qbits.. qb[s1_bit] + qb[s2_bit]
 * Input:
 *    digit 1: s1_bit
 *    digit 2: s2_bit
 *    prev carry bit: p_bit
 *    on zero_bit must be 0
 *
 * Return:
 *    sum bit: s2_bit
 *    carry bit: p_bit
 */
void sum_1bit( quantum_reg * reg, int s1_bit, int s2_bit, int p_bit, int zero_bit )
{
	quantum_sigma_x( p_bit, reg); /* sigmaX i.e. NOT */
	quantum_unbounded_toffoli( 3, reg, s1_bit, s2_bit, p_bit, zero_bit );
	quantum_sigma_x( p_bit, reg);
	quantum_sigma_x( s2_bit, reg);
	quantum_sigma_x( s1_bit, reg);
	quantum_unbounded_toffoli( 3, reg, s1_bit, s2_bit, p_bit, zero_bit );
	quantum_sigma_x( s2_bit, reg);
	quantum_sigma_x( s1_bit, reg);
	quantum_cnot( p_bit, s2_bit, reg );
	quantum_cnot( s1_bit, s2_bit, reg );
	quantum_cnot( zero_bit, p_bit, reg );
}


int main()
{
	quantum_reg reg;
	unsigned int result;

	srand( time( 0 ) );

	reg = quantum_new_qureg( 0xe/* initval */, 4/* qubits */ );
	quantum_print_qureg( reg );

	//quantum_hadamard( 0/* qbit */, &reg );
	quantum_hadamard( 1/* qbit */, &reg );
	quantum_hadamard( 2/* qbit */, &reg );
	quantum_hadamard( 3/* qbit */, &reg );
	printf( "Сделали quantum_hadamard по вводам\n" );
	quantum_print_qureg( reg );



	sum_1bit( &reg, 3, 2, 1, 0 );
	printf( "Сделали sum\n" );
	quantum_print_qureg( reg );


	result = quantum_measure( reg );
	printf( "Измерили и получили: 0x%08x\n", result );

	return 0;
}

