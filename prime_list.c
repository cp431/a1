#include "prime_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

void init_prime_list(long long int *list, const long long int *problem_size) 
{
	mpz_t previous_prime, next_prime, temp;
	long int prime = 0L;

	// The LL suffix specifies the this literal is a long long. Avoids implicit typecasting.
	mpz_init_set_si(previous_prime, 3);
	mpz_init_set_si(next_prime, 0);
	
	// mpz_cmp returns a positive int if next_prime > upper_bound, 0 if =, negative if <
	//for (long long int prime_count = 0LL; prime_count < *problem_size; ++prime_count)
	//{
		// Add another prime number to the list.
		//mpz_export(&list[prime_count], NULL, -1, sizeof(long long int), -1, 0, previous_prime);
		//mpz_set(temp, previous_prime);
		//gmp_printf("Prime %lld: %Zd\n", prime_count, temp);
		//prime = mpz_get_si(temp);
		//printf("%ld\n", prime);
		//printf("Prime %lld: %lld", prime_count, prime);
		
	long long int i = 2, c;
	for (long long int count = 1; count <= *problem_size; ) {
	   for (c = 2 ; c <= i - 1 ; c++) {
		if (i % c == 0)
		   break;
	      }  
	   if (c == i) {
		list[count-1] = i;
		printf("%lld prime found: %lld\n", count, list[count-1]);
		count++;
	   }
	   i++;
	 }
		
		// Determine the next prime number greater than the last prime added to the list.
		//mpz_nextprime(next_prime, previous_prime);
		//mpz_set(previous_prime, next_prime);
	//}

	mpz_clear(previous_prime);
	mpz_clear(next_prime);
}
