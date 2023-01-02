#include "Book.h"

// implemented code
Book::Book(int x, int y): Item(x, y) {}

Book::~Book() {}

void Book::triggered_by(Player& p) {
	if (is_valid()) {
		p.gain_exp(3);
		invalidate();
	}
}

string Book::get_item_str() const {
	return SYM_BOOK;
}
