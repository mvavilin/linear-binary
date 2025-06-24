#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "file_operations.h"

int fill_with_random_number(FileData *fd) {
    if (fd == NULL || fd->file_ptr == NULL) {
        fprintf(stderr, "Ошибка: файл не открыт!\n");
        return 1;
    }

    int count;
    printf("Введите количество чисел для заполнения в файл: ");
    
    if (scanf("%d", &count) != 1) {
        fprintf(stderr, "Ошибка ввода!\n");
        return 1;
    }
    if (count <= 0) {
        fprintf(stderr, "Ошибка ввода. Введите положительное число!\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        int random_num = (rand() % 201) - 100;
        fprintf(fd->file_ptr, "%d\n", random_num);
    }

    fflush(fd->file_ptr);
    
    printf("Успешное заполнение в файл %d случайных чисел (-100..100)\n", count);
    return 0;
}