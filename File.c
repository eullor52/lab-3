#include "File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int is_valid_int(const char* str, int* value)
{
    if (str == NULL || *str == '\0')
    {
        return 0;
    }
    while (isspace((unsigned char)*str))
    {
        str++;
    }
    int sign = 1;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }
    if (!isdigit((unsigned char)*str))
    {
        return 0;
    }
    char* endptr;
    errno = 0;
    long num = strtol(str, &endptr, 10);
    if (errno == ERANGE)
    {
        return 0;
    }
    while (*endptr != '\0')
    {
        if (!isspace((unsigned char)*endptr))
        {
            return 0;
        }
        endptr++;
    }
    if (num > INT_MAX || num < INT_MIN)
    {
        return 0;
    }
    *value = (int)num * sign;
    return 1;
}

int read_queue_from_file(Queue* q, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "      :                         '%s'\n", filename);
        return 0;
    }
    clear_queue(q);
    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    int total_numbers = 0;
    int errors = 0;
    while (fgets(line, sizeof(line), file))
    {
        line_num++;
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0' || line[0] == '#')
        {
            continue;
        }
        char* token = strtok(line, " \t");
        while (token != NULL)
        {
            int value;
            if (is_valid_int(token, &value))
            {
                if (!enqueue(q, value))
                {
                    fprintf(stderr, "      :                           %d           (       %d)\n", value, line_num);
                    errors++;
                }
                else
                {
                    total_numbers++;
                }
            }
            else
            {
                fprintf(stderr, "                %d: '%s'                                    \n", line_num, token);
                errors++;
            }

            token = strtok(NULL, " \t");
        }
    }
    fclose(file);
    if (errors > 0)
    {
        fprintf(stderr, "           %d                        \n", errors);
    }
    if (total_numbers == 0)
    {
        fprintf(stderr, "              :                                  \n");
    }
    return (total_numbers > 0);
}

int write_queue_to_file(Queue* q, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "      :                         '%s'\n", filename);
        return 0;
    }
    Elem* current = q->front;
    int count = 0;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->data);
        current = current->next;
        count++;
        if (count % 10 == 0)
        {
            fprintf(file, "\n");
        }
    }
    if (count % 10 != 0)
    {
        fprintf(file, "\n");
    }
    fclose(file);
    return 1;
}

int read_queue_from_stdin(Queue* q)
{
    printf("                                             : ");
    char line[MAX_LINE_LENGTH];
    if (fgets(line, sizeof(line), stdin) == NULL)
    {
        printf("                       \n");
        return 0;
    }
    size_t len = strlen(line);
    if (len > 0 && line[len-1] == '\n') {
        line[len-1] = '\0';
    }
    if (len == 0 || (len == 1 && line[0] == '\n'))
    {
        printf("                     \n");
        return 0;
    }
    clear_queue(q);
    char* token = strtok(line, " \t");
    int count = 0;
    int errors = 0;
    while (token != NULL)
    {
        int value;
        if (is_valid_int(token, &value))
        {
            if (enqueue(q, value))
            {
                count++;
            }
            else
            {
                errors++;
            }
        }
        else
        {
            errors++;
        }

        token = strtok(NULL, " \t");
    }

    if (errors > 0)
    {
        printf("           %d                 \n", errors);
    }

    if (count == 0)
    {
        printf("                                 \n");
        return 0;
    }

    return 1;
}

int handle_file_argument(Queue* q, const char* filename)
{
    if (!read_queue_from_file(q, filename))
    {
        return 0;
    }
    printf("                         (%d          ):\n", queue_size(q));
    print_queue(q);
    Queue sorted;
    init_queue(&sorted);
    if (!copy_queue(&sorted, q))
    {
        fprintf(stderr, "                              \n");
        clear_queue(&sorted);
        return 0;
    }
    printf("\n                         ...\n");
    selection_sort_queue(&sorted);
    printf("                   :\n");
    print_queue(&sorted);
    char sorted_filename[MAX_FILENAME_LENGTH];
    snprintf(sorted_filename, sizeof(sorted_filename), "sorted_%s", filename);
    if (write_queue_to_file(&sorted, sorted_filename))
    {
        printf("                         : %s\n", sorted_filename);
    }
    clear_queue(&sorted);
    return 1;
}
