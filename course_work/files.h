#pragma once
#include "book.h"


struct Files
{
	Book* books;
	size_t size;
};

static void SetFiles(Files* files, int size)
{
	files->books = new Book[size];
	files->size = 0;
}

static void DeleteFiles(Files* files)
{
	delete[] files->books;
	delete files;
}

void AddBook(Files*, Book*);
void RemoveBook(Files*, int);

void WorkWithFiles();