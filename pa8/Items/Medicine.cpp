#include "Medicine.h"

// implemented code
Medicine::Medicine(int x, int y): Item(x, y) {}

Medicine::~Medicine() {}

void Medicine::triggered_by(Player& p) {
	if (is_valid()) {
		p.recover_hp(3);
		invalidate();
	}
}

string Medicine::get_item_str() const {
	return SYM_MEDICINE;
}
