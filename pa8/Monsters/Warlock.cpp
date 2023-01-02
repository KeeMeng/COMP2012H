#include "Warlock.h"

// skeleton code
Warlock::Warlock(int x, int y) : Monster(x, y)
{
	cur_hp = max_hp = 15;
	atk = 5, def = 1;
}


// implemented code
Warlock::~Warlock() {}

string Warlock::get_monster_str() const {
	string str = "W";
	if (cur_hp < 10) {
		str += '0';
		str += (cur_hp + '0');
	} else {
		str += (cur_hp / 10 + '0');
		str += (cur_hp % 10 + '0');
	}
	return str;
}

void Warlock::action(Player& p, MapUnit* map[][MAP_SIZE]) {
	int player_x = 0;
	int player_y = 0;
	p.get_position(player_x, player_y);
	int monster_x = x;
	int monster_y = y;
	int distance = abs(monster_x - player_x) + abs(monster_y - player_y);
	
	if (distance <= 1) {
		p.attacked_by(atk);
	}
	
	int surround_x = 0;
	int surround_y = 0;
	// create zombies in a 3x3 grid around warlock
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			surround_x = monster_x + i;
			surround_y = monster_y + j;
			
			if ((surround_x >= 0 && surround_x < MAP_SIZE && surround_y >= 0 && surround_y < MAP_SIZE) && // in map
				!(surround_x == player_x && surround_y == player_y) && // not player
				!(surround_x == monster_x && surround_y == monster_y) && // not warlock
				!(map[surround_x][surround_y]->is_blocked()) // is not blocked
				) {
				delete map[surround_x][surround_y];
				map[surround_x][surround_y] = new Zombie(surround_x, surround_y);
			}
		}
	}
}
