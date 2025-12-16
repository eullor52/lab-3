#ifndef QUEUE_H
#define QUEUE_H

typedef struct Elem {
    int data;
    struct Elem* next;
} Elem;

typedef struct {
    Elem* front;
    Elem* rear;
    int size;
} Queue;

void init_queue(Queue* q);
int enqueue(Queue* q, int value);
int dequeue(Queue* q, int* value);
void clear_queue(Queue* q);
int queue_size(Queue* q);
int copy_queue(Queue* dest, Queue* src);
void print_queue(Queue* q);
int is_empty(Queue* q);
int get_at(Queue* q, int index, int* value);
int set_at(Queue* q, int index, int value);

#endif
