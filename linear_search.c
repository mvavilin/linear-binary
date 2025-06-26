#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "file_operations.h"
#include "linear_search.h"
#include "binary_search.h"

void linear_search(FileData *fd)
{
    if (fd->file_ptr)
    {
        int value;
        printf("Введите значение для поиска: ");
        if (scanf("%d", &value) == 1)
        {
            linear_search_fd(fd, value);
        }
        else
        {
            printf("Ошибка ввода!\n");
        }
    }
    else
    {
        printf("Сначала откройте файл!\n");
    }
}

static SearchResult linear_search_analyze(const int *array, int count, int value)
{
    SearchResult result = {0};
    result.first_pos = -1;
    result.last_pos = -1;
    result.iterations = 0;
    result.iterations = count;

    for (int i = 0; i < count; i++)
    {
        result.iterations++;
        if (array[i] == value)
        {
            result.occurrences++;
            if (result.first_pos == -1)
            {
                result.first_pos = i;
            }
            result.last_pos = i;
        }
    }

    return result;
}

static void print_search_stats(const SearchStats *stats)
{
    printf("\nСтатистика поиска:\n");
    printf("--------------------------------\n");
    printf("Общее время выполнения: %.6f мс\n", stats->time_ms);
    printf("Всего итераций (сравнений): %d\n", stats->iterations);
    printf("--------------------------------\n");
}

static void print_search_results(int value, const SearchResult *result)
{
    printf("\nРезультаты поиска:\n");
    printf("--------------------------------\n");
    if (result->occurrences > 0)
    {
        printf("Значение %d найдено %d раз(а)\n", value, result->occurrences);
        printf("Первое вхождение: позиция %d\n", result->first_pos + 1);
        printf("Последнее вхождение: позиция %d\n", result->last_pos + 1);
    }
    else
    {
        printf("Значение %d не найдено в файле.\n", value);
    }
    printf("--------------------------------\n");
}

bool linear_search_fd(FileData *fd, int value)
{
    if (fd->file_ptr == NULL)
    {
        printf("Ошибка: файл не открыт.\n");
        return false;
    }

    rewind(fd->file_ptr);
    int *numbers = NULL;
    int count = 0;

    if (!read_numbers_from_file(fd->file_ptr, &numbers, &count))
    {
        return false;
    }

    if (count == 0)
    {
        printf("Файл пуст.\n");
        free(numbers);
        return false;
    }

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    SearchResult result = linear_search_analyze(numbers, count, value);

    QueryPerformanceCounter(&end);
    SearchStats stats = {
        .time_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart,
        .iterations = result.iterations};

    print_search_stats(&stats);
    print_search_results(value, &result);

    free(numbers);
    return result.occurrences > 0;
}