#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "file_operations.h"
#include "binary_search.h"

int find_first_occurrence(const int *array, int count, int value, int *iterations)
{
	int left = 0;
	int right = count - 1;
	int result = -1;
	*iterations = 0;

	while (left <= right)
	{
		(*iterations)++;
		int mid = left + (right - left) / 2;

		if (array[mid] >= value)
		{
			right = mid - 1;
			if (array[mid] == value)
			{
				result = mid;
			}
		}
		else
		{
			left = mid + 1;
		}
	}

	return result;
}

int find_last_occurrence(const int *array, int count, int value, int *iterations)
{
	int left = 0;
	int right = count - 1;
	int result = -1;
	*iterations = 0;

	while (left <= right)
	{
		(*iterations)++;
		int mid = left + (right - left) / 2;

		if (array[mid] <= value)
		{
			left = mid + 1;
			if (array[mid] == value)
			{
				result = mid;
			}
		}
		else
		{
			right = mid - 1;
		}
	}

	return result;
}

bool read_numbers_from_file(FILE *file_ptr, int **numbers, int *count)
{
	*count = 0;
	int capacity = 100; // Вместимость массива
	*numbers = (int *)malloc(capacity * sizeof(int));
	if (!*numbers)
	{
		printf("Ошибка выделения памяти.\n");
		return false;
	}

	int num; // Текущее число из файла
	while (fscanf(file_ptr, "%d", &num) == 1)
	{
		if (*count >= capacity)
		{
			capacity *= 2;
			int *temp = (int *)realloc(*numbers, capacity * sizeof(int));
			if (!temp)
			{
				printf("Ошибка перевыделения памяти.\n");
				free(*numbers);
				return false;
			}
			*numbers = temp;
		}
		(*numbers)[(*count)++] = num; // Запись num в массив и увеличение счетчика
	}

	return true;
}

bool is_sorted(const int *numbers, int count)
{
	for (int i = 1; i < count; i++)
	{
		if (numbers[i] < numbers[i - 1])
		{
			return false;
		}
	}
	return true;
}

void print_search_stats(double time_ms, int iterations_start, int iterations_end)
{
	printf("\nСтатистика поиска:\n");
	printf("--------------------------------\n");
	printf("Общее время выполнения: %.6f мс\n", time_ms);
	printf("Итераций поиска первого вхождения: %d\n", iterations_start);
	printf("Итераций поиска последнего вхождения: %d\n", iterations_end);
	printf("Всего итераций: %d\n", iterations_start + iterations_end);
	printf("--------------------------------\n");
}

void print_search_results(int value, int first_occurrence, int last_occurrence)
{
	printf("\nРезультаты поиска:\n");
	printf("--------------------------------\n");
	if (first_occurrence != -1)
	{
		printf("Значение %d найдено %d раз(а)\n", value, last_occurrence - first_occurrence + 1);
		printf("Первое вхождение: позиция %d\n", first_occurrence + 1);
		printf("Последнее вхождение: позиция %d\n", last_occurrence + 1);
	}
	else
	{
		printf("Значение %d не найдено в файле.\n", value);
	}
	printf("--------------------------------\n");
}

bool binary_search_fd(FileData *fd, int value)
{
	if (fd->file_ptr == NULL)
	{
		printf("Ошибка: файл не открыт.\n");
		return false;
	}


	rewind(fd->file_ptr);

	int *numbers = NULL; // Массив чисел из файла
	int count = 0;			 // Количество чисел в массиве

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

	if (!is_sorted(numbers, count))
	{
		printf("Ошибка: данные в файле не отсортированы по возрастанию.\n");
		free(numbers);
		return false;
	}

	// clock_t start_time = clock();
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	int iterations_from_start = 0;
	int iterations_from_end = 0;

	int first_occurrence = find_first_occurrence(numbers, count, value, &iterations_from_start);
	int last_occurrence = find_last_occurrence(numbers, count, value, &iterations_from_end);
	// clock_t end_time = clock();
	// double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;

	QueryPerformanceCounter(&end);
	double time_s = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

	// print_search_stats(time_spent, iterations_from_start, iterations_from_end);
	print_search_stats(time_s, iterations_from_start, iterations_from_end);
	print_search_results(value, first_occurrence, last_occurrence);

	free(numbers);
	return first_occurrence != -1;
}