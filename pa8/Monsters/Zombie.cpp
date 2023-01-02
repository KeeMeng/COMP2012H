#include "Zombie.h"

// skeleton code
Zombie::Zombie(int x, int y) : Monster(x, y)
{
	cur_hp = max_hp = 20;
	atk = 9, def = 3;
}


// implemented code
Zombie::~Zombie() {}

string Zombie::get_monster_str() const {
	string str = "Z";
	if (cur_hp < 10) {
		str += '0';
		str += (cur_hp + '0');
	} else {
		str += (cur_hp / 10 + '0');
		str += (cur_hp % 10 + '0');
	}
	return str;
}

void Zombie::action(Player& p, MapUnit* map[][MAP_SIZE]) {
	int player_x = 0;
	int player_y = 0;
	p.get_position(player_x, player_y);
	int monster_x = x;
	int monster_y = y;
	int distance = abs(monster_x - player_x) + abs(monster_y - player_y);
	
	if (distance <= 1) {
		p.attacked_by(atk);
	}
}
