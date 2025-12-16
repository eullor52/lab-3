#ifndef SORT_H
#define SORT_H

#include "Queue.h"

void selection_sort_queue(Queue* q);

void swap_elems_queue(Queue* q, int i, int j);

void quick_sort_queue(Queue* q);
void quick_sort_recursive(Queue* q, int left, int right);
int partition_queue(Queue* q, int left, int right);

#endif
