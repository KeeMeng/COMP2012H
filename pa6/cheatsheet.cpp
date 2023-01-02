#include "String.h"
enum TYPE { INT, STRING };
struct Field {
	String name;	// Name of the current field
	Field* next;	// Pointer to the next field in the table's linked-list
	String* column;	// Dynamic array of String to store all data of this field, each element corresponds to a row
	TYPE type;		// Type of the field. 0 if int. 1 if String
};
class Table {
	public:
		void addRecord(int index, String* record);
		void addField(int index, const String& name, TYPE type);
		void deleteRecord(int row);
		void modifyRecord(int row, int column, const String& newVal);
		void setPrimaryKey(const String& name);
		void setColumnIndex(int index, const String& target);
		void deleteField(const String& name);
		Field* findField(const String& name) const;
		void sortTable(Field* field);
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
class Database {
	public:
		bool addTable(Table* table);
		void addTable(const String& name);
		Table* findTable(const String& name) const;
		void listTables() const;
		void deleteTable(const String& name);
		void setCurrentTable(const String& name);
		void saveDatabase(const String& filename) const;
		void innerJoin(Table* table1, Table* table2);
		Table* getCurrentTable() const { return currentTable; }	// Simple getter for currentTable pointer
		int getNumTables() const { return numTables; }			// Simple getter for numTables
		void printTable(Table* table) const;	
	private:
		String name;			// Name of the Database
		Table* tableHead;		// Pointer to the first node in the linked-list of tables in the database.
		Table* currentTable;	// Pointer to the table that is currently being modified in main.
		int numTables;			// Number of tables in the database.
};