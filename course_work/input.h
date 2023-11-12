#pragma once
#include <cstdio>
#include <iostream>

#include "book.h"
#include "library.h"

static void scan(char* input)
{
	scanf("%[^\n]s\n", input);
	getchar();
}

static void GetBookData(Library* library, char* location)
{
	char* temp = new char[1000];
	strcpy(temp, "data/");

	FILE* book_file = fopen(strcat(temp, location), "r");
	if (book_file == 0)
	{
#if defined _DEBUG
		printf("[DEBUG] FILE data/%s IS NOT FOUND. CRITICAL ERROR", location);
#endif
		return;
	}
		
	Book* book = new Book;
	char buffer[1000];
	char input_buffer[1000];
	char* input_string = input_buffer;

	for (int j = 0; j < BOOK_STRUCT_FIELD_AMOUNT; j++)
	{
		fscanf(book_file, "%[^\n]s\n", input_string);
		INPUT_FUNCTION_STACK[j](book, input_string);
		fgets(buffer, 2, book_file);
	}
	AddBook(library, book);

	fclose(book_file);
	delete[] temp;
}

static void GetLibraryData(Library* library)
{
	unsigned int files_size = 0;
	FILE* files_data = fopen("data/files_data.txt", "r");
	char buffer[1000];
	char* book_location = buffer;

	printf("Gathering Files information from ./data folder.\n\n\n");

	fscanf(files_data, "%d\n", &files_size);

	SetLibrary(library, files_size);
	
	for (int i = 0; i < files_size; i++)
	{
		fscanf(files_data, "%[^\n]s\n", book_location);
		
#if defined _DEBUG
		printf("[DEBUG] Opening ./data/%s and reading information", book_location);
		printf("\n");
#endif

		GetBookData(library, book_location);

		fgets(buffer, 2, files_data);
	}

	fclose(files_data);
}
