/**
   a1.c
   ====
   This program will eventually do things.
*/
#include "prime_list.h"
#include <stdio.h>
#include <string.h>

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
extern inline mpz_t get_prime_list_element_at(const prime_list *list, const long long int *index);
extern inline const long long int* get_prime_list_length(const prime_list *list);
extern inline void subtract_primes(const mpz_t num1, const mpz_t num2, mpz_t out_result);

int main(int argc, char **argv) 
{
  
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
  
  // gmp_printf has to be used to print mpz_ts, otherwise output makes no sense.
  gmp_printf("Testing get element: %Zd\n", *(get_prime_list_element_at(&list, &index)));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &processors);
   
  int greatest_index_1 = 0;
  int greatest_index_2 = 0;
  char *greatest_prime_gap = "0";
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
   
  if (p_rank == FIRST) {
     
    long long int greatest_index_1 = 0;
    long long int greatest_index_2 = 0;
    char *greatest_prime_gap = "0";
  
     // Return largest prime gap from other processors
     for (int source = 1; source < processors; source++) { 
        int temp_index_1 = 0;
        int temp_index_2 = 0;
        char *temp_prime_gap = NULL;
        
        MPI_Recv(&temp_index_1, 1, MPI_LONG_LONG_INT, source, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_index_2, 1, MPI_LONG_LONG_INT, source, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        MPI_Recv(temp_prime_gap, 1, MPI_CHAR, source, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        
        if (strcmp(temp_prime_gap, greatest_prime_gap) == 1) {
           greatest_prime_gap = temp_prime_gap;
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
    prime_list list;
    /******************** split up array for load balancing ********************/
  	 int list_length = 0, processors = 0, j = 0;
    long long int evaluate_length = 0, i_start = 0;
    mpz_t max_diff, diff;
    char *max_diff_str = NULL;
    long long int prime1, prime2;
    mpz_init(max_diff);
    mpz_init(diff);

  	evaluate_length = floor(list_length / processors);
  	if (p_rank < list_length % processors)
  			evaluate_length += 1;

  	i_start = (p_rank - 1) * floor(list_length / processors) + ((p_rank < processors) ? (p_rank - 1) : processors);
   init_prime_list(&list, &i_start, &evaluate_length);
     
  	for (i = 0; i < evaluate_length; i++) {
   		j = i + 1;
  		subtract_primes(get_prime_list_element_at(&list, &i), get_prime_list_element_at(&list, &j), diff);
  		if (mpz_cmp(diff, max_diff) == 1)
  			mpz_set(max_diff, diff);
    }
    
    int base = 10;
    mpz_get_str(max_diff_str, base, max_diff);
     
    int count = 1;
    int len = strlen(max_diff_str);
    MPI_Send(&prime1, count, MPI_LONG_LONG_INT, destination, PRIME_INDEX_1, MPI_COMM_WORLD);
    MPI_Send(&prime2, count, MPI_LONG_LONG_INT, destination, PRIME_INDEX_2, MPI_COMM_WORLD);
    MPI_Send(max_diff_str, count, MPI_CHAR, destination, PRIME_GAP_STRING, MPI_COMM_WORLD);
    MPI_Finalize();
  }

  return 0;
}
