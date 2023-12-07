#pragma once
#include <cstdio>
#include <iostream>

#include "book.h"
#include "library.h"
#include "generics.h"

bool CheckFolderLocation(const char* folder_location);
bool CheckFileLocation(const char* file_location);

void scan_line(char* long_input);
void scan_infinitely(
	char* long_input,
	const char* input_msg,
	bool (*error_condition)(const char*),
	const char* error_msg,
	const char* before_modifier = "",
	const char* after_modifier = ""
);
void scan_infinitely(
	Library* library,
	char* long_input,
	const char* input_msg,
	bool (*error_condition)(Library*, const char*),
	const char* error_msg
);

Picture* GetLogoData();
void GetBookData(Library* library, char* location);
void GetBookDataFull(Library* library, char* location);
void GetLibraryData(Library* library);
