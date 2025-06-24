#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "file_operations.h"
#include "binary_search.h"

void fill_with_random_number(FileData *fd) {
    if (fd == NULL || fd->file_ptr == NULL) {
        fprintf(stderr, "Ошибка: файл не открыт!\n");
        return;
    }

    int count;
    printf("Введите количество чисел для заполнения в файл: ");
    
    if (scanf("%d", &count) != 1) {
        fprintf(stderr, "Ошибка ввода!\n");
        return;
    }
    if (count <= 0) {
        fprintf(stderr, "Ошибка ввода. Введите положительное число!\n");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        int random_num = (rand() % 201) - 100;
        fprintf(fd->file_ptr, "%d\n", random_num);
    }

    fflush(fd->file_ptr);
    
    printf("Успешное заполнение в файл %d случайных чисел (-100..100)\n", count);
    return;
}

void bubble_sort(FileData *fd) {
    if (fd == NULL || fd->file_ptr == NULL) {
        fprintf(stderr, "Ошибка: файл не открыт!\n");
        return;
    }

    rewind(fd->file_ptr);

    int *numbers = NULL;
    int count = 0;

    if (!read_numbers_from_file(fd->file_ptr, &numbers, &count)) {
        return;
    }

    if (count == 0) {
        printf("Файл не содержит чисел для сортировки!\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    rewind(fd->file_ptr); 
    
    for (int i = 0; i < count; i++) {
        fprintf(fd->file_ptr, "%d\n", numbers[i]);
    }

    free(numbers);
    fflush(fd->file_ptr);
    printf("Отсортировано %d чисел!\n", count);
}