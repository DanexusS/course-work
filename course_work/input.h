#pragma once
#include <cstdio>
#include <iostream>

#include "book.h"
#include "library.h"

struct Logo {
	char** picture;
	int height;
};

static void DeleteLogo(Logo* logo) {
	for (int i = 0; i < logo->height; i++)
		delete[] logo->picture[i];
	delete[] logo->picture;
	delete logo;
}

void scan_char(char* input);
void scan_line(char* input);

Logo* GetLogoData();
void GetBookData(Library* library, char* location);
void GetLibraryData(Library* library);
