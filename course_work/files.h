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
	//unsigned int files_size = 0;
	//FILE* files_data = fopen("data/files_data.txt", "r");
	//char buffer[1000];
	//char* book_location = buffer;

	//print("Gathering Files information from ./data folder.\n\n\n");

	//fscanf(files_data, "%d\n", &files_size);

	//files->size = files_size;

	//for (int i = 0; i < files_size; i++)
	//{
	//	fscanf(files_data, "%[^\n]s\n", book_location);
	//	//print("Opening ./data/%s and reading information", )

	//	fgets(buffer, 2, files_data);
	//}

	//fclose(files_data);
}

static void DeleteFiles(Files* files)
{
	delete[] files->books;
	delete files;
}

void AddBook(Files*, Book*);
