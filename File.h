#ifndef FILE_H
#define FILE_H

#include "Sort.h"
#include "Queue.h"

#define MAX_LINE_LENGTH 4096
#define MAX_FILENAME_LENGTH 256

int is_valid_int(const char* str, int* value);

int read_queue_from_file(Queue* q, const char* filename);

int write_queue_to_file(Queue* q, const char* filename);

int read_queue_from_stdin(Queue* q);

int handle_file_argument(Queue* q, const char* filename);

#endif
