#include "prime_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

void init_prime_list(long long int *list, const long long int *problem_size) 
{
	mpz_t previous_prime, next_prime;

	// The LL suffix specifies the this literal is a long long. Avoids implicit typecasting.
	mpz_init_set_si(previous_prime, 1LL);
	mpz_init_set_si(next_prime, 1LL);
	
	// mpz_cmp returns a positive int if next_prime > upper_bound, 0 if =, negative if <
	for (long long int prime_count = 0; prime_count < *problem_size; ++prime_count)
	{
		// Add another prime number to the list.
		//mpz_export(&list[prime_count], NULL, -1, sizeof(long long int), -1, 0, previous_prime);
		list[prime_count] = mpz_get_si(previous_prime);
		
		// Determine the next prime number greater than the last prime added to the list.
		mpz_nextprime(next_prime, previous_prime);
		mpz_set(previous_prime, next_prime);
	}

	mpz_clear(previous_prime);
	mpz_clear(next_prime);
}
