#pragma once
#include <cstdio>
#include <iostream>

#include "book.h"
#include "library.h"

static void scan(const char* format, char* input) {
	scanf(format, input);
	getchar();
}

static void scan_char(char* input) { scan("%c", input); }
static void scan_line(char* input) { scan("%[^\n]s\n", input); }

static void NextLiner(FILE* file)
{
	char garbage_buffer[3];
	fgets(garbage_buffer, 2, file);
}

static void GetBookData(Library* library, char* location) {
	char* data_string = new char[1000];
	strcpy(data_string, "data/");

	FILE* book_file = fopen(strcat(data_string, location), "r");

	if (book_file == 0) {
		printf("FILE data/%s IS NOT FOUND. CRITICAL ERROR.", location);
		return;
	}
		
	Book* book = new Book;
	char* input_string = new char[1000];

	for (int j = 0; j < BOOK_STRUCT_FIELD_AMOUNT; j++) {
		fscanf(book_file, "%[^\n]s\n", input_string);
		INPUT_FUNCTION_STACK[j](book, input_string);
		NextLiner(book_file);
	}
	AddBook(library, book);

	fclose(book_file);
	delete[] data_string;
	delete[] input_string;
}

static void GetLibraryData(Library* library) {
	unsigned int files_size = 0;
	FILE* files_data = fopen("data/files_data.txt", "r");
	char* book_location = new char[1000];

	printf("Gathering Files information from ./data folder.\n\n\n");

	fscanf(files_data, "%d\n", &files_size);
	SetLibrary(library, files_size);
	
	for (int i = 0; i < files_size; i++) {
		fscanf(files_data, "%[^\n]s\n", book_location);
		
#if defined _DEBUG
		printf("[DEBUG] Opening ./data/%s and reading information", book_location);
		printf("\n");
#endif

		GetBookData(library, book_location);
		NextLiner(files_data);
	}

	fclose(files_data);
	delete[] book_location;
}
