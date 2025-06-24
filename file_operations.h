#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdbool.h>

typedef struct
{
  FILE *file_ptr;
  char filename[256];
  bool is_open;
} FileHandler;

void print_filename(FileHandler *fh);
void input_filename(char *filename, size_t max_length);

bool create_file(FileHandler *fh);
bool open_file(FileHandler *fh, const char *mode);
bool delete_file(const char *filename);
bool clear_file(FileHandler *fh);
void close_file(FileHandler *fh);

#endif