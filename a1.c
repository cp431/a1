/**
   a1.c
   ====
   This program will eventually do things.
*/
#include "prime_list.h"
#include <stdio.h>
#include <string.h>

// Misc Constants
#define FIRST 0
#define BASE_DECIMAL 10

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
  
  long long int problem_size = 10LL;
  int num_processors = 0;
  double start_time = 0.0;
  double end_time = 0.0;
  int p_rank = 0;
  MPI_Status status;
  
   // gmp_printf has to be used to print mpz_ts, otherwise output makes no sense.
  // gmp_printf("Testing get element: %Zd\n", *(get_prime_list_element_at(&list, &index)));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_processors);
   
  int greatest_index_1 = 0;
  int greatest_index_2 = 0;
  char *greatest_prime_gap = "0";
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
   
  if (p_rank == FIRST) {
     printf("Beep Boop! Process %d here, starting my stuff!", p_rank);
    long long int greatest_index_1 = 0;
    long long int greatest_index_2 = 0;
    char *greatest_prime_gap = "0";
  
     // Return largest prime gap from other processors
     for (int source = 1; source < num_processors; source++) { 
        int temp_index_1 = 0;
        int temp_index_2 = 0;
        char *temp_prime_gap = NULL;
        
        MPI_Recv(&temp_index_1, 1, MPI_LONG_LONG_INT, FIRST, PRIME_INDEX_1, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_index_2, 1, MPI_LONG_LONG_INT, FIRST, PRIME_INDEX_2, MPI_COMM_WORLD, &status);
        MPI_Recv(temp_prime_gap, 1, MPI_CHAR, FIRST, PRIME_GAP_STRING, MPI_COMM_WORLD, &status);
        
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
    /******************** split up array for load balancing ********************/
    long long int evaluate_length = 0, i_start = 0;
    char *max_diff_str = NULL;
    char *prime1_str = NULL;
    char *prime2_str = NULL;
    
    mpz_t max_diff, diff;
    mpz_init(max_diff);
    mpz_init(diff);

  	evaluate_length = floor(problem_size / num_processors);
  	
    if (p_rank < problem_size % num_processors)
  			evaluate_length += 1;

  	i_start = p_rank * floor(problem_size / num_processors) + ((p_rank < num_processors) ? (p_rank) : num_processors);
   
   prime_list list;
   init_prime_list(&list, &i_start, &evaluate_length);
    
   long long int j, prime1_index, prime2_index; 
   printf("Doot Doot! Process %d here, starting to compare primes!", p_rank);  
  	for (long long int i = 0; i < evaluate_length; i++) {
   		j = i + 1;
  		subtract_primes(*(get_prime_list_element_at(&list, &i)), *(get_prime_list_element_at(&list, &j)), diff);
  		
      if (mpz_cmp(diff, max_diff) == 1)
      {
         printf("Boop Beep! Process %d here, found a new maximum!", p_rank);
  			mpz_set(max_diff, diff);
         prime1_index = i;
         prime2_index = j;
      }
    }
    
    mpz_get_str(max_diff_str, BASE_DECIMAL, max_diff);
    mpz_get_str(prime1_str, BASE_DECIMAL, *(get_prime_list_element_at(&list, &prime1_index)));
    mpz_get_str(prime2_str, BASE_DECIMAL, *(get_prime_list_element_at(&list, &prime2_index)));
       
    mpz_clear(max_diff);
    mpz_clear(diff);
    clear_prime_list(&list); 
                
    MPI_Send(&prime1, SINGLE_VARIABLE_MESSAGE, MPI_LONG_LONG_INT, FIRST, PRIME_INDEX_1, MPI_COMM_WORLD);
    MPI_Send(&prime2, SINGLE_VARIABLE_MESSAGE, MPI_LONG_LONG_INT, FIRST, PRIME_INDEX_2, MPI_COMM_WORLD);
    MPI_Send(max_diff_str, strlen(max_diff_str), MPI_CHAR, FIRST, PRIME_GAP_STRING, MPI_COMM_WORLD);
    MPI_Finalize();
  }

  return 0;
}
