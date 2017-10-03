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
       list->values = realloc(list->values, sizeof(mpz_t) * *(list->capacity));
	
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
        list->values = realloc(list->values, sizeof(mpz_t) * *(list->used));
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
	list->values = malloc(sizeof(mpz_t) * *(list->capacity));
	// Ensure that memory allocation succeeded
	assert(list->values != NULL);
	
	mpz_t previous_prime, next_prime, max_primes, prime_count;

	// The LL suffix specifies the this literal is a long long. Avoids implicit typecasting.
	mpz_init_set_ui(previous_prime, 1LL);
	mpz_init_set_ui(next_prime, 1LL);
	mpz_init_set_ui(max_primes, *problem_size);
	mpz_init_set_ui(prime_count, 0LL);
	
	// Fast forward to starting_point if starting_point is > 0LL
	if (*starting_point > 0LL)
	{
		mpz_t start_point;
		mpz_init_set_ui(start_point, *starting_point);
		
		while (mpz_cmp(prime_count, start_point - 1) < 0)
		{
			mpz_nextprime(next_prime, previous_prime);
			mpz_set(previous_prime, next_prime);
			mpz_add_ui(prime_count, prime_count, 1LL);
		}
		
		mpz_set_ui(prime_count, 0LL);
		mpz_clear(start_point);
	}
	
	long long int index = 0LL;
	
	// mpz_cmp returns a positive int if next_prime > upper_bound, 0 if =, negative if <
	while (mpz_cmp(prime_count, max_primes) < 0)
	{
		// Lengthen the list if needed.
	        if (index >= *(list->capacity))
			extend_prime_list(list);
		
		// Add another prime number to the list.
		mpz_init_set(list->values[index], previous_prime);
		mpz_add_ui(prime_count, prime_count, 1LL);
		(*(list->used))++;
		index++;
		
		// Determine the next prime number greater than the last prime added to the list.
		mpz_nextprime(next_prime, previous_prime);
		mpz_set(previous_prime, next_prime);
	}
	
	if (*(list->used) < *(list->capacity))
		trim_prime_list(list);

	mpz_clear(previous_prime);
	mpz_clear(next_prime);
	mpz_clear(max_primes);
	mpz_clear(prime_count);
}

void clear_prime_list(prime_list *list)
{
  // First free the memory taken by every mpz_t integer.
  for (long long int i = 0LL; i < *(list->capacity); ++i)
    mpz_clear(list->values[i]);

  free(list->values);
  free(list->used);
  free(list->capacity);
}
