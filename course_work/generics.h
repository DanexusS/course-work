#pragma once
static const int LONG_INPUT_BUFFER = 1000;

static const int CHOOSE_FUNCTIONS_AMOUNT = 4;

static const char* DEFAULT_SETTINGS_LOCATION = ".init/settings.txt";

static const char* DEFAULT_COMMAND_DISPLAY[][2] = { {"Normal", "Sorted"}, {"Single", "Range"}, {"Single", "Multiple"}, {"Default folder", "User's folder"} };

static const char* DEFAULT_BOOKS_FOLDER = "data/";
static const char* DEFAULT_FILES_DATA_NAME = "files_data.txt";
static int DEFAULT_DEFAULT_FUNCTION_IDS[CHOOSE_FUNCTIONS_AMOUNT] = { 0, 0, 0, 0 };
static const int SETTINGS_FIELD_AMOUNT = 4;

static const char SETTINGS_CHAR = '\\';
static const char DEFAULT_CHAR = ' ';
static const char EXIT_CHAR = '`';
static const char HELP_CHAR = '?';
static const char CLEAR_CHAR = '#';

struct Picture {
	char** picture;
	int height;
};

static void DeleteLogo(Picture* picture) {
	for (int i = 0; i < picture->height; i++)
		delete[] picture->picture[i];
	delete[] picture->picture;
	delete picture;
}

struct LibrarySettings {
	char* books_folder;
	char* files_data_name;

	int default_command_ids[CHOOSE_FUNCTIONS_AMOUNT];
};

static void DeleteLibrarySettings(LibrarySettings* settings) {
	delete[] settings->books_folder;
	delete[] settings->files_data_name;
	delete settings;
}

int CmpStr(const char* first, const char* second);
