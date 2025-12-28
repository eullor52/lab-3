#ifndef FILE_H
#define FILE_H

#include "Queue.h"

void clean_input_buffer();
int file_work(const char* file_name);
int sort_time_comparison();
int read_numbers_and_save(const char* filename);
int fprint_queue(Queue* q, FILE* file);
int print_queue(Queue* q);

#endif