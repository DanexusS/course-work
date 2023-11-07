#pragma once
#include "book.h"
#include "input_output.h"

struct Files
{
	Book* books;
	size_t size;
};

static void GetFilesData(Files* files)
{
	
}

static void DeleteFiles(Files* files)
{
	delete[] files->books;
	delete files;
}

void AddBook(Files*, Book*);
