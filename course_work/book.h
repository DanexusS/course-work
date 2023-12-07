#pragma once
#include <iostream>

static const char BACK_CHAR = '-';
static const char* BOOK_CATEGORY_TITLES[5] = { "Educational", "Popular-Scientific", "Scientific", "Reference", "Artistic" };

static const int BOOK_STRUCT_FIELD_AMOUNT = 5;
static const int BOOK_CATEGORY_AMOUNT = (sizeof(BOOK_CATEGORY_TITLES) / sizeof(*BOOK_CATEGORY_TITLES));

static enum Category {
	Educational,
	PopularScientific,
	Scientific,
	Reference,
	Artistic
};

struct Book {
	int _id;
	char* author;
	char* title;
	unsigned short year;
	float price;
	Category category;
};

static void DeleteBook(Book* book) {
	delete[] book->author;
	delete[] book->title;
	delete book;
}

static void SetAuthor(Book* book, char* string) {
	int length = strlen(string) + 1;

	book->author = new char[length];
	strcpy(book->author, string);
}
static void SetTitle(Book* book, char* string) {
	int length = strlen(string) + 1;

	book->title = new char[length];
	strcpy(book->title, string);
}
static void SetYear(Book* book, char* string) { book->year = atoi(string); }
static void SetPrice(Book* book, char* string) { book->price = atof(string); }
static void SetCategory(Book* book, char* string) { book->category = (Category)atoi(string); }

bool SetBookData(Book* book, char* long_input);

static void(*INPUT_FUNCTION_STACK[])(Book*, char*) = { SetAuthor, SetTitle, SetYear, SetPrice, SetCategory };
