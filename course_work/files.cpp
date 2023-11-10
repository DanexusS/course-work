#include "files.h"
#include "book.h"
#include "input.h"
#include "output.h"
#include "generics.h"






// TODO: IMPLEMENT BASE SETTINGS


const PREDIFINED_COMMANDS PREDIFINED_FILES_COMMANDS;
//const char* FILES_EXIT_CHAR = "`";



Book** BookSort(Files* files, int (*Compare)(Book*, Book*, int), int order)
{
	Book** sorted_books = files->books;


	for (int i = 0; i < files->size - 1; i++)
	{
		bool b = false;
		for (int j = 0; j < files->size - i - 1; j++)
		{
			Book* curBook = sorted_books[j];
			Book* nextBook = sorted_books[j + 1];
			if ((*Compare)(curBook, nextBook, order) > 0)
			{
				
				Book* temp = curBook;

				sorted_books[j] = nextBook;
				sorted_books[j + 1] = temp;

				b = true;
			}
		}
		if (!b)
			break;
	}





	return sorted_books;
}


Book** BookSort(Files* files, int (*Compare)(Book*, Book*, SortingData**, int), SortingData** sortingData, int size)
{
	Book** sorted_books = files->books;


	for (int i = 0; i < files->size - 1; i++)
	{
		bool b = false;
		for (int j = 0; j < files->size - i - 1; j++)
		{
			Book* curBook = sorted_books[j];
			Book* nextBook = sorted_books[j + 1];
			if ((*Compare)(curBook, nextBook, sortingData, size) > 0)
			{

				Book* temp = curBook;

				sorted_books[j] = nextBook;
				sorted_books[j + 1] = temp;

				b = true;
			}
		}
		if (!b)
			break;
	}





	return sorted_books;
}

//void BookSort(char* pcFirst, int size, void (*Swap)(void*, void*), int (*Compare)(void*, void*))
//{
//	for (int i = 0; i < size - 1; i++)
//	{
//		bool b = false;
//		for (int j = 0; j < size - i - 1; j++)
//		{
//			char* pCurrent = pcFirst + j;
//			char* pNext = pcFirst + j + 1;
//
//			//if ((*Compare)(pCurrent, pNext) > 0)
//			//{
//			//	(*Swap)(pCurrent, pNext);
//			//	b = true;
//			//}
//		}
//		if (!b)
//			return;
//	}
//
//
//
//	//int i;
//	//for (int i = 1; i < nNumber; i++)
//	//{
//	//	for (int j = nNumber - 1; j >= i; j--)
//	//	{
//	//		char* pCurrent = pcFirst + j * size;
//	//		char* pPrevious = pcFirst + (j - 1) * size;
//	//		if ((*Compare)(pPrevious, pCurrent) > 0)
//	//			(*Swap)(pPrevious, pCurrent);
//	//	}
//	//}
//
//}
//void BookSort()
//{
//
//}


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
			scan(input);
			//choose mode
			if (strcmp(input, "1") == 0)
			{
				DisplayFiles(files);
			}
			else if (strcmp(input, "2") == 0)
			{
				// chose mode
				 
				scan(input);
				if (strcmp(input, "1") == 0)
				{
					// chose field to sort
					
					scan(input);

					char new_buffer[1000];
					char* max = new_buffer;
					Book** sorted_books;

					scan(max);
					if (atoi(max) == 1)
						sorted_books = BookSort(files, COMPARISON_FUNCTION_STACK[atoi(input)], -1);
					else
						sorted_books = BookSort(files, COMPARISON_FUNCTION_STACK[atoi(input)], 1);
					DisplayBookList(sorted_books, files->size);
				}
				else if (strcmp(input, "2") == 0)
				{

					//print sort variants
					//enter sort amount
					//ids
					//int (*display_comparison_function_stack[])(Book*, Book*);


					printf("enter size\n");
					scan(input);
					int size = atoi(input);
					SortingData** sorting_functions = new SortingData*[atoi(input)];
					for (int i = 0; i < atoi(input); i++)
					{
						SortingData* sortingData = new SortingData;
						
						printf("enter type\n");
						scan(input);

						char new_buffer[1000];
						char* max = new_buffer;


						// ascend/descend order

						printf("enter order\n");
						scan(max);



						//BookSort(input, 10, , )

						SetSortingData(sortingData, atoi(input), atoi(max));

						sorting_functions[i] = sortingData;
					}

					Book** sorted_books = BookSort(files, CompareByMultiple, sorting_functions, size);
					DisplayBookList(sorted_books, files->size);
				}
			}

		}
		else if (strcmp(input, "2") == 0)
		{
			Book* book = new Book;

			//SetBook(book);

			if (SetBookData(book))
			{
				//msg adding book
				AddBook(files, book);
			}
			else
			{
				//error msg
				delete book;
			}
		}
		else if (strcmp(input, "3") == 0)
		{
			//display files
			//choose mode
			scan(input);
			if (strcmp(input, "1") == 0)
			{
				//enter book #
				scan(input);
				RemoveBook(files, atoi(input));
			}
			else if (strcmp(input, "2") == 0)
			{
				//enter min and max book id
				char new_buffer[1000];
				char* max = new_buffer;

				scan(input);
				scan(max);
				RemoveBooks(files, atoi(input), atoi(max));
			}
		}
		else if (strcmp(input, "4") == 0)
		{
			ExportFilesData(files);
		}
		else if (strcmp(input, "5") == 0)
		{
			//display info
			scan(input);
			get_book_data(files, input);
		}
		else if (strcmp(input, PREDIFINED_FILES_COMMANDS.HELP_CHAR) == 0)
		{
			//print help func
		}
		else if (strcmp(input, PREDIFINED_FILES_COMMANDS.EXIT_CHAR) == 0)
		{
			DeleteFiles(files);
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
		if (files->books[i]->_id == _id)
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

	Book** newArray = new Book*[files->size - 1];

	DeleteBook(files->books[i]);

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

		files->books[old_array_id]->_id = j;

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

void RemoveBooks(Files* files, int min, int max)
{
	for (int i = min; i < max + 1; i++)
	{
		RemoveBook(files, i);
	}
}

//Book FindBook(Files* files)
//{
//
//}

void AddBook(Files* files, Book* book)
{
	book->_id = files->size;


	Book** newArray = new Book*[files->size + 1];

	for (int i = 0; i < files->size; i++)
		newArray[i] = files->books[i];
	newArray[files->size] = book;

	delete[] files->books;
	files->books = newArray;
	files->size++;
}
