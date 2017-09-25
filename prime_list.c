#include "prime_list.h"

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
	list->capacity += INIT_LIST_LENGTH;
	list->values = realloc(list->values, sizeof(list->values) * list->capacity);
	
	assert(list->values != null);
}

/**
* Trims any unused memory from the end of a given prime_list.
* Called after prime number generation is finished.
*
* @param list pointer to the list of prime numbers.
*/
static void trim_prime_list(prime_list *list)
{
	list->values = realloc(list->values, sizeof(list->values) * list->used);
	list->capacity = list->used;
	
	assert(list->values != null);
}

// Implementations of the prime_list functions specified in prime_list.h.

void init_prime_list(prime_list *list, const int *upper_prime_bound) 
{
	// Initialize the array of prime_ints to hold 100 primes at the beginning.
	list->capacity = INIT_LIST_LENGTH;
	list->used = 0;
	list->values = malloc(sizeof(prime_int) * list->capacity);
	// Ensure that memory allocation succeeded
	assert(list->values != null);
	
	prime_int previous_prime, next_prime;
	// The LL suffix specifies the this literal is a long long. Avoids implicit typecasting.
	mpz_init_set_ui(previous_prime, 1LL);
	mpz_init_set_ui(next_prime, 1LL);
	
	long long index = 0;
	
	while (current_prime < *upper_prime_bound)
	{
		// Lengthen the list if needed.
		if (index >= list->capacity)
			extend_prime_list(list);
		
		// Add another prime number to the list.
		list->values[index] = previous_prime;
		list->used++;
		index++;
		
		// Determine the next prime number greater than the last prime added to the list.
		mpz_nextprime(next_prime, previous_prime);
		previous_prime = next_prime;
	}
	
	if (list->used < list->capacity)
		trim_prime_list(list);
}

int get_length(const prime_list *list)
{
	return list->used;
}

const prime_int get_element_at(const prime_list *list, const int *index)
{
	// Ensure that the index does not exceed the list's boundaries.
	assert(*index < get_length(list));
	return list->values[index];
}