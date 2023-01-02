#include "Mage.h"

// skeleton code
void Mage::level_up() {
	max_hp += 2;
	cur_hp = max_hp;
	atk += 2;
	def += 2;
	max_mp += 1;
	level += 1;
	max_exp += 2;
}


// implemented code
Mage::Mage(int x_, int y_, const string& name_): Player(x_, y_, name_) {
	atk = 4;
	def = 2;
	cur_hp = 15;
	max_hp = 15;
}

Mage::~Mage() {}

Role Mage::get_role() const {
	return Role::MAGE;
}

int Mage::get_range() const {
	return 2;
}

int Mage::skill(int& atk_, int& range) {
	if (cur_mp > 0) {
		cur_mp--;
		atk_ = atk * 2;
		range = 2;
		cur_hp += atk;
		// bug fix
		if (cur_hp > max_hp) {
			cur_hp = max_hp;
		}
		return 0;
	} else {
		return 1;
	}
}
