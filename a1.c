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
#define COUNT 1

#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) 
{
   
  long long int problem_size = 10LL;
  int num_processors = 0;
  double start_time = 0.0;
  double end_time = 0.0;
  int p_rank = 0;
  MPI_Status status;
  MPI_Request request;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_processors);
  num_processors--;
  
  long long int temp_prime_1;
  long long int temp_prime_2;
  long long int temp_prime_gap;

  long long int greatest_prime_1;
  long long int greatest_prime_2;
  long long int greatest_prime_gap;
   
  long int primes[problem_size];
   
  for (long int i; i < problem_size; i++) {
     primes[i] = i;
  }
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
   
  /******************** all other tasks do this part ***********************/
  if (p_rank > FIRST) {
     
    /******************** split up array for load balancing ********************/
    long long int evaluate_length = 0LL, i_start = 0LL, max_diff = 0LL, diff = 0LL;

  	 evaluate_length = floor(problem_size / num_processors);
     
    if (p_rank < problem_size % num_processors)
  			evaluate_length += 1;

  	 i_start = (p_rank - 1) * floor(problem_size / num_processors) + (((p_rank - 1) < num_processors) ? (p_rank - 1) : num_processors);
     
    // testing prime list
    printf("Printing prime list for process %d\n", p_rank);
    for (int i = 0; i < evaluate_length; i++) {
       printf("%ld ", primes[i]);
    }
    printf("\n");
    
   long long int j = 0LL, prime1_index = 0LL, prime2_index = 0LL; 
   printf("Doot Doot! Process %d here, starting to compare primes!\n", p_rank);  
  	for (long long int i = 0; i < evaluate_length - 1LL; ++i) {
   		j = i + 1;
         
         printf("Prime 1: %d\n", primes[i]);
         printf("Prime 2: %d\n", primes[j]);
      
  		   diff = primes[j] - primes[i];
         printf("Difference: %d\n", diff);
  		
         if (diff > max_diff)
         {
            printf("Boop Beep! Process %d here, found a new maximum!\n", p_rank);
            printf("New max: %d\n", diff);
            max_diff = diff;
            prime1_index = i;
            prime2_index = j;
         }
    }
   
    printf("temp_prime_gap @ process %d: %d\n", p_rank, temp_prime_gap);
    printf("temp_prime_1 @ process %d: %d\n", p_rank, temp_prime_1);
    printf("temp_prime_2 @ process %d: %d\n", p_rank, temp_prime_2);
                
    MPI_Send(&temp_prime_1, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME1, MPI_COMM_WORLD);
    MPI_Send(&temp_prime_2, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME2, MPI_COMM_WORLD);
    MPI_Send(&temp_prime_gap, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME_GAP, MPI_COMM_WORLD);
  }
   
   if (p_rank == FIRST) {
      
     printf("Beep Boop! Process %d here, starting my stuff!\n", p_rank);
      
     //init_prime_list(primes, &problem_size);
      

     // Return largest prime gap from other processors
     for (int source = 1; source < num_processors; ++source) { 

        MPI_Recv(&temp_prime_1, COUNT, MPI_LONG_LONG_INT, source, PRIME1, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_prime_2, COUNT, MPI_LONG_LONG_INT, source, PRIME2, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_prime_gap, COUNT, MPI_LONG_LONG_INT, source, PRIME_GAP, MPI_COMM_WORLD, &status);
        
        printf("temp_prime_gap @ process %d: %d\n", source, temp_prime_gap);
        printf("greatest_prime_1 @ process %d: %d\n", source, greatest_prime_1);
        printf("greatest_prime_2 @ process %d: %d\n", source, greatest_prime_2);
       
        
        if (temp_prime_gap > greatest_prime_gap) {
           greatest_prime_gap = temp_prime_gap;
           greatest_prime_1 = temp_prime_1;
           greatest_prime_2 = temp_prime_2;
        }
     }

     end_time = MPI_Wtime();
     printf("\nWallclock time elapsed: %.2lf seconds\n", end_time - start_time);
     printf("The largest prime gap is: %d\n", greatest_prime_gap);
     printf("This gap is realized by the difference between %d and %d\n", greatest_prime_1, greatest_prime_2); 
  }
   
  
  MPI_Finalize();
  return 0;
}
