/**
   a1.c
   ====
   This program will eventually do things.
*/

#include "mpi.h"
#include "prime_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Misc Constants
#define FIRST 0
#define BASE_DECIMAL 10

// MPI Send/Receive Tag Names
#define PRIME1 0
#define PRIME2 1
#define PRIME_GAP 2
#define BUFF 1024
#define COUNT 1



int main(int argc, char **argv) 
{
  if (argc < 2)
  {
     printf("ERROR: Missing problem size. Please specify on the command line.\n");
     return -1;
  }
   
  long long int problem_size = atoll(argv[1]);
  int num_processors = 0;
  double start_time = 0.0;
  double end_time = 0.0;
  int p_rank = 0;
  MPI_Status status;
  MPI_Request request;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_processors);
  
  long long int temp_prime_1 = 0LL;
  long long int temp_prime_2 = 0LL;
  long long int temp_prime_gap = 0LL;

  long long int greatest_prime_1 = 0LL;
  long long int greatest_prime_2 = 0LL;
  long long int greatest_prime_gap = 0LL;
  
  long long int *primes = calloc(problem_size, sizeof(long long int));
   
  /******************** task with rank 0 does this part ********************/
  start_time = MPI_Wtime();   /* Initialize start time */
   
  if (p_rank == FIRST) {
      printf("Beep Boop! Process %d here, starting my stuff!\n", p_rank);
      printf("Initializing list...\n");
       init_prime_list(primes, &problem_size);
      printf("Initializing list complete!\n");
      // testing prime list
      printf("Printing prime list for process %d\n", p_rank);
      for (int i = 0; i < problem_size; i++) {
         printf("%lld ", primes[i]);
      }
      printf("\n");
    }

   /******************** all tasks do this part ***********************/
   
    MPI_Barrier(MPI_COMM_WORLD);
   
    MPI_Bcast(
       primes,
       problem_size,
       MPI_LONG_LONG_INT,
       FIRST,
       MPI_COMM_WORLD);
       
    /******************** split up array for load balancing ********************/
    long long int evaluate_length = 0LL, i_start = 0LL, max_diff = 0LL, diff = 0LL;

  	 evaluate_length = floor(problem_size / num_processors);
     
    if (p_rank < problem_size % num_processors)
  			evaluate_length += 1;
   
    int other_bit = MIN(p_rank, problem_size % num_processors);

  	 i_start = p_rank * evaluate_length + other_bit;
   
    if (p_rank != num_processors - 1) {
       evaluate_length++;
    }
    
   
     printf("i_start for process %d: %lld\n", p_rank, i_start);
      
     // testing prime list
     printf("Printing prime list for process %d\n", p_rank);
     for (int i = i_start; i < i_start + evaluate_length; i++) {
        printf("%lld ", primes[i]);
     }
     printf("\n");
    
   long long int j = 0LL, prime1_index = 0LL, prime2_index = 0LL; 
   printf("Doot Doot! Process %d here, starting to compare primes!\n", p_rank); 
  	for (long long int i = i_start; i < i_start + evaluate_length - 1; ++i) {
   		
         j = i + 1;
  		   diff = primes[j] - primes[i];
         printf("Prime 1 at index %lld: %lld\n", i, primes[i]);
         printf("Prime 2 at index %lld: %lld\n", j, primes[j]);
         printf("Difference: %lld\n", diff);
  		
         if (diff > max_diff) {
            max_diff = diff;
            prime1_index = i;
            prime2_index = j;
         }
    }
   
    temp_prime_1 = primes[prime1_index];
    temp_prime_2 = primes[prime2_index];
    temp_prime_gap = max_diff;
                
    MPI_Send(&temp_prime_1, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME1, MPI_COMM_WORLD);
    MPI_Send(&temp_prime_2, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME2, MPI_COMM_WORLD);
    MPI_Send(&temp_prime_gap, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME_GAP, MPI_COMM_WORLD);
   
   MPI_Barrier(MPI_COMM_WORLD);
   
   if (p_rank == FIRST) {
           // Return largest prime gap from other processors
     for (int source = 0; source < num_processors; ++source) { 

        MPI_Recv(&temp_prime_1, COUNT, MPI_LONG_LONG_INT, source, PRIME1, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_prime_2, COUNT, MPI_LONG_LONG_INT, source, PRIME2, MPI_COMM_WORLD, &status);
        MPI_Recv(&temp_prime_gap, COUNT, MPI_LONG_LONG_INT, source, PRIME_GAP, MPI_COMM_WORLD, &status);
        
        if (temp_prime_gap > greatest_prime_gap) {
           greatest_prime_gap = temp_prime_gap;
           greatest_prime_1 = temp_prime_1;
           greatest_prime_2 = temp_prime_2;
        }
     }

     end_time = MPI_Wtime();
     printf("\nWallclock time elapsed: %.2lf seconds\n", end_time - start_time);
     printf("The largest prime gap is: %lld\n", greatest_prime_gap);
     printf("This gap is realized by the difference between %lld and %lld\n", greatest_prime_1, greatest_prime_2); 
  }
   
  MPI_Finalize();
  return 0;
}
