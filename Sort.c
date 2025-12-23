#include "Sort.h"
#include <stdio.h>

static Elem* find_min_elem(Elem* start) 
{
    if (start == NULL) return NULL;
    Elem* min_elem = start;
    Elem* current = start->link;
    while (current != NULL) 
    {
        if (current->data < min_elem->data) 
        {
            min_elem = current;
        }
        current = current->link;
    }
    return min_elem;
}

void selection_sort_queue(Queue* q) 
{
    if (q->size <= 1) return;
    Elem* sorted_end = NULL;  
    while (sorted_end != q->EndQ) 
    {
        Elem* start_search = (sorted_end == NULL) ? q->BegQ : sorted_end->link;
        Elem* min_elem = find_min_elem(start_search);
        if (min_elem != start_search) 
        {
            Elem* prev_min = get_prev_elem(q, min_elem);
            extract_elem(q, prev_min, min_elem);
            if (sorted_end == NULL) 
            {
                insert_after(q, NULL, min_elem);
            } else 
            {
                insert_after(q, sorted_end, min_elem);
            }
            sorted_end = min_elem;
        } 
        else 
        {
            sorted_end = min_elem;
        }
    }
}

static Elem* partition_queue(Elem* start, Elem* end, Elem** new_start, Elem** new_end) 
{
    Elem* pivot = end;
    Elem* prev = NULL;
    Elem* current = start;
    Elem* tail = pivot;
    
    while (current != pivot) 
    {
        if (current->data < pivot->data) 
        {
            if (*new_start == NULL) 
            {
                *new_start = current;
            }
            prev = current;
            current = current->link;
        } 
        else 
        {
            Elem* link = current->link;
            if (prev) 
            {
                prev->link = link;
            }
            if (start == current) 
            {
                start = link; 
            }
            current->link = NULL;
            tail->link = current;
            tail = current;
            current = link;
        }
    }
    
    if (*new_start == NULL) 
    {
        *new_start = pivot;
    }
    *new_end = tail;
    return pivot;
}

static Elem* quick_sort_recursive(Elem* start, Elem* end) 
{
    if (start == NULL || start == end) 
    {
        return start;
    }
    
    Elem* new_start = NULL;
    Elem* new_end = NULL;
    Elem* pivot = partition_queue(start, end, &new_start, &new_end);

    if (new_start != pivot) 
    {
        Elem* temp = new_start;
        while (temp->link != pivot) 
        {
            temp = temp->link;
        }
        temp->link = NULL;
        
        new_start = quick_sort_recursive(new_start, temp);
        

        temp = new_start;
        while (temp->link != NULL) 
        {
            temp = temp->link;
        }
        temp->link = pivot;
    }
    
    if (pivot != new_end && pivot->link != NULL) 
    {
        pivot->link = quick_sort_recursive(pivot->link, new_end);
    }
    
    return new_start;
}

void quick_sort_queue(Queue* q) 
{
    if (q->size <= 1) return;
    
    Elem* start = q->BegQ;
    Elem* end = q->EndQ;
    
    q->BegQ = quick_sort_recursive(start, end);
    
    Elem* current = q->BegQ;
    while (current != NULL && current->link != NULL) 
    {
        current = current->link;
    }
    q->EndQ = current;
}