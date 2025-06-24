#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"

void clear_input_buffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

bool print_filename(FileData *fd)
{
	if (fd->file_ptr && fd->filename[0] != '\0')
		printf("\nТекущий файл: %s\n", fd->filename);

	return true;
}

bool input_filename(FileData *fd)
{
	printf("Введите имя файла: ");
	clear_input_buffer();

	if (fgets(fd->filename, sizeof(fd->filename), stdin) == NULL)
	{
		printf("Ошибка ввода: не удалось прочитать имя файла.\n");
		fd->filename[0] = '\0';
		return false;
	}

	fd->filename[strcspn(fd->filename, "\n")] = '\0';

	if (fd->filename[0] == '\0')
	{
		printf("Ошибка: имя файла не может быть пустым!\n");
		return false;
	}

	return true;
}

bool create_fd(FileData *fd)
{
	if (fd->file_ptr)
		close_fd(fd);

	input_filename(fd);

	if (fd->filename[0] == '\0')
	{
		printf("Ошибка: имя файла не указано.\n");
		return false;
	}

	fd->file_ptr = fopen(fd->filename, "wx");
	if (!fd->file_ptr)
	{
		printf("Ошибка: не удалось создать файл '%s'.\n", fd->filename);
		fd->filename[0] = '\0';
		return false;
	}

	printf("Файл '%s' создан.\n", fd->filename);
	close_fd(fd);
	return true;
}

bool open_fd(FileData *fd)
{
	if (fd->filename[0] == '\0')
		input_filename(fd);

	if (fd->file_ptr)
	{
		printf("Ошибка: открыт файл '%s'.\n", fd->filename);
		return false;
	}

	fd->file_ptr = fopen(fd->filename, "r+");
	if (!fd->file_ptr)
	{
		printf("Ошибка: не удалось открыть файл '%s'.\n", fd->filename);
		fd->filename[0] = '\0';
		return false;
	}

	printf("Файл '%s' открыт.\n", fd->filename);
	return true;
}

bool close_fd(FileData *fd)
{
	if (fd->file_ptr)
	{
		fclose(fd->file_ptr);
		fd->file_ptr = NULL;
		printf("Файл '%s' закрыт.\n", fd->filename);
		fd->filename[0] = '\0';
		return true;
	}
}

bool delete_fd(FileData *fd)
{
	if (fd->filename[0] == '\0')
		input_filename(fd);

	if (fd->filename[0] == '\0')
	{
		printf("Ошибка: имя файла не указано.\n");
		return false;
	}

	if (fd->file_ptr)
	{
		fclose(fd->file_ptr);
		fd->file_ptr = NULL;
	}

	if (remove(fd->filename) != 0)
	{
		printf("Ошибка: не удалось удалить файл '%s'.\n", fd->filename);
		fd->filename[0] = '\0';
		return false;
	}

	printf("Файл '%s' удален.\n", fd->filename);
	fd->filename[0] = '\0';
	return true;
}

bool clear_fd(FileData *fd)
{
	if (fd->file_ptr == NULL)
	{
		printf("Ошибка: файл не открыт.\n");
		return false;
	}

	fd->file_ptr = freopen(fd->filename, "w", fd->file_ptr);
	if (fd->file_ptr == NULL)
	{
		printf("Ошибка: не удалось очистить файл '%s'.\n", fd->filename);
		return false;
	}

	printf("Файл '%s' очищен.\n", fd->filename);
	return true;
}
