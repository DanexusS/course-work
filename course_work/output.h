#pragma once
#include <cstdio>
#include "files.h"
#include "book.h"

static void DisplayBook(Book* book)
{
	printf("\n\n\n");
	printf("\t\tBOOK INFORMATION\n\n");
#if defined _DEBUG
	printf("[DEBUG] _id: %d", book->_id);
	printf("\n");
#endif
	printf(
		"Author: %s\nTitle: %s\nPublish year: %d\nPrice: %f\nBook category: %s\n\n\n",
		book->author, book->title, book->year, book->price, categoryTitles[(int)book->category]
	);
}

static void DisplayFiles(Files* files)
{
	for (int i = 0; i < files->size; i++)
	{
		DisplayBook(files->books[i]);
	}
}

static void ExportBookData(Book* book)
{
	char* temp = new char[1000];
	char* temp2 = new char[1000];
	strcpy(temp, "data/");
	strcpy(temp2, book->title);
	FILE* book_file = fopen(strcat(temp, strcat(temp2, ".txt")), "w");
#if defined _DEBUG
	printf("[DEBUG] Opening ./data/%s.txt and writing information there", book->title);
	printf("\n");
#endif
	fprintf(book_file, "%s\n%s\n%d\n%lf\n%d", book->author, book->title, book->year, book->price, book->category);
	fclose(book_file);
}

static void ExportFilesData(Files* files)
{
	FILE* files_data = fopen("data/files_data.txt", "w");

	fprintf(files_data, "%d\n", files->size);

	for (int i = 0; i < files->size; i++)
	{
		ExportBookData(files->books[i]);
		
		

		fprintf(files_data, files->books[i]->title);
		fprintf(files_data, ".txt\n");

		
	}
	//refresh files_data.txt

	fclose(files_data);
}

//static void DeleteBook(Files* files, int _id)
//{
//
//}

//
//static void print(const char* message)
//{
//	printf(message);
//}
