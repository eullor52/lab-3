#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Sort.h"
#include <time.h>

double time_for_sort(Queue* q, int mode)
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
    initialize(&q);
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
    int written = print_to_file(&q, output);
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
    initialize(&q);
    FILE* file = fopen("test_data.txt","r");
    FILE* output = fopen("result_time.txt","w");
    if (!file) return 1;
    for(int i = 10; i < 15; i++)
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

void read_queue(FILE* file)
{
    Queue q;
    int num;
    initialize(&q);
    while(scanf("%d",&num)!=0)
    {
        append(&q,num);
    }
    print_to_file(&q,file);
    clear_queue(&q);
}