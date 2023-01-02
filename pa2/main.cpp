#include <iostream>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX_STRLEN = 1000;
const int NUM_CHARS_PER_LINE = 50;
const int MAX_LINES = 15;

int countCharacters(const char str[]);
int countWords(const char str[]);
int countNumOccurences(const char str[], const char target[]);

void swapString(char str[], const char target[], const char to[]);
void encryptText(char str[], int shift);

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE]);
void printRightJustified(const char str[]);
void printLeftJustified(const char str[]);

void convertStrToPigLatin(char word[]);
void printPigLatin(const char str[]);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// You codes start here. Please do not modify codes above
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++

// My custom functions

void cout_spaces(const int n) {
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
}

// void flush_buffer(char words[MAX_STRLEN][NUM_CHARS_PER_LINE], char buffer[NUM_CHARS_PER_LINE], int& buffer_count, int& word_index) {
// 	for (int i = 0; i < buffer_count; i++) {
// 		words[word_index][i] = buffer[i];
// 	}
// 	words[word_index++][buffer_count] = '\0';
// 	buffer_count = 0;
// }

int convertIntoWords(const char str[], char words[MAX_STRLEN][MAX_STRLEN]) {
	int word_index = 0;
	int buffer_count = 0;
	char buffer[MAX_STRLEN];
	bool is_word = !(str[0] == ',' || str[0] == '.' || str[0] == ' ');
	
	// auto is only used for this lambda expression
	// flush_buffer(words, buffer, buffer_count, word_index) can be used instead, but looks more messy
	auto flush_buffer = [&] {
		for (int i = 0; i < buffer_count; i++) {
			words[word_index][i] = buffer[i];
		}
		words[word_index++][buffer_count] = '\0';
		buffer_count = 0;
	};
	
	for (int char_index = 0; str[char_index] != '\0'; char_index++) {
		if (str[char_index] == ',' || str[char_index] == '.' || str[char_index] == ' ') {
			// Character is non-word
			if (is_word){
				// Character is new non-word
				is_word = false;
				flush_buffer();
			}
		} else {
			// Character is word
			if (!is_word) {
				// Character is new word
				is_word = true;
				flush_buffer();
			}
		}
		buffer[buffer_count++] = str[char_index];
	}
	// Last buffer flush
	flush_buffer();
	
	return word_index;
}

// Skeleton code functions below

int countCharacters(const char str[]) {
	int characters = 0;
	for (; str[characters] != '\0'; characters++);
	return characters;
}

int countWords(const char str[]) {
	int words = 0;
	bool is_word = false;
	for (int char_index = 0; str[char_index] != '\0'; char_index++) {
		if (str[char_index] == ',' || str[char_index] == '.' || str[char_index] == ' ') {
			// Character is non-word
			if (is_word) {
				// Character is new non-word
				is_word = false;
			}
		} else {
			// Character is word
			if (!is_word) {
				// Character is new word
				is_word = true;
				words++;
			}
		}
	}
	
	return words;
}

void swapString(char str[], const char target[], const char to[]) {
	bool swap;
	int temp_index = 0;
	char temp_str[MAX_STRLEN];
	int to_length = countCharacters(to);
	int target_length = countCharacters(target);
	
	for (int char_index = 0; str[char_index] != '\0';) {
		swap = true;
		for (int target_index = 0; target_index < target_length; target_index++) {
			// Break loop if substring doesn't match
			if (!(str[char_index + target_index] == target[target_index])) {
				swap = false;
				break;
			}
		}
		if (swap) {
			for (int to_index = 0; to_index < to_length; to_index++) {
				temp_str[temp_index++] = to[to_index];
			}
			char_index += target_length;
		} else {
			temp_str[temp_index++] = str[char_index++];
		}
	}
	temp_str[temp_index++] = '\0';

	// Copy over to str
	for (int i = 0; i < temp_index; i++) {
		str[i] = temp_str[i];
	}
}

void encryptText(char str[], int shift) {
	shift = ((shift % 26) + 26) % 26;
	if (shift) {
		for (int char_index = 0; str[char_index] != '\0'; char_index++) {
			if (str[char_index] >= 'a' && str[char_index] <= 'z') {
				str[char_index] = (str[char_index] - 'a' + shift) % 26 + 'a';
			} else if (str[char_index] >= 'A' && str[char_index] <= 'Z'){
				str[char_index] = (str[char_index] - 'A' + shift) % 26 + 'A';
			}
		}
	}
}

int countNumOccurences(const char str[], const char target[]) {
	bool occur;
	int occurences = 0;
	int target_length = countCharacters(target);
	
	for (int char_index = 0; str[char_index] != '\0';) {
		occur = true;
		for (int target_index = 0; target_index < target_length; target_index++) {
			if (!(str[char_index + target_index] == target[target_index])) {
				occur = false;
				break;
			}
		}
		if (occur) {
			char_index += target_length;
			occurences++;
		} else {
			char_index++;
		}
	}
	
	return occurences;
}

void convertIntoLines(const char str[], char lines[MAX_LINES][NUM_CHARS_PER_LINE]) {
	// Convert string into words, punctuations are also counted as a seperate word
	char words[MAX_STRLEN][MAX_STRLEN];
	int total_words = convertIntoWords(str, words);
	
	
	// Add words to lines
	int line = 0;
	int length = 0;
	int word_length = 0;
	int rtrim_word_length;
	int ltrim_word_length;
	
	// auto is only used for this lambda expression
	auto next_line = [&] {
		lines[line][length] = '\0';
		for (int char_index = length - 1; char_index >= 0; char_index--) {
			if (lines[line][char_index] == ' ') {
				lines[line][char_index] = '\0';
			} else {
				break;
			}
		}
		length = 0;
		line++;
	};
	
	for (int word_index = 0; word_index < total_words; word_index++) {
		// Word length with whitespaces
		word_length = countCharacters(words[word_index]);
		// Word length without whitespaces at the front
		ltrim_word_length = word_length;
		for (int i = 0; i < word_length; i++) {
			if (words[word_index][i] == ' ') {
				ltrim_word_length--;
			} else {
				break;
			}
		}
		// Word length without whitespaces at the back
		rtrim_word_length = word_length;
		for (int i = word_length - 1; i >= 0; i--) {
			if (words[word_index][i] == ' ') {
				rtrim_word_length--;
			} else {
				break;
			}
		}
		
		while (true) {
			if (length == 0) {
				// First word on the line cannot have leading whitespaces
				for (int i = 0; words[word_index][word_length - ltrim_word_length + i] != '\0'; i++) {
					if (length <= NUM_CHARS_PER_LINE - 2) {
						lines[line][length++] = words[word_index][word_length - ltrim_word_length + i];
					} else {
						break;
					}
				}
				break;
			} else if (length + rtrim_word_length <= NUM_CHARS_PER_LINE - 1) {
				// Add word to current line if it is not too long
				for (int i = 0; words[word_index][i] != '\0'; i++) {
					if (length <= NUM_CHARS_PER_LINE - 2) {
						lines[line][length++] = words[word_index][i];
					} else {
						break;
					}
				}
				break;
			} else {
				// Line is full, remove whitespace from end and add \0
				next_line();
			}
		}
	}
	next_line();
	
	// Add \0 for empty lines
	for (int i = line; i < MAX_LINES; i++) {
		lines[i][0] = '\0';
	}
}

void printLeftJustified(const char str[]) {
	char lines[MAX_LINES][NUM_CHARS_PER_LINE];
	convertIntoLines(str, lines);
	
	for (int line = 0; line < MAX_LINES; line++) {
		if (lines[line][0] != '\0') {
			cout << lines[line] << "\n";
		}
	}
	cout << flush;
}

void printRightJustified(const char str[]) {
	char lines[MAX_LINES][NUM_CHARS_PER_LINE];
	convertIntoLines(str, lines);
	
	for (int line = 0; line < MAX_LINES; line++) {
		if (lines[line][0] != '\0') {
			cout_spaces(NUM_CHARS_PER_LINE - countCharacters(lines[line]) - 1);
			cout << lines[line] << "\n";
		}
	}
	cout << flush;
}

void printJustified(const char str[]) {
	char lines[MAX_LINES][NUM_CHARS_PER_LINE];
	convertIntoLines(str, lines);
	
	for (int line = 0; line < MAX_LINES - 1; line++) {
		if (lines[line + 1][0] != '\0') {
			// Count consecutive spaces
			int add_spaces = NUM_CHARS_PER_LINE - countCharacters(lines[line]) - 1;
			int spaces = 0;
			for (int i = 1; lines[line][i] != '\0'; i++) {
				if (lines[line][i] == ' ' && lines[line][i - 1] != ' ') {
					spaces++;
				}
			}
			
			int space_count = 0;
			int base_spaces = add_spaces / spaces;
			int extra_spaces = add_spaces % spaces;			
			
			cout << lines[line][0];
			for (int char_index = 1; lines[line][char_index] != '\0'; char_index++) {
				cout << lines[line][char_index];
				// Only add spaces for the first consecutive space
				if (lines[line][char_index] == ' ' && lines[line][char_index - 1] != ' ') {
					cout_spaces(base_spaces);
					if (space_count < extra_spaces) {
						cout << ' ';
					}
					space_count++;
				}
			}
			cout << "\n";
		} else {
			// No need to justify last line
			cout << lines[line] << endl;
			break;
		}
	}
}

void convertStrToPigLatin(char str[]) {
	// Convert all characters to lowercase
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] -= 'A' - 'a';
		}
	}
	
	char words[MAX_STRLEN][MAX_STRLEN];
	int total_words = convertIntoWords(str, words);
	
	int temp_index = 0;
	char temp_str[MAX_STRLEN];
	for (int word_index = 0; word_index < total_words; word_index++) {
		if (words[word_index][0] == ',' || words[word_index][0] == '.' || words[word_index][0] == ' ') {
			// Word only contains punctuations
			for (int char_index = 0; words[word_index][char_index] != '\0'; char_index++) {
				temp_str[temp_index++] = words[word_index][char_index];
			}
			
		} else {
			// Word only contains letters
			if (words[word_index][0] == 'a' || words[word_index][0] == 'e' || words[word_index][0] == 'i' || words[word_index][0] == 'o' || words[word_index][0] == 'u') {
				// Starts with a vowel
				// Append word
				for (int char_index = 0; words[word_index][char_index] != '\0'; char_index++) {
					temp_str[temp_index++] = words[word_index][char_index];
				}
				// Append "y" now, "ay" later
				temp_str[temp_index++] = 'y';
				
			} else {
				// Starts with a consonant
				// Find index of the first vowel
				int vowel_index = 0;
				int word_length = countCharacters(words[word_index]);
				for (; !(words[word_index][vowel_index] == 'a' || words[word_index][vowel_index] == 'e' || words[word_index][vowel_index] == 'i' || words[word_index][vowel_index] == 'o' || words[word_index][vowel_index] == 'u') && words[word_index][vowel_index] != '\0'; vowel_index++);
					
				// Append word
				for (int char_index = vowel_index; char_index < word_length + vowel_index; char_index++) {
					temp_str[temp_index++] = words[word_index][char_index % word_length];
				}
			}
			// Append "ay"
			temp_str[temp_index++] = 'a';
			temp_str[temp_index++] = 'y';
		}
	}
	temp_str[temp_index++] = '\0';
	
	// Copy over to str
	for (int i = 0; i < temp_index; i++) {
		str[i] = temp_str[i];
	}
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++
// You codes end here. Please do not modify codes below
// ++++++++++++++++++++++++++++++++++++++++++++++++++++

void printPigLatin(const char str[])
{
	char pigLatin[MAX_STRLEN];
	for (int i = 0; i < MAX_STRLEN; ++i)
	{
		pigLatin[i] = str[i];
	}
	convertStrToPigLatin(pigLatin);
	int strLen = countCharacters(pigLatin);
	for (int i = 0; i < strLen; ++i)
	{
		if (pigLatin[i] >= 'A' && pigLatin[i] <= 'Z')
		{
			pigLatin[i] = 'a' + pigLatin[i] - 'A';
		}
	}
	cout << pigLatin << endl;
}

void printMainDisplay(const char str[])
{
	cout << str << endl
		 << "===================================\n"
		 << "1. Character Count\n"
		 << "2. Word Count\n"
		 << "3. Encrypt (Caeser Cipher)\n"
		 << "4. Find and Replace String Globally\n"
		 << "5. Find Frequency of String\n"
		 << "6. Print Left Align Text\n"
		 << "7. Print Right Align Text\n"
		 << "8. Print Left-Right Align Text\n"
		 << "9. Print Pig Latin\n"
		 << "Please make your choice: ";
}

int main()
{
	int choice = 0;
	char str[MAX_STRLEN];

	cout << "Enter text: ";
	cin.getline(str, MAX_STRLEN, '\n');

	do
	{
		printMainDisplay(str);
		cin >> choice;
	} while (choice < 1 || choice > 9);

	if (choice == 1)
	{
		cout << "Total character count: " << countCharacters(str) << endl;
	}
	else if (choice == 2)
	{
		cout << "Total word count: " << countWords(str) << endl;
	}
	else if (choice == 3)
	{
		cout << "Enter the shift amount for the caeser cipher encryption (rotation encryption): ";
		int shift;
		cin >> shift;
		encryptText(str, shift);
		cout << str << endl;
	}
	else if (choice == 4)
	{
		cout << "Enter the string to find and replace: ";
		char target[MAX_STRLEN];
		cin.ignore(INT_MAX, '\n');
		cin.getline(target, MAX_STRLEN, '\n');

		cout << "Enter the string to replace it with: ";
		char to[MAX_STRLEN];
		cin.getline(to, MAX_STRLEN, '\n');

		swapString(str, target, to);
		cout << str << endl;
	}
	else if (choice == 5)
	{
		cout << "Enter the string to count the occurences of: ";
		char target[MAX_STRLEN];
		cin.ignore(INT_MAX, '\n');
		cin.getline(target, MAX_STRLEN, '\n');

		cout << '"' << target << '"' << " appears in the text " << countNumOccurences(str, target) << " time(s).\n";
	}
	else if (choice == 6)
	{
		printLeftJustified(str);
	}
	else if (choice == 7)
	{
		printRightJustified(str);
	}
	else if (choice == 8)
	{
		printJustified(str);
	}
	else if (choice == 9)
	{
		printPigLatin(str);
	}
}
