/*
 -------------------------------------------------------
 data.c
 Data for List
 -------------------------------------------------------
 */
 
// Includes
#include <stdio.h>

#include "data.h"

// Functions

void data_initialize(data_type *d, int n) {
	d->n = n;
	return;
}

void data_destroy(data_type *d) {
	d->n = 0;
	return;
}

void data_print(const data_type *d) {
	printf("n: %d", d->n);
	return;
}

int data_compare(const data_type *d1, const data_type *d2) {
	int result = 0;

	if (d1->n > d2->n) {
		result = 1;
	} else if (d1->n < d2->n) {
		result = -1;
	}
	return (result);
}
