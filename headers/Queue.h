#ifndef QUEUE_H
#define QUEUE_H
#include<stdio.h>

typedef struct Elem 
{
    int data;
    struct Elem* link;
} Elem;

typedef struct 
{
    Elem* BegQ;
    Elem* EndQ;
    int size;
}Queue;

int initialize_queue(Queue* q);
int append(Queue* q, int value);
int delete(Queue* q, int* value);
void clear_queue(Queue* q);
int queue_size(Queue* q);
int copy_queue(Queue* dest, Queue* src);
int is_empty(Queue* q);
Elem* get_elem_at(Queue* q, int index);
Elem* get_prev_elem(Queue* q, Elem* target);
int extract_elem(Queue* q, Elem* prev, Elem* elem);
int insert_after(Queue* q, Elem* prev, Elem* elem);

#endif
