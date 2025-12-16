#include "Sort.h"
#include <stdio.h>

void swap_elems_queue(Queue* q, int i, int j)
{
    int val_i, val_j;
    get_at(q, i, &val_i);
    get_at(q, j, &val_j);
    set_at(q, i, val_j);
    set_at(q, j, val_i);
}

void selection_sort_queue(Queue* q)
{
    int n = queue_size(q);
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        int min_val, current_val;
        get_at(q, i, &min_val);
        for (int j = i + 1; j < n; j++)
        {
            get_at(q, j, &current_val);
            if (current_val < min_val)
            {
                min_val = current_val;
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap_elems_queue(q, i, min_idx);
        }
    }
}

int partition_queue(Queue* q, int left, int right)
{
    int pivot, pivot_val;
    get_at(q, right, &pivot_val);
    pivot = pivot_val;
    int i = left - 1;
    for (int j = left; j < right; j++)
    {
        int current_val;
        get_at(q, j, &current_val);
        if (current_val <= pivot)
        {
            i++;
            swap_elems_queue(q, i, j);
        }
    }
    swap_elems_queue(q, i + 1, right);
    return i + 1;
}

void quick_sort_recursive(Queue* q, int left, int right)
{
    if (left < right)
    {
        int pi = partition_queue(q, left, right);
        quick_sort_recursive(q, left, pi - 1);
        quick_sort_recursive(q, pi + 1, right);
    }
}

void quick_sort_queue(Queue* q)
{
    int size = queue_size(q);
    if (size <= 1) return;
    quick_sort_recursive(q, 0, size - 1);
}
