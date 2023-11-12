#pragma once
#include "book.h"

struct Library
{
	Book** books;
	size_t size;
};

static void SetLibrary(Library* library, int size)
{
	library->books = new Book*[size];
	library->size = 0;
}

static void DeleteLibrary(Library* library)
{
	for (int i = 0; i < library->size; i++)
		DeleteBook(library->books[i]);

	delete[] library->books;
	delete library;
}

void AddBook(Library*, Book*);
void RemoveBook(Library*, int);
void RemoveBooks(Library*, int, int);

void WorkWithLibrary();