#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "file_operations.h"

int main()
{
	FileHandler fh = {0};
	char filename[256];
	int choice;

	while (1)
	{
		print_filename(&fh);

		print_main_menu();
		choice = get_user_choice();

		switch (choice)
		{
		// Выход
		case 0: // Выйти из программы
			close_file(&fh);
			return 0;
		// Управление файлом
		case 1: // Создать
			create_file(&fh);
			break;
		case 2: // Открыть (для чтения и записи)
			open_file(&fh, "r+");
			break;
		case 3: // Закрыть
			close_file(&fh);
			break;
		case 4: // Очистить
			clear_file(&fh);
			break;
		case 5: // Удалить
			close_file(&fh);
			delete_file(fh.filename);
			break;
		// Редактирование
		case 6: // Заполнить автоматически
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