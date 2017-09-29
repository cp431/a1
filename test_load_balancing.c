/*
 * test_load_balancing.c
 *
 *  Created on: Sep 29, 2017
 *      Author: shar1370
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]) {

	int list[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};
	int evaluate_length, list_length, p_rank, processors, i_start, j, diff, max_diff;
	max_diff = 0;

	/*********** TEST VALUES ***********/
	list_length = 46; // determined at run time
	p_rank = 3;
	processors = 8;
	/***********************************/

	evaluate_length = floor(list_length / processors);
	if (p_rank < list_length % processors)
			evaluate_length += 1;

	i_start = (p_rank - 1) * floor(list_length / processors) + ((p_rank < processors) ? (p_rank - 1) : processors);
	printf("List length for process %i: %i\n", p_rank, evaluate_length);

	for (int i = i_start; i < evaluate_length + i_start; i++) {
 		j = i + 1;
		diff = list[j] - list[i];
		if (diff > max_diff)
			max_diff = diff;
     }

	printf("Max prime difference in process %i starting at index %i: %i\n", p_rank, i_start, max_diff);
	return (EXIT_SUCCESS);
}
