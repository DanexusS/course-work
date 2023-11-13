#pragma once
#include "book.h"
#include "library.h"

Book** SortBooks(Library* library, int (*Compare)(Book*, Book*), int order);

int CompareByAuthor(Book*, Book*);
int CompareByTitle(Book*, Book*);
int CompareByYear(Book*, Book*);
int CompareByPrice(Book*, Book*);
int CompareByCategory(Book*, Book*);
