/**
   a1.c
   ====
   This program will eventually do things.
*/
#include "prime_list.h"
#include <stdio.h>

#define FIRST 0

// MPI Send/Receive Tag Names
#define PRIME_INDEX_1 0
#define PRIME_INDEX_2 1
#define PRIME_GAP_STRING 2

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
  int processors;
  int i, j;
  double start_time = 0;
  double end_time = 0;
  int p_rank = 0;
  int destination = 0;
  MPI_Status status;
  
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
     
     int greatest_index_1 = 0;
     int greatest_index_2 = 0;
     char *greatest_prime_gap = "0";
     
     // Return largest prime gap from other processors
     for (int source = 1; source < processors; source++) { 
        int temp_index_1 = 0;
        int temp_index_2 = 0;
        char *temp_prime_gap;
        
        MPI_Recv(temp_index1, 1, MPI_LONG_LONG_INT, source, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        MPI_Recv(temp_index2, 1, MPI_LONG_LONG_INT, source, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        MPI_Recv(temp_prime_gap, 1, MPI_CHAR, source, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        
        if (strcmp(temp_prime, greatest_prime_gap) == 1) {
           greates_prime_gap = temp_prime_gap;
           greatest_index_1 = temp_index_1;
           greatest_index_2 = temp_index_2;
        }
     printf("Largest gap %s", greatest_prime_gap);
     }
     
     end_time = MPI_Wtime();
     printf("Wallclock time elapsed: %.2lf seconds\n", end_time - start_time);
  }
   
  /******************** all other tasks do this part ***********************/
  if (p_rank > FIRST) {
    /******************** split up array for load balancing ********************/
  	 int evaluate_length = 0, list_length = 0, processors = 0, i_start = 0, j = 0;
    mpz_t max_diff, diff;
    mpz_init(max_diff);
    mpz_init(diff);
     
    int prime1 = 0;
    int prime2 = 0;
    char *max_diff_str = NULL;

  	evaluate_length = floor(list_length / processors);
  	if (p_rank < list_length % processors)
  			evaluate_length += 1;

  	i_start = (p_rank - 1) * floor(list_length / processors) + ((p_rank < processors) ? (p_rank - 1) : processors);
  	for (i = i_start; i < evaluate_length + i_start; i++) {
   		j = i + 1;
  		subtract_primes(list[i], list[j], diff);
  		if (mpz_cmp(diff, max_diff) == 1)
  			mpz_set(max_diff, diff);
    }
    
    int base = 10;
    mpz_get_str(max_diff_str, base, max_diff);
     
    int count = 1;
    int len = str_len(max_diff_str);
    MPI_Send(&prime1, count, MPI_LONG_LONG_INT, destination, PRIME_INDEX_1, MPI_COMM_WORLD);
    MPI_Send(&prime2, count, MPI_LONG_LONG_INT, destination, PRIME_INDEX_2, MPI_COMM_WORLD);
    MPI_Send(max_diff_str, count, MPI_CHAR, destination, PRIME_GAP_STRING, MPI_COMM_WORLD);
    MPI_Finalize();
  }

  return 0;
}
