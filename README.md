# MPI programming for gaps between prime numbers

CP431,CP631 Parallel Programming, Assignment 1

Instructor: I. Kotsireas, e-mailikotsire@wlu.ca

- This assignment must be completed exclusively on the orca SHARCnet cluster using MPIC or Python programming.
- Strict adherence to the SHARCNET etiquette (as per the course outline) is required.
- Refer to the course outline for details on the assignment submission instructions.

The gap between consecutive prime numbers 11 and 13 is equal to 2. The gap between consecutive prime numbers 503 and 509 is equal to 6. Write an MPI C or Python program to determine the largest gap between a pair of consecutiveprime numbers, up to 1,000,000,00 (one billion). Your program should also output two primenumbers in the range [1:109] that realize the largest gap found.

You can use any of the Number Theoretic Functions implemented in GMP, GNU Multiple Precision Arithmetic Library, http://gmplib.org/, such as mpz_probab_prime_p, mpz_next_prime. 

Benchmark the performance of your parallel program, when executed on 2, 3, 4, 5, 6, 7, 8 processors. Use a graph to illustrate your conclusions.

Marking Scheme:
1. obtaining the correct results: [35]
2. code correctness, documentation and legibility: [50]
3. overall presentation & adherence to the assignment submission instructions: [15]
4. Bonus Marks:[10] Is your code scalable up to 1,000,000,000,000 (one trillion)? If yes, what are the corresponding results?
