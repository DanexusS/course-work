#include <stdio.h>
#include <direct.h>
#include <iostream>
#include <Windows.h>

#include "input.h"
#include "output.h"
#include "generics.h"

#if defined _DEBUG
#define TURN_OFF_ANIMATION
#endif

#define BOLD "\x1B[1m"
#define UNDERLINE "\033[4m"

void AnimateDotLoadingScreen(const char* loading_text, int cycles_amount = 3, int animation_delay = 250) {
	for (int i = 0; i < cycles_amount; i++) {
		printf(loading_text);
		for (int j = 0; j < 3; j++) {
			Sleep(animation_delay);
			printf(".");
		}
		system("cls");
	}
}

void DisplayCategories() {
	printf(" NOTE: Category number and its name:\n");
	for (int i = 0; i < BOOK_CATEGORY_AMOUNT; i++)
		printf(" %s: %d\n", BOOK_CATEGORY_TITLES[i], i + 1);
	printf("\n");
}

void DisplayDefaultCommand(const char* text, const char* after_text) {
	printf(" %s%s%s%s%s\t%s\n", BOLD, UNDERLINE, text, RESET, RESET, after_text);
}

void DisplayDefaultCommandsMenu(Library* library, bool is_numerated) {
	int default_book_amount = library->settings->default_command_ids[2];

	printf(
		" %s Library Display: %s%s%s display;\n",
		(is_numerated ? "1." : ""),
		UNDERLINE, DEFAULT_COMMAND_DISPLAY[0][library->settings->default_command_ids[0]], RESET
	);
	printf(
		" %s Book removal: %s%s%s mode;\n",
		(is_numerated ? "2." : ""),
		UNDERLINE, DEFAULT_COMMAND_DISPLAY[1][library->settings->default_command_ids[1]], RESET
	);
	printf(
		" %s Getting book data from files: %s%s%s book%s;\n",
		(is_numerated ? "3." : ""),
		UNDERLINE, DEFAULT_COMMAND_DISPLAY[2][default_book_amount], RESET, (default_book_amount ? "s" : "")
	);
	printf(
		" %s Getting book data from files: %s%s%s;\n",
		(is_numerated ? "4." : ""),
		UNDERLINE, DEFAULT_COMMAND_DISPLAY[3][library->settings->default_command_ids[3]], RESET
	);
}

void DisplaySettingsMenu(Library* library) {
	printf("\t\t\t%s%sSETTINGS%s%s\n\n", BOLD, UNDERLINE, RESET, RESET);
	printf("%s1. Books folder:%s %s\n", BOLD, RESET, library->settings->books_folder);
	printf("%s2. Files data file name:%s %s\n", BOLD, RESET, library->settings->files_data_name);
	printf("%s3. Default commands in program for:%s\n", BOLD, RESET);
	DisplayDefaultCommandsMenu(library, false);
	printf("%s4. Save current settings to the file.%s\n\n", BOLD, RESET);
	printf("To change any parameter, you simply type needed number to the console.\n");
	printf("To exit settings menu type %c.\n\n", EXIT_CHAR);
}

void DisplayCategoryAmountCommandText() {
	printf("Choose the category number to display the amount of the books in the according category.\n");
	DisplayCategories();
}

void DisplaySortedBookDisplayText() {
	printf("Choose the field to sort library's books by it.\n");
	printf("To choose it you should type field number and order.\n");
	printf("Field titles and their numbers:\n");
	printf(" 1. Author;\n");
	printf(" 2. Title;\n");
	printf(" 3. Price;\n");
	printf(" 4. Publish year;\n");
	printf(" 5. Category.\n");
	printf("Order varients and thier numbers:\n");
	printf(" 1. Descending order;\n");
	printf(" 2. Ascending order.\n\n");
}

void DisplayExportLibraryDataCommandText(Library* library) { printf("Exporting library data to ./%s folder.\n", library->settings->books_folder); }

void DisplayGetBookDataCommandText(int default_amount_id, int default_location_id) {
	printf("There are two types of getting books' information:\n");
	if (default_amount_id == 0) {
		DisplayDefaultCommand("1. Getting one book;");
		printf(" 2. Getting several books.\n\n");
	}
	else {
		printf(" 1. Getting one book;\n");
		DisplayDefaultCommand("2. Getting several books.");
		printf("\n");
	}
	printf("There are two different types of getting information:\n");

	if (default_location_id == 0) {
		DisplayDefaultCommand("1. Getting information from default folder (specified in settings);");
		printf(" 2. Getting information from specific folder (entered by user).\n\n");
	}
	else {
		printf(" 1. Getting information from default folder (specified in settings);\n");
		DisplayDefaultCommand("2. Getting information from specific folder (entered by user).");
		printf("\n");
	}
}

void DisplayRemoveBooksCommandText(int default_command_id) {
	printf("There are two types of removing books: \n");
	if (default_command_id == 0) {
		DisplayDefaultCommand("1. Single book removal;");
		printf(" 2. Range book removal.\n\n");
	}
	else {
		printf(" 1. Single book removal;\n");
		DisplayDefaultCommand("2. Range book removal.");
		printf("\n");
	}
}

void DisplayLibraryCommandText(int default_command_id) {
	printf("\t\tDisplay Library Command:\n");
	printf("Choose display mode (enter number to choose):\n");
	if (default_command_id == 0) {
		DisplayDefaultCommand("1. Normal display;");
		printf(" 2. Sorted display by specific field and order.\n\n");
	}
	else {
		printf(" 1. Normal display;\n");
		DisplayDefaultCommand("2. Sorted display by specific field and order.");
		printf("\n");
	}
}

void DisplayErrorMessage(const char* message) {
	printf("\n");
	printf("%s%s   CRITICAL ERROR!%s%s\n", BOLD, RED, RESET, RESET);
	printf("%s%s%s\n\n", RED, message, RESET);
}

void DisplayLibraryHelpMessage() {
	printf("\n\n");
	printf("\t\t%sHOW TO USE%s\n", BOLD, RESET);
	printf(" There are several different commands to work with librar.\n");
	printf(" To choose specific command just input number of that command.\n");
	printf(" Commands list and their numbers:\n");
	printf("   1. Display library's books normally or sorted;\n");
	printf("   2. Input new book and add it to the library;\n");
	printf("   3. Delete one/several book(s) to the library;\n");
	printf("   4. Export current library's books;\n");
	printf("   5. Get new book's data from file;\n");
	printf("   6. Display amount of books in the specific category;\n");
	printf(" To open settings: type %c. %s*%s\n", SETTINGS_CHAR, BOLD, RESET);
	printf(" To exit the program: type %c.\n", EXIT_CHAR);
	printf(" To help text again: type %c. %s**%s\n", HELP_CHAR, BOLD, RESET);
	printf(" To clear the console entirely: type %c.\n\n", CLEAR_CHAR);
	printf("*NOTE: you can change default commands in settings. So as the default book location and more!\n");
	printf("**PLEASE NOTE: '%c' char also can be used in all commands to remind you of the commmand's functionality.\n", HELP_CHAR);
	printf("\n\n");
}

void DisplayInitializationFinish() {
	printf("\n\n\n");
	printf("Library initialization done.\n");
	Sleep(1000);
	system("cls");

	AnimateDotLoadingScreen("Opening User Interface");
}

void DisplayLogo() {
	Picture* logo = GetLogoData();

	for (int i = 0; i < logo->height; i++) {
		printf(logo->picture[i]);
		printf("\n");
		Sleep(15);
	}

	DeleteLogo(logo);
}

void PrintProgramBegining() {
#if !defined TURN_OFF_ANIMATION
	DisplayInitializationFinish();
	system("cls");
	DisplayLogo();
#endif
	DisplayLibraryHelpMessage();
}

void DisplayBookShorted(Book* book) {
	printf(
		"%d. \"%s\" by %s. Published in %d. %f$. %s.\n",
		book->_id + 1, book->title, book->author, book->year, book->price, BOOK_CATEGORY_TITLES[(int)book->category]\
	);
}

void DisplayBook(Book* book_list, bool display_title = false) {
	if (display_title) {
		printf("\n\n");
		printf("\t\tBOOK INFORMATION\n\n");
	}
	else
		printf("\n");
		
	printf(
		"Number: %d\nAuthor: %s\nTitle: %s\nPublish year: %d\nPrice: %f\nBook category: %s\n",
		book_list->_id + 1, 
		book_list->author, 
		book_list->title, 
		book_list->year, 
		book_list->price, 
		BOOK_CATEGORY_TITLES[(int)book_list->category]
	);
}

void DisplayShorterBookList(Book** books, int size) {
	printf("\n\n");
	printf("\t\tLIBRARY INFORMATION\n");
	for (int i = 0; i < size; i++)
		DisplayBookShorted(books[i]);
}

void DisplayBookList(Book** books, int size) {
	DisplayBook(books[0], true);
	for (int i = 1; i < size; i++)
		DisplayBook(books[i]);
}

void DisplayBookInputHelpMessage() {
	printf("\n\n");
	printf("How to use:\n");
	printf(" The input is queued specificly in this order: (author -> title -> year -> price -> category\n");
	printf(" To return to the previous queue position: type %c\n", BACK_CHAR);
	printf(" To cancel entering book data: type %c\n", EXIT_CHAR);
	printf(" To show this text again: type %c\n", HELP_CHAR);
	DisplayCategories();
}

// WORKING WITH FILES

void ExportSettingsData(Library* library) {
	FILE* settings_file = fopen(DEFAULT_SETTINGS_LOCATION, "w");

	fprintf(settings_file, "%s\n%s\n", library->settings->books_folder, library->settings->files_data_name);
	for (int i = 0; i < CHOOSE_FUNCTIONS_AMOUNT; i++) {
		fprintf(settings_file, "%d", library->settings->default_command_ids[i]);
		if (i != CHOOSE_FUNCTIONS_AMOUNT - 1)
			fprintf(settings_file, ",");
	}
	fprintf(settings_file, "\n");

	fclose(settings_file);
}

void ExportBookData(Library* library, Book* book) {
	char* file_location = new char[LONG_INPUT_BUFFER];
	strcpy(file_location, library->settings->books_folder);
	strcat(file_location, book->title);
	strcat(file_location, ".txt");

	FILE* book_file = fopen(file_location, "w");

#if defined _DEBUG
	printf("[DEBUG] Opening ./%s and writing information there", file_location);
	printf("\n");
#endif

	fprintf(book_file, "%s\n%s\n%d\n%lf\n%d", book->author, book->title, book->year, book->price, book->category);

	fclose(book_file);
	delete[] file_location;
}

void ExportLibraryData(Library* library) {
	char* library_data_location = new char[LONG_INPUT_BUFFER];
	strcpy(library_data_location, library->settings->books_folder);
	strcat(library_data_location, library->settings->files_data_name);

	if (CheckFileLocation(library_data_location)) {
		int result = _mkdir(library->settings->books_folder);
		if (result == 0) {
			DisplayErrorMessage("Program has no access to the folder, where you want to create a folder!");
			delete[] library_data_location;
			return;
		}
	}
	
	FILE* library_data_file = fopen(library_data_location, "w");

	fprintf(library_data_file, "%d\n", library->size);

	for (int i = 0; i < library->size; i++) {
		ExportBookData(library, library->books[i]);
		fprintf(library_data_file, "%s.txt\n", library->books[i]->title);
	}
	
	fclose(library_data_file);

	printf("\n");
	printf("Finished exporting library\n");

	delete[] library_data_location;
}
