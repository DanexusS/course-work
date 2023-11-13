#include "book.h"
#include "sort.h"
#include "input.h"
#include "output.h"
#include "library.h"
#include "generics.h"

int (*COMPARISON_FUNCTION_STACK[])(Book*, Book*) = { CompareByAuthor, CompareByTitle, CompareByYear, CompareByPrice, CompareByCategory };

void AddBook(Library* library, Book* book) {
	if (library->size + 1 >= library->free_space) {
		library->free_space *= 2;
		Book** newArray = new Book*[library->free_space];

		for (int i = 0; i < library->size; i++)
			newArray[i] = library->books[i];
		book->_id = library->size;
		newArray[library->size] = book;

		delete[] library->books;
		library->books = newArray;
		library->size++;
		return;
	}

	book->_id = library->size;
	library->books[library->size] = book;
	library->size++;
}

void RemoveBook(Library* library, int _id) {
	_id--;

	if (_id < 0 || _id > library->size) {
		DisplayErrorMessage("Entered id is not in the library");
		return;
	}

	if (library->size - 1 < library->free_space / 2) library->free_space /= 2;

	int old_array_id = 0;
	Book** newArray = new Book*[library->free_space];

	for (int i = 0; i < library->size - 1; i++) {
		if (_id == old_array_id)
			old_array_id++;

		library->books[old_array_id]->_id = old_array_id;
		newArray[i] = library->books[old_array_id];
		old_array_id++;
		if (old_array_id == library->size)
			break;
	}

	DeleteBook(library->books[_id]);
	delete[] library->books;

	library->books = newArray;
	library->size--;
}

bool RemoveBooks(Library* library, int min, int max) {
	if (min < 0 || max > library->size || min > max) {
		DisplayErrorMessage("Entered input range is not corrected.");
		return false;
	}

	int delete_size = max - min + 1;

	if (library->size - delete_size < library->free_space / 2)
		while (library->size - delete_size < library->free_space - 1)
			library->free_space /= 2;

	int old_array_id = 0;
	Book** newArray = new Book*[library->free_space];

	int new_id = 0;
	for (int _id = 0; _id < library->size; _id++) {
		if (_id >= min - 1 && _id < max) {
			DeleteBook(library->books[_id]);
			
			old_array_id++;
			continue;
		}

		library->books[old_array_id]->_id = new_id;
		newArray[new_id] = library->books[old_array_id];
		old_array_id++;
		new_id++;
	}

	delete[] library->books;

	library->books = newArray;
	library->size -= delete_size;

	return true;
}

void DisplayLibraryCommand(Library* library, char* input) {
	DisplayLibraryCommandText();

	scan_char(input);
	
	while (true) {
		switch (*input)
		{
		case '1':
			printf("Displaying library's books normally:\n");
			DisplayLibrary(library);
			return;
		case '2': {
			char second_input = DEFAULT_CHAR;

			DisplaySortedBookDisplayText();

			printf("Enter field's number: ");
			scan_char(input);
			if (atoi(input) < 0 || atoi(input) > 4) DisplayErrorMessage("Incorrect field's number!");
			printf("\n");

			printf("Enter order's number: ");
			scan_char(&second_input);
			if (atoi(&second_input) < 0 || atoi(&second_input) > 1) DisplayErrorMessage("Incorrect order's number!");
			printf("\n");

			Book** sorted_books = SortBooks(
				library,
				COMPARISON_FUNCTION_STACK[atoi(input)],
				((atoi(&second_input) == 1) ? -1 : 1)
			);

			DisplayBookList(sorted_books, library->size);
			return;
		}
		default:
			DisplayErrorMessage("There is no any other availible command number, except listed higher.");
			break;
		}
	}
}

void RemoveBookCommand(Library* library, char* input, char* long_input) {
	RemoveBooksCommandText();
	DisplayLibrary(library);

	printf("\n\n\n");
	printf("Choose removal type: ");
	scan_char(input);
	printf("\n");

	while (true) {
		switch (*input)
		{
		case '1':
			printf("Enter book's id (from 1 to %d): ", library->size + 1);
			scan_line(long_input);
			printf("\n");

			RemoveBook(library, atoi(input));
			return;
		case '2': {
			char* second_long_input = new char[100];

			printf("Enter id to start deleting from: ");
			scan_line(long_input);
			printf("\n");

			printf("Enter id to end deleting to: ");
			scan_char(second_long_input);
			printf("\n");

			RemoveBooks(library, atoi(long_input), atoi(second_long_input));

			delete[] second_long_input;
			return;
		}
		case EXIT_CHAR:
			printf("Returning to the main menu.\n");
			return;
		default:
			DisplayErrorMessage("There is no any other availible removal type's number, except listed higher.");
			break;
		}
	}
}

void WorkWithLibrary() {
	char input = DEFAULT_CHAR;
	char* long_input = new char[1000];
	Library* library = new Library;

	GetLibraryData(library);

	PrintProgramBegining();
	
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
				printf(" Book was initialized, so the book is added into the library.\n");
				AddBook(library, book);
			}
			else {
				printf(" Book wasn't fully initialized, so the book won't be added into the library.\n");
				delete book;
			}
			break;
		}
		case '3':
			RemoveBookCommand(library, &input, long_input);
			break;
		case '4':
			DisplayExportLibraryDataCommandText();
			ExportLibraryData(library);
			break;
		case '5': {
			scan_line(long_input);
			GetBookData(library, long_input);
			break;
		}
		case '6': {
			int category_count = 0;

			scan_char(&input);

			if (atoi(&input) < 0 || atoi(&input) > CATEGORY_AMOUNT) {
				DisplayErrorMessage("Entered category id is not valid");
				break;
			}

			for (int _id = 0; _id < library->size; _id++)
				if ((int)library->books[_id]->category == atoi(&input))
					category_count++;

			printf("%d\n", category_count);
			break;
		}
		case HELP_CHAR:
			DisplayLibraryHelpMessage();
			break;
		case EXIT_CHAR:
			printf("\n\n\n");
			printf("Exiting the program, goodbye for now!\n");
			break;
		case CLEAR_CHAR:
			system("cls");
			break;
		default:
			DisplayErrorMessage("This command is not supported by this program!");
			break;
		}
		if (input != EXIT_CHAR) DisplayLibraryHelpMessage();
	}

	DeleteLibrary(library);

	delete[] long_input;
}
