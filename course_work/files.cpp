#include "files.h"
#include "book.h"
#include "input.h"
#include "output.h"
#include "generics.h"

const PREDIFINED_COMMANDS PREDIFINED_FILES_COMMANDS;
//const char* FILES_EXIT_CHAR = "`";

void WorkWithFiles()
{
	//print init
	//print help func
	Files* files = new Files;
	get_files_data(files);
	//msg done -> help how to
	char buffer[1000];
	char* input = buffer;
	
	while (input != PREDIFINED_FILES_COMMANDS.EXIT_CHAR)
	{
		scan(input);
		if (strcmp(input, "1") == 0)
		{
			DisplayFiles(files);
		}
		else if (strcmp(input, "2") == 0)
		{
			Book* book = new Book;

			SetBook(book);

			if (SetBookData(book))
			{
				//msg adding book
				AddBook(files, book);
			}
			else
			{
				//error msg
			}
		}
		else if (strcmp(input, "3") == 0)
		{
			//display files
			//enter book #
			scan(input);
			RemoveBook(files, atoi(input));
		}
		else if (strcmp(input, "4") == 0)
		{
			ExportFilesData(files);
		}
		else if (input == PREDIFINED_FILES_COMMANDS.HELP_CHAR)
		{
			//print help func
		}
		else if (input == PREDIFINED_FILES_COMMANDS.EXIT_CHAR)
		{
			return;
		}

	}

}

void RemoveBook(Files* files, int _id)
{
	_id--;
	//_id check
	int i = 0;
	bool found = false;
	for (; i < files->size; i++)
	{
		if (files->books[i]._id == _id)
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		//print error
		return;
	}

	Book* newArray = new Book[files->size - 1];

	//int j = 0;
	//while (j < files->size)
	//{
	//	if (j == i)
	//		continue;
	//	newArray[j] = files->books[j];
	//	j++;
	//}
	int old_array_id = 0;
	for (int j = 0; j < files->size - 1; j++)
	{
		/*if (j == i)
			continue;*/
		if (i == old_array_id)
			old_array_id++;

		files->books[old_array_id]._id = j;

		newArray[j] = files->books[old_array_id];




		//DisplayBook(&newArray[j]);
		old_array_id++;
		if (old_array_id == files->size)
			break;
	}

	

	delete[] files->books;
	files->books = newArray;
	files->size--;
}

//Book FindBook(Files* files)
//{
//
//}

void AddBook(Files* files, Book* book)
{
	book->_id = files->size;


	Book* newArray = new Book[files->size + 1];

	for (int i = 0; i < files->size; i++)
		newArray[i] = files->books[i];
	newArray[files->size] = *book;

	delete[] files->books;
	files->books = newArray;
	files->size++;
}
