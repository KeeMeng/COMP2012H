#include <iostream>
using namespace std;

// Constants (These can be editable and the program will still work
const int FIRST_YEAR = 1800;
const int LAST_YEAR = 9999;
const int MONTHS_IN_YEAR = 12;
const int DAYS_IN_WEEK = 7;
const int CALENDAR_WIDTH = 3 * DAYS_IN_WEEK + 1;
const int DAYS_IN_MONTH[MONTHS_IN_YEAR] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const char MONTH_NAMES[MONTHS_IN_YEAR][10] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const char WEEKDAY_NAMES[DAYS_IN_WEEK][3] = { "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" };


bool IsLeapYear(int year) {
	// Divisible by four true, divisible by 100 false, divisible by 400 true
	if (year % 400 == 0) {
		return true;
	} else if (year % 100 == 0) {
		return false;
	} else if (year % 4 == 0) {
		return true;
	} else {
		return false;
	}
}

int FirstWeekday(int year, int month) {
	// 436 leap years before 1800
	int initial_leap_years = FIRST_YEAR/4 - FIRST_YEAR/100 + FIRST_YEAR/400;
	int total_leap_years = (year-1)/4 - (year-1)/100 + (year-1)/400;
	
	int days_in_year = 0;
	for (int i = 0; i < MONTHS_IN_YEAR; i++) {
		days_in_year += DAYS_IN_MONTH[i];
	}
	// Days passed since 1800 including leap days
	int days_passed = ((year - FIRST_YEAR) * days_in_year) + (total_leap_years - initial_leap_years);
	for (int i = 0; i < month; i++) {
		days_passed += DAYS_IN_MONTH[i];
	}
	if (IsLeapYear(year) && month > 1) {
		days_passed++;
	}
	
	// Jan 1 1800 is Wednesday (3)
	return (days_passed + 3) % DAYS_IN_WEEK;
}

void cout_spaces(int n) {
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
}

int len(const char text[]) {
	int length = 0;
	for (; text[length] != '\0'; length++);
	return length;
}

void cout_triple_calendar(int center_year, int center_month, bool cout_year = false) {
	// A is previous month, B is inputted month, C is next month
	const int A_YEAR = center_year - (center_month == 0) + (center_month / MONTHS_IN_YEAR);
	const int B_YEAR = center_year + (center_month / MONTHS_IN_YEAR);
	const int C_YEAR = center_year + (center_month + 1 == MONTHS_IN_YEAR) + (center_month / MONTHS_IN_YEAR);
	
	const int A_MONTH = (center_month - 1 + MONTHS_IN_YEAR) % MONTHS_IN_YEAR;;
	const int B_MONTH = center_month % MONTHS_IN_YEAR;
	const int C_MONTH = (center_month + 1) % MONTHS_IN_YEAR;
	
	const int A_FIRST_WEEKDAY = FirstWeekday(A_YEAR, A_MONTH);
	const int B_FIRST_WEEKDAY = FirstWeekday(B_YEAR, B_MONTH);
	const int C_FIRST_WEEKDAY = FirstWeekday(C_YEAR, C_MONTH);
	
	// Month 1 is February
	const int A_DAYS = DAYS_IN_MONTH[A_MONTH] + (IsLeapYear(A_YEAR) && A_MONTH == 1);
	const int B_DAYS = DAYS_IN_MONTH[B_MONTH] + (IsLeapYear(B_YEAR) && B_MONTH == 1);
	const int C_DAYS = DAYS_IN_MONTH[C_MONTH] + (IsLeapYear(C_YEAR) && C_MONTH == 1);
	const int DAYS[3] = { A_DAYS, B_DAYS, C_DAYS };
	
	const int A_ROWS = ((A_FIRST_WEEKDAY + A_DAYS) / DAYS_IN_WEEK) + ((A_FIRST_WEEKDAY + A_DAYS) % DAYS_IN_WEEK != 0);
	const int B_ROWS = ((B_FIRST_WEEKDAY + B_DAYS) / DAYS_IN_WEEK) + ((B_FIRST_WEEKDAY + B_DAYS) % DAYS_IN_WEEK != 0);
	const int C_ROWS = ((C_FIRST_WEEKDAY + C_DAYS) / DAYS_IN_WEEK) + ((C_FIRST_WEEKDAY + C_DAYS) % DAYS_IN_WEEK != 0);
	const int ROWS[3] = { A_ROWS, B_ROWS, C_ROWS };
	
	if (cout_year) {
		// Minus 5 as "MONTH YEAR" has 5 more characters than "MONTH"
		cout << MONTH_NAMES[A_MONTH] << " " << A_YEAR;
		cout_spaces(CALENDAR_WIDTH - 5 - len(MONTH_NAMES[A_MONTH]));
		cout << MONTH_NAMES[B_MONTH] << " " << B_YEAR;
		cout_spaces(CALENDAR_WIDTH - 5 - len(MONTH_NAMES[B_MONTH]));
		cout << MONTH_NAMES[C_MONTH] << " " << C_YEAR << "\n";
	} else {
		cout << MONTH_NAMES[A_MONTH];
		cout_spaces(CALENDAR_WIDTH - len(MONTH_NAMES[A_MONTH]));
		cout << MONTH_NAMES[B_MONTH];
		cout_spaces(CALENDAR_WIDTH - len(MONTH_NAMES[B_MONTH]));
		cout << MONTH_NAMES[C_MONTH] << "\n";
	}
	
	// "Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa\n"
	for (int i = 0; i < 3 * DAYS_IN_WEEK; i++) {
		cout << WEEKDAY_NAMES[i % DAYS_IN_WEEK];
		if ((i + 1) / DAYS_IN_WEEK < 3) {
			if ((i + 1) % DAYS_IN_WEEK == 0) {
				cout << " ";
			}
			cout << " ";
		}
	}
	cout << "\n";
	
	int biggest_row = 0;
	for (int i = 0; i < 3; i++) {
		if (ROWS[i] >= biggest_row) {
			biggest_row = ROWS[i];
		}
	}
	int day_counters[3] = { 1 - A_FIRST_WEEKDAY, 1 - B_FIRST_WEEKDAY, 1 - C_FIRST_WEEKDAY };
	
	for (int row = 1; row <= biggest_row; row++) {
		for (int cal = 0; cal < 3; cal++) {
			if (cal != 0) {
				// Add space before new calendar
				cout << "  ";
			}
			for (int col = 1; col <= DAYS_IN_WEEK; col++) {
				if (col != 1) {
					cout << " ";
				}
				if (day_counters[cal] <= 0 || day_counters[cal] > DAYS[cal]) {
					cout << "  ";
				} else {
					if (day_counters[cal] < 10) {
						cout << " " << day_counters[cal];
					} else {
						cout << day_counters[cal];
					}
				}
				day_counters[cal]++;
			}
		}
		cout << "\n";
	}
	cout << "\n";
}


int main() {
	// Task 1
	// Validate year
	int year;
	do {
		cout << "Enter year (in range " << FIRST_YEAR << "-" << LAST_YEAR << "): ";
		cin >> year;
	} while (year < FIRST_YEAR || year > LAST_YEAR);
	
	// Validate month
	int month;
	do {
		cout << "Enter month (in range 1-" << MONTHS_IN_YEAR << "): ";
		cin >> month;
	} while (!((month >= 1 && month <= MONTHS_IN_YEAR) || month == -1 || month == -3));
	
	if (month >= 1 && month <= MONTHS_IN_YEAR) {
		// Decrease month so that it has the same index as MONTH_NAMES
		month--;
		
		// Validate s or m
		char week_start_day;
		do {
			cout << "Enter the first day of week ('s' for Sunday, 'm' for Monday): ";
			cin >> week_start_day;
		} while (week_start_day != 's' && week_start_day != 'm');
		
		// Validate h or v
		char direction;
		do {
			cout << "Print horizontally (h) or vertically (v): ";
			cin >> direction;
		} while (direction != 'h' && direction != 'v');
		
		cout << MONTH_NAMES[month] << " " << year << "\n";
		
		int days = DAYS_IN_MONTH[month] + (IsLeapYear(year) && month == 1);
		int weekday = FirstWeekday(year, month);
		
		// "Su Mo Tu We Th Fr Sa" or "Mo Tu We Th Fr Sa Su"
		int start;
		if (week_start_day == 's') {
			// Task 2
			start = 0;
		} else {
			// Task 3
			start = 1;
		}
		int end = start + DAYS_IN_WEEK;
		
		if (direction == 'h') {
			for (int i = start; i < end - 1; i++) {
				cout << WEEKDAY_NAMES[i] << " ";
			}
			cout << WEEKDAY_NAMES[(end - 1) % DAYS_IN_WEEK] << "\n";
			
			int day_count = 1;
			for (int date = (1 - weekday + start); date <= days; date++, day_count++) {
				if (date <= 0) {
					cout << "   ";
				} else {
					if (date < 10) {
						cout << " " << date;
					} else {
						cout << date;
					}
					
					if (day_count < DAYS_IN_WEEK && date != days) {
						cout << " ";
						// No whitespace for last date
					} else {
						day_count = 0;
						cout << "\n";
					}
				}
			}
		} else if (direction == 'v') {
			for (int line = start; line < end; line++) {
				cout << WEEKDAY_NAMES[line % DAYS_IN_WEEK];
				// for (int date = (1 - weekday + line); date <= days; date += 7) {
				// MISTAKE!
				for (int date = (1 - weekday + line - 7*(start == 1 && weekday == 0)); date <= days; date += 7) {
					if (date <= 0) {
						cout << "   ";
					} else if (date < 10) {
						cout << "  " << date;
					} else {
						cout << " " << date;
					}
				}
				cout << "\n";
			}
		}
		
	} else if (month == -1) {
		// Bonus task 1
		cout << "Year " << year << "\n";
		for (int row = 0; row < MONTHS_IN_YEAR; row += 3) {
			// Output 3 months in a row 4 times to get 12 months
			cout_triple_calendar(year, row + 1);
		}
	
	} else if (month == -3) {
		// Bonus task 2
		int center_month;
		do {
			cout << "Enter the month in the center (in range 1-" << MONTHS_IN_YEAR << "): ";
			cin >> center_month;
		} while (!(center_month >= 1 && center_month <= MONTHS_IN_YEAR) || (center_month == 1 && year == FIRST_YEAR) || (center_month == MONTHS_IN_YEAR && year == LAST_YEAR));
		
		// Output 3 months in a row
		cout_triple_calendar(year, center_month - 1, true);
	}
	cout << endl;
	
	return 0;
}
