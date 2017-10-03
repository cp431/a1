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
* Initializes a given prime_list to hold the first problem_size prime numbers after at and after starting_point.
*
* @param list pointer to the list of prime numbers.
* @param upper_prime_bound the upper bound for prime number generation.
*/
void init_prime_list(prime_list *list, const long long int *starting_point, const long long int *problem_size);

/**
* Returns the element at a given index.
*
* @param list pointer to the list of prime numbers.
* @param index pointer to the index of the desired list element.
* @return pointer to the element of list at index.
*/
inline mpz_t* get_prime_list_element_at(const prime_list *list, const long long int *index)
{
  return list->values[*index];
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
* Subtracts num1 and num2 and stores the result in out_result.
*
* @param num1 pointer to the first operand
* @param num2 pointer to the second operand
* @param out_result pointer to the result of the subtraction
*/
inline void subtract_primes(const mpz_t num1, const mpz_t num2, mpz_t out_result)
{
	mpz_sub(out_result, num1, num2);
}

/**
* Frees all memory taken by the prime list and sets capacity and used back to 0.
* 
* @param list pointer to the list of prime numbers.
*/
void clear_prime_list(prime_list *list);
#endif
