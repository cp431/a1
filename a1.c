/**
   a1.c
   ====
   This program will eventually do things.
*/
#include "prime_list.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
  prime_list test;
  long long int upper_bound = 10LL;
  long long int index = 0LL;

  printf("Init prime list\n");
  init_prime_list(&test, &upper_bound);
  // gmp_printf has to be used to print mpz_ts, otherwise output makes no sense.
  gmp_printf("Testing get element: %Zd\n", *(get_prime_list_element_at(&test, &index)));
  printf("Testing get length: %d\n", get_prime_list_length(&test));
  printf("Clear prime list\n");
  clear_prime_list(&test);
  printf("Yeeeeeaaaaahhhhh!!!!!!\n");

  return 0;
}
