#ifndef FILE_H
#define FILE_H

#include "Queue.h"

double time_for_sort(Queue* q, int mode);
int file_work(const char* file_name);
int sort_time_comparison();
void read_queue(FILE* file);


#endif