#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>

class String
{
private:
	char* str;

public:
	String();
	String(const char* str);
	String(const String& string);
	~String();
	
	int length() const;
	friend String operator+(const String& string1, const String& string2);
	friend String operator+(const String& string1, char a);
	friend std::ostream& operator<<(std::ostream& os, const String& string);
	friend std::istream& operator>>(std::istream& is, String& string);
	friend std::istream& getline(std::istream& is, String& string, char end);
	String& operator=(const String& string);
	String substr(int begin, int count) const;
	friend bool operator==(const String& string1, const String& string2);
	friend bool operator>(const String& string1, const String& string2);
	friend bool operator<(const String& string1, const String& string2);
	friend bool operator>=(const String& string1, const String& string2);
	friend bool operator<=(const String& string1, const String& string2);
	friend bool operator!=(const String& string1, const String& string2);
	friend int strcmp(const String& string1, const String& string2);
	char& operator[](int index);
	const char& operator[](int index) const;
	friend int stoi(const String& string);
	const char* getStr() const { return str; }
};

#endif