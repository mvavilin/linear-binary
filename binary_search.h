#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stdbool.h>

void binary_search(FileData *fd);
bool binary_search_fd(FileData *fd, int value);
bool read_numbers_from_file(FILE *file_ptr, int **numbers, int *count);

#endif