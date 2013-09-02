#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <quantum.h>


int main()
{
	quantum_reg reg;
	unsigned int result;

	srand( time( 0 ) );

	reg = quantum_new_qureg( 0x2/* initval */, 3/* qubits */ );
	quantum_print_qureg( reg );

	quantum_hadamard( 0/* qbit */, &reg );
	quantum_hadamard( 2/* qbit */, &reg );
	//quantum_hadamard( 1/* qbit */, &reg );
	//quantum_hadamard( 2/* qbit */, &reg );
	//quantum_hadamard( 3/* qbit */, &reg );
	printf( "Сделали quantum_hadamard по 0\n" );
	quantum_print_qureg( reg );

	//printf( "Сделали CNOT\n" );
	//quantum_cnot( 3/* control */, 0/* target */, &reg );
	//quantum_print_qureg( reg );

	printf( "Сделали CCNOT\n" );
	quantum_toffoli( 0/* control1 */, 1/* control2 */, 2/* target */, &reg );
	quantum_print_qureg( reg );

	//printf( "Сделали CCNOT\n" );
	//quantum_toffoli( 0/* control1 */, 1/* control2 */, 2/* target */, &reg );
	//quantum_print_qureg( reg );


	//quantum_hadamard( 0/* qbit */, &reg );
	//quantum_hadamard( 1/* qbit */, &reg );
	//quantum_hadamard( 2/* qbit */, &reg );
	//quantum_hadamard( 3/* qbit */, &reg );
	//printf( "Сделали quantum_hadamard по всем\n" );
	//quantum_print_qureg( reg );

	quantum_cond_phase( 1, 0, &reg);
	printf( "Сделали quantum_cond_phase\n" );
	quantum_print_qureg( reg );


	result = quantum_measure( reg );
	printf( "Измерили и получили: 0x%08x\n", result );

	return 0;
}

