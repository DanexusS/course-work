#include "book.h"
#include "sort.h"
#include "input.h"
#include "output.h"
#include "library.h"
#include "generics.h"

const char CHANGE_FOLDER_CHAR = '*';

// TODO: MAKE MULTIPLE BOOK READING AND CHOOSING FOLDER LOCATION

void AddBook(Library* library, Book* book) {
	if (library->size + 1 >= library->free_space) {
		library->free_space *= 2;
		Book** newArray = new Book * [library->free_space];

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

//
//				1. DISPLAY LIBRARY COMMAND
//

int (*COMPARISON_FUNCTION_STACK[])(Book*, Book*) = { 
	CompareByAuthor, CompareByTitle, CompareByYear, CompareByPrice, CompareByCategory 
};

bool FieldSelectionCheck(const char* long_input) {
	int chosen_field_number = atoi(long_input);
	return chosen_field_number < 0 || chosen_field_number > BOOK_STRUCT_FIELD_AMOUNT;
}

bool OrderSelectionCheck(const char* long_input) {
	int chosen_order_number = atoi(long_input);
	return chosen_order_number < 1 || chosen_order_number > 2;
}

void DisplayLibraryCommand(Library* library, char* long_input) {
	if (library->size == 0) {
		printf("Currently, there are no books in library to display.\n");
		return;
	}

	int default_command_id = library->settings->default_command_ids[0];

	DisplayLibraryCommandText(default_command_id);

	if (default_command_id == 0) {
		printf("Displaying library's books normally:\n");
		DisplayLibrary(library);
		return;
	}

	char* second_long_input = new char[LONG_INPUT_BUFFER];

	DisplaySortedBookDisplayText();
	scan_infinitely(long_input, "Enter field's number: ", FieldSelectionCheck, "Incorrect field's number!");
	scan_infinitely(second_long_input, "Enter order's number: ", OrderSelectionCheck, "Incorrect order's number!");

	Book** sorted_books = SortBooks(
		library,
		COMPARISON_FUNCTION_STACK[atoi(long_input)],
		((atoi(second_long_input) == 1) ? -1 : 1)
	);

	DisplayBookList(sorted_books, library->size);
	delete[] second_long_input;
	return;
}


//
//				2. ADD BOOK COMMAND
//

void AddBookCommand(Library* library, char* long_input) {
	Book* book = new Book;

	if (SetBookData(book, long_input)) {
		printf(" Book was initialized, so the book is added into the library.\n");
		AddBook(library, book);
	}
	else {
		printf(" Book wasn't fully initialized, so the book won't be added into the library.\n");
		delete book;
	}
}

//
//				3. REMOVE BOOK(s) FROM LIBRARY COMMAND		
//

void RemoveBook(Library* library, int _id) {
	_id--;

	if (library->size - 1 < library->free_space / 2) library->free_space /= 2;

	int old_array_id = 0;
	Book** newArray = new Book * [library->free_space];

	for (int i = 0; i < library->size; i++) {
		if (_id == old_array_id)
			old_array_id++;

		library->books[old_array_id]->_id = i;
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

void RemoveBooks(Library* library, int min, int max) {
	if (min < 0 || max > library->size) {
		DisplayErrorMessage("Entered input range is not corrected.");
		return;
	}
	if (min > max) {
		printf("[SYSTEM] Entered range, where min is more than max values, these values were inverted.\n");

		int temp = min;
		min = max;
		max = temp;
	}

	int delete_size = max - min + 1;

	if (library->size - delete_size < library->free_space / 2)
		while (library->size - delete_size < library->free_space - 1)
			library->free_space /= 2;

	int old_array_id = 0;
	Book** newArray = new Book * [library->free_space];

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

	return;
}

bool CheckRangeNumber(Library* library, const char* long_input) {
	int id = atoi(long_input);
	return id < 0 || id > library->size;
}

void RemoveBookCommand(Library* library, char* long_input) {
	if (library->size == 0) {
		printf("Currently, there are no books in library to delete.\n");
		return;
	}

	DisplayShorterBookList(library->books, library->size);
	printf("\n");

	int default_command_id = library->settings->default_command_ids[1];

	DisplayRemoveBooksCommandText(default_command_id);

	if (default_command_id == 0) {
		printf("You can enter book's number (from 1 to %d).\n", library->size);
		scan_infinitely(
			library,
			long_input,
			"Enter book's number to delete it: ",
			CheckRangeNumber,
			"You entered invalid start number!"
		);

		RemoveBook(library, atoi(long_input));

		printf("Done! The book number %s was deleted!", long_input);
		return;
	}

	char* second_long_input = new char[LONG_INPUT_BUFFER];

	printf("You can choose start and end book's number from 1 to %d.\n", library->size);
	scan_infinitely(
		library,
		long_input,
		"Enter number to start deleting from: ",
		CheckRangeNumber,
		"You entered invalid start number!"
	);
	scan_infinitely(
		library,
		second_long_input,
		"Enter number to end deleting to: ",
		CheckRangeNumber,
		"You entered invalid end number!"
	);

	RemoveBooks(library, atoi(long_input), atoi(second_long_input));
	delete[] second_long_input;
}

//
//				4. EXPORT LIBRARY DATA COMMAND
//

void ExportLibraryDataCommand(Library* library) {
	DisplayExportLibraryDataCommandText(library);
	ExportLibraryData(library);
}

//
//				5. GET BOOK(s) DATA COMMAND
//

void GetFolderLocation(char* location, char* long_input) {
	scan_infinitely(
		long_input,
		"Enter location to gather books from: ",
		CheckFolderLocation,
		"There is no valid folder by this name!",
		"",
		"/"
	);
	strcpy(location, strcat(long_input, "/"));
}

void GetBookDataCommand(Library* library, char* long_input) {
	int default_amount_id = library->settings->default_command_ids[2];
	int default_location_id = library->settings->default_command_ids[3];

	char* location = new char[LONG_INPUT_BUFFER];
	strcpy(location, library->settings->books_folder);

	DisplayGetBookDataCommandText(default_amount_id, default_location_id);

	if (default_location_id == 1)
		GetFolderLocation(location, long_input);

	if (default_amount_id == 0) {
		scan_infinitely(
			long_input,
			"Enter file name: ",
			CheckFileLocation,
			"There is no book file with this name!",
			location,
			".txt"
		);
		strcat(location, long_input);
		strcat(location, ".txt");

		GetBookDataFull(library, location);

		delete[] location;
		return;
	}

	printf("If you wish to exit type %c in the console or just hit Enter key on a keyboard. Else you will enter as many files as you want.\n", EXIT_CHAR);
	printf("To change folder - type %c.\n", CHANGE_FOLDER_CHAR);

	char* book_location = new char[LONG_INPUT_BUFFER];

	while (true) {
		printf("Enter file name, change folder or exit: ");
		scan_line(long_input);
		if (strlen(long_input) == 1) {
			if (*long_input == EXIT_CHAR) {
				printf("Returning to the main cycle.\n");
				strcpy(long_input, "");
				break;
			}
			if (*long_input == CHANGE_FOLDER_CHAR) {
				GetFolderLocation(location, long_input);
				continue;
			}
		}

		strcpy(book_location, location);
		strcat(book_location, long_input);
		strcat(book_location, ".txt");

		if (CheckFileLocation(book_location)) {
			DisplayErrorMessage("There is no file by this name!");
			continue;
		}

		GetBookDataFull(library, book_location);
	}

	delete[] book_location;
	delete[] location;
}

//
//				6. DISPLAY CATEGORY AMOUNT COMMAND
//

bool CheckCategoryNumber(const char* long_input) {
	int chosen_category = atoi(long_input);
	return chosen_category < 1 || chosen_category > BOOK_CATEGORY_AMOUNT;
}

void DisplayCategoryAmountCommand(Library* library, char* long_input) {
	DisplayCategoryAmountCommandText();

	scan_infinitely(
		long_input,
		"Enter category number: ",
		CheckCategoryNumber,
		"Entered category number is not valid!"
	);

	int category_count = 0;
	int chosen_category = atoi(long_input) - 1;
	const char* chosen_category_title = BOOK_CATEGORY_TITLES[chosen_category];

	for (int _id = 0; _id < library->size; _id++)
		if ((int)library->books[_id]->category == chosen_category)
			category_count++;

	if (category_count == 0) {
		printf("There are no books in %s category.\n", chosen_category_title);
		return;
	}
	printf("There are exactly %d books in %s category.\n", category_count, chosen_category_title);
}

//
//				SETTINGS COMMAND
//

bool CheckSettingsNumber(const char* input) {
	int chosen_number = atoi(input);
	return CmpStr(input, &EXIT_CHAR) != 0 && (chosen_number < 0 || chosen_number > SETTINGS_FIELD_AMOUNT);
}

bool CheckChooseFunctionNumber(const char* input) {
	int chosen_number = atoi(input);
	return chosen_number < 0 || chosen_number > CHOOSE_FUNCTIONS_AMOUNT;
}

bool CheckDefaultFunctionID(const char* input) {
	int chosen_number = atoi(input);
	return chosen_number < 0 || chosen_number > 2;
}

void ChangeDefaultFunctionID(Library* library, char* long_input) {
	printf("\n");
	DisplayDefaultCommandsMenu(library, true);
	printf("To change any parameter, you simply type needed number to the console.\n");
	printf("\n");

	scan_infinitely(
		long_input,
		"Enter default program number to change it: ",
		CheckChooseFunctionNumber,
		"This command is not supported by this program!"
	);

	int chosen_number = atoi(long_input) - 1;
	char* default_command_text = new char[LONG_INPUT_BUFFER];
	char* number_buffer = new char[5];
	strcpy(default_command_text, _itoa(library->settings->default_command_ids[chosen_number] + 1, number_buffer, 5));
	strcat(default_command_text, ". ");
	strcat(default_command_text, DEFAULT_COMMAND_DISPLAY[chosen_number][library->settings->default_command_ids[chosen_number]]);

	printf("You chose function #%d. You can these variants:\n", chosen_number + 1);
	if (library->settings->default_command_ids[chosen_number] == 0) {

		DisplayDefaultCommand(default_command_text, "");
		printf(" 2. %s\n\n", DEFAULT_COMMAND_DISPLAY[chosen_number][!library->settings->default_command_ids[chosen_number]]);
	}
	else {
		printf(" 1. %s\n", DEFAULT_COMMAND_DISPLAY[chosen_number][!library->settings->default_command_ids[chosen_number]]);
		DisplayDefaultCommand(default_command_text, "");
		printf("\n");
	}

	scan_infinitely(
		long_input,
		"Enter new default program number: ",
		CheckDefaultFunctionID,
		"There is no default command by this id!"
	);

	library->settings->default_command_ids[chosen_number] = atoi(long_input) - 1;

	delete[] default_command_text;
	delete[] number_buffer;
}

void OpenSettings(Library* library, char* long_input) {
	DisplaySettingsMenu(library);

	while (true) {
		scan_infinitely(
			long_input,
			"Enter setting's field number to change it: ",
			CheckSettingsNumber,
			"This command is not supported by this program!"
		);

		switch (*long_input)
		{
		case '1':
			printf("Enter new default books' folder location: ");
			scan_line(long_input);
			strcpy(library->settings->books_folder, strcat(long_input, "/"));
			break;
		case '2':
			printf("Enter new default files data file name: ");
			scan_line(long_input);
			strcpy(library->settings->files_data_name, strcat(long_input, ".txt"));
			break;
		case '3': {
			ChangeDefaultFunctionID(library, long_input);
			break;
		}
		case '4':
#if defined _DEBUG
			printf("[DEBUG] Exporting settings to the %s location...", DEFAULT_SETTINGS_LOCATION);
#endif
			ExportSettingsData(library);
			printf("Done! Settings were saved locally!\n");
			break;
		case EXIT_CHAR:
			strcpy(long_input, "");
			return;
		default:
			DisplayErrorMessage("This command is not supported!");
			break;
		}

		DisplaySettingsMenu(library);
	}
}

//
//				MAIN CYCLE
//

void WorkWithLibrary() {
	char* long_input = new char[LONG_INPUT_BUFFER];
	Library* library = new Library;

	GetLibraryData(library);

	PrintProgramBegining();
	
	while (*long_input != EXIT_CHAR) {
		scan_line(long_input);

		if (strlen(long_input) > 1) {
			DisplayErrorMessage("This command is not supported by this program!");
			continue;
		}

		switch (*long_input)
		{
		case '1':
			DisplayLibraryCommand(library, long_input);
			break;
		case '2':
			AddBookCommand(library, long_input);
			break;
		case '3':
			RemoveBookCommand(library, long_input);
			break;
		case '4':
			ExportLibraryDataCommand(library);
			break;
		case '5':
			GetBookDataCommand(library, long_input);
			break;
		case '6':
			DisplayCategoryAmountCommand(library, long_input);
			break;
		case CLEAR_CHAR:
			system("cls");
			break;
		case HELP_CHAR:
			DisplayLibraryHelpMessage();
			break;
		case EXIT_CHAR:
			printf("\n\n\n");
			printf("Exiting the program, goodbye for now!\n");
			break;
		case SETTINGS_CHAR:
			OpenSettings(library, long_input);
			break;
		default:
			DisplayErrorMessage("This command is not supported by this program!");
			break;
		}
		if (*long_input != EXIT_CHAR) DisplayLibraryHelpMessage();
	}

	DeleteLibrary(library);
	delete[] long_input;
}
