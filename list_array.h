/*
-------------------------------------
File:    list_array.h
 Project: data_structures_array
file description
-------------------------------------
 */

#ifndef LIST_ARRAY_H_
#define LIST_ARRAY_H_

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

// typedefs

// Structures

#define LIST_INIT 8

/**
 * List header.
 */
typedef struct {
	unsigned int capacity; ///< current capacity of the list.
	int rear; ///< index of next rear element of the list.
	list_data *values; ///< pointer to array of data values.
	list_data_print print; ///< prints list data element
	list_data_destroy destroy; ///< destroys list
	list_data_compare compare; ///< compares list data
	list_data_copy copy; ///< performs deep copy of data
} list;

// Prototypes

/**
 * @param list
 */
/**
 * Initializes a list structure.
 * @param l pointer to the list to initialize.
 * @param print function to print one list_data element.
 * @param destroy function to destroy one list_data element.
 * @param compare function to compare two list data elements.
 */
void list_initialize(list *l, list_data_print print, list_data_destroy destroy,
		list_data_compare compare, list_data_copy copy);

/**
 * Destroys a list.
 * @param l pointer to a list.
 */
void list_destroy(list *l);

/**
 *
 * @param l
 */
void list_display(const list *l);

/**
 * Determines if a list is empty.
 * @param l pointer to a list.
 * @return 1 if the list is empty, 0 otherwise.
 */
int list_empty(const list *l);

/**
 * Determines if the list is full.
 * @param l pointer to a list.
 * @return 1 if the list is full, 0 otherwise.
 */
int list_full(const list *l);

/**
 * Adds a value to a list at location i. Value currently at location i is moved to the
 * end of the list. i must be between 0 and l->rear inclusive or assertion failure.
 * @param l pointer to a list.
 * @param v pointer to the value to insert.
 * @param i the index to put the new value.
 */
void list_insert(list *l, list_data *v, int i);

/**
 * Appends a value to the end of the list.
 * @param l pointer to a list.
 * @param v pointer to the value to append.
 */
void list_append(list *l, list_data *v);

/**
 * Returns the number of values stored in the list.
 * @param l pointer to a list.
 * @return the number of values in list.
 */
int list_length(const list *l);

/**
 * Returns the value on the front of a list, the list is unchanged.
 * Asserts that the list is not empty.
 * @param q pointer to a list.
 * @return  value at the front of the list.
 */
list_data list_peek(const list *l);

/**
 * Returns the number of times key appears in list.
 * @param l pointer to a list.
 * @param key key of the value to find.
 * @return the number of times key appears in list.
 */
int list_count(const list *l, const list_data *key);

#endif /* LIST_ARRAY_H_ */
