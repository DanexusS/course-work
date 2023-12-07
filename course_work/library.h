#pragma once
#include <cmath>

#include "book.h"
#include "generics.h"

struct Library {
	Book** books;
	int size;
	int free_space;
	LibrarySettings* settings;
};

static void SetLibrary(Library* library, int size) {
	if (size != 0)
		library->free_space = pow(2, ceil(log2(abs(size))) + 1);
	else if (size == 0)
		library->free_space = 1;
	library->books = new Book*[library->free_space];
	library->size = 0;
}

static void DeleteLibrary(Library* library) {
	for (int i = 0; i < library->size; i++)
		DeleteBook(library->books[i]);
	delete[] library->books;
	
	DeleteLibrarySettings(library->settings);

	delete library;
}

void AddBook(Library* library, Book* book);
void WorkWithLibrary();