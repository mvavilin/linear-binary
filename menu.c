#include <stdio.h>
#include <string.h>
#include "menu.h"

void print_main_menu(void)
{
  printf("Выход\n");
  printf("0. Выйти из программы\n");
  printf("Управление файлом\n");
  printf("1. Создать\n");
  printf("2. Открыть (для чтения и записи)\n");
  printf("3. Закрыть\n");
  printf("4. Очистить\n");
  printf("5. Удалить\n");
  printf("Редактирование\n");
  printf("6. Заполнить автоматически\n");
  printf("7. Отсортировать\n");
  printf("Поиск\n");
  printf("8. Линейный\n");
  printf("9. Бинарный\n");
  printf("Выберите пункт: ");
}

int get_user_choice(void)
{
  int choice;
  while (scanf("%d", &choice) != 1)
  {
    printf("Ошибка: введите число!\n");
    while (getchar() != '\n')
      ;
  }
  return choice;
}