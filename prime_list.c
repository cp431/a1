#include "prime_list.h"
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

// Private helper functions.

/**
* Resizes a given prime_list to make room for INIT_LIST_LENGTH more elements.
* The idea is to greatly reduce the amount of times we have to resize the underlying array while
* generating millions of prime numbers. Any trailing memory will be trimmed after prime number generation.
*
* @param list pointer to the list of prime numbers.
*/
static void extend_prime_list(prime_list *list)
{
       *(list->capacity) += INIT_LIST_LENGTH;
       list->values = realloc(list->values, sizeof(long long int) * *(list->capacity));
	
       assert(list->values != NULL);
}

/**
* Trims any unused memory from the end of a given prime_list.
* Called after prime number generation is finished.
*
* @param list pointer to the list of prime numbers.
*/
static void trim_prime_list(prime_list *list)
{
        list->values = realloc(list->values, sizeof(long long int) * *(list->used));
	*(list->capacity) = *(list->used);
	
	assert(list->values != NULL);
}

// Implementations of the prime_list functions specified in prime_list.h.

void init_prime_list(prime_list *list, const long long int *starting_point, const long long int *problem_size) 
{
	// Initialize the array of mpz_t structs to hold INIT_LIST_LENGTH  primes at the beginning.
        list->capacity = malloc(sizeof(long long int));
	*(list->capacity) = INIT_LIST_LENGTH;
	list->used = malloc(sizeof(long long int));
	*(list->used) = 0LL;
	list->values = malloc(sizeof(long long int) * *(list->capacity));
	// Ensure that memory allocation succeeded
	assert(list->values != NULL);
	
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
	
	if (*(list->used) < *(list->capacity))
		trim_prime_list(list);

	mpz_clear(previous_prime);
	mpz_clear(next_prime);
}

void clear_prime_list(prime_list *list)
{
  // First free the memory taken by every integer in list->values.
  for (long long int i = 0LL; i < *(list->capacity); ++i)
    free(list->values[i]);

  free(list->values);
  free(list->used);
  free(list->capacity);
}
