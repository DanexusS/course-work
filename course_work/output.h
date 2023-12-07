#pragma once
#include "book.h"
#include "library.h"

#define RESET "\x1B[0m"

#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"

void AnimateDotLoadingScreen(
	const char* loading_text,
	int cycles_amount,
	int animation_delay
);

void DisplaySettingsMenu(Library* library);
void DisplayDefaultCommandsMenu(Library* library, bool is_numerated);
void DisplayDefaultCommand(const char* text, const char* after_text = "(default)");

void DisplayGetBookDataCommandText(int default_amount_id, int default_location_id);
void DisplaySortedBookDisplayText();
void DisplayExportLibraryDataCommandText(Library* library);
void DisplayRemoveBooksCommandText(int default_command_id);
void DisplayLibraryCommandText(int default_command_id);
void DisplayCategoryAmountCommandText();

void DisplayErrorMessage(const char* error_msg);

void DisplayLogo();
void DisplayInitializationFinish();
void DisplayLibraryHelpMessage();
void PrintProgramBegining();

void DisplayBook(Book* book, bool display_title);
void DisplayBookShorted(Book* book);
void DisplayBookList(Book** book_list, int size);
void DisplayShorterBookList(Book** book_list, int size);

void DisplayBookInputHelpMessage();

static void DisplayLibrary(Library* library) { DisplayBookList(library->books, library->size); }

void ExportSettingsData(Library* library);

static void PrintYearText(char* input) { printf("There were no existing book published in %s year.", input); }
static void PrintPriceText(char* input) { printf("The '%s$' is not valid price.", input); }
static void PrintCategoryText(char* input) { printf("The category under %s number is not found. Acceptable numbers from 1 to %d.", input, BOOK_CATEGORY_AMOUNT); }

void ExportBookData(Library* library, Book* book);
void ExportLibraryData(Library* library);
