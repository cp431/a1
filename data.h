/*
 -------------------------------------------------------
 data.h
Data for list.
 -------------------------------------------------------
 */
#ifndef DATA_H_
#define DATA_H_

#include <stdlib.h>

// Structures

/**
 * Data structure.
 */
typedef struct {
	int n;
} data_type;

// Prototypes

/**
 * Assigns values to data fields. String field is malloc'd.
 * @param d pointer to data structure.
 * @param n integer.
er. */
void data_initialize(data_type *d, int n);

/**
 * Destroys contents of data structure.
 * @param d pointer to data structure.
 */
void data_destroy(data_type *d);

/**
 * Prints contents of data structure.
 * @param d pointer to data structure.
 */
void data_print(const data_type *d);

/**
 *
 * @param d1
 * @param d2
 * @return
 */
int data_compare(const data_type *d1, const data_type *d2);

#endif /* DATA_H_ */
