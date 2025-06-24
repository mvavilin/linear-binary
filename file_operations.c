#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"

void print_filename(FileHandler *fh)
{
  if (fh == NULL)
  {
    return;
  }

  if (fh->is_open && fh->filename[0] != '\0')
  {
    printf("Текущий файл: %s\n", fh->filename);
  }
}

void input_filename(char *filename, size_t max_length)
{
  printf("Введите имя файла: ");

  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  if (fgets(filename, max_length, stdin) == NULL)
  {
    printf("Ошибка: имя файла не указано.\n");
  }

  filename[strcspn(filename, "\n")] = '\0';

  if (filename[0] == '\0')
  {
    printf("Ошибка: имя файла не может быть пустым!\n");
  }
}

bool create_file(FileHandler *fh)
{
  if (fh->is_open)
  {
    fclose(fh->file_ptr);
    fh->is_open = false;
    printf("Закрыт предыдущий файл '%s'.\n", fh->filename);
  }

  input_filename(fh->filename, sizeof(fh->filename));

  if (fh->filename[0] == '\0')
  {
    printf("Ошибка: имя файла не указано.\n");
    return false;
  }

  FILE *file = fopen(fh->filename, "w");
  if (!file)
  {
    printf("Ошибка: не удалось создать файл '%s'.\n", fh->filename);
    return false;
  }

  fclose(file);
  printf("Файл '%s' создан.\n", fh->filename);
  return true;
}

bool open_file(FileHandler *fh, const char *mode)
{
  if (fh->filename[0] == '\0')
  {
    input_filename(fh->filename, sizeof(fh->filename));
  }

  if (fh->is_open)
  {
    printf("Ошибка: файл уже открыт ('%s').\n", fh->filename);
    return false;
  }

  FILE *file = fopen(fh->filename, mode);
  if (!file)
  {
    printf("Ошибка: не удалось открыть файл '%s'.\n", fh->filename);
    return false;
  }

  fh->file_ptr = file;
  fh->is_open = true;
  printf("Файл '%s' открыт.\n", fh->filename);
  return true;
}

bool delete_file(const char *filename)
{
  if (!filename || filename[0] == '\0')
  {
    printf("Ошибка: имя файла не указано.\n");
    return false;
  }

  if (remove(filename) != 0)
  {
    printf("Ошибка: не удалось удалить файл '%s'.\n", filename);
    return false;
  }

  printf("Файл '%s' удалён.\n", filename);
  return true;
}

bool clear_file(FileHandler *fh)
{
  if (!fh->is_open)
  {
    printf("Ошибка: файл не открыт.\n");
    return false;
  }

  FILE *file = freopen(fh->filename, "w", fh->file_ptr);
  if (!file)
  {
    printf("Ошибка: не удалось очистить файл.\n");
    return false;
  }

  fclose(file);
  printf("Файл '%s' очищен.\n", fh->filename);
  return true;
}

void close_file(FileHandler *fh)
{
  if (fh->is_open)
  {
    fclose(fh->file_ptr);
    fh->is_open = false;
    printf("Файл '%s' закрыт.\n", fh->filename);
  }
}