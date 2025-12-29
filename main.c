#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include <string.h>
#include "File.h"

int main(int argc, char** argv)
{
    char choice;
    int err = 0;
    if (argc < 2) 
    {
        printf("Использование:\n");
        printf("  %s --file <имя_файла>\n", argv[0]);
        printf("  %s --time\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--file") == 0)
    {
        int result = 0;
        for(;;)
        {
            if (result == 0) err = file_work(argv[2]);
            result = read_numbers_and_save(argv[2]);
            if (result == 0)
            {
                puts("Запись прошла успешно.");
            }
            else
            {
                if (result == -1) puts("Ошибка записи чисел в файл, код ошибки: -1 (ошибка выделения памяти)");
                if (result == -2) puts("Ошибка записи чисел в файл, код ошибки: -2 (пустой ввод)");
                if (result == -3) puts("Ошибка записи чисел в файл, код ошибки: -3 (ошибка открытия файла для записи)");
                else puts("Ошибка записи чисел в файл, код ошибки: -4 (некорректный ввод)");
            }
            for(;;)
            {
                puts("Для завершения введите N, для продолжения - Y:");
                if (scanf("%c",&choice) != 1)
                {
                    puts("Ошибка: неизвестный символ.");
                    clean_input_buffer();
                    continue;
                }
                if (choice == 'Y' || choice == 'N')
                {
                    break;
                }
                else
                {
                    puts("Ошибка: неизвестный символ.");
                    clean_input_buffer();
                    continue;
                }
            }
            if (choice == 'Y')
            {
                puts("================================================");
                clean_input_buffer();
                continue;
            } 
            else
            {
                puts("Выполнение програмы завершено.");
                break;
            }
        }
    }
    else if (strcmp(argv[1], "--time") == 0)
    {
        return sort_time_comparison();
    }
    else
    {
        printf("Неизвестный параметр: %s\n", argv[1]);
        puts("Доступные параметры:");
        puts("--file <имя_файла>");
        puts("--time");
        return 1;
    }

    return err;
}