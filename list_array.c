/*
 -------------------------------------
 File:    list_array.c
 Project: data_structures_array
 Dynamic array in C
 -------------------------------------
 */

#include "list_array.h"

// Private helper functions

/**
 * Increases size of list capacity.
 * @param target pointer to a list.
 */
static void list_resize(list *target, int max_size) {

	if (max_size >= target->capacity) {
		// Update the target list capacity if necessary.
		target->capacity = max_size * 2;

		if (target->capacity > INT_MAX) {
			// Can do this because capacity is unsigned.
			target->capacity = INT_MAX;
		}
		target->values = realloc(target->values,
				(sizeof *target->values) * target->capacity);
		// Must be able to allocate more memory to list.
		assert(target->values != NULL);
	}
	return;
}

/**
 * Determines if index is valid.
 * @param l pointer to a list.
 * @param i index.
 * @return 1 if i between 0 and l->rear inclusive, 0 otherwise.
 */
static int list_valid_index(const list *l, int i) {
	return (i >= 0 && i <= l->rear);
}

// Public functions

void list_initialize(list *l, list_data_print print, list_data_destroy destroy,
		list_data_compare compare, list_data_copy copy) {
	l->capacity = LIST_INIT;
	l->values = malloc((sizeof *l->values) * l->capacity);
	// Must be able to allocate memory to list data storage.
	assert(l->values != NULL);

	l->rear = 0;
	l->print = print;
	l->destroy = destroy;
	l->compare = compare;
	l->copy = copy;
}

void list_destroy(list *l) {
	int i;

	for (i = 0; i < l->rear; i++) {
		// Destroy individual array elements (in case they are malloc'd)
		l->destroy(&l->values[i]);
	}
	// Free up the data array.
	free(l->values);
	l->values = NULL;
	l->capacity = 0;
	l->rear = 0;
	return;
}

int list_empty(const list *l) {
	return (l->rear == 0);
}

int list_full(const list *l) {
	// l->rear cannot equal or exceed type maximum.
	return (l->rear < (INT_MAX - 1));
}

void list_append(list *l, list_data *v) {

	// Check list capacity.
	list_resize(l, l->rear);
	// Add value to rear of array.
	l->copy(&l->values[l->rear], v);
	l->rear++;
	return;
}

int list_length(const list *l) {
	return (l->rear);
}

list_data list_peek(const list *l) {
	return (l->values[0]);
}

int list_count(const list *l, const list_data *key) {
	int i = 0, count = 0;

	for (i = 0; i < l->rear; i++) {

		if (l->compare(&l->values[i], key) == 0) {
			count++;
		}
	}
	return (count);
}

