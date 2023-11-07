#include "files.h"

void AddBook(Files* files, Book* book)
{
	Book* newArray = new Book[files->size + 1];

	for (int i = 0; i < files->size; i++)
		newArray[i] = files->books[i];
	newArray[files->size] = *book;

	delete[] files->books;
	files->books = newArray;
	files->size++;
}
