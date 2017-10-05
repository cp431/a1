#ifndef PRIME_LIST_H_
#define PRIME_LIST_H_

#include <gmp.h>

// prime_list functions

/**
* Initializes a given array of long long ints to hold the first problem_size prime numbers.
*
* @param list pointer to the list of prime numbers.
* @param problem_size the amount of prime numbers to generate.
*/
void init_prime_list(long long int **list, const long long int *problem_size);

/**
* Frees all memory taken by the prime list and sets capacity and used back to 0.
* 
* @param list pointer to the list of prime numbers.
*/
void clear_prime_list(long long int **list);
#endif
