#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include "String.h"
#include "Table.h"

using namespace std;

class Database {
	public:
		Database(const String& name, int numTables);
		Database(const String& filename);
		Database() = delete;
		~Database();
		
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

#endif