#pragma once
#include <iostream>

static const int BOOK_STRUCT_FIELD_AMOUNT = 5;
static const char* CATEGORY_TITLES[5] = { "Educational", "Popular-Scientific", "Scientific", "Reference", "Artistic" };

static enum Category {
	Educational,
	PopularScientific,
	Scientific,
	Reference,
	Artistic
};

struct Book {
	char* author;
	char* title;
	unsigned short year;
	float price;
	Category category;
};

static void SetAuthor(Book* book, char* string) {
	book->author = new char[strlen(string) + 1];
	strcpy(book->author, string);
}
static void SetTitle(Book* book, char* string) {
	book->title = new char[strlen(string) + 1];
	strcpy(book->title, string);
}
static void SetYear(Book* book, char* string) { book->year = atoi(string); }
static void SetPrice(Book* book, char* string) { book->price = atof(string); }
static void SetCategory(Book* book, char* string) { book->category = (Category)atoi(string); }

static void DeleteBook(Book* book) {
	delete[] book->author;
	delete[] book->title;
	delete book;
}

bool SetBookData(Book*);

int CompareBooks(Book*, Book*);
int CompareByAuthor(Book*, Book*);
int CompareByTitle(Book*, Book*);
int CompareByYear(Book*, Book*);
int CompareByPrice(Book*, Book*);
int CompareByCategory(Book*, Book*);

static void(*INPUT_FUNCTION_STACK[])(Book*, char*) = { SetAuthor, SetTitle, SetYear, SetPrice, SetCategory };
