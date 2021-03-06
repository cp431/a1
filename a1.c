/**
   a1.c
   MPI programming for gaps between prime numbers
   Contributors:
   -> Frank Khalil	160226600
   -> Sarah Johnston	150139570
   -> Brad Katz		130750210
   -> Gareth Sharpe	090361370
*/

// Include statment(s)
#include "mpi.h"
#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Macro definition(s)
#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

// Constant definition(s)
#define FIRST 0
#define BASE_DECIMAL 10

// MPI Send/Receive Tag Names
#define PRIME1 0
#define PRIME2 1
#define PRIME_GAP 2
#define BUFF 1024
#define COUNT 1

int main(int argc, char **argv) {
  
   // Error message prompting user for command line arguments
   if (argc < 2) {
     printf("ERROR: Missing problem size. Please specify on the command line.\n");
     return -1;
  }
  
  // Define problem paramaters
  long long int problem_size = atoll(argv[1]);
  int num_processors = 0;
  int p_rank = 0;
  
  // Initialize start/end time 
  double start_time = 0.0;
  double end_time = 0.0;
  
  // Define MPI status and request variables
  MPI_Status status;
  MPI_Request request;

  // Begin parallel process(es)
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_processors);
  
  // Define temporary variables to store potential solutions
  long long int temp_prime_1 = 0LL;
  long long int temp_prime_2 = 0LL;
  long long int temp_prime_gap = 0LL;

  // Define variables to store correct solutions
  long long int greatest_prime_1 = 0LL;
  long long int greatest_prime_2 = 0LL;
  long long int greatest_prime_gap = 0LL;
   
  // Wait for all processes to finish initialization
  MPI_Barrier(MPI_COMM_WORLD);
  // Initialize start time
  start_time = MPI_Wtime();   

  /******************** Load balancing ********************/
  long long int evaluate_length = 0LL, i_start = 0LL;
  // Calculate evaluate_length, the number of primes this processor has to loop through
  evaluate_length = floor(problem_size / num_processors);

  if (p_rank < problem_size % num_processors)
  		evaluate_length += 1;

  int remainder = MIN(p_rank, problem_size % num_processors);

  i_start = p_rank * evaluate_length + remainder;
   
  // To create overlap between each sub-problem (excluding the last processor), 1 is added to evaluate_length.
  if (p_rank != num_processors - 1) {
  evaluate_length++;
  }

  /******************** Initialize and/or set mpz_t variables ********************/

  mpz_t previous_prime, next_prime, diff, max_diff, prime1, prime2, end_prime;

  // Initialize solution storage variables
  mpz_init(diff);
  mpz_init(max_diff);
  mpz_init(prime1);
  mpz_init(prime2);

  // Initialize and set previous, next and end primes to initial indicies 
  mpz_init_set_si(previous_prime, i_start);
  mpz_init_set_si(next_prime, i_start);
  mpz_init_set_si(end_prime, evaluate_length + i_start);

  // Get the next prime beyond start/end indicies
  mpz_nextprime(next_prime, previous_prime);
  mpz_nextprime(end_prime, end_prime);

  // Loop through all primes between the starting prime and the ending prime
  while (mpz_cmp(end_prime, next_prime) == 1) {
    
    // Set up for mpz_nextprime by shifting next prime to previous prime
    mpz_set(previous_prime, next_prime);
    // Get the next prime past our previous prime
    mpz_nextprime(next_prime, previous_prime);
    // Determine the difference between the primes by subtracting them
    mpz_sub(diff, next_prime, previous_prime);

    // If the difference found is greater than the current max difference, update max_diff 
    if (mpz_cmp(diff, max_diff) == 1) {
      mpz_set(max_diff, diff);
      mpz_set(prime1, previous_prime);
      mpz_set(prime2, next_prime);
    }
  }

  // Export each processor's greatest found prime gap, as well as the two primes that created the gap
  mpz_export(&temp_prime_1, 0, -1, sizeof(long long int), 0, 0, prime1);
  mpz_export(&temp_prime_2, 0, -1, sizeof(long long int), 0, 0, prime2);
  mpz_export(&temp_prime_gap, 0, -1, sizeof(long long int), 0, 0, max_diff);

  // Send the data to process zero            
  MPI_Send(&temp_prime_1, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME1, MPI_COMM_WORLD);
  MPI_Send(&temp_prime_2, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME2, MPI_COMM_WORLD);
  MPI_Send(&temp_prime_gap, COUNT, MPI_LONG_LONG_INT, FIRST, PRIME_GAP, MPI_COMM_WORLD);

  /******************** Only process 0 completes this task ********************/
  if (p_rank == FIRST) {

    // Loop through each source processor 
    for (int source = 0; source < num_processors; ++source) { 

      // Receive each processor's greatest found prime gap, as well as the two primes that created the gap
      MPI_Recv(&temp_prime_1, COUNT, MPI_LONG_LONG_INT, source, PRIME1, MPI_COMM_WORLD, &status);
      MPI_Recv(&temp_prime_2, COUNT, MPI_LONG_LONG_INT, source, PRIME2, MPI_COMM_WORLD, &status);
      MPI_Recv(&temp_prime_gap, COUNT, MPI_LONG_LONG_INT, source, PRIME_GAP, MPI_COMM_WORLD, &status);

      // Determine the greatest prime gap from amongst all the processors and update solution variables
      if (temp_prime_gap > greatest_prime_gap) {
         greatest_prime_gap = temp_prime_gap;
         greatest_prime_1 = temp_prime_1;
         greatest_prime_2 = temp_prime_2;
      }
    }

    // Initialize end time
    end_time = MPI_Wtime();

    // Print computed elapsed time and solution
    printf("\nWallclock time elapsed: %.2lf seconds\n", end_time - start_time);
    printf("The largest prime gap is: %lld\n", greatest_prime_gap);
    printf("This gap is realized by the difference between %lld and %lld\n", greatest_prime_1, greatest_prime_2); 
  }

  // Finalize the parallel process
  MPI_Finalize();
  // Return exit success
  return 0;
}
