/*
Реализация класса объекта "Телефон" - хранение и обработка данных о телефоне.
Представляется телефон с характеристиками: модель, встроенная память, ОЗУ, год выпуска, цвет и цена.
Используются динамические строки для текстовых полей.
Поддерживается чтение/запись в бинарном режиме.
Интерфейс:
- inputPhone(): запрашивает данные у пользователя
- saveToFile(): сохраняет данные в бинарный файл
- loadAndPrintFromFile(): загружает данные из файла и выводит на экран
Тестирование:
ввод:
Введите модель телефона: Samsung
Введите встроенную память (ГБ): 512
Введите оперативную память (ГБ): 16
Введите год выпуска: 2025
Введите цвет телефона: black
Введите цену: 123456,99
вывод:
Данные сохранены в файл 'phone.dat':
Модель: Samsung
Встроенная память (ГБ): 512
Оперативная память (ГБ): 16
Год выпуска: 2025
Цвет: black
Цена: 123456,99
Программа сохранит данные в phone.dat
Выполнил Базан Игорь 303ИС-22
*/

#include "phone.h"
#include <locale.h>
#define MAX	256

void inputPhone(Phone *phone) {
	char buffer[MAX];
	printf("Введите модель телефона: ");
	scanf("%255s", buffer);
	phone->model = malloc(strlen(buffer) + 1);
	strcpy(phone->model, buffer);
	
	printf("Введите встроенную память (ГБ): ");
	scanf("%d", &phone->internal_memory);
	
	printf("Введите оперативную память (ГБ): ");
	scanf("%d", &phone->ram);
	
	printf("Введите год выпуска: ");
	scanf("%d", &phone->year);
	
	printf("Введите цвет телефона: ");
	scanf("%255s", buffer);
	phone->color = malloc(strlen(buffer) + 1);
	strcpy(phone->color, buffer);
	
	printf("Введите цену: ");
	scanf("%f", &phone->price);
}

void saveToFile(const Phone *phone, const char *filename) {
	FILE *file = fopen(filename, "wb");
	size_t len_model = strlen(phone->model) + 1;
	fwrite(&len_model, sizeof(size_t), 1, file);
	fwrite(phone->model, sizeof(char), len_model, file);
	
	fwrite(&phone->internal_memory, sizeof(int), 1, file);
	
	fwrite(&phone->ram, sizeof(int), 1, file);
	
	fwrite(&phone->year, sizeof(int), 1, file);
	
	size_t len_color = strlen(phone->color) + 1;
	fwrite(&len_color, sizeof(size_t), 1, file);
	fwrite(phone->color, sizeof(char), len_color, file);
	
	fwrite(&phone->price, sizeof(float), 1, file);
	
	fclose(file);
	printf("Данные сохранены в файл '%s':\n", filename);
}

void loadAndPrintFromFile(Phone *phone, const char *filename) {
	FILE *file = fopen(filename, "rb");
	size_t len_model;
	fread(&len_model, sizeof(size_t), 1, file);
	free(phone->model);
	phone->model = malloc(len_model);
	fread(phone->model, sizeof(char), len_model, file);
	
	fread(&phone->internal_memory, sizeof(int), 1, file);
	
	fread(&phone->ram, sizeof(int), 1, file);
	
	fread(&phone->year, sizeof(int), 1, file);
	
	size_t len_color;
	fread(&len_color, sizeof(size_t), 1, file);
	free(phone->color);
	phone->color = malloc(len_color);
	fread(phone->color, sizeof(char), len_color, file);
	
	fread(&phone->price, sizeof(float), 1, file);
	
	fclose(file);
	printf("Модель: %s\n", phone->model);
	printf("Встроенная память (ГБ): %d\n", phone->internal_memory);
	printf("Оперативная память (ГБ): %d\n", phone->ram);
	printf("Год выпуска: %d\n", phone->year);
	printf("Цвет: %s\n", phone->color);
	printf("Цена: %.2f\n", phone->price);
}

int main() {
	setlocale(LC_ALL, "");
	Phone myPhone = {0};
	inputPhone(&myPhone);
	saveToFile(&myPhone, "phone.dat");
	loadAndPrintFromFile(&myPhone, "phone.dat");
	free(myPhone.model);
	free(myPhone.color);
	return 0;
}
