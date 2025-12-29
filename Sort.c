#include "Sort.h"
#include <stdio.h>

static Elem* find_min_elem(Elem* start)
{
    if (start == NULL) return NULL;

    Elem* min_elem = start;
    Elem* current = start->link;

    while (current != NULL)
    {
        if (current->data < min_elem->data) min_elem = current;
        current = current->link;
    }
    return min_elem;
}

void selection_sort_queue(Queue* q)
{
    if (is_empty(q) || q->BegQ->link == NULL) return;

    Elem* sorted_end = NULL;
    Elem* start_search;
    Elem* min_elem;
    Elem* prev_min;

    while (sorted_end != q->EndQ)
    {
        start_search = (sorted_end == NULL) ? q->BegQ : sorted_end->link;
        min_elem = find_min_elem(start_search);
        if (min_elem != start_search)
        {
            prev_min = get_prev_elem(q, min_elem);
            extract_elem(q, prev_min, min_elem);
            if (sorted_end == NULL) insert_after(q, NULL, min_elem);
            else insert_after(q, sorted_end, min_elem);
            sorted_end = min_elem;
        }
        else sorted_end = min_elem;
    }
}

static void concat_queues(Queue* q,Queue left,Elem* pivot,Queue right)
{
    if (!is_empty(&left) && !is_empty(&right)) 
    {
        left.EndQ->link = pivot;
        pivot->link = right.BegQ;
        q->BegQ = left.BegQ;
        q->EndQ = right.EndQ;
    } 
    else if (!is_empty(&left)) 
    {
        left.EndQ->link = pivot;
        q->BegQ = left.BegQ;
        q->EndQ = pivot;
    } 
    else if (!is_empty(&right)) 
    {
        pivot->link = right.BegQ;
        q->BegQ = pivot;
        q->EndQ = right.EndQ;
    } 
    else 
    {
        q->BegQ = q->EndQ = pivot;
    }
}

void quick_sort_queue(Queue *q)
{
    if (is_empty(q) || q->BegQ == q->EndQ) return;

    Elem* pivot = q->BegQ;
    
    Queue left, right;
    initialize_queue(&left);
    initialize_queue(&right);
    
    Elem* current = pivot->link;
    pivot->link = NULL; 
    
    while (current) 
    {
        Elem* next = current->link;  
        current->link = NULL;        
        
        if (current->data < pivot->data) 
        {
            if (is_empty(&left)) 
            {
                left.BegQ = left.EndQ = current;
            } 
            else 
            {
                left.EndQ->link = current;
                left.EndQ = current;
            }
        } 
        else 
        {
            if (is_empty(&right)) 
            {
                right.BegQ = right.EndQ = current;
            } 
            else 
            {
                right.EndQ->link = current;
                right.EndQ = current;
            }
        }
        current = next;
    }
    
    quick_sort_queue(&left);
    quick_sort_queue(&right);

    concat_queues(q, left, pivot, right);
}