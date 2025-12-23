#ifndef FILE_H
#define FILE_H

#include "Queue.h"

double time_for_sort(Queue* q, int mode);
int file_work(const char* file_name);
int sort_time_comparison();
int read_numbers_and_save(const char* filename);

#endif