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

void init_prime_list(prime_list *list, const long long int *upper_prime_bound) 
{
	// Initialize the array of mpz_t structs to hold INIT_LIST_LENGTH  primes at the beginning.
        list->capacity = malloc(sizeof(long long int));
	*(list->capacity) = INIT_LIST_LENGTH;
	list->used = malloc(sizeof(long long int));
	*(list->used) = 0LL;
	list->values = malloc(sizeof(mpz_t) * *(list->capacity));
	// Ensure that memory allocation succeeded
	assert(list->values != NULL);
	
	mpz_t previous_prime, next_prime, upper_bound;

	// The LL suffix specifies the this literal is a long long. Avoids implicit typecasting.
	mpz_init_set_ui(previous_prime, 1LL);
	mpz_init_set_ui(next_prime, 1LL);
	mpz_init_set_ui(upper_bound, *upper_prime_bound);
	
	long long int index = 0LL;
	
	// mpz_cmp returns a positive int if next_prime > upper_bound, 0 if =, negative if <
	while (mpz_cmp(next_prime, upper_bound) < 0)
	{
		// Lengthen the list if needed.
	        if (index >= *(list->capacity))
			extend_prime_list(list);
		
		// Add another prime number to the list.
		mpz_init_set(list->values[index], previous_prime);
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
	mpz_clear(upper_bound);
}

const long long int* get_prime_list_length(const prime_list *list)
{
	return list->used;
}

mpz_t* get_prime_list_element_at(const prime_list *list, const long long int *index)
{
	// Ensure that the index does not exceed the list's boundaries.
        assert(*index < *(get_prime_list_length(list)));
	return &(list->values[*index]);
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
