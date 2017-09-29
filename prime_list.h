#ifndef PRIME_LIST_H_
#define PRIME_LIST_H_

#include <gmp.h>

// The exact value of this constant will be tweaked as we continue development.
#define INIT_LIST_LENGTH 10000LL;

// Typedefs
typedef struct 
{
	long long int *capacity;
	long long int *used;
	mpz_t *values;
} prime_list;

// prime_list functions

/**
* Initializes a given prime_list to hold every prime number from 1 to upper_prime_bound.
*
* @param list pointer to the list of prime numbers.
* @param upper_prime_bound the upper bound for prime number generation.
*/
void init_prime_list(prime_list *list, const long long int *upper_prime_bound);

/**
* Returns the element at a given index.
*
* @param list pointer to the list of prime numbers.
* @param index pointer to the index of the desired list element.
* @return pointer to the element of list at index.
*/
inline mpz_t* get_prime_list_element_at(const prime_list *list, const long long int *index)
{
  return &(list->values[*index]);
}

/**
* Returns the length of the list.
*
* @param list pointer to the list of prime numbers
* @return the length of the prime_list this function was given
*/
inline const long long int* get_prime_list_length(const prime_list *list)
{
  return list->used;
}

/**
* Subtracts the two prime numbers at two given indices and returns the result.
*
* @param list pointer to the list of prime numbers.
* @param num1_index pointer to the index of the first operand.
* @param num2_index pointer to the index of the second operand.
*/
mpz_t subtract_primes(prime_list *list, const long long int *num1_index, const long long int *num2_index);

/**
* Frees all memory taken by the prime list and sets capacity and used back to 0.
* 
* @param list pointer to the list of prime numbers.
*/
void clear_prime_list(prime_list *list);
#endif
