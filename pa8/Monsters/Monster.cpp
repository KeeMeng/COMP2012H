#include "Monster.h"
#include <cmath>

// implemented code
Monster::Monster(int x, int y): MapUnit(x, y) {}

Monster::~Monster() {}

bool Monster::is_active() const {
	return active;
}

void Monster::set_active() {
	if (is_valid()) {
		active = true;
	}
}

void Monster::recover_hp(int hp) {
	cur_hp += hp;
	if (cur_hp > max_hp) {
		cur_hp = max_hp;
	}
}

UnitType Monster::get_unit_type() const {
	return UnitType::MONSTER;
}

bool Monster::is_blocked() const {
	if (is_valid()) {
		return true;
	} else {
		return false;
	}
}

int Monster::attacked_by(int atk_) {
	if (!is_valid()) {
		return 0;
	} else {
		int damage = atk_ - def;
		if (damage < 0) {
			return 0;
		} else {
			cur_hp -= damage;
			if (cur_hp <= 0) {
				invalidate();
				active = false;
				return 1;
			} else {
				return 0;
			}
		}
	}
}

string Monster::get_display_str() const {
	if (!is_valid()) {
		return SYM_EMPTY;
	} else {
		if (!is_discovered()) {
			return SYM_DANGER;
		} else {
			return get_monster_str();
		}
	}
}

void Monster::follow(const Player& p, MapUnit* map[][MAP_SIZE]) {
	int player_x = 0;
	int player_y = 0;
	p.get_position(player_x, player_y);
	int monster_x = x;
	int monster_y = y;
	int distance_x = monster_x - player_x;
	int distance_y = monster_y - player_y;
	int distance = abs(distance_x) + abs(distance_y);
	
	if (distance > 1) {
		bool left = (monster_x - 1) >= 0;
		bool right = (monster_x + 1) < MAP_SIZE;
		bool down = (monster_y - 1) >= 0;
		bool up = (monster_y + 1) < MAP_SIZE;
		
		if (left && distance_x > 0 && !map[monster_x - 1][monster_y]->is_blocked()) {
			monster_x--;
		} else if (right && distance_x < 0 && !map[monster_x + 1][monster_y]->is_blocked()) {
			monster_x++;
		} else if (down && distance_y > 0 && !map[monster_x][monster_y - 1]->is_blocked()) {
			monster_y--;
		} else if (up && distance_y < 0 && !map[monster_x][monster_y + 1]->is_blocked()) {
			monster_y++;
		} else {
			return;
		}
		// since function didn't return, monster moved
		// delete previous position
		delete map[monster_x][monster_y];
		map[monster_x][monster_y] = map[x][y];
		map[x][y] = new EmptyLand(x, y);
		// update monster current coordinates
		x = monster_x;
		y = monster_y;
	}
}
