/**
   a1.c
   ====
   This program will eventually do things.
*/
#include "prime_list.h"
#include <stdio.h>

// Must do this in order to call those inline functions in this module, because inline is powerful but weird.
extern inline mpz_t* get_prime_list_element_at(const prime_list *list, const long long int *index);
extern inline const long long int* get_prime_list_length(const prime_list *list);

int main(int argc, char **argv) 
{
  prime_list test;
  long long int upper_bound = 10LL;
  long long int index = 0LL;

  printf("Init prime list\n");
  init_prime_list(&test, &upper_bound);
  // gmp_printf has to be used to print mpz_ts, otherwise output makes no sense.
  gmp_printf("Testing get element: %Zd\n", *(get_prime_list_element_at(&test, &index)));
  printf("Testing get length: %d\n", *(get_prime_list_length(&test)));
  printf("Clear prime list\n");
  clear_prime_list(&test);
  printf("Yeeeeeaaaaahhhhh!!!!!!\n");

  return 0;
}
