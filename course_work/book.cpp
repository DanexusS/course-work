#include "book.h"
#include "input.h"
#include "output.h"
#include "generics.h"

const int START_ITER_CHECK = 2;
const char* PRINT_PROMPTS[BOOK_STRUCT_FIELD_AMOUNT] = { "Enter author: ", "Enter title: ", "Enter publish year: ", "Enter price: ", "Enter category number: " };

bool CheckIsNumber(char* input) {
	int i = 0;
	bool wasDot = false;

	if (input[0] == '-')
		i = 1;

	for (; input[i] != '\0'; i++)
		if (input[i] == '.') {
			if (wasDot)
				return false;
			wasDot = true;
		}
		else if (!isdigit(input[i]))
			return false;

	return true;
}
bool CheckYearValidity(char* year) { return !CheckIsNumber(year) || atoi(year) < 1056; }
bool CheckPriceValidity(char* price) { return !CheckIsNumber(price) || atof(price) < 0; }
bool CheckCategoryValidity(char* category) { return !CheckIsNumber(category) || (atoi(category) < 0 || atoi(category) > CATEGORY_AMOUNT - 1); }

static enum ReturnResults {
	ExitInput,
	SkipIteration,
	ContinueCurrentIteration
};

ReturnResults WorkWithPrebuiltCommands(char* input, unsigned short& iter) {
	switch (*input)
	{
	case BACK_CHAR: {
		if (iter == 0)
			printf("   You are at the begining of the input queue, no need to go back.\n\n");
		else {
			printf("\n");
			printf("   Returning to the previous position in input queue\n\n");
			iter--;
		}

		return SkipIteration;
	}
	case EXIT_CHAR:
		printf("Exiting from getting book data module\n\n\n");
		return ExitInput;
	case HELP_CHAR:
		DisplayBookInputHelpMessage();
		return SkipIteration;
	default:
		break;
	}

	return ContinueCurrentIteration;
}

int CheckValidity(char* input, unsigned short& queuePosition, bool (*ifstatement)(char*), void (*print)(char*))
{
	bool wentBack = false;

	while (ifstatement(input)) {
		print(input);
		printf(" Enter valid input, go back, or exit: ");
		scan_line(input);

		ReturnResults workWithPrebuiltCommandsResult = WorkWithPrebuiltCommands(input, queuePosition);

		if (workWithPrebuiltCommandsResult == SkipIteration) {
			wentBack = true;
			break;
		}
		else if (workWithPrebuiltCommandsResult == ExitInput)
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
	DisplayBookInputHelpMessage();

	char* input = new char[1000];
	unsigned short queuePosition = 0;

	while (queuePosition != BOOK_STRUCT_FIELD_AMOUNT) {
		printf(PRINT_PROMPTS[queuePosition]);
		scan_line(input);

		short prebuiltCommandsResult = WorkWithPrebuiltCommands(input, queuePosition);

		if (prebuiltCommandsResult == SkipIteration)
			continue;
		else if (prebuiltCommandsResult == ExitInput)
			return false;

		if (queuePosition >= START_ITER_CHECK) {
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

	delete[] input;
	return true;
}
