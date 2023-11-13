#pragma once
#include <cmath>

#include "book.h"

struct Library {
	Book** books;
	int size;
	int free_space;
};

static void SetLibrary(Library* library, int size) {
	library->free_space = pow(2, ceil(log2(size)) + 1);
	library->books = new Book*[library->free_space];
	library->size = 0;
}

static void DeleteLibrary(Library* library) {
	for (int i = 0; i < library->size; i++)
		DeleteBook(library->books[i]);

	delete[] library->books;
	delete library;
}

void AddBook(Library*, Book*);
void WorkWithLibrary();