/*
	Uses the general Sieve of Eratosthenes algorithm to generate a list of
	all prime numbers from 2 to upperBound.
*/

#include "data.h"
#include "sieve.h"
#include "list_array.h"

int* generate_prime_array(int problemSize) {

	n = problem_size;
	mpz_t rop;
	mpz_t op = 0;

	prime_list promlem_list;
	list_initialize(&l1, data_print, data_destroy, data_compare, data_initialize);

	mpz_init(rop);
	mpz_init(op);
	while (n > 0) {
		mpz_nextprime(mpz_t rop, const mpz_t op)
		list_append()
		n--;
	}
}
