#include "book.h"
#include "input.h"
#include "output.h"
#include "library.h"
#include "generics.h"

// TODO: IMPLEMENT BASE SETTINGS

Book** SortBooks(Library* library, int (*Compare)(Book*, Book*, int), int order)
{
	Book** sorted_books = library->books;

	for (int i = 0; i < library->size - 1; i++)
	{
		bool b = false;
		for (int j = 0; j < library->size - i - 1; j++)
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

void WorkWithLibrary()
{
	//print init
	//print help func
	char* input = new char[1000];
	char* second_input = new char[1000];

	Library* library = new Library;

	GetLibraryData(library);
	//msg done -> help how to
	
	while (input != EXIT_CHAR)
	{
		scan(input);
		if (strcmp(input, "1") == 0)
		{
			//choose mode
			scan(input);
			
			if (strcmp(input, "1") == 0) 
				DisplayLibrary(library);
			else if (strcmp(input, "2") == 0)
			{
				// choose field to sort
				scan(input);
				scan(second_input);

				Book** sorted_books = SortBooks(
					library,
					COMPARISON_FUNCTION_STACK[atoi(input)],
					((atoi(second_input) == 1) ? -1 : 1)
				);

				DisplayBookList(sorted_books, library->size);
			}
		}
		else if (strcmp(input, "2") == 0)
		{
			Book* book = new Book;

			if (SetBookData(book))
			{
				//msg adding book
				AddBook(library, book);
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
				RemoveBook(library, atoi(input));
			}
			else if (strcmp(input, "2") == 0)
			{
				//enter min and max book id
				char new_buffer[1000];
				char* max = new_buffer;

				scan(input);
				scan(max);
				RemoveBooks(library, atoi(input), atoi(max));
			}
		}
		else if (strcmp(input, "4") == 0)
		{
			ExportLibraryData(library);
		}
		else if (strcmp(input, "5") == 0)
		{
			//display info
			scan(input);
			GetBookData(library, input);
		}
		else if (strcmp(input, HELP_CHAR) == 0)
		{
			//print help func
		}
	}

	delete[] input;
	delete[] second_input;
}

void AddBook(Library* library, Book* book)
{
	book->_id = library->size;

	Book** newArray = new Book * [library->size + 1];

	for (int i = 0; i < library->size; i++)
		newArray[i] = library->books[i];
	newArray[library->size] = book;

	delete[] library->books;
	library->books = newArray;
	library->size++;
}

void RemoveBook(Library* library, int _id)
{
	_id--;
	//_id check

	int i = 0;
	bool found = false;

	for (; i < library->size; i++)
	{
		if (library->books[i]->_id == _id)
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

	Book** newArray = new Book*[library->size - 1];

	DeleteBook(library->books[i]);

	int old_array_id = 0;
	for (int j = 0; j < library->size - 1; j++)
	{
		if (i == old_array_id)
			old_array_id++;

		library->books[old_array_id]->_id = j;

		newArray[j] = library->books[old_array_id];
		old_array_id++;
		if (old_array_id == library->size)
			break;
	}

	delete[] library->books;
	library->books = newArray;
	library->size--;
}

void RemoveBooks(Library* library, int min, int max)
{
	for (int i = min; i < max + 1; i++)
		RemoveBook(library, i);
}
