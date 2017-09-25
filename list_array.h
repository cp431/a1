/*
-------------------------------------
File:    list_array.h
 Project: data_structures_array
file description
-------------------------------------
Author:  David Brown
ID:      999999999
Email:   dbrown@wlu.ca
 Version  2017-06-03
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
 * Finds the value matching key int the list. Returns -1 if the value cannot be found.
 * @param l pointer to a list.
 * @param value holds a copy of the value found.
 * @param key key of the value to find.
 * @return -1 if the value cannot be found, the index of key otherwise.
 */
int list_find(const list *l, list_data *value, const list_data *key);

/**
 * Removes the value matching key from the list. The value at the end of the list must be moved
 * to fill up the hole opened by the removal, if there is one. Returns NULL if the value cannot be found.
 * @param l pointer to a list.
 * @param value holds a copy of the value removed.
 * @param key key of the value to remove.
 * @return -1 if the value cannot be found, the index of key otherwise.
 */
int list_remove(list *l, list_data *value, const list_data *key);

/**
 * Returns the index of key in list.values, -1 if key not in list.
 * @param l pointer to a list.
 * @param key key of the value to find.
 * @return index of the location of key in list.values.
 */
int list_index(const list *l, const list_data *key);

/**
 * Determines is key is in list.
 * @param l pointer to a list.
 * @param key key of the value to find.
 * @return 1 if key in list.values, 0 otherwise.
 */
int list_contains(const list *l, const list_data *key);

/**
 * Returns the number of times key appears in list.
 * @param l pointer to a list.
 * @param key key of the value to find.
 * @return the number of times key appears in list.
 */
int list_count(const list *l, const list_data *key);

/**
 * Finds the maximum value in list. Assert that list is not empty.
 * @param l pointer to a list.
 * @param value pointer to the uninitialized maximum value.
 * @return the pointer to value.
 */
list_data *list_max(list *l, list_data *value);

/**
 * Finds the minimum value in list. Assert that list is not empty.
 * @param l pointer to a list.
 * @param value pointer to the uninitialized minimum value.
 * @return the pointer to value.
 */
list_data *list_min(const list *l, list_data *value);

/**
 * Removes all duplicate values from list. Only one copy of each value in the list remains.
 * @param l pointer to a list.
 */
void list_clean(list *l);

/**
 * Compares two lists. Returns 1 if they contain the same data in the same order,
 * 0 otherwise.
 * @param l1 the first list to compare.
 * @param l2 the second list to compare.
 * @return
 */
int list_identical(const list *l1, const list *l2);

/**
 * Returns a list that contains all values in both source1 and source2.
 * source1 and source2 are unchanged.
 * @param target pointer to the initialized result list.
 * @param source1 pointer to the first source list.
 * @param source2 pointer to the second source list.
 */
void list_union(list *target, const list *source1, const list *source2);

/**
 * Returns a list that contains only values that appear in both source1 and source2.
 * @param target pointer to the initialized result list.
 * @param source1 pointer to the first source list.
 * @param source2 pointer to the second source list.
 */
void list_intersection(list *target, const list *source1, const list *source2);

#endif /* LIST_ARRAY_H_ */
