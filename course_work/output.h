#pragma once
#include "book.h"
#include "library.h"

void DisplaySortedBookDisplayText();

void DisplayExportLibraryDataCommandText();
void RemoveBooksCommandText();
void DisplayLibraryCommandText();

void DisplayErrorMessage(const char*);

void DisplayLogo();
void DisplayInitializationFinish();
void DisplayLibraryHelpMessage();
void PrintProgramBegining();

void DisplayBook(Book*);
void DisplayBookList(Book**, int);

void DisplayBookInputHelpMessage();

static void DisplayLibrary(Library* library) { DisplayBookList(library->books, library->size); }

static void PrintYearText(char* input) { printf("There were no existing book published in %s year.", input); }
static void PrintPriceText(char* input) { printf("The '%s$' is not valid price.", input); }
static void PrintCategoryText(char* input) { printf("The category under %s number is not found. Acceptable numbers from 0 to %d.", input, CATEGORY_AMOUNT - 1); }

void ExportBookData(Book*);
void ExportLibraryData(Library*);

