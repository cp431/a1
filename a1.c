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
#define PRIME1 0
#define PRIME2 1
#define PRIME_GAP 2
#define BUFF 1024

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
  
  char temp_prime_1[BUFF];
  char temp_prime_2[BUFF];
  char temp_prime_gap[BUFF];
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
   
  if (p_rank == FIRST) {
     printf("Beep Boop! Process %d here, starting my stuff!", p_rank);
    char *greatest_prime_1[BUFF];
    char *greatest_prime_2[BUFF];
    char *greatest_prime_gap[BUFF];
  
     // Return largest prime gap from other processors
     for (int source = 1; source < num_processors; source++) { 

        MPI_Recv(temp_prime_1, BUFF, MPI_CHAR, MPI_ANY_SOURCE, PRIME1, MPI_COMM_WORLD, &status);
        MPI_Recv(temp_prime_2, BUFF, MPI_CHAR, MPI_ANY_SOURCE, PRIME2, MPI_COMM_WORLD, &status);
        MPI_Recv(temp_prime_gap, BUFF, MPI_CHAR, MPI_ANY_SOURCE, PRIME_GAP, MPI_COMM_WORLD, &status);
        
        if (strcmp(temp_prime_gap, greatest_prime_gap) == 1) {
           greatest_prime_gap = temp_prime_gap;
           greatest_prime_1 = temp_prime_1;
           greatest_prime_2 = temp_prime_2;
        }
     }
     
     end_time = MPI_Wtime();
     printf("Largest gap %s\n", greatest_prime_gap);
     printf("Wallclock time elapsed: %.2lf seconds\n", end_time - start_time);
  }
   
  /******************** all other tasks do this part ***********************/
  if (p_rank > FIRST) {
    /******************** split up array for load balancing ********************/
    long long int evaluate_length = 0, i_start = 0;
    
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
                
    MPI_Send(temp_prime_1, strlen(temp_prime_1)+1, MPI_CHAR, FIRST, PRIME1, MPI_COMM_WORLD);
    MPI_Send(temp_prime_2, strlen(temp_prime_2)+1, MPI_CHAR, FIRST, PRIME2, MPI_COMM_WORLD);
    MPI_Send(temp_prime_gap, strlen(temp_prime_gap)+1, MPI_CHAR, FIRST, PRIME_GAP, MPI_COMM_WORLD);
    MPI_Finalize();
  }

  return 0;
}
