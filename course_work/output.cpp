#include <cstdio>
#include <iostream>
#include <Windows.h>

#include "input.h"
#include "output.h"
#include "generics.h"

void DisplaySortedBookDisplayText() {
	printf("\n");
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

void DisplayExportLibraryDataCommandText() {
	printf("\n");
	printf("Exporting library data to .\\data folder.\n");
}

void RemoveBooksCommandText() {
	printf("\n");
	printf("There are two types of removing books: \n");
	printf(" 1. Single book removal;\n");
	printf(" 2. Range book removal.\n\n");
}

void DisplayLibraryCommandText() {
	printf("\n\n");
	printf("\t\tDisplay Library Command:\n");
	printf("Choose display mode (enter number to choose):\n");
	printf(" 1. Normal display;\n");
	printf(" 2. Sorted display by specific field and order.\n\n");
}

void DisplayErrorMessage(const char* message) {
	printf("\n\n\n");
	printf("CRITICAL ERROR!\n");
	printf(message);
	printf("\n\n\n");
}

void DisplayLibraryHelpMessage() {
	printf("\n\n");
	printf("How to use:\n");
	printf(" There are several different commands to work with librar.\n");
	printf(" To choose specific command just input number of that command.\n");
	printf(" Commands list and their numbers:\n");
	printf("   1. Display library's books normally or sorted;\n");
	printf("   2. Input new book and add it to the library;\n");
	printf("   3. Delete one/several book(s) to the library;\n");
	printf("   4. Export current library's books;\n");
	printf("   5. Get new book's data from file;\n");
	printf("   6. Display amount of books in the specific category;\n");
	printf(" To exit the program: type %c\n", EXIT_CHAR);
	printf(" To show this text again: type %c\n", HELP_CHAR);
	printf(" To clear the console entirely: type %c\n", CLEAR_CHAR);
	printf("\n\n");
}

void DisplayInitializationFinish() {
	printf("\n\n\n");
	printf("Library initialization done.\n");
	Sleep(1000);
	system("cls");
	for (int i = 0; i < 3; i++) {
		printf("Opening User Interface.");
		Sleep(250);
		printf(".");
		Sleep(250);
		printf(".");
		Sleep(250);
		system("cls");
	}
}

void DisplayLogo() {
	Logo* logo = GetLogoData();

	for (int i = 0; i < logo->height; i++) {
		printf(logo->picture[i]);
		printf("\n");
		Sleep(10);
	}

	DeleteLogo(logo);
}

void PrintProgramBegining() {
	DisplayInitializationFinish();
	DisplayLogo();
	DisplayLibraryHelpMessage();
}

void DisplayBook(Book* book) {
	printf("\n\n");
	printf("\t\tBOOK INFORMATION\n\n");
	printf(
		"Number: %d\nAuthor: %s\nTitle: %s\nPublish year: %d\nPrice: %f\nBook category: %s\n",
		book->_id + 1, book->author, book->title, book->year, book->price, CATEGORY_TITLES[(int)book->category]
	);
}

void DisplayBookList(Book** books, int size) {
	for (int i = 0; i < size; i++)
		DisplayBook(books[i]);
}

void DisplayBookInputHelpMessage() {
	printf("\n\n");
	printf("How to use:\n");
	printf(" The input is queued specificly in this order: (author -> title -> year -> price -> category\n");
	printf(" To return to the previous queue position: type %c\n", BACK_CHAR);
	printf(" To cancel entering book data: type %c\n", EXIT_CHAR);
	printf(" To show this text again: type %c\n", HELP_CHAR);
	printf(" NOTE: Category number and its name:\n");
	for (int i = 0; i < CATEGORY_AMOUNT; i++)
		printf(" %s: %d\n", CATEGORY_TITLES[i], i);
	printf("\n");
}

// WORKING WITH FILES

void ExportBookData(Book* book) {
	char* data_string = new char[6];
	char* file_name = new char[1000];

	strcpy(data_string, "data/");
	strcpy(file_name, book->title);

	FILE* book_file = fopen(strcat(data_string, strcat(file_name, ".txt")), "w");

#if defined _DEBUG
	printf("[DEBUG] Opening ./data/%s.txt and writing information there", book->title);
	printf("\n");
#endif

	fprintf(book_file, "%s\n%s\n%d\n%lf\n%d", book->author, book->title, book->year, book->price, book->category);

	fclose(book_file);
}

void ExportLibraryData(Library* library) {
	FILE* library_data = fopen("data/files_data.txt", "w");

	fprintf(library_data, "%d\n", library->size);

	for (int i = 0; i < library->size; i++) {
		ExportBookData(library->books[i]);

		fprintf(library_data, library->books[i]->title);
		fprintf(library_data, ".txt\n");
	}

	fclose(library_data);

	printf("\n");
	printf("Ended exporting library\n");
}
