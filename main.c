#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "Sort.h"
#include <string.h>
#include "File.h"

int main(int argc, char** argv)
{
    // Проверка количества аргументов
    if (argc < 3) 
    {
        printf("Использование:\n");
        printf("  %s -file <имя_файла>\n", argv[0]);
        return 1;
    }
    
    // Обработка аргументов
    if (strcmp(argv[1], "-file") == 0)
    {
        return file_work(argv[2]);  // Передаем имя файла
    }
    else if (strcmp(argv[1], "-time") == 0)
    {
        return sort_time_comparison();
    }
    else
    {
        printf("Неизвестный параметр: %s\n", argv[1]);
        printf("Доступные параметры: -file <имя_файла>\n");
        return 1;
    }
    
    return 0;
}