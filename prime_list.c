#include "prime_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

// Implementations of the prime_list functions specified in prime_list.h.

void init_prime_list(long long int **list, const long long int *problem_size) 
{
	mpz_t previous_prime, next_prime;

	// The LL suffix specifies the this literal is a long long. Avoids implicit typecasting.
	mpz_init_set_ui(previous_prime, 1LL);
	mpz_init_set_ui(next_prime, 1LL);
	
	// mpz_cmp returns a positive int if next_prime > upper_bound, 0 if =, negative if <
	while ((*(list->used)) < *problem_size)
	{
		// Lengthen the list if needed.
	        if ((*(list->used)) >= *(list->capacity))
			extend_prime_list(list);
		
		// Add another prime number to the list.
		mpz_export(&(list->values[(*(list->used))])), 0, -1, sizeof(long long int), 0, 0, previous_prime);
		(*(list->used))++;
		
		// Determine the next prime number greater than the last prime added to the list.
		mpz_nextprime(next_prime, previous_prime);
		mpz_set(previous_prime, next_prime);
	}

	mpz_clear(previous_prime);
	mpz_clear(next_prime);
}

void clear_prime_list(long long int **list)
{
  // First free the memory taken by every integer in list->values.
  for (long long int i = 0LL; i < *(list->capacity); ++i)
    free(list->values[i]);

  free(list->values);
}
