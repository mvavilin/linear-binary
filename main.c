#include <stdio.h>
#include <string.h>
#include "menu.h"

int main()
{
	char filename[256] = "";
	int choice;

	while (1)
	{
		print_main_menu();
		choice = get_user_choice();

		switch (choice)
		{
		// Выход
		case 0: // Выйти из программы
			return 0;
		// Управление файлом
		case 1: // Создать
			break;
		case 2: // Открыть
			break;
		case 3: // Удалить
			break;
		case 4: // Очистить
			break;
		// Редактирование
		case 5: // Заполнить автоматически
			break;
		case 6: // Заполнить вручную
			break;
		case 7: // Отсортировать
			break;
		// Поиск
		case 8: // Линейный
			break;
		case 9: // Бинарный
			break;
		default:
			printf("Неверный пункт!\n");
		}
	}
	return 0;
}