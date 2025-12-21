#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

int initialize(Queue* q) 
{
    if (!q) return 1;
    q->BegQ = NULL;
    q->EndQ = NULL;
    q->size = 0;
    return 0;
}

int append(Queue* q, int value) 
{
    Elem* new_elem = (Elem*)malloc(sizeof(Elem));
    if (!new_elem) 
    {
        fprintf(stderr, "Ошибка: не удалось выделить память для элемента очереди\n");
        return 0;
    }
    new_elem->data = value;
    new_elem->link = NULL;
    if (q->EndQ == NULL)
    {
        q->BegQ = new_elem;
    }
    else 
    {
        q->EndQ->link = new_elem;
    }
    q->EndQ = new_elem;
    q->size++;
    return 1;
}

int delete(Queue* q, int* value) 
{
    if (q->BegQ == NULL)  return 0;
    Elem* temp = q->BegQ;
    *value = temp->data;
    q->BegQ = q->BegQ->link;
    if (q->BegQ == NULL) 
    {
        q->EndQ = NULL;
    }
    free(temp);
    q->size--;
    return 1;
}

void clear_queue(Queue* q) 
{
    int value;
    while (!is_empty(q)) 
    {
        delete(q, &value);
    }
}

int queue_size(Queue* q) 
{
    return q->size;
}

int copy_queue(Queue* dest, Queue* src) 
{
    initialize(dest);
    Elem* current = src->BegQ;
    while (current != NULL) 
    {
        if (!append(dest, current->data)) 
        {
            clear_queue(dest);
            return 0;
        }
        current = current->link;
    }
    return 1;
}

int print_queue(Queue* q) 
{
    if (is_empty(q)) 
    {
        printf("(пусто)\n");
        return 0;
    }
    Elem* current = q->BegQ;
    int count = 0;
    while (current != NULL) 
    {
        printf("%d ", current->data);
        current = current->link;
        count++;
        if (count % 10 == 0 && current != NULL) 
        {
            puts("");
        }
    }
    puts("");
    return count;
}

int print_to_file(Queue* q, FILE* file) 
{
    if (is_empty(q)) return 0;
    Elem* current = q->BegQ;
    int count = 0;
    while (current != NULL) 
    {
        fprintf(file, "%d ", current->data);
        current = current->link;
        count++;
        if (count % 20 == 0 && current != NULL) fputc(10,file);
    }
    return count;
    fputc(10,file);
}

int is_empty(Queue* q) 
{
    return q->BegQ == NULL;
}

Elem* get_elem_at(Queue* q, int index) 
{
    if (index < 0 || index >= q->size) 
    {
        return NULL;
    }
    Elem* current = q->BegQ;
    for (int i = 0; i < index; i++) 
    {
        current = current->link;
    }
    return current;
}

Elem* get_prev_elem(Queue* q, Elem* target) 
{
    if (q->BegQ == NULL || target == q->BegQ) 
    {
        return NULL;
    }
    Elem* current = q->BegQ;
    while (current != NULL && current->link != target) 
    {
        current = current->link;
    }
    return current;
}

int extract_elem(Queue* q, Elem* prev, Elem* elem) 
{
    if (elem == NULL) return 0;
    if (prev == NULL) 
    {
        q->BegQ = elem->link;
        if (q->BegQ == NULL) 
        {
            q->EndQ = NULL;
        }
    } 
    else 
    {
        prev->link = elem->link;
        if (elem == q->EndQ)
        {
            q->EndQ = prev;
        }
    }
    elem->link = NULL;
    q->size--;
    return 1;
}

int insert_after(Queue* q, Elem* prev, Elem* elem) 
{
    if (elem == NULL) return 0;
    
    if (prev == NULL) 
    {
        elem->link = q->BegQ;
        q->BegQ = elem;
        if (q->EndQ == NULL) 
        {
            q->EndQ = elem;
        }
    } 
    else 
    {
        elem->link = prev->link;
        prev->link = elem;
        if (prev == q->EndQ) 
        {
            q->EndQ = elem;
        }
    }
    q->size++;
    return 1;
}