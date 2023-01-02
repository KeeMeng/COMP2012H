#include <iostream>
using namespace std;

// some constraints for board
const int MAX_ROW = 15, MAX_COL = 15;
const int MAX_CONSTRAINT_NUM = 15;  // constraint cannot exceed MAX_ROW/MAX_COL

// board and its size
int num_rows = 0, num_cols = 0;
char board[MAX_ROW][MAX_COL] = {{0}};

// constraints and their sizes
int num_row_constraints[MAX_ROW] = {0}, num_col_constraints[MAX_COL] = {0};
int row_constraints[MAX_ROW][MAX_CONSTRAINT_NUM] = {{0}};
int col_constraints[MAX_COL][MAX_CONSTRAINT_NUM] = {{0}};

/**********************************
 * Part 1: Initialize the board   *
 **********************************/

/**
 **********  Task 1  **********
 * 
 * This function reads the board size and constraints from user input,
 * store the information in global variables and init the board.
 * 
 * Don't forget to check whether row/column constraints are valid.
 * Please refer to webpage for a detailed description.
 *
 * For simplicity, we assume the user's other inputs are always valid.
 */
void get_input_board() {
	// START YOUR CODES HERE
	cout << "Enter the number of rows: ";
	cin >> num_rows;
	
	cout << "Enter the number of columns: ";
	cin >> num_cols;
	
	for (int row = 0; row < num_rows; row++) {
		cout << "Enter the number of constraints for row " << row << " (end with -1): ";
		int sum = -1;
		int temp;
		int constraint_count = 0;
		while (true) {
			cin >> temp;
			if (temp != -1) {
				// Add to row_constraints
				row_constraints[row][constraint_count++] = temp;
				sum += 1 + temp;
			} else {
				if (sum > num_cols || constraint_count > num_cols) {
					// Invalid
					cout << "Invalid row constraint, please try again." << endl;
					cout << "Enter the number of constraints for row " << row << " (end with -1): ";
					sum = -1;
					constraint_count = 0;
				} else {
					// Valid
					for (int i = constraint_count; i < MAX_COL; i++) {
						row_constraints[row][i] = 0;
					}
					break;
				}
			}
		}
		num_row_constraints[row] = constraint_count;
	}
	
	for (int col = 0; col < num_cols; col++) {
		cout << "Enter the number of constraints for column " << col << " (end with -1): ";
		int sum = -1;
		int temp;
		int constraint_count = 0;
		while (true) {
			cin >> temp;
			if (temp != -1) {
				// Add to col_constraints
				col_constraints[col][constraint_count++] = temp;
				sum += 1 + temp;
			} else {
				if (sum > num_rows || constraint_count > num_rows) {
					// Invalid
					cout << "Invalid column constraint, please try again." << endl;
					cout << "Enter the number of constraints for column " << col << " (end with -1): ";
					sum = -1;
					constraint_count = 0;
				} else {
					// Valid
					for (int i = constraint_count; i < MAX_ROW; i++) {
						col_constraints[col][i] = 0;
					}
					break;
				}
			}
		}
		num_col_constraints[col] = constraint_count;
	}
	
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {
			board[i][j] = '.';
		}
	}
	// END YOUR CODES HERE
}


/**
 **********  Task 2  **********
 *
 * This function prints the board and the constraints for each row and column.
 * Constraints should be printed on the bottom of each column and on the left of each row.
 *
 * You may find an example in webpage.
 */
void cout_spaces(const int n) {
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
}

void print_board() {
	// START YOUR CODES HERE
	
	int max_num_row_constraints = 0;
	for (int i = 0; i < num_rows; i++) {
		if (num_row_constraints[i] > max_num_row_constraints) {
			max_num_row_constraints = num_row_constraints[i];
		}
	}
	
	int max_num_col_constraints = 0;
	for (int i = 0; i < num_cols; i++) {
		if (num_col_constraints[i] > max_num_col_constraints) {
			max_num_col_constraints = num_col_constraints[i];
		}
	}
	
	// First row with alphabets
	cout_spaces(2 * max_num_row_constraints + 4);
	for (int i = 0; i < num_cols; i++) {
		cout << " " << (char)('A' + i);
	}
	cout << "\n";
	
	// Start printing rows
	for (int row = 0; row < num_rows; row++) {
		// Print row constraints
		cout_spaces(2 * (max_num_row_constraints - num_row_constraints[row]));
		for (int j = 0; j < num_row_constraints[row]; j++) {
			cout << row_constraints[row][j] << " ";
		}
		cout << "| ";
		
		// Print board
		if (row < 10) {
			cout << " " << row;
		} else {
			cout << row;
		}
		
		for (int col = 0; col < num_cols; col++) {
			cout << " " << board[row][col];
		}
		cout << "\n";
	}
	
	for (int line = 0; line < max_num_col_constraints; line++) {
		cout_spaces(2 * max_num_row_constraints + 4);
		for (int col = 0; col < num_cols; col++) {
			if (col_constraints[col][line]) {
				cout << " " << col_constraints[col][line];
			} else {
				cout << "  ";
			}
			
		}
		cout << "\n";
	}
	
	// END YOUR CODES HERE
}


/********************************
 * Part 2: User play on board   *
 ********************************/

/**
 **********  Task 3  **********
 *
 * This function will be called when user choose to set/unset a cell. 
 *
 * You need to:
 * 1. Ask user to input which cell he/she wants to modify
 * 2. Check if the user input is a valid cell(i.e., it is within the board)
 *    If invalid, keep asking the user to input.
 * 3. Set/unset the cell
 * 4. Print the new board
 */
void user_operate_board() {
	// START YOUR CODES HERE
	
	char letter;
	int row;
	int col;
	while (true) {
		cout << "Enter the cell you want to modify (e.g. A 2): ";
		cin >> letter;
		cin >> row;
		col = letter - 'A';
		
		if (row >= 0 && row < num_rows && col >= 0 && col < num_cols) {
			break;
		} else {
			cout << "Invalid row or column. Try again." << endl;
		}
	}
	
	// Toggle cell
	if (board[row][col] == '.') {
		board[row][col] = 'X';
	} else {
		board[row][col] = '.';
	}
	
	// END YOUR CODES HERE
}


/**
 **********  Task 4  **********
 *
 * This function will be called after user finish filling the whole board.
 * You need to check whether his/her solution is correct, 
 * i.e., follow all constraints.
 *
 * Return true if his/her solution is correct; false otherwise.
 */
bool check_whole_board_valid() {
	// START YOUR CODES HERE
	
	// Check row constraints
	for (int row = 0; row < num_rows; row++) {
		int temp_row_constraint_count = 0;
		int temp_row_constraint = 0;
		bool coloured = false;
		for (int col = 0; col < num_cols; col++) {
			if (board[row][col] == 'X') {
				temp_row_constraint++;
				coloured = true;
				if (temp_row_constraint > row_constraints[row][temp_row_constraint_count]) {
					break;
				}
			} else {
				if (coloured) {
					if (temp_row_constraint == row_constraints[row][temp_row_constraint_count]) {
						temp_row_constraint_count++;
						temp_row_constraint = 0;
						if (temp_row_constraint_count > num_row_constraints[row]) {
							return false;
						}
					} else {
						return false;
					}
					coloured = false;
				}
			}
		}
		if (coloured) {
			temp_row_constraint_count++;
		}
		if (temp_row_constraint_count != num_row_constraints[row]) {
			return false;
		}
	}
	
	// Check col constraints
	for (int col = 0; col < num_cols; col++) {
		int temp_col_constraint_count = 0;
		int temp_col_constraint = 0;
		bool coloured = false;
		for (int row = 0; row < num_rows; row++) {
			if (board[row][col] == 'X') {
				temp_col_constraint++;
				coloured = true;
				if (temp_col_constraint > col_constraints[col][temp_col_constraint_count]) {
					break;
				}
			} else {
				if (coloured) {
					if (temp_col_constraint == col_constraints[col][temp_col_constraint_count]) {
						temp_col_constraint_count++;
						temp_col_constraint = 0;
						if (temp_col_constraint_count > num_col_constraints[col]) {
							return false;
						}
					} else {
						return false;
					}
					coloured = false;
				}
			}
		}
		if (coloured) {
			temp_col_constraint_count++;
		}
		if (temp_col_constraint_count != num_col_constraints[col]) {
			return false;
		}
	}
	
	return true;
	
	// END YOUR CODES HERE
}


/*******************************
 * Part 3: A nonogram solver   *
 *******************************/

/**
 **********  Task 5  **********
 *
 * This function coverts a position vector of a row into a real row.
 * 
 * For example, if num_col = 8, position vector = {0, 3, 5}, 
 * row_constraint for this row is {2, 1, 1}, then the row should be:
 * [X X . X . X . .]
 * It will store the result row in variable 'result_row[]'
 *
 * You may assume the parameters given are always valid.
 */
void positions_to_row(int row_idx, const int positions[], int num_pos, char result_row[]) {
	// START YOUR CODES HERE
	for (int i = 0; i < num_cols; i++) {
		result_row[i] = '.';
	}
	
	for (int pos_index = 0; pos_index < num_pos; pos_index++) {
		for (int i = 0; i < row_constraints[row_idx][pos_index]; i++) {
			result_row[positions[pos_index] + i] = 'X';
		}
	}
	
	// END YOUR CODES HERE
}


/**
 **********  Task 6  **********
 * 
 * This function checks if the given block on given row can be shifted right
 * for one cell. 
 * For example, if the position vector is {0, 4, 6}, num_col = 8, constraints are {2, 1, 1}
 * then the row is: [X X . . X . X .], and there are 3 blocks
 * then block_can_shift(row_idx, 0, {0, 4, 6}) = true, 
 *      block_can_shift(row_idx, 1, {0, 4, 6}) = false, since it will hit 2nd block after shift
 *      block_can_shift(row_idx, 2, {0, 4, 6}) = true.
 * 
 * More details can be found on webpage.
 */
bool block_can_shift(int row_idx, int block_idx, const int positions[], int num_pos) {
	// START YOUR CODES HERE
	
	if (block_idx == num_pos - 1) {
		// Last block
		if (positions[block_idx] + row_constraints[row_idx][block_idx] < num_cols) {
			return true;
		} else {
			return false;
		}
	} else {
		if (positions[block_idx] + row_constraints[row_idx][block_idx] + 1 < positions[block_idx + 1]) {
			return true;
		} else {
			return false;
		}
	}
	
	// END YOUR CODES HERE
}

// this array stores all valid permutations for each row
// it's expected that num of permutations for each row should not exceed 2^(num_cols)
const int MAX_PERM = 1 << MAX_COL;     // A way to calculate 2^(num_cols)
char row_perms[MAX_ROW][MAX_PERM][MAX_COL];
// this array stores num of permutations for each row
int num_row_perms[MAX_ROW] = {0};


/**
 **********  Task 7  **********
 * 
 * This function gets all valid permutations for a row, 
 * and store all results in global variables 'row_perms' and 'num_row_perms'.
 * 
 * Hint: You may use recursion to do that, with the help of helper functions
 * 'block_can_shift()', etc.
 * 
 */

void row_recursive_shift(const int row_idx, const int shift_block, const int (&temp_positions)[MAX_CONSTRAINT_NUM], const int num_pos) {
	
	int positions[MAX_CONSTRAINT_NUM] = {0};
	for (int i = 0; i < num_pos; i++) {
		positions[i] = temp_positions[i];
	}
	if (shift_block != -1) {
		positions[shift_block]++;
	}
	
	char result_row[MAX_COL];
	positions_to_row(row_idx, positions, num_pos, result_row);
	for (int i = 0; i < num_cols; i++) {
		row_perms[row_idx][num_row_perms[row_idx]][i] = result_row[i];
	}
	
	num_row_perms[row_idx]++;
	
	bool adjacent = true;
	// for (int block_idx = 0; block_idx < num_pos; block_idx++) {
	for (int block_idx = num_pos - 1; block_idx >= 0; block_idx--) {
		if (block_idx != num_pos - 1) {
			if (block_can_shift(row_idx, block_idx, positions, num_pos) && positions[block_idx] + row_constraints[row_idx][block_idx] + 2 == positions[block_idx + 1] && adjacent) {
				row_recursive_shift(row_idx, block_idx, positions, num_pos);
			}
			if (adjacent && (positions[block_idx] + row_constraints[row_idx][block_idx] + 1 != positions[block_idx + 1])) {
				adjacent = false;
			}
		} else if (block_can_shift(row_idx, block_idx, positions, num_pos)) {
			row_recursive_shift(row_idx, block_idx, positions, num_pos);
		}
	}
}

void get_row_perms(int row_idx) {
	// START YOUR CODES HERE
	
	// Start with all groups left aligned
	// Shift the largest group right by 1, then 2...
	// Shift the second largest group as much as possible by using block_can_shift to check
	// Use recursion to shift the largest group in the current branch and repeat
	// Use positions_to_row to add positions to global variable row_perms
	
	
	// Create base case positions array with left shifted values
	int positions[MAX_CONSTRAINT_NUM] = {0};
	int num_pos = num_row_constraints[row_idx];
	for (int i = 0; i < num_pos - 1; i++) {
		positions[i + 1] = row_constraints[row_idx][i] + positions[i] + 1;
	}
	
	row_recursive_shift(row_idx, -1, positions, num_pos);
	
	
	// END YOUR CODES HERE
}



// COLUMN VERSION
void positions_to_col(int col_idx, const int positions[], int num_pos, char result_col[]) {
	for (int i = 0; i < num_rows; i++) {
		result_col[i] = '.';
	}
	
	for (int pos_index = 0; pos_index < num_pos; pos_index++) {
		for (int i = 0; i < col_constraints[col_idx][pos_index]; i++) {
			result_col[positions[pos_index] + i] = 'X';
		}
	}
}

bool col_block_can_shift(int col_idx, int block_idx, const int positions[], int num_pos) {
	if (block_idx == num_pos - 1) {
		// Last block
		if (positions[block_idx] + col_constraints[col_idx][block_idx] < num_rows) {
			return true;
		} else {
			return false;
		}
	} else {
		if (positions[block_idx] + col_constraints[col_idx][block_idx] + 1 < positions[block_idx + 1]) {
			return true;
		} else {
			return false;
		}
	}
}

char col_perms[MAX_COL][MAX_PERM][MAX_ROW];
int num_col_perms[MAX_COL] = {0};


void col_recursive_shift(const int col_idx, const int shift_block, const int (&temp_positions)[MAX_CONSTRAINT_NUM], const int num_pos) {
	
	int positions[MAX_CONSTRAINT_NUM] = {0};
	for (int i = 0; i < num_pos; i++) {
		positions[i] = temp_positions[i];
	}
	if (shift_block != -1) {
		positions[shift_block]++;
	}
	
	char result_col[MAX_ROW];
	positions_to_col(col_idx, positions, num_pos, result_col);
	for (int i = 0; i < num_rows; i++) {
		col_perms[col_idx][num_col_perms[col_idx]][i] = result_col[i];
	}
	
	num_col_perms[col_idx]++;
	
	bool adjacent = true;
	// for (int block_idx = 0; block_idx < num_pos; block_idx++) {
	for (int block_idx = num_pos - 1; block_idx >= 0; block_idx--) {
		if (block_idx != num_pos - 1) {
			if (col_block_can_shift(col_idx, block_idx, positions, num_pos) && positions[block_idx] + col_constraints[col_idx][block_idx] + 2 == positions[block_idx + 1] && adjacent) {
				col_recursive_shift(col_idx, block_idx, positions, num_pos);
			}
			if (adjacent && (positions[block_idx] + col_constraints[col_idx][block_idx] + 1 != positions[block_idx + 1])) {
				adjacent = false;
			}
		} else if (col_block_can_shift(col_idx, block_idx, positions, num_pos)) {
			col_recursive_shift(col_idx, block_idx, positions, num_pos);
		}
	}
}

void get_col_perms(int col_idx) {
	// Create base case positions array with left shifted values
	int positions[MAX_CONSTRAINT_NUM] = {0};
	int num_pos = num_col_constraints[col_idx];
	for (int i = 0; i < num_pos - 1; i++) {
		positions[i + 1] = col_constraints[col_idx][i] + positions[i] + 1;
	}
	
	col_recursive_shift(col_idx, -1, positions, num_pos);
}


/**
 **********  Task 8  **********
 * 
 * This function checks if current state is valid, after 
 * we finish filling 'num_complete_rows' rows.
 *
 * For example, if num_complete_rows = 2, it will only check
 * if the first two rows (with index 0 and 1) do not 
 * break column constraints.
 *
 * Note that this function is different from 'check_whole_board_valid()'
 * in 2 ways:
 * 1. We don't check whole board here, only check the first 'num_complete_rows' rows.
 * 2. We don't (need to) check row_constraints here, only check column_constraints.
 *    This is because this function will only be called during solver, 
 *    so the rows are generated in permutation process, which must be valid.
 */
bool check_rows_valid(int num_complete_rows) {
	// START YOUR CODES HERE
	
	// Check col constraints
	for (int col = 0; col < num_cols; col++) {
		int temp_constraint_count = 0;
		int temp_constraint = 0;
		bool coloured = false;
		for (int row = 0; row < num_complete_rows; row++) {
			if (board[row][col] == 'X') {
				temp_constraint++;
				coloured = true;
				if (temp_constraint > col_constraints[col][temp_constraint_count]) {
					return false;
				}
			} else {
				if (coloured) {
					if (temp_constraint == col_constraints[col][temp_constraint_count]) {
						temp_constraint_count++;
						temp_constraint = 0;
						if (temp_constraint_count > num_col_constraints[col]) {
							return false;
						}
					} else {
						return false;
					}
					coloured = false;
				}
			}
		}
		if (temp_constraint > col_constraints[col][temp_constraint_count]) {
			return false;
		}
		if (coloured) {
			temp_constraint_count++;
		}
		if (temp_constraint_count > num_col_constraints[col]) {
			return false;
		}
	}
	
	return true;

	// END YOUR CODES HERE
}


/**
 **********  Task 9  **********
 * 
 * This function will solve the board, and store the solution
 * into board[][] directly.
 * 
 * Hint: You may use recursion to do that, with the help of helper functions
 * 'get_row_perms()', â€˜check_rows_valid()â€™, etc.
 */
void solve() {
	// START YOUR CODES HERE
	
	// Generate all perms
	for (int i = 0; i < num_rows; i++) {
		get_row_perms(i);
	}
	
	for (int i = 0; i < num_cols; i++) {
		get_col_perms(i);
	}
	
	// for (int x = 0; x < num_rows; x++) {
	// 	cout << "line: " << x << endl;
	// 	for (int i = 0; i < num_col_perms[x]; i++) {
	// 		cout << col_perms[x][i] << endl;
	// 	}
	// }
	
	
	
	// Filter some permutations
	// If the row only has 1 constraint which is longer than half of the row length, then you can fill some cells in the middle
	bool always_coloured_row[MAX_ROW][MAX_COL];
	bool always_coloured_col[MAX_ROW][MAX_COL];
	
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			always_coloured_row[row][col] = true;
			always_coloured_col[row][col] = true;
		}
	}
	
	for (int row = 0; row < num_rows; row++) {
		for (int index = 0; index < num_row_perms[row]; index++) {
			for (int col = 0; col < num_cols; col++) {
				if (row_perms[row][index][col] == '.') {
					always_coloured_row[row][col] = false;
				}
			}
		}
	}
	
	for (int col = 0; col < num_cols; col++) {
		for (int index = 0; index < num_col_perms[col]; index++) {
			for (int row = 0; row < num_rows; row++) {
				if (col_perms[col][index][row] == '.') {
					always_coloured_col[row][col] = false;
				}
			}
		}
	}
	
	int count = 0;
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			if (always_coloured_row[row][col] || always_coloured_col[row][col]) {
				for (int index = 0; index < num_row_perms[row]; index++) {
					if (row_perms[row][index][col] == '.') {
						row_perms[row][index][0] = '0';
						count++;
					}
				}
			}
		}
	}
	
	// Debug stuff
	// for (int row = 0; row < num_rows; row++) {
	// 	for (int col = 0; col < num_cols; col++) {
	// 		cout << always_coloured_row[row][col] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	
	// for (int row = 0; row < num_rows; row++) {
	// 	for (int col = 0; col < num_cols; col++) {
	// 		cout << always_coloured_col[row][col] << " ";
	// 	}
	// 	cout << endl;
	// }
	
	// cout << count << endl;
	
	
	int row = 0;
	int current_perm[MAX_ROW] = {0};
	// int groups_size[MAX_COL][MAX_CONSTRAINT_NUM] = {{0}};
	// int current_group[MAX_COL] = {0};
	// int counter = 0;
	while (true) {
		// Put row into board
		// for (int col = 0; col < num_cols; col++) {
		// 	board[row][col] = row_perms[row][current_perm[row]][col];
		// }
		
		
		bool valid = true;
		
		// for (int col = 0; col < num_cols; col++) {
		// 	if (row_perms[row][current_perm[row]][col] == 'X') {
		// 		groups_size[col][current_group[col]]++;
				
		// 		if (groups_size[col][current_group[col]] > col_constraints[col][current_group[col]]) {
		// 			valid = false;
		// 			// break;
		// 		}
				
		// 		if (row == num_rows - 1) {
		// 			current_group[col]++;
		// 		}
				
		// 		if (current_group[col] > num_col_constraints[col]) {
		// 			valid = false;
		// 			// break;
		// 		}
		// 	} else if (row != 0) {
		// 		if (row_perms[row - 1][current_perm[row - 1]][col] == 'X') {
		// 			if (groups_size[col][current_group[col]] != col_constraints[col][current_group[col]]) {
		// 				valid = false;
		// 				// break;
		// 			}
					
		// 			current_group[col]++;
		// 			if (current_group[col] > num_col_constraints[col]) {
		// 				valid = false;
		// 				// break;
		// 			}
		// 		}
		// 	}
		// }
		
		if (row_perms[row][current_perm[row]][0] == '0') {
			valid = false;
		} else {
			for (int col = 0; col < num_cols; col++) {
				int temp_constraint_count = 0;
				int temp_constraint = 0;
				bool coloured = false;
				for (int line = 0; line <= row; line++) {
					if (row_perms[line][current_perm[line]][col] == 'X') {
						temp_constraint++;
						coloured = true;
						if (temp_constraint > col_constraints[col][temp_constraint_count]) {
							valid = false;
							break;
						}
					} else {
						if (coloured) {
							if (temp_constraint == col_constraints[col][temp_constraint_count]) {
								temp_constraint_count++;
								temp_constraint = 0;
								if (temp_constraint_count > num_col_constraints[col]) {
									valid = false;
									break;
								} else if (temp_constraint_count < num_col_constraints[col]){
									int sum = -1;
									for (int i = temp_constraint_count; i < num_col_constraints[col]; i++) {
										sum += col_constraints[col][i] + 1;
									}
									if (line + sum >= num_rows) {
										valid = false;
										break;
									}
								}
								
								
								
							} else {
								valid = false;
								break;
							}
							coloured = false;
						}
					}
				}
				if (!valid) {
					break;
				}
				if (temp_constraint > col_constraints[col][temp_constraint_count]) {
					valid = false;
					break;
				}
				if (coloured) {
					temp_constraint_count++;
				}
				if (temp_constraint_count > num_col_constraints[col]) {
					valid = false;
					break;
				}
			}
		}
		
		
		if (valid) {
			// counter++;
			row++;
			if (row == num_rows) {
				break;
			}
		} else {
			while (true) {
				// Opposite of above
				// for (int col = 0; col < num_cols; col++) {
				// 	if (row_perms[row][current_perm[row]][col] == 'X') {
				// 		if (row == num_rows - 1) {
				// 			current_group[col]--;
				// 		}
				// 		groups_size[col][current_group[col]]--;
						
				// 	} else if (row != 0) {
				// 		if (row_perms[row - 1][current_perm[row - 1]][col] == 'X') {
				// 			current_group[col]--;
				// 		}
				// 	}
				// }
				
				// Increase permutation, or backtrack to previous row
				current_perm[row]++;
				if (current_perm[row] == num_row_perms[row]) {
					current_perm[row--] = 0;
					
				} else {
					break;
				}
			}
		}	
	}
	
	// Add valid permutations to board
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			board[row][col] = row_perms[row][current_perm[row]][col];
		}
	}
	// cout << "Counter: " << counter << endl;
	
	// END YOUR CODES HERE
}


int main() {
	get_input_board();
	print_board();
	
	

	while (true) {
		cout << "===== Welcome to Nonogram Game =====" << endl;
		cout << "Please enter your choice:" << endl;
		cout << "Enter 'p' to print the current board." << endl;
		cout << "Enter 'm' to modify a cell." << endl;
		cout << "Enter 'c' to check your solution." << endl;
		cout << "Enter 's' to invoke solver." << endl;
		cout << "Enter 'q' to quit." << endl;
		cout << "Your choice: ";
		char input;
		cin >> input;
		if (input == 'p') {
			print_board();
		} else if (input == 'm') {
			user_operate_board();
		} else if (input == 'c') {
			if (check_whole_board_valid()) {
				cout << "Congratulations! Your solution is correct!" << endl;
			} else {
				cout << "Ahh, your solution is incorrect, try again." << endl;
			}
		} else if (input == 's') {
			cout << "Generating solution:" << endl;
			solve();
			print_board();
		} else if (input == 'q') {
			cout << "Bye!" << endl;
			break;
		} else {
			cout << "Invalid input. Try again." << endl;
		}
	}
	return 0;
}