#include "book.h"
#include "input.h"
#include "output.h"
#include "library.h"
#include "generics.h"

int (*COMPARISON_FUNCTION_STACK[])(Book*, Book*) = { CompareByAuthor, CompareByTitle, CompareByYear, CompareByPrice, CompareByCategory };

void AddBook(Library* library, Book* book) {
	Book** newArray = new Book * [library->size + 1];

	for (int i = 0; i < library->size; i++)
		newArray[i] = library->books[i];
	newArray[library->size] = book;

	delete[] library->books;
	library->books = newArray;
	library->size++;
}

Book** SortBooks(Library* library, int (*Compare)(Book*, Book*), int order) {
	Book** sorted_books = library->books;

	for (int i = 0; i < library->size - 1; i++) {
		bool b = false;
		for (int j = 0; j < library->size - i - 1; j++) {
			Book* curBook = sorted_books[j];
			Book* nextBook = sorted_books[j + 1];
			if (order * (*Compare)(curBook, nextBook) > 0) {
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

void RemoveBook(Library* library, int _id) {
	_id--;
	//_id check

	Book** newArray = new Book * [library->size - 1];

	DeleteBook(library->books[_id]);

	int old_array_id = 0;
	for (int i = 0; i < library->size - 1; i++) {
		if (_id == old_array_id)
			old_array_id++;

		newArray[i] = library->books[old_array_id];
		old_array_id++;
		if (old_array_id == library->size)
			break;
	}

	delete[] library->books;
	library->books = newArray;
	library->size--;
}

void RemoveBooks(Library* library, int min, int max) {
	//check min and max

	Book** newArray = new Book * [library->size - max + min - 1];
	int old_array_id = 0;

	for (int _id = 0; _id < library->size; _id++) {
		if (_id >= min - 1 && _id < max) {
			DeleteBook(library->books[_id]);
			old_array_id++;
			continue;
		}

		newArray[_id] = library->books[old_array_id];
		old_array_id++;
	}

	delete[] library->books;
	library->books = newArray;
	library->size -= max - min + 1;
}

void DisplayLibraryCommand(Library* library, char* input) {
	scan_char(input);
	
	switch (*input)
	{
	case '1':
		DisplayLibrary(library);
		break;
	case '2': {
		char second_input = DEFAULT_CHAR;

		// choose field to sort
		printf("sorted display");
		scan_char(input);
		scan_char(&second_input);

		Book** sorted_books = SortBooks(
			library,
			COMPARISON_FUNCTION_STACK[atoi(input)],
			((atoi(&second_input) == 1) ? -1 : 1)
		);

		DisplayBookList(sorted_books, library->size);
		break;
	}
	default:
		break;
	}
}

void RemoveBookCommand(Library* library, char* input) {
	//display files
	//choose mode
	printf("delete char\n");
	scan_char(input);

	if (strcmp(input, "1") == 0) {
		//enter book #
		scan_char(input);
		RemoveBook(library, atoi(input));
	}
	else if (strcmp(input, "2") == 0) {
		char second_input = DEFAULT_CHAR;
		
		//enter min and max book id
		scan_char(input);
		scan_char(&second_input);
		RemoveBooks(library, atoi(input), atoi(&second_input));
	}
	else {
		// error
	}
}

void WorkWithLibrary() {
	//print init
	//print help func
	char input = DEFAULT_CHAR;
	char* input_string = new char[1000];
	Library* library = new Library;

	GetLibraryData(library);
	//msg done -> help how to
	
	while (input != EXIT_CHAR) {
		scan_char(&input);

		switch (input)
		{
		case '1':
			DisplayLibraryCommand(library, &input);
			break;
		case '2': {
			Book* book = new Book;

			if (SetBookData(book)) {
				AddBook(library, book);
			}
			else {
				delete book;
			}
			break;
		}
		case '3':
			RemoveBookCommand(library, &input);
			break;
		case '4':
			ExportLibraryData(library);
			break;
		case '5':
			scan_line(input_string);
			GetBookData(library, input_string);
			break;
		case HELP_CHAR:
			break;
		case EXIT_CHAR:
			break;
		default:
			break;
		}
	}

	DeleteLibrary(library);

	delete[] input_string;
}
