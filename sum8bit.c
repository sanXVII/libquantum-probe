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
/* Reverce Sum 2 qbits */
void sum_1bit_r( quantum_reg * reg, int s1_bit, int s2_bit, int p_bit, int zero_bit )
{
	quantum_cnot( zero_bit, p_bit, reg );
	quantum_cnot( s1_bit, s2_bit, reg );
	quantum_cnot( p_bit, s2_bit, reg );
	quantum_sigma_x( s1_bit, reg);
	quantum_sigma_x( s2_bit, reg);
	quantum_unbounded_toffoli( 3, reg, s1_bit, s2_bit, p_bit, zero_bit );
	quantum_sigma_x( s1_bit, reg);
	quantum_sigma_x( s2_bit, reg);
	quantum_sigma_x( p_bit, reg);
	quantum_unbounded_toffoli( 3, reg, s1_bit, s2_bit, p_bit, zero_bit );
	quantum_sigma_x( p_bit, reg); /* sigmaX i.e. NOT */
}


/* Sum 8-qbit digits.. int8[s1] + int8[s2]
 * Input:
 *    s1 and s2 - bit indexes of digits.
 *    zero_bits - indexes of additional qbits.
 *        p_bit - carry bit
 *
 * Return:
 *    result is in s2 qbits.
 *    carry bit is in p_bit qbit.
 */
void sum_8bit( quantum_reg * reg, int s1[8], int s2[8], int p_bit, int zero_bits[8] )
{
	int i;
	for( i = 0; i < 8; i++ )
	{
		sum_1bit( reg, s1[i], s2[i], p_bit, zero_bits[i] );
	}
}
void sum_8bit_r( quantum_reg * reg, int s1[8], int s2[8], int p_bit, int zero_bits[8] )
{
	int i;
	for( i = 7; i >= 0; i-- )
	{
		sum_1bit_r( reg, s1[i], s2[i], p_bit, zero_bits[i] );
	}
}


int main()
{
	quantum_reg reg;
	unsigned int result;

	srand( time( 0 ) );

	int s2[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int s1[8] = { 8, 9, 10, 11, 12, 13, 14, 15 };
	int zero_bits[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };

	reg = quantum_new_qureg( 0x050a/* initval */, 25/* qubits */ );
	quantum_print_qureg( reg );

	//quantum_hadamard( 0/* qbit */, &reg );
	//quantum_hadamard( 1/* qbit */, &reg );
	//quantum_hadamard( 2/* qbit */, &reg );
	//quantum_hadamard( 3/* qbit */, &reg );

	int i;
	for( i = 0; i < 8; i++ )
	{
		quantum_hadamard( zero_bits[i], &reg );
	}
	printf( "Сделали quantum_hadamard по вводам\n" );
	quantum_print_qureg( reg );

	printf( "Сделали sum_8bit_r" );
	sum_8bit_r( &reg, s1, s2, 24/* carry bit */, zero_bits );
	quantum_print_qureg( reg );

	//printf( "Сделали sum_8bit" );
	//sum_8bit( &reg, s1, s2, 24/* carry bit */, zero_bits );
	//quantum_print_qureg( reg );

	result = quantum_measure( reg );
	printf( "Измерили и получили: 0x%08x\n", result );

	return 0;
}

