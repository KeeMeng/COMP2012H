#include "./String.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

class String;

String::String() : str{nullptr}
{
	str = new char[1];
	str[0] = '\0';
}

String::String(const char *str)
{
	if (str == nullptr)
	{
		this->str = new char[1];
		this->str[0] = '\0';
	}
	else
	{
		int len = strlen(str) + 1;
		this->str = new char[len];
		strcpy(this->str, str);
		this->str[len - 1] = '\0';
	}
}

String::String(const String &string)
{
	str = new char[strlen(string.str) + 1];
	strcpy(str, string.str);
	str[strlen(string.str)] = '\0';
}

int String::length() const
{
	return strlen(str);
}
char &String::operator[](int index) { return str[index]; }
const char &String::operator[](int index) const { return str[index]; }

String::~String() { delete[] str; }

String &String::operator=(const String &string)
{
	if (this == &string)
		return *this;
	delete[] str;
	str = new char[strlen(string.str) + 1];
	strcpy(str, string.str);
	return *this;
}

String operator+(const String &string1, const String &string2)
{
	int newLength = strlen(string1.str) + strlen(string2.str);
	char *newstr = new char[newLength + 1];

	strcpy(newstr, string1.str);
	strcat(newstr, string2.str);
	newstr[newLength] = '\0';

	String temp(newstr);
	delete[] newstr;
	return temp;
}

String operator+(const String &string1, char a)
{
	int newLength = strlen(string1.str) + 1;
	char *newstr = new char[newLength + 1];

	strcpy(newstr, string1.str);
	newstr[newLength - 1] = a;
	newstr[newLength] = '\0';

	String temp(newstr);
	delete[] newstr;
	return temp;
}

std::ostream &operator<<(std::ostream &os, const String &string)
{
	os << string.str;
	return os;
}

std::istream &operator>>(std::istream &is, String &string)
{
	std::istream::sentry sentry(is);
	if (!sentry)
		return is;

	std::vector<char> temp;
	int next;

	while ((next = is.get()) != is.eof() && !std::isspace(next))
		temp.push_back(next);
	temp.push_back('\0');
	string = &temp[0];
	return is;
}

std::istream &getline(std::istream &is, String &string, char end)
{
	std::istream::sentry sentry(is);
	if (!sentry)
		return is;

	std::vector<char> temp;
	int next;

	while ((next = is.get()) != is.eof() && next != end)
		temp.push_back(next);
	temp.push_back('\0');
	string = &temp[0];
	return is;
}

String String::substr(int begin, int count) const
{
	char *newstr = new char[count + 1];
	newstr[count] = '\0';
	for (int i = 0; i < count; ++i)
	{
		newstr[i] = str[i + begin];
	}
	String temp = String(newstr);
	delete[] newstr;
	return temp;
}

int strcmp(const String &string1, const String &string2)
{
	return strcmp(string1.str, string2.str);
}

bool operator==(const String &string1, const String &string2)
{
	return !strcmp(string1, string2);
}

bool operator>(const String &string1, const String &string2)
{
	for (int i = 0; i < string1.length() && i < string2.length(); ++i)
	{
		if (string1[i] == '\0')
		{
			return true;
		}
		if (string2[i] == '\0')
		{
			return false;
		}
		if (toupper(string1[i]) > toupper(string2[i]))
		{
			return true;
		}
		else if (toupper(string1[i]) < toupper(string2[i]))
		{
			return false;
		}
	}
	return true;
}

bool operator<(const String &string1, const String &string2)
{
	for (int i = 0; i < string1.length() && i < string2.length(); ++i)
	{
		if (string1[i] == '\0')
		{
			return false;
		}
		if (string2[i] == '\0')
		{
			return true;
		}
		if (toupper(string1[i]) < toupper(string2[i]))
		{
			return true;
		}
		else if (toupper(string1[i]) > toupper(string2[i]))
		{
			return false;
		}
	}
	return false;
}
bool operator>=(const String &string1, const String &string2) { return !(string1 < string2); }
bool operator<=(const String &string1, const String &string2) { return !(string1 > string2); }
bool operator!=(const String &string1, const String &string2) { return !(string1 == string2); }

int stoi(const String &string) { return atoi(string.str); }