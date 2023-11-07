#pragma once
#include <cstdio>
#include <iostream>
#include "files.h"
#include "book.h"

static void scan(char* input)
{
	scanf("%[^\n]s\n", input);
	getchar();
}

static void get_files_data(Files* files)
{
	unsigned int files_size = 0;
	FILE* files_data = fopen("data/files_data.txt", "r");
	char buffer[1000];
	char* book_location = buffer;

	printf("Gathering Files information from ./data folder.\n\n\n");

	fscanf(files_data, "%d\n", &files_size);

	//files->size = files_size;
	SetFiles(files, files_size);

	char input_buffer[1000];
	char* input_string = input_buffer;

	for (int i = 0; i < files_size; i++)
	{
		char* temp = new char[1000];
		strcpy(temp, "data/");

		fscanf(files_data, "%[^\n]s\n", book_location);
		
#if defined _DEBUG
		printf("[DEBUG] Opening ./data/%s and reading information", book_location);
		printf("\n");
#endif

		// Подсказка2: удобно в качестве первого данного в файле хранить количество
		// книг в картотеке
		//Если файл существует и его удалось открыть
		//if()
		//{
		//Чтение данных из файла
		//а) считали количество элементов
		//б) создали массив требуемой размерности
		//в) считали данные из файла в массив
		//}

		FILE* book_file = fopen(strcat(temp, book_location), "r");

		Book* book = new Book;
		SetBook(book);

		for (int j = 0; j < BOOK_STRUCT_FIELD_AMOUNT; j++)
		{


			fscanf(book_file, "%[^\n]s\n", input_string);

			INPUT_FUNCTION_STACK[j](book, input_string);

			fgets(buffer, 2, book_file);
		}

		//files->books[i] = book;

		AddBook(files, book);


		//
		//FILE* book = fopen(DATA_LOCATION + book_location, "r");
		//printf(strcat(book_location, "data/"));

		fclose(book_file);
		fgets(buffer, 2, files_data);
	}

	fclose(files_data);
}
