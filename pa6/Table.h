#ifndef TABLE_H
#define TABLE_H

#include "String.h"

using namespace std;

enum TYPE {
	INT,
	STRING
};

// Field struct
struct Field {
	String name;	// Name of the current field
	Field* next;	// Pointer to the next field in the table's linked-list
	String* column;	// Dynamic array of String to store all data of this field, each element corresponds to a row
	TYPE type;		// Type of the field. 0 if int. 1 if String
};

class Table {
	public:
		Table(const String& name);
		Table(ifstream& ifs, const String& name);
		Table() = delete;
		~Table();
		
		void addRecord(int index, String* record);
		void addField(int index, const String& name, TYPE type);
		void deleteRecord(int row);
		void modifyRecord(int row, int column, const String& newVal);
		void setPrimaryKey(const String& name);
		void setColumnIndex(int index, const String& target);
		void deleteField(const String& name);
		Field* findField(const String& name) const;
		void sortTable(Field* field);
		
		// Helper functions written to get and set some parameters
		
		String* operator[](int index) const;
		int getNumRows() const { return numRows; }
		int getNumCols() const { return numCols; }
		Field* getFieldHead() const { return fieldHead; }
		Field* getPrimaryKey() const { return primaryKey; }
		void setName(const String& name) { this->name = name; }
		String getName() const { return name; }
		
		Table* next; // Pointer to the next table in the Database's linked-list

	private:
		Field* primaryKey;	// Pointer to the primary key field of the table
		Field* fieldHead;	// Pointer to the first node in the linked-list of fields in this table
		int numRows;		// Number of rows currently in use in the table
		int numCols;		// Number of columns in the table
		int tableSize;		// Size of the dynamic arrays of fields
		String name;		// Name of the table
};

bool isInteger(const String& test);

#endif