//#include <iostream>
//#include <cstring>
#include "input.h"
#include "book.h"

#include "generics.h"

//NOTE: archive

// TODO: use custom strcmp
int CompareByAuthor(Book* first, Book* second, int order)
{
	return strcmp(first->author, second->author) * order;
}
int CompareByTitle(Book* first, Book* second, int order)
{
	return strcmp(first->title, second->title) * order;
}
int CompareByYear(Book* first, Book* second, int order)
{
	if (first->year > second->year)
		return order;
	if (first->year < second->year)
		return order;
	return 0;
}
int CompareByPrice(Book* first, Book* second, int order)
{
	if (first->price > second->price)
		return order;
	if (first->price < second->price)
		return order;
	return 0;
}
int CompareByCategory(Book* first, Book* second, int order)
{
	if (first->category > second->category)
		return order;
	if (first->category < second->category)
		return order;
	return 0;
}


int CompareByMultiple(Book* first, Book* second, SortingData** sortingData, int size)
{
	for (int i = 0; i < size; i++)
	{
		int compareResult = COMPARISON_FUNCTION_STACK[sortingData[i]->field_id](first, second, sortingData[i]->order);
		if (compareResult != 0)
			return compareResult;
	}
	return 0;
}


//int CompareByAll(Book* first, Book* second)
//{
//	int authorCompareResult = CompareByAuthor(first, second);
//	if (authorCompareResult != 0)
//		return authorCompareResult;
//	int titleCompareResult = CompareByTitle(first, second);
//	if (titleCompareResult != 0)
//		return titleCompareResult;
//	int yearCompareResult = CompareByYear(first, second);
//	if (yearCompareResult != 0)
//		return yearCompareResult;
//	int priceCompareResult = CompareByPrice(first, second);
//	if (priceCompareResult != 0)
//		return priceCompareResult;
//	int categoryCompareResult = CompareByCategory(first, second);
//	if (categoryCompareResult != 0)
//		return categoryCompareResult;
//	return 0;
//}


//int CompareBooks(int (*compare_func)(Book*, Book*), Book* first, Book* second)
//{
//	return compare_func(first, second);
//}

//int (*FIELD_COMPARE_FUNCTION_STACK[])(Book*, Book*) = {};

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

const PREDIFINED_COMMANDS PREDIFINED_BOOK_COMMANDS;
const char* BACK_CHAR = "-";

const char* PRINT_PROMPTS[BOOK_TEXT_FILD_SIZE] = { "Enter author: ", "Enter title: ", "Enter publish year: ", "Enter price: ", "Enter category number: " };

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
	printf(" To cancel entering book data: type %s\n", PREDIFINED_BOOK_COMMANDS.EXIT_CHAR);
	printf(" To show this text again: type %s\n", PREDIFINED_BOOK_COMMANDS.HELP_CHAR);
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
	if (strcmp(input, PREDIFINED_BOOK_COMMANDS.EXIT_CHAR) == 0)
	{
		printf("Exiting from getting book data module\n\n\n");
		return ExitInput;
	}
	if (strcmp(input, PREDIFINED_BOOK_COMMANDS.HELP_CHAR) == 0)
	{
		PrintHelpInformation();
		return SkipIteration;
	}

	return ContinueCurrentIteration;
}

short CheckValidity(char* input, unsigned short& queuePosition, bool (*ifstatement)(char*), void (*print)(char*))
{
	bool wentBack = false;

	while (ifstatement(input))
	{
		print(input);
		printf(" Enter valid input, go back, or exit: ");
		scan(input);

		short workWithPrebuiltCommandsResult = WorkWithPrebuiltCommands(input, queuePosition);

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

void(*PRINT_FUNCTION_STACK[])(char*) = { PrintYearText, PrintPriceText, PrintCategoryText };

bool(*CHECK_FUNCTION_STACK[])(char*) = { CheckYearValidity, CheckPriceValidity, CheckCategoryValidity };

bool SetBookData(Book* book)
{
	printf("\n\n\n");
	printf("\t\t\tGETTING BOOK DATA FROM INPUT\n\t\t\t----------------------------");
	PrintHelpInformation();

	char buffer[BOOK_TEXT_FILD_SIZE];
	char* input = buffer;
	unsigned short queuePosition = 0;

	while (queuePosition != BOOK_STRUCT_FIELD_AMOUNT)
	{
		printf(PRINT_PROMPTS[queuePosition]);
		scan(input);

		short prebuiltCommandsResult = WorkWithPrebuiltCommands(input, queuePosition);

		if (prebuiltCommandsResult == SkipIteration)
			continue;
		else if (prebuiltCommandsResult == ExitInput)
			return false;

		if (queuePosition >= START_ITER_CHECK)
		{
			int validityCheckResult = CheckValidity(
				input, queuePosition, CHECK_FUNCTION_STACK[queuePosition - START_ITER_CHECK], PRINT_FUNCTION_STACK[queuePosition - START_ITER_CHECK]
			);

			if (validityCheckResult == 0)
				return false;
			if (validityCheckResult == -1)
				continue;
		}

		INPUT_FUNCTION_STACK[queuePosition](book, input);
		queuePosition++;
	}

	return true;
}
