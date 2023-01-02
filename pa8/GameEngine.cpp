#include "GameEngine.h"
using namespace std;

// skeleton code
void GameEngine::print_active_monsters() {
	int i = 0;
	cout << "Active Monsters:" << endl;
	MonsterNode* cur = head;
	while (cur != nullptr) {
		cout << cur->data->get_display_str();
		cout << "@(" << cur->data->get_x();
		cout << "," << cur->data->get_y() << "), ";
		cur = cur->next;
		i++;
		if (i == 4) {
			i = 0;
			cout << endl;
		}
	}
}

bool GameEngine::player_win() const {
	int px, py;
	player->get_position(px, py);
	if (px == MAP_SIZE - 1 && py == MAP_SIZE - 1) {
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				if (map[i][j]->get_unit_type() == UnitType::MONSTER && map[i][j]->is_valid()) {
					return false;
				}
			}
		}
		return true;
	} else {
		return false;
	}
}

GameEngine::GameEngine() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (i > 8 && i < 12 && j > 2 && j < 6) {
				map[i][j] = new Wall(i, j);
			} else if (i > 14 && i < 18 && j > 2 && j < 6) {
				map[i][j] = new Grass(i, j);
			} else if (i > 2 && i < 6 && j == 9) {
				map[i][j] = new Gem(i, j, GemType::RUBY);
			} else if (i > 2 && i < 6 && j == 10) {
				map[i][j] = new Gem(i, j, GemType::EMERALD);
			} else if (i > 2 && i < 6 && j == 11) {
				map[i][j] = new Gem(i, j, GemType::SAPPHIRE);
			} else if (i > 8 && i < 12 && j > 8 && j < 12) {
				map[i][j] = new Book(i, j);
			} else if (i > 14 && i < 18 && j > 8 && j < 12) {
				map[i][j] = new Medicine(i, j);
			} else if (i > 2 && i < 6 && j > 14 && j < 18) {
				map[i][j] = new Zombie(i, j);
			} else if (i > 8 && i < 12 && j > 14 && j < 18) {
				map[i][j] = new Warlock(i, j);
			} else if (i > 14 && i < 18 && j > 14 && j < 18) {
				map[i][j] = new ShadowPriest(i, j);
			} else {
				map[i][j] = new EmptyLand(i, j);
			}
		}
	}
}

char GameEngine::input() {
	char c;
	cin >> c;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.clear();
	return c;
}

void GameEngine::run() {
	string name;
	cout << "Please enter your name:" << endl;
	cin >> name;
	cout << "Please choose your role:" << endl;
	cout << "1 Warrior" << endl;
	cout << "2 Archer" << endl;
	cout << "3 Mage" << endl;

	int x = 0, y = 0;
	char role = input();
	switch (role) {
		case '1':
			create_player(x, y, name, Role::WARRIOR);
			break;
		case '2':
			create_player(x, y, name, Role::ARCHER);
			break;
		case '3':
			create_player(x, y, name, Role::MAGE);
			break;
		default:
			exit(0);
			break;
	}
	ui.refresh(this->map, *player);

	while (true) {
		switch (input()) {
			case 'w':
				this->player_move(Direction::UP);
				break;
			case 'a':
				this->player_move(Direction::LEFT);
				break;
			case 's':
				this->player_move(Direction::DOWN);
				break;
			case 'd':
				this->player_move(Direction::RIGHT);
				break;
			case 'h':
				this->player_attack();
				break;
			case 'j':
				this->player_skill();
				break;
			default:
				break;
		}
		if (player_win()) {
			cout << endl;
			cout << "You win." << endl;
			break;
		}
		player_discover();
		activate_monsters();
		monster_follow();
		monster_act();
		ui.refresh(this->map, *player);
		print_active_monsters();
		if (!player->is_alive()) {
			cout << endl;
			cout << "You lose." << endl;
			break;
		}
	}
}


// implemented code
GameEngine::~GameEngine() {
	delete player;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			delete map[i][j];
		}
	}
	
	if (head != nullptr) {
		MonsterNode* node = head;
		MonsterNode* next_node = head;
		while (next_node != nullptr) {
			next_node = node->next;
			delete node;
			node = next_node;
		}
	}
}

void GameEngine::create_player(int x, int y, const string& name, Role role) {
	if (role == Role::WARRIOR) {
		player = new Warrior(x, y, name);
	} else if (role == Role::ARCHER) {
		player = new Archer(x, y, name);
	} else if (role == Role::MAGE) {
		player = new Mage(x, y, name);
	}
}

void GameEngine::activate_monster(Monster* monster) {
	if (monster->is_valid() && !monster->is_active()) {
		monster->set_active();
		MonsterNode* node = new MonsterNode();
		node->data = monster;
		node->next = head;
		head = node;
	}
}

void GameEngine::activate_monsters() {
	int player_x = 0;
	int player_y = 0;
	player->get_position(player_x, player_y);
	
	int surround_x = 0;
	int surround_y = 0;
	// find monsters in a 3x3 grid around player
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			surround_x = player_x + i;
			surround_y = player_y + j;
			if ((surround_x >= 0 && surround_x < MAP_SIZE && surround_y >= 0 && surround_y < MAP_SIZE) && // in map
				!(surround_x == player_x && surround_y == player_y) && // not player
				(map[surround_x][surround_y]->get_unit_type() == UnitType::MONSTER) // is monster
				) {
				activate_monster(dynamic_cast<Monster*>(map[surround_x][surround_y]));
			}
		}
	}
}

void GameEngine::deactivate_monster(const Monster* const monster) {
	if (head == nullptr) {
		return;
	} else if (head->data == monster) {
		delete head;
		head = nullptr;
	} else {
		MonsterNode* node = head;
		MonsterNode* prev_node = head;
		while (node->data != monster) {
			if (node == nullptr) {
				return;
			}
			prev_node = node;
			node = node->next;
		}
		prev_node->next = node->next;
		delete node;
	}
}

void GameEngine::player_move(Direction d) {
	int player_x = 0;
	int player_y = 0;
	player->get_position(player_x, player_y);
	
	bool destination_valid = false;
	switch (d) {
		case Direction::UP:
			if (player_y + 1 < MAP_SIZE && !map[player_x][player_y + 1]->is_blocked()) {
				player_y++;
				destination_valid = true;
			}
			break;
		case Direction::DOWN:
			if (player_y - 1 >= 0 && !map[player_x][player_y - 1]->is_blocked()) {
				player_y--;
				destination_valid = true;
			}
			break;
		case Direction::LEFT:
			if (player_x - 1 >= 0 && !map[player_x - 1][player_y]->is_blocked()) {
				player_x--;
				destination_valid = true;
			}
			break;
		case Direction::RIGHT:
			if (player_x + 1 < MAP_SIZE && !map[player_x + 1][player_y]->is_blocked()) {
				player_x++;
				destination_valid = true;
			}
			break;
	}
	
	if (destination_valid) {
		player->move(d, 1);
		map[player_x][player_y]->triggered_by(*player);
	} else {
		player->move(d, 0);
	}
}

void GameEngine::player_discover() {
	int player_x = 0;
	int player_y = 0;
	player->get_position(player_x, player_y);
	
	int surround_x = 0;
	int surround_y = 0;
	// find mapunits in a 5x5 grid around player
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			surround_x = player_x + i;
			surround_y = player_y + j;
			if ((surround_x >= 0 && surround_x < MAP_SIZE && surround_y >= 0 && surround_y < MAP_SIZE) && // in map
				!(surround_x == player_x && surround_y == player_y) // not player
				) {
				map[surround_x][surround_y]->set_discovered();
			}
		}
	}
}

void GameEngine::player_attack() {
	int x, y, atk, def;
	player->get_position(x, y);
	player->get_atk_def(atk, def);
	int range = player->get_range();
	
	for (int i = 0; i < range; i++) {
		// attack in direction range times
		switch (player->get_direction()) {
			case Direction::UP:
				y++;
				break;
			case Direction::DOWN:
				y--;
				break;
			case Direction::LEFT:
				x--;
				break;
			case Direction::RIGHT:
				x++;
				break;
		}
		if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
			// attack map unit
			int value = map[x][y]->attacked_by(atk);
			
			if (map[x][y]->get_unit_type() == UnitType::MONSTER) {
				if (value > 0) {
					deactivate_monster(dynamic_cast<Monster*>(map[x][y]));
					player->gain_exp(1);
				} else {
					if (map[x][y]->is_valid() && !dynamic_cast<Monster*>(map[x][y])->is_active()) {
						activate_monster(dynamic_cast<Monster*>(map[x][y]));
					}
				}
			}
		}
	}
}

void GameEngine::player_skill() {
	int x, y, atk, def;
	player->get_position(x, y);
	player->get_atk_def(atk, def);
	int range = player->get_range();
	
	if (player->skill(atk, range) != 1) {
		for (int i = 0; i < range; i++) {
			// attack in direction range times
			switch (player->get_direction()) {
				case Direction::UP:
					y++;
					break;
				case Direction::DOWN:
					y--;
					break;
				case Direction::LEFT:
					x--;
					break;
				case Direction::RIGHT:
					x++;
					break;
			}
			if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
				// attack map unit
				int value = map[x][y]->attacked_by(atk);
				
				if (map[x][y]->get_unit_type() == UnitType::MONSTER) {
					if (value > 0) {
						deactivate_monster(dynamic_cast<Monster*>(map[x][y]));
						player->gain_exp(1);
					} else {
						if (map[x][y]->is_valid() && !dynamic_cast<Monster*>(map[x][y])->is_active()) {
							activate_monster(dynamic_cast<Monster*>(map[x][y]));
						}
					}
				}
			}
		}
	}
}

void GameEngine::monster_follow() {
	for (MonsterNode* node = head; node != nullptr; node = node->next) {
		node->data->follow(*player, map);
	}
}

void GameEngine::monster_act() {
	for (MonsterNode* node = head; node != nullptr; node = node->next) {
		node->data->action(*player, map);
	}
}
