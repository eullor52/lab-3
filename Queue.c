#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

void init_queue(Queue* q)
{
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int enqueue(Queue* q, int value)
{
    Elem* new_elem = (Elem*)malloc(sizeof(Elem));
    if (!new_elem)
    {
        fprintf(stderr, "Ошибка: не удалось выделить память для элемента очереди\n");
        return 0;
    }
    new_elem->data = value;
    new_elem->next = NULL;
    if (q->rear == NULL)
    {
        q->front = new_elem;
    }
    else
    {
        q->rear->next = new_elem;
    }
    q->rear = new_elem;
    q->size++;
    return 1;
}

int dequeue(Queue* q, int* value)
{
    if (q->front == NULL)
    {
        fprintf(stderr, "Ошибка: попытка удаления из пустой очереди\n");
        return 0;
    }
    Elem* temp = q->front;
    *value = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
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
        dequeue(q, &value);
    }
}

int queue_size(Queue* q)
{
    return q->size;
}

int copy_queue(Queue* dest, Queue* src)
{
    init_queue(dest);
    Elem* current = src->front;
    while (current != NULL)
    {
        if (!enqueue(dest, current->data))
        {
            clear_queue(dest);
            return 0;
        }
        current = current->next;
    }
    return 1;
}

void print_queue(Queue* q)
{
    if (is_empty(q))
    {
        printf("(пусто)\n");
        return;
    }
    Elem* current = q->front;
    int count = 0;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
        count++;
        if (count % 10 == 0 && current != NULL)
        {
            printf("\n");
        }
    }
    printf("\n");
}

int is_empty(Queue* q)
{
    return q->front == NULL;
}

int get_at(Queue* q, int index, int* value)
{
    if (index < 0 || index >= q->size)
    {
        fprintf(stderr, "Ошибка: индекс %d выходит за пределы очереди (размер: %d)\n", index, q->size);
        return 0;
    }
    Elem* current = q->front;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    *value = current->data;
    return 1;
}

int set_at(Queue* q, int index, int value)
{
    if (index < 0 || index >= q->size)
    {
        fprintf(stderr, "Ошибка: индекс %d выходит за пределы очереди (размер: %d)\n", index, q->size);
        return 0;
    }
    Elem* current = q->front;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    current->data = value;
    return 1;
}
