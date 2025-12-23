#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include <string.h>
#include "File.h"

int main(int argc, char** argv)
{
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
        err = file_work(argv[2]);
        puts("Введите новую очередь:");
        int result = read_numbers_and_save(argv[2]);
        if (result == 0)
        {
            puts("Запись прошла успешно.");  
        }
        else
        {
            printf("Ошибка записи чисел в файл, код ошибки: %d\n", result);
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
        puts("-file <имя_файла>");
        puts("-time");
        return 1;
    }
    
    return err;
}