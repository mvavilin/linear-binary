#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "file_operations.h"
#include "binary_search.h"
#include "edit.h" 

int main()
{
	FileData fd = {0};
	int choice;

	while (1)
	{
		print_filename(&fd);

		print_main_menu();
		choice = get_user_choice();

		switch (choice)
		{

		// Управление файлом
		case 1: // Создать
			create_fd(&fd);
			break;
		case 2: // Открыть (для чтения и записи)
			open_fd(&fd);
			break;
		case 3: // Закрыть
			close_fd(&fd);
			break;
		case 4: // Очистить
			clear_fd(&fd);
			break;
		case 5: // Удалить
			delete_fd(&fd);
			break;

		// Редактирование
		case 6: // Заполнить автоматически
			fill_with_random_number(&fd);
			break;
		case 7: // Отсортировать
			break;

		// Поиск
		case 8: // Линейный
			break;
		case 9: // Бинарный
			if (fd.file_ptr)
			{
				printf("Введите значение для поиска: ");
				int value;
				if (scanf("%d", &value) == 1)
				{
					binary_search_fd(&fd, value);
				}
				else
				{
					printf("Ошибка: введите корректное число.\n");
					clear_input_buffer();
				}
			}
			else
			{
				printf("Ошибка: файл не открыт.\n");
			}
			break;

		// Выход
		case 0: // Выйти из программы
			close_fd(&fd);
			return 0;
		default:
			printf("Неверный пункт!\n");
		}
	}
	return 0;
}