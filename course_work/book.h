#pragma once

static const size_t BOOK_TEXT_FILD_SIZE = 100;

static const int BOOK_STRUCT_FIELD_AMOUNT = 5;

static const char* categoryTitles[5] = { "Educational", "Popular-Scientific", "Scientific", "Reference", "Artistic" };

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
	char* author;
	char* title;
	unsigned short year;
	float price;
	Category category;
};

static void SetBook(Book* book)
{
	book->author = new char[BOOK_TEXT_FILD_SIZE];
	book->title = new char[BOOK_TEXT_FILD_SIZE];
}

static void DeleteBook(Book* book)
{
	delete[] book->author;
	delete[] book->title;
	delete book;
}

// 4.
void DisplayBook(Book*);

// 5.
bool SetBookData(Book*);
