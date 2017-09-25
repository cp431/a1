#ifndef PRIME_LIST_H_
#define PRIME_LIST_H_

#include <gmp.h>

#define INIT_LIST_LENGTH 10000

// Typedefs
typedef mpz_t prime_int;

typedef struct 
{
	long long capacity;
	long long used;
	prime_int *values;
} prime_list;

// prime_list functions

/**
* Initializes a given prime_list to hold every prime number from 1 to upper_prime_bound.
*
* @param list pointer to the list of prime numbers.
* @param upper_prime_bound the upper bound for prime number generation.
*/
void init_prime_list(const prime_list *list, const int *upper_prime_bound);

/**
* Returns the element at a given index.
*
* @param list pointer to the list of prime numbers.
* @param index pointer to the index of the desired list element.
*/
const prime_int get_element_at(const prime_list *list, const int *index);

/**
* Returns the length of the list.
*
* @param list pointer to the list of prime numbers.
* @return the length of the prime_list this function was given
*/
int get_length(const prime_list *list);
#endif