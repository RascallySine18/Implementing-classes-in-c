/*
Реализация класса объекта "Телевизор" - хранение и обработка данных о телевизоре.
Представляется телевизор с характеристиками: модель, диагональ, разрешение, технология экрана и цена
Используются динамические строки для текстовых полей.
Поддерживается чтение/запись в бинарном режиме.
Интерфейс:
- inputTV(): запрашивает данные у пользователя
- saveToFile(): сохраняет данные в бинарный файл
- loadAndPrintFromFile(): загружает данные из файла и выводит на экран
Тестирование:
ввод:
	Введите модель телевизора: LG
	Введите диагональ (дюймы): 32
	Введите ширину разрешения: 1920
	Введите высоту разрешения: 1080
	Введите технологию (OLED/QLED/LED): LED
	Введите цену: 49990,99
вывод:
	Данные сохранены в файл 'tv.dat'
	Модель: LG
	Диагональ: 32,0"
	Разрешение: 1920x1080
	Технология: LED
	Цена: 49990,99 руб.
Программа сохранит данные в tv.dat
Выполнил Базан Игорь 303ИС-22
*/

#include "tv.h"
#include <locale.h>
#define MAX	256

void inputTV(Television *tv) {
	char buffer[MAX];
	printf("Введите модель телевизора: ");
	scanf("%255s", buffer);
	tv->model = malloc(strlen(buffer) + 1);
	strcpy(tv->model, buffer);
	
	printf("Введите диагональ (дюймы): ");
	scanf("%f", &tv->diagonal);
	
	printf("Введите ширину разрешения: ");
	scanf("%d", &tv->resolution_w);
	
	printf("Введите высоту разрешения: ");
	scanf("%d", &tv->resolution_h);
	
	printf("Введите технологию (OLED/QLED/LED): ");
	scanf("%255s", buffer);
	tv->tech = malloc(strlen(buffer) + 1);
	strcpy(tv->tech, buffer);
	
	printf("Введите цену: ");
	scanf("%f", &tv->price);
}

void saveToFile(const Television *tv, const char *filename) {
	FILE *file = fopen(filename, "wb");
	size_t len = strlen(tv->model) + 1;
	fwrite(&len, sizeof(size_t), 1, file);
	fwrite(tv->model, sizeof(char), len, file);
	
	fwrite(&tv->diagonal, sizeof(float), 1, file);
	
	fwrite(&tv->resolution_w, sizeof(int), 1, file);
	
	fwrite(&tv->resolution_h, sizeof(int), 1, file);
	
	len = strlen(tv->tech) + 1;
	fwrite(&len, sizeof(size_t), 1, file);
	fwrite(tv->tech, sizeof(char), len, file);
	
	fwrite(&tv->price, sizeof(float), 1, file);
	
	fclose(file);
	printf("Данные сохранены в файл '%s'\n", filename);
}

void loadAndPrintFromFile(Television *tv, const char *filename) {
	FILE *file = fopen(filename, "rb");
	size_t len;
	fread(&len, sizeof(size_t), 1, file);
	free(tv->model);
	tv->model = malloc(len);
	fread(tv->model, sizeof(char), len, file);
	
	fread(&tv->diagonal, sizeof(float), 1, file);
	
	fread(&tv->resolution_w, sizeof(int), 1, file);
	
	fread(&tv->resolution_h, sizeof(int), 1, file);
	
	fread(&len, sizeof(size_t), 1, file);
	free(tv->tech);
	tv->tech = malloc(len);
	fread(tv->tech, sizeof(char), len, file);
	
	fread(&tv->price, sizeof(float), 1, file);
	
	fclose(file);
	printf("Модель: %s\n", tv->model);
	printf("Диагональ: %.1f\"\n", tv->diagonal);
	printf("Разрешение: %dx%d\n", tv->resolution_w, tv->resolution_h);
	printf("Технология: %s\n", tv->tech);
	printf("Цена: %.2f руб.\n", tv->price);
}

int main() {
	setlocale(LC_ALL, "");
	Television myTV = {0};
	inputTV(&myTV);
	saveToFile(&myTV, "tv.dat");
	loadAndPrintFromFile(&myTV, "tv.dat");
	free(myTV.model);
	free(myTV.tech);
	return 0;
}
