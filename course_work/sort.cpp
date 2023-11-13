#include "book.h"
#include "library.h"

int CompareStrings(char** first, char** second) {
	while (*first == *second && *first != "\0" && *second != "\0") {
		first++;
		second++;
	}

	int difference = *first - *second;

	if (difference < -1)
		return -1;
	if (difference > 1)
		return 1;
	return 0;
}
int CompareByAuthor(Book* first_book, Book* second_book) { return CompareStrings(&first_book->author, &second_book->author); }
int CompareByTitle(Book* first_book, Book* second_book) { return CompareStrings(&first_book->title, &second_book->title); }

int CompareByYear(Book* first_book, Book* second_book) {
	if (first_book->year > second_book->year)
		return 1;
	if (first_book->year < second_book->year)
		return -1;
	return 0;
}
int CompareByPrice(Book* first_book, Book* second_book) {
	if (first_book->price > second_book->price)
		return 1;
	if (first_book->price < second_book->price)
		return -1;
	return 0;
}
int CompareByCategory(Book* first_book, Book* second_book) {
	if (first_book->category > second_book->category)
		return 1;
	if (first_book->category < second_book->category)
		return -1;
	return 0;
}

Book** SortBooks(Library* library, int (*Compare)(Book*, Book*), int order) {
	Book** sorted_books = library->books;

	for (int i = 0; i < library->size - 1; i++) {
		bool b = false;
		for (int j = 0; j < library->size - i - 1; j++) {
			Book* curBook = sorted_books[j];
			Book* nextBook = sorted_books[j + 1];
			if (order * (*Compare)(curBook, nextBook) > 0) {
				Book* temp = curBook;

				sorted_books[j] = nextBook;
				sorted_books[j + 1] = temp;

				b = true;
			}
		}
		if (!b)
			break;
	}

	return sorted_books;
}
