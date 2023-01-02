#include "GameUI.h"
#ifdef _WIN32 // In Windows
#define CLEAR "cls"
#else // In any other OS
#define CLEAR "clear"
#endif

string GameUI::format_status_column(const string& prefix, const string& value) {
	int pad = (UI_WIDTH - 2) / 2 - prefix.length() - value.length();
	string s = "";
	return s + prefix + value + string(pad, ' ');
}

string GameUI::format_status_string(const string& lvalue, const string& rvalue) {
	int lpad = MAX_DIGITS - lvalue.length();
	int rpad = MAX_DIGITS - rvalue.length();
	string s;
	return s + string(lpad, ' ') + lvalue + " / " + string(rpad, ' ') + rvalue;
}

void GameUI::refresh_status(Player& p) {
	Role role = p.get_role();
	string role_str;

	switch (role) {
		case Role::ARCHER:
			role_str = "Archer";
			break;
		case Role::WARRIOR:
			role_str = "Warrior";
			break;
		case Role::MAGE:
			role_str = "Mage";
			break;

		default:
			break;
	}

	int atk, def;
	int cur_hp, max_hp;
	int cur_mp, max_mp;
	int cur_exp, max_exp;
	int level;

	p.get_atk_def(atk, def);
	p.get_hp(cur_hp, max_hp);
	p.get_mp(cur_mp, max_mp);
	p.get_exp(cur_exp, max_exp);
	level = p.get_level();

	status_lines[0] = "=";
	status_lines[0] += this->format_status_column(NAME_STR, p.get_name());
	status_lines[0] += this->format_status_column(ROLE_STR, role_str);
	status_lines[0] += "=";

	string hp = this->format_status_string(to_string(cur_hp), to_string(max_hp));
	status_lines[1] = "=";
	status_lines[1] += this->format_status_column(HP_STR, hp);
	status_lines[1] += this->format_status_column(ATK_STR, to_string(atk));
	status_lines[1] += "=";

	string mp = this->format_status_string(to_string(cur_mp), to_string(max_mp));
	status_lines[2] = "=";
	status_lines[2] += this->format_status_column(WPC_STR, mp);
	status_lines[2] += this->format_status_column(DFS_STR, to_string(def));
	status_lines[2] += "=";

	string exp = this->format_status_string(to_string(cur_exp), to_string(max_exp));
	status_lines[3] = "=";
	status_lines[3] += this->format_status_column(EXP_STR, exp);
	status_lines[3] += this->format_status_column(LVL_STR, to_string(level));
	status_lines[3] += "=";
}

void GameUI::show_borderline() const {
	for (int i = 0; i < UI_WIDTH; i++)
		cout << "=";
	cout << endl;
}

void GameUI::show_status() const {
	show_borderline();
	for (int i = 0; i < 4; i++) {
		cout << status_lines[i] << endl;
	}
	show_borderline();
}

void GameUI::refresh_map(MapUnit* map[][MAP_SIZE], Player& p) {
	int x, y;
	p.get_position(x, y);
	int east = x + 9;
	int west = x - 9;
	int north = y + 3;
	int south = y - 3;

	int idx = 0;

	for (int j = north; j >= south; j--) {
		// iterate the y coordinate of map from north to south
		if (j > 9 || j < 0) {
			map_lines[idx] = "";
		} else {
			map_lines[idx] = " ";
		}
		map_lines[idx] += to_string(j);
		map_lines[idx] += "| ";
		for (int i = west; i <= east; i++) {
			// iterate the x coordinate of map from west to east
			if (i < 0 || i >= MAP_SIZE || j < 0 || j >= MAP_SIZE) {
				map_lines[idx] += "XXX";
			} else if (i != x || j != y) {
				map_lines[idx] += map[i][j]->get_display_str();
			} else {
				// print user's location
				map_lines[idx] += p.get_display_str(); 
			}
			// print the right-most boundary
			map_lines[idx] += LIGHT_VERTICAL; 
		}
		idx++;
		map_lines[idx] = "  |";
		idx++;
	}

	map_lines[idx] = "   ";
	map_lines[idx + 1] = "   ";

	for (int i = west; i < east + 1; i++) {
		map_lines[idx] += "----";
		if (i > 9 || i < 0) {
			map_lines[idx + 1] += "  ";
		} else {
			map_lines[idx + 1] += "   ";
		}
		map_lines[idx + 1] += to_string(i);
	}
}

void GameUI::show_map() const {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		cout << map_lines[i] << '\n';
	}
}

void GameUI::show_control() const {
	cout << "Move: W/A/S/D, Attack: H, Skill:J, press Enter to confirm." << endl;
}

void GameUI::clear() const {
	system(CLEAR);
	cout << endl;
}

void GameUI::refresh(MapUnit* map[][MAP_SIZE], Player& p) {
	refresh_status(p);
	refresh_map(map, p);
	clear();
	cout << endl;
	show_status();
	show_map();
	show_control();
}
