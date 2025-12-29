#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

int initialize_queue(Queue* q)
{
    if (!q) return 1;
    q->BegQ = NULL;
    q->EndQ = NULL;
    return 0;
}

int is_empty(Queue* q)
{
    return q->BegQ == NULL;
}

int append(Queue* q, int value)
{
    Elem* new_elem = (Elem*)malloc(sizeof(Elem));

    if (!new_elem)
    {
        fprintf(stderr, "Ошибка: не удалось выделить память для элемента очереди.\n");
        return 1;
    }

    new_elem->data = value;
    new_elem->link = NULL;

    if (is_empty(q))
    {
        q->BegQ = new_elem;
    }
    else
    {
        q->EndQ->link = new_elem;
    }
    q->EndQ = new_elem;
    return 0;
}

int delete(Queue* q, int* value)
{
    if (is_empty(q))  return 1;

    Elem* temp = q->BegQ;
    *value = temp->data;
    q->BegQ = q->BegQ->link;

    if (q->BegQ == NULL) q->EndQ = NULL;

    free(temp);
    return 0;
}

void clear_queue(Queue* q) 
{
    int value;

    while (!delete(q, &value));
    q->BegQ = NULL;
    q->EndQ = NULL;
}

int copy_queue(Queue* copy, Queue* queue_to_copy) 
{
    if (initialize_queue(copy)) return 1;
    Elem* current = queue_to_copy->BegQ;

    while (current != NULL) 
    {
        if (!append(copy, current->data))
        {
            clear_queue(copy);
            return 1;
        }
        current = current->link;
    }
    return 0;
}

Elem* get_prev_elem(Queue* q, Elem* target) 
{
    if (q->BegQ == NULL || target == q->BegQ) return NULL;
    Elem* current = q->BegQ;

    while (current != NULL && current->link != target) current = current->link;
    return current;
}

int extract_elem(Queue* q, Elem* prev, Elem* elem) 
{
    if (elem == NULL) return 1;

    if (prev == NULL)
    {
        q->BegQ = elem->link;
        if (q->BegQ == NULL) q->EndQ = NULL;
    }
    else
    {
        prev->link = elem->link;
        if (elem == q->EndQ) q->EndQ = prev;
    }

    elem->link = NULL;
    return 0;
}

int insert_after(Queue* q, Elem* prev, Elem* elem) 
{
    if (elem == NULL) return 0;
    
    if (prev == NULL)
    {
        elem->link = q->BegQ;
        q->BegQ = elem;
        if (q->EndQ == NULL) q->EndQ = elem;
    }
    else
    {
        elem->link = prev->link;
        prev->link = elem;
        if (prev == q->EndQ) q->EndQ = elem;
    }

    return 1;
}