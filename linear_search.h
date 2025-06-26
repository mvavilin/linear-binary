#ifndef LINEAR_SEARCH_H
#define LINEAR_SEARCH_H

#include "file_operations.h"

typedef struct
{
    int occurrences;
    int first_pos;
    int last_pos;
    int iterations;
} SearchResult;

typedef struct
{
    double time_ms;
    int iterations;
} SearchStats;

void linear_search(FileData *fd);
bool linear_search_fd(FileData *fd, int value);

#endif