#include "Player.h"

Player::Player(int x_, int y_, const string& name_) : x(x_), y(y_), name(name_) {}
Player::~Player() {}
string Player::get_name() const { return name; }
Direction Player::get_direction() const { return cur_dir; }
string Player::get_display_str() const {
	switch (cur_dir) {
		case Direction::UP:
			return "P^^";
			break;
		case Direction::DOWN:
			return "Pvv";
			break;
		case Direction::RIGHT:
			return "P>>";
			break;
		case Direction::LEFT:
			return "P<<";
			break;
		default:
			break;
	}
	return "   ";
}

void Player::get_position(int& x_, int& y_) const {
	x_ = x;
	y_ = y;
}
void Player::get_atk_def(int& atk_, int& def_) const {
	atk_ = atk;
	def_ = def;
}
void Player::get_hp(int& cur, int& max) const {
	cur = cur_hp;
	max = max_hp;
}
void Player::get_mp(int& cur, int& max) const {
	cur = cur_mp;
	max = max_mp;
}
void Player::get_exp(int& cur, int& max) const {
	cur = cur_exp;
	max = max_exp;
}
int Player::get_level() const { return level; }
bool Player::is_alive() const { return cur_hp > 0; }

void Player::move(Direction d, int step) {
	cur_dir = d;
	switch (d) {
		case Direction::UP:
			y += step;
			break;
		case Direction::DOWN:
			y -= step;
			break;
		case Direction::RIGHT:
			x += step;
			break;
		case Direction::LEFT:
			x -= step;
			break;
		default:
			break;
	}
}

void Player::recover_hp(int hp) {
	cur_hp += hp;
	if (cur_hp > max_hp) {
		cur_hp = max_hp;
	}
}

void Player::charge_mp() {
	if (cur_mp < max_mp) {
		cur_mp++;
	}
}

void Player::gain_exp(int exp) {
	cur_exp += exp;
	if (cur_exp >= max_exp) {
		cur_exp -= max_exp;
		level_up();
	}
}

void Player::attacked_by(int atk_) {
	int damage = atk_ - def;
	if (damage > 0) {
		cur_hp -= damage;
	}
}
