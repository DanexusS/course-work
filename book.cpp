#include <iostream>
#include "course_work/input.h"
#include "course_work/book.h"

void DisplayBook(Book* book)
{
	printf("\n\n\n");
	printf("\t\tBOOK INFORMATION\n\n");
	printf(
		"Author: %s\nTitle: %s\nPublish year: %d\nPrice: %f\nBook category: %s\n\n\n",
		book->author, book->title, book->year, book->price, categoryTitles[(int)book->category]
	);
}

bool CheckIsNumber(char* input)
{
	int i = 0;
	bool wasDot = false;

	if (input[0] == '-')
		i = 1;

	for (; input[i] != '\0'; i++)
		if (input[i] == '.')
		{
			if (wasDot)
				return false;
			wasDot = true;
		}
		else if (!isdigit(input[i]))
			return false;

	return true;
}

// CONSTANTS
const int CATEGORY_AMOUNT = (sizeof(categoryTitles) / sizeof(*categoryTitles));
const int START_ITER_CHECK = 2;

const char* BACK_CHAR = "-";
const char* BOOK_EXIT_CHAR = "`";
const char* HELP_CHAR = "?";

const char* PRINT_PROMPTS[BOOK_TEXT_FILD_SIZE] = { "Enter author: ", "Enter title: ", "Enter publish year: ", "Enter price: ", "Enter category number: " };

void SetAuthor(char* string, Book* book) { strcpy(book->author, string); }
void SetTitle(char* string, Book* book) { strcpy(book->title, string);}
void SetYear(char* string, Book* book) { book->year = atoi(string); }
void SetPrice(char* string, Book* book) { book->price = atof(string); }
void SetCategory(char* string, Book* book) { book->category = (Category)atoi(string); }

bool CheckYearValidity(char* year) { return !CheckIsNumber(year) || atoi(year) < 1056; }
bool CheckPriceValidity(char* price) { return !CheckIsNumber(price) || atof(price) < 0; }
bool CheckCategoryValidity(char* category) { return !CheckIsNumber(category) || (atoi(category) < 0 || atoi(category) > CATEGORY_AMOUNT - 1); }

void PrintYearText(char* input) { printf("There were no existing book published in %s year.", input); }
void PrintPriceText(char* input) { printf("The '%s$' is not valid price.", input); }
void PrintCategoryText(char* input) { printf("The category under %s number is not found. Acceptable numbers from 0 to %d.", input, CATEGORY_AMOUNT - 1); }

void PrintHelpInformation()
{
	printf("\n\n");
	printf("How to use:\n");
	printf(" The input is queued specificly in this order: (author -> title -> year -> price -> category\n");
	printf(" To return to the previous queue position: type %s\n", BACK_CHAR);
	printf(" To cancel entering book data: type %s\n", BOOK_EXIT_CHAR);
	printf(" To show this text again: type %s\n", HELP_CHAR);
	printf(" NOTE: Category number and its name:\n");
	for (int i = 0; i < CATEGORY_AMOUNT; i++)
		printf(" %s: %d\n", categoryTitles[i], i);
	printf("\n");
}

static enum ReturnResults
{
	ExitInput,
	SkipIteration,
	ContinueCurrentIteration
};

ReturnResults WorkWithPrebuiltCommands(char* input, unsigned short& iter)
{
	if (strcmp(input, BACK_CHAR) == 0)
	{
		if (iter == 0)
			printf("   You are at the begining of the input queue, no need to go back.\n\n");
		else
		{
			printf("\n");
			printf("   Returning to the previous position in input queue\n\n");
			iter--;
		}

		return SkipIteration;
	}
	if (strcmp(input, BOOK_EXIT_CHAR) == 0)
	{
		printf("Exiting from getting book data module\n\n\n");
		return ExitInput;
	}
	if (strcmp(input, HELP_CHAR) == 0)
	{
		PrintHelpInformation();
		return SkipIteration;
	}

	return ContinueCurrentIteration;
}

short CheckValidity(char* input, unsigned short& iter, bool (*ifstatement)(char*), void (*print)(char*))
{
	bool wentBack = false;

	while (ifstatement(input))
	{
		print(input);
		printf(" Enter valid input, go back, or exit: ");
		scan(input);

		short workWithPrebuiltCommandsResult = WorkWithPrebuiltCommands(input, iter);

		if (workWithPrebuiltCommandsResult == 0)
		{
			wentBack = true;
			break;
		}
		else if (workWithPrebuiltCommandsResult == -1)
			return 0;
	}
	if (wentBack)
		return -1;

	return 1;
}

void(*INPUT_FUNCTION_STACK[])(char*, Book*) = { SetAuthor, SetTitle, SetYear, SetPrice, SetCategory };
void(*PRINT_FUNCTION_STACK[])(char*) = { PrintYearText, PrintPriceText, PrintCategoryText };

bool(*CHECK_FUNCTION_STACK[])(char*) = { CheckYearValidity, CheckPriceValidity, CheckCategoryValidity };

bool SetBookData(Book* book)
{
	printf("\n\n\n");
	printf("\t\t\tGETTING BOOK DATA FROM INPUT\n\t\t\t----------------------------");
	PrintHelpInformation();

	char buffer[BOOK_TEXT_FILD_SIZE];
	char* input = buffer;
	unsigned short iter = 0;

	while (iter != BOOK_STRUCT_FIELD_AMOUNT)
	{
		printf(PRINT_PROMPTS[iter]);
		scan(input);

		short prebuiltCommandsResult = WorkWithPrebuiltCommands(input, iter);

		if (prebuiltCommandsResult == SkipIteration)
			continue;
		else if (prebuiltCommandsResult == ExitInput)
			return false;

		if (iter >= START_ITER_CHECK)
		{
			int validityCheckResult = CheckValidity(
				input, iter, CHECK_FUNCTION_STACK[iter - START_ITER_CHECK], PRINT_FUNCTION_STACK[iter - START_ITER_CHECK]
			);

			if (validityCheckResult == 0)
				return false;
			if (validityCheckResult == -1)
				continue;
		}

		INPUT_FUNCTION_STACK[iter](input, book);
		iter++;
	}

	return true;
}
