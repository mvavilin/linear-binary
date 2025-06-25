#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdbool.h>

typedef struct
{
	FILE *file_ptr;
	char filename[256];
} FileData;

void clear_input_buffer();
bool print_filename(FileData *fd);
bool input_filename(FileData *fd);

bool create_fd(FileData *fd);
bool open_fd(FileData *fd);
bool close_fd(FileData *fd);
bool delete_fd(FileData *fd);
bool clear_fd(FileData *fd);

#endif