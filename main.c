#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Queue.h"
#include "Sort.h"
#include "File.h"

void print_usage()
{
    printf("Использование:\n");
    printf("  program.exe                          - ввод данных с клавиатуры\n");
    printf("  program.exe --file filename.txt      - загрузка данных из файла\n");
    printf("  program.exe --compare                - сравнение алгоритмов сортировки\n");
    printf("\nПараметры для сравнения:\n");
    printf("  --min SIZE    минимальный размер (по умолчанию 1000)\n");
    printf("  --max SIZE    максимальный размер (по умолчанию 10000)\n");
    printf("  --step SIZE   шаг увеличения (по умолчанию 1000)\n");
}

void generate_test_file(const char* filename, int size)
{
    FILE* file = fopen(filename, "w");
    if (!file) return;

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", rand() % 10000);
        if ((i + 1) % 10 == 0) fprintf(file, "\n");
    }

    fclose(file);
}

void compare_algorithms(int min_size, int max_size, int step)
{
    printf("Сравнение алгоритмов сортировки\n");
    printf("Размер данных от %d до %d с шагом %d\n\n", min_size, max_size, step);
    printf("Размер | Выбором (сек) | Быстрая (сек) | Отношение\n");
    printf("---------------------------------------------------\n");
    for (int size = min_size; size <= max_size; size += step)
    {
        char filename[256];
        sprintf(filename, "test_%d.txt", size);
        generate_test_file(filename, size);
        Queue q1, q2;
        init_queue(&q1);
        init_queue(&q2);
        read_queue_from_file(&q1, filename);
        copy_queue(&q2, &q1);
        clock_t start = clock();
        selection_sort_queue(&q1);
        clock_t end = clock();
        double time_selection = (double)(end - start) / CLOCKS_PER_SEC;
        start = clock();
        quick_sort_queue(&q2);
        end = clock();
        double time_quick = (double)(end - start) / CLOCKS_PER_SEC;
        double ratio = (time_quick > 0) ? time_selection / time_quick : 0;
        printf("%6d | %13.6f | %13.6f | %8.2f\n",
               size, time_selection, time_quick, ratio);
        clear_queue(&q1);
        clear_queue(&q2);
        remove(filename);
    }
}
int main(int argc, char* argv[])
{
    if (argc >= 2 && strcmp(argv[1], "--compare") == 0) {
        int min_size = 1000;
        int max_size = 10000;
        int step = 1000;
        for (int i = 2; i < argc; i++)
        {
            if (strcmp(argv[i], "--min") == 0 && i + 1 < argc)
            {
                min_size = atoi(argv[i + 1]);
                i++;
            }
            else if (strcmp(argv[i], "--max") == 0 && i + 1 < argc)
            {
                max_size = atoi(argv[i + 1]);
                i++;
            }
            else if (strcmp(argv[i], "--step") == 0 && i + 1 < argc)
            {
                step = atoi(argv[i + 1]);
                i++;
            }
        }
        compare_algorithms(min_size, max_size, step);
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "--file") == 0)
    {
        Queue file_queue;
        init_queue(&file_queue);
        if (handle_file_argument(&file_queue, argv[2]))
        {
            clear_queue(&file_queue);
            return 0;
        }
        clear_queue(&file_queue);
        return 1;
    }
    if (argc == 1)
    {
        Queue numbers;
        init_queue(&numbers);
        if (!read_queue_from_stdin(&numbers))
        {
            printf("Не удалось прочитать числа.\n");
            return 1;
        }
        if (is_empty(&numbers))
        {
            printf("Очередь пуста.\n");
            return 0;
        }
        printf("\nВведенная последовательность (%d элементов):\n", queue_size(&numbers));
        print_queue(&numbers);
        write_queue_to_file(&numbers, "original.txt");
        printf("Исходные данные сохранены в файл: original.txt\n");
        Queue selection_sorted, quick_sorted;
        init_queue(&selection_sorted);
        init_queue(&quick_sorted);
        copy_queue(&selection_sorted, &numbers);
        copy_queue(&quick_sorted, &numbers);
        printf("\n--- Сортировка прямым выбором ---\n");
        clock_t start = clock();
        selection_sort_queue(&selection_sorted);
        clock_t end = clock();
        double selection_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Результат:\n");
        print_queue(&selection_sorted);
        printf("Время выполнения: %.6f секунд\n", selection_time);
        write_queue_to_file(&selection_sorted, "output_selection.txt");
        printf("Результат сохранен в файл: output_selection.txt\n");
        printf("\n--- Быстрая сортировка (Хоара) ---\n");
        start = clock();
        quick_sort_queue(&quick_sorted);
        end = clock();
        double quick_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Результат:\n");
        print_queue(&quick_sorted);
        printf("Время выполнения: %.6f секунд\n", quick_time);
        write_queue_to_file(&quick_sorted, "output_quick.txt");
        printf("Результат сохранен в файл: output_quick.txt\n");
        printf("\n=== Сравнение производительности ===\n");
        printf("Размер данных: %d элементов\n", queue_size(&numbers));
        printf("Сортировка выбором: %.6f сек\n", selection_time);
        printf("Быстрая сортировка: %.6f сек\n", quick_time);
        if (quick_time > 0)
        {
            printf("Быстрая сортировка быстрее в %.2f раз\n", selection_time / quick_time);
        }
        clear_queue(&numbers);
        clear_queue(&selection_sorted);
        clear_queue(&quick_sorted);
        printf("\nДля полного сравнения алгоритмов выполните:\n");
        printf("program.exe --compare --min 1000 --max 10000 --step 1000\n");
        return 0;
    }
    print_usage();
    return 1;
}
