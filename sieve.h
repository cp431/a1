/*
	sieve.h
	=======
	Provides functions that wrap around the GMP prime functions in order to make for cleaner, more descriptive code.
*/
#include <gmp.h>

/*
	Generates an array of prime numbers between 1 and problemSize.

	problemSize: The upper bound for the prime array generation.
*/
int* generatePrimeArray(int problemSize);
