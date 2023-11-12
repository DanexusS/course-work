#pragma once
#include <cstdio>

#include "book.h"
#include "library.h"

static void DisplayBook(Book* book) {
	printf("\n\n\n");
	printf("\t\tBOOK INFORMATION\n\n");
	printf(
		"Author: %s\nTitle: %s\nPublish year: %d\nPrice: %f\nBook category: %s\n\n\n",
		book->author, book->title, book->year, book->price, CATEGORY_TITLES[(int)book->category]
	);
}

static void DisplayBookList(Book** books, int size) {
	for (int i = 0; i < size; i++)
		DisplayBook(books[i]);
}

static void DisplayLibrary(Library* library) { DisplayBookList(library->books, library->size); }

static void ExportBookData(Book* book) {
	char* data_string = new char[6];
	char* file_name = new char[1000];

	strcpy(data_string, "data/");
	strcpy(file_name, book->title);

	FILE* book_file = fopen(strcat(data_string, strcat(file_name, ".txt")), "w");

#if defined _DEBUG
	printf("[DEBUG] Opening ./data/%s.txt and writing information there", book->title);
	printf("\n");
#endif

	fprintf(book_file, "%s\n%s\n%d\n%lf\n%d", book->author, book->title, book->year, book->price, book->category);

	fclose(book_file);
}

static void ExportLibraryData(Library* library) {
	FILE* library_data = fopen("data/files_data.txt", "w");

	fprintf(library_data, "%d\n", library->size);

	for (int i = 0; i < library->size; i++) {
		ExportBookData(library->books[i]);

		fprintf(library_data, library->books[i]->title);
		fprintf(library_data, ".txt\n");
	}

	fclose(library_data);
}
