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
extern inline void subtract_primes(const mpz_t num1, const mpz_t num2, mpz_t out_result);

int main(int argc, char **argv) 
{
  prime_list list;
  long long int upper_bound = 10LL;
  long long int index = 0LL;
  long long int max_diff = 0LL;
  double start_time, end_time;
  int processors;
  int i, j;
  double start_time = 0;
  double end_time = 0;
  int p_rank = 0;
  int tag = MPI_ANY_TAG;
  MPI_Status = status;
  
  printf("Init prime list\n");
  init_prime_list(&list, &upper_bound);
  // gmp_printf has to be used to print mpz_ts, otherwise output makes no sense.
  gmp_printf("Testing get element: %Zd\n", *(get_prime_list_element_at(&list, &index)));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &processors);
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
  if (p_rank == FIRST) {
     mpz_t = final;
     mpz_init(final);
     
     // Return largest prime gap from other processors
     for (source = 1; source < processors; source++) { 
        MPI_Recv(&max_diff, 1, MPI_LONG_LONG_INT, source, tag, MPI_COMM_WORLD, &status);
          mpz_set_ui(final, max_diff);
     }
     
     end_time = MPI_Wtime();
     printf("Wallclock time elapsed: %.2lf seconds\n", end_time-start_time);
  }
   
  /******************** all other tasks do this part ***********************/
  if (p_rank > FIRST) {
    /******************** split up array for load balancing ********************/
  	 int evaluate_length = 0, list_length = 0, processors = 0, i_start = 0, j = 0; 
    mpz_t max_diff, diff;
    mpz_init(max_diff);
    mpz_init(diff);

  	evaluate_length = floor(list_length / processors);
  	if (p_rank < list_length % processors)
  			evaluate_length += 1;

  	i_start = (p_rank - 1) * floor(list_length / processors) + ((p_rank < processors) ? (p_rank - 1) : processors);
  	for (i = i_start; i < evaluate_length + i_start; i++) {
   		j = i + 1;
  		diff = subtract_primes(&i, &j);
  		if (mpz_cmp(diff, max_diff))
  			mpz_set(max_diff, diff);
    }

    MPI_Finalize();
  }

  return 0;
}
