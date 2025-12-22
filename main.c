#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Sort.h"
#include <string.h>
#include "File.h"

int main(int argc, char** argv)
{
    int err;
    if (argc < 3) 
    {
        printf("Использование:\n");
        printf("  %s -file <имя_файла>\n", argv[0]);
        printf("  %s -sort\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-file") == 0)
    {
        err = file_work(argv[2]);
        puts("Введите новую очередь:");
        FILE* input = fopen("input.txt","w");
        read_queue(input);
        fclose(input);
    }
    else if (strcmp(argv[1], "-time") == 0)
    {
        return sort_time_comparison();
    }
    else
    {
        printf("Неизвестный параметр: %s\n", argv[1]);
        puts("Доступные параметры:");
        puts("-file <имя_файла>");
        puts("-sort");
        return 1;
    }
    
    return err;
}