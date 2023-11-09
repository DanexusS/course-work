#pragma once
#include <iostream>
static enum Category
{
	Educational,
	PopularScientific,
	Scientific,
	Reference,
	Artistic
};





struct Book
{
	int _id;
	char* author;
	char* title;
	unsigned short year;
	float price;
	Category category;
};
static void SetAuthor(Book* book, char* string) 
{
	book->author = new char[strlen(string) + 1];
	strcpy(book->author, string);
}
static void SetTitle(Book* book, char* string) 
{
	book->title = new char[strlen(string) + 1];
	strcpy(book->title, string);
}
static void SetYear(Book* book, char* string) { book->year = atoi(string); }
static void SetPrice(Book* book, char* string) { book->price = atof(string); }
static void SetCategory(Book* book, char* string) { book->category = (Category)atoi(string); }

static const size_t BOOK_TEXT_FILD_SIZE = 100;

static const int BOOK_STRUCT_FIELD_AMOUNT = 5;

static const char* categoryTitles[5] = { "Educational", "Popular-Scientific", "Scientific", "Reference", "Artistic" };

static void(*INPUT_FUNCTION_STACK[])(Book*, char*) = { SetAuthor, SetTitle, SetYear, SetPrice, SetCategory };

int CompareBooks(Book*, Book*);

//static void SetBook(Book* book)
//{
//	book->author = new char[BOOK_TEXT_FILD_SIZE];
//	book->title = new char[BOOK_TEXT_FILD_SIZE];
//}

static void DeleteBook(Book* book)
{
	delete[] book->author;
	delete[] book->title;
	delete book;
}

bool SetBookData(Book*);





int CompareByAuthor(Book*, Book*);
int CompareByTitle(Book*, Book*);
int CompareByYear(Book*, Book*);
int CompareByPrice(Book*, Book*);
int CompareByCategory(Book*, Book*);
int CompareByAll(Book*, Book*);
