#include "input.h"
#include "output.h"
#include "generics.h"

void scan(const char* format, char* input) {
	scanf(format, input);
	getchar();
}

void scan_line(char* long_input) { scan("%[^\n]s\n", long_input); }

void scan_infinitely(
	char* long_input,
	const char* input_msg,
	bool (*error_condition)(const char*),
	const char* error_msg,
	const char* before_modifier,
	const char* after_modifier
) {
	char* label_to_check = new char[LONG_INPUT_BUFFER];

	while (true) {
		strcpy(label_to_check, before_modifier);

		printf(input_msg);
		scan_line(long_input);
		strcat(label_to_check, long_input);

		strcat(label_to_check, after_modifier);

		if (error_condition(label_to_check)) {
			DisplayErrorMessage(error_msg);
			continue;
		}
		break;
	}

	delete[] label_to_check;
}
void scan_infinitely(
	Library* library, 
	char* long_input, 
	const char* input_msg,
	bool (*error_condition)(Library*, const char*),
	const char* error_msg
) {
	while (true) {
		printf(input_msg);
		scan_line(long_input);

		if (error_condition(library, long_input)) {
			DisplayErrorMessage(error_msg);
			continue;
		}
		break;
	}
}

// WORK WITH FILES

void NextLiner(FILE* file) {
	char garbage_buffer[3];
	fgets(garbage_buffer, 2, file);
}

Picture* GetLogoData() {
	FILE* logo_file = fopen(".init/logo.txt", "r");
	Picture* logo = new Picture;

	fscanf(logo_file, "%d\n", &logo->height);

	logo->picture = new char* [logo->height];
	for (int i = 0; i < logo->height; i++) {
		char* logo_line = new char[100];

		fscanf(logo_file, "%[^\n]s\n", logo_line);
		logo->picture[i] = logo_line;
		NextLiner(logo_file);
	}

	return logo;
}

void GetBookDataFull(Library* library, char* full_location) {
	FILE* book_file = fopen(full_location, "r");
	Book* book = new Book;
	char* long_input = new char[LONG_INPUT_BUFFER];

#if defined _DEBUG
	printf("[DEBUG] Opening ./%s and reading information.\n", full_location);
#endif

	for (int i = 0; i < BOOK_STRUCT_FIELD_AMOUNT; i++) {
		fscanf(book_file, "%[^\n]s\n", long_input);
		INPUT_FUNCTION_STACK[i](book, long_input);
		NextLiner(book_file);
	}
	AddBook(library, book);

	fclose(book_file);
	delete[] long_input;
}

void GetBookData(Library* library, char* location) {
	char* data_string = new char[LONG_INPUT_BUFFER];
	strcpy(data_string, library->settings->books_folder);
	strcat(data_string, location);

	if (CheckFileLocation(data_string)) {
#if defined _DEBUG
		printf("%s [DEBUG] Book file ./%s is not found.%s\n", RED, data_string, RESET);
#endif

		return;
	}

	FILE* book_file = fopen(data_string, "r");
	Book* book = new Book;
	char* long_input = new char[LONG_INPUT_BUFFER];

#if defined _DEBUG
	printf("[DEBUG] Opening ./%s and reading information.\n", data_string);
#endif

	for (int i = 0; i < BOOK_STRUCT_FIELD_AMOUNT; i++) {
		fscanf(book_file, "%[^\n]s\n", long_input);
		INPUT_FUNCTION_STACK[i](book, long_input);
		NextLiner(book_file);
	}
	AddBook(library, book);
	
	fclose(book_file);
	delete[] data_string;
	delete[] long_input;
}

char* GetBookFolderData(FILE* file) {
	if (file == 0) return const_cast<char*>(DEFAULT_BOOKS_FOLDER);

	char* long_input = new char[LONG_INPUT_BUFFER];
	fscanf(file, "%s", long_input);

	if (CmpStr(DEFAULT_BOOKS_FOLDER, long_input) == 0 || strlen(long_input) == 0) {
		delete[] long_input;
		return const_cast<char*>(DEFAULT_BOOKS_FOLDER);
	}
	return long_input;
}

char* GetFilesDataNameData(FILE* file) {
	if (file == 0) return const_cast<char*>(DEFAULT_FILES_DATA_NAME);

	char* long_input = new char[LONG_INPUT_BUFFER];
	fscanf(file, "%s", long_input);

	if (CmpStr(DEFAULT_FILES_DATA_NAME, long_input) == 0 || strlen(long_input) == 0) {
		delete[] long_input;
		return const_cast<char*>(DEFAULT_FILES_DATA_NAME);
	}
	return long_input;
}

int* GetDefaultFunctionIdsData(FILE* file) {
	if (file == 0) return DEFAULT_DEFAULT_FUNCTION_IDS;

	char* long_input = new char[LONG_INPUT_BUFFER];
	fscanf(file, "%s", long_input);

	int long_input_len = strlen(long_input);
	
	if (long_input_len == 0 || long_input_len != 2 * CHOOSE_FUNCTIONS_AMOUNT - 1) {
#if defined _DEBUG
		if (long_input_len != 2 * CHOOSE_FUNCTIONS_AMOUNT - 1)
			printf("[DEBUG] Choose function amount line in settings config file is corrupted.\n");
#endif
		delete[] long_input;
		return DEFAULT_DEFAULT_FUNCTION_IDS;
	}

	int pos = 0;
	int return_array[CHOOSE_FUNCTIONS_AMOUNT];
	for (int i = 0; i < long_input_len; i++) {
		if (long_input[i] == ',') {
			return_array[pos] = atoi(&long_input[i - 1]);
			pos++;
		}
		if (i == long_input_len - 1) {
			return_array[pos] = atoi(&long_input[i]);
		}
	}

	delete[] long_input;
	return return_array;
}

void GetSettingsData(Library* library) {
#if defined _DEBUG
	if (CheckFileLocation(DEFAULT_SETTINGS_LOCATION))
		printf("[DEBUG] Settings file is not found. Using default settings.\n");
#endif

	FILE* settings_location_file = fopen(DEFAULT_SETTINGS_LOCATION, "r");

	library->settings = new LibrarySettings;
	library->settings->books_folder = new char[LONG_INPUT_BUFFER];
	library->settings->files_data_name = new char[LONG_INPUT_BUFFER];

	strcpy(library->settings->books_folder, GetBookFolderData(settings_location_file));
	strcpy(library->settings->files_data_name, GetFilesDataNameData(settings_location_file));
	int* default_command_ids = GetDefaultFunctionIdsData(settings_location_file);

	for (int i = 0; i < CHOOSE_FUNCTIONS_AMOUNT; i++)
		library->settings->default_command_ids[i] = default_command_ids[i];

	fclose(settings_location_file);
}

void GetLibraryData(Library* library) {
	int files_size = 0;
	char* long_input = new char[LONG_INPUT_BUFFER];

	GetSettingsData(library);

	char* library_location = new char[LONG_INPUT_BUFFER];
	strcpy(library_location, library->settings->books_folder);
	strcat(library_location, library->settings->files_data_name);

	if (CheckFileLocation(library_location)) {
#if defined _DEBUG
		printf("[DEBUG] There is no book data in specified in settings config folder. Skipping addition of books.\n");
#endif
		SetLibrary(library, files_size);
		return;
	}

	FILE* files_data_file = fopen(library_location, "r");

	fscanf(files_data_file, "%d\n", &files_size);
	SetLibrary(library, files_size);

	for (int i = 0; i < files_size; i++) {
		fscanf(files_data_file, "%[^\n]s\n", long_input);
		GetBookData(library, long_input);
		NextLiner(files_data_file);
	}

	fclose(files_data_file);
	delete[] long_input;
	delete[] library_location;
}
