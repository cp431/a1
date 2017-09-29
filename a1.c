/**
   a1.c
   ====
   This program will eventually do things.
*/
#include "prime_list.h"
#include <stdio.h>

#define FIRST 0

#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Must do this in order to call those inline functions in this module, because inline is powerful but weird.
extern inline mpz_t* get_prime_list_element_at(const prime_list *list, const long long int *index);
extern inline const long long int* get_prime_list_length(const prime_list *list);

int main(int argc, char **argv) 
{
  prime_list test;
  long long int upper_bound = 10LL;
  long long int index = 0LL;
  double start_time, end_time;
  int processors;
  
  printf("Init prime list\n");
  init_prime_list(&list, &upper_bound);
  // gmp_printf has to be used to print mpz_ts, otherwise output makes no sense.
  gmp_printf("Testing get element: %Zd\n", *(get_prime_list_element_at(&list, &index)));
   
  // Put prime list into centralized memory
   
  //printf("Testing get length: %d\n", *(get_prime_list_length(&test)));
  //printf("Clear prime list\n");
  //clear_prime_list(&test);
  printf("Yeeeeeaaaaahhhhh!!!!!!\n");
   
  int p_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &processors);
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
  if (rank == FIRST) {
     
     // Return largest prime gap from other processors
     
     end_time = MPI_Wtime();
     printf("Done. Largest prime gap is %d Total primes %d\n",maxprime,pcsum);
     printf("Wallclock time elapsed: %.2lf seconds\n",end_time-start_time);
  }
   
  /******************** all other tasks do this part ***********************/
  if (rank > FIRST) {
     int max_diff = 0;
     /******************** split up array for load balancing ********************/
     evaluate_length = floor(processors / list_length)
     if (p_rank < mod(list_len, processors) { evaluate_length += 1; }
  
     i_start = p_rank * floor(list_len/processes) + min(p_rank, mod(list_len, processors));
     for(int i = i_start; i < evaluate_length + i_start; i++) {
        j = i + 1;
        diff = diff(list[i], list[j]);
        if (diff > max_diff)
           max_diff = diff;
     }
     
     MPI_Finalize();
  }

  return 0;
}
