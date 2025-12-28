#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Sort.h"
#include <time.h>
#include <limits.h>
#include <ctype.h>

#define START_TEST 10
#define END_TEST 15

void clean_input_buffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int fprint_queue(Queue* q, FILE* file) 
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

static double time_for_sort(Queue* q, int mode)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    mode == 1 ? selection_sort_queue(q) : quick_sort_queue(q);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double sort_time = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    return sort_time/1e6;
}

int file_work(const char* file_name) 
{
    Queue q; 
    initialize_queue(&q);
    FILE* input = fopen(file_name, "r");
    if (!input) 
    {
        printf("Ошибка открытия файла: %s\n", file_name);
        return 1;
    }
    int num;
    int count = 0;
    while (fscanf(input, "%d", &num) != EOF) 
    {
        append(&q, num);
        count++;
    }
    fclose(input);
    printf("Чисел прочитано: %d\n", count);
    if (is_empty(&q)) 
    {
        printf("Очередь пуста, сортировка не требуется\n");
        return 1;
    }
    puts("Неотсортированная очередь:");
    print_queue(&q);
    quick_sort_queue(&q);
    FILE* output = fopen("output.txt", "w");
    if (!output) 
    {
        printf("Ошибка создания output.txt\n");
        clear_queue(&q);
        return 1;
    }
    int written = fprint_queue(&q, output);
    printf("В файл записано %d элементов.\n", written);
    
    puts("Отсортированная очередь:");
    print_queue(&q);
    clear_queue(&q);
    fclose(output);
    return 0;
}

static int power(int number, int degree)
{
    int result = number;
    for (int i = 1; i < degree; i++) result *= number;
    return result;
}

int sort_time_comparison()
{
    int num;
    Queue q;
    initialize_queue(&q);
    FILE* file = fopen("test_data.txt","r");
    FILE* output = fopen("result_time.txt","w");
    if (!file) return 1;
    for(int i = START_TEST; i < END_TEST; i++)
    {
        for(int n = 0; n < power(2,i); n++)
        {
            fscanf(file, "%d", &num);
            append(&q, num);
        }
        fprintf(output, "%d   %f  %f", power(2,i), time_for_sort(&q, 1), time_for_sort(&q, 2));
        fputc(10,output);
        clear_queue(&q);
    }
    fclose(file);
    fclose(output);
    return 0;
}

static int parse_int(const char *s, int *result) 
{
    long value = 0;
    int sign = 1;

    if (*s == '-') 
    {
        sign = -1;
        s++;
    }

    if (!isdigit(*s))
    {
        return 1;
    }

    while (isdigit(*s))
    {
        int digit = *s - '0';
        if (sign == 1)
        {
            if (value > (INT_MAX - digit) / 10)
            {
                return -1;
            }
        } 
        else 
        {
            if (-value < (INT_MIN + digit) / 10)
            {
                return -1; 
            }
        }
        value = value * 10 + digit;
        s++;
    }
    *result = (int)(sign * value);
    return 0;
}

int read_numbers_and_save(const char *filename)
{
    char *buffer = NULL;
    size_t size = 0;
    int c;

    printf("Введите целые числа через пробел:\n");

    while ((c = getchar()) != '\n' && c != EOF) 
    {
        char *tmp = realloc(buffer, size + 2);
        if (!tmp) 
        {
            free(buffer);
            return -1; 
        }
        buffer = tmp;
        buffer[size++] = (char)c;
        buffer[size] = '\0';
    }

    if (!buffer)
    {
        return -2;
    }

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        free(buffer);
        return -3;
    }

    char *p = buffer;
    while (*p)
    {
        while (*p == ' ') p++;
        if (*p == '\0') break;
        int value;
        if (parse_int(p,&value) != 0)
        {
            fclose(file);
            free(buffer);
            return -4;
        }
        fprintf(file, "%d ", value);
        if (*p == '-') p++;
        while (isdigit(*p)) p++;
    }

    fclose(file);
    free(buffer);
    return 0;
}