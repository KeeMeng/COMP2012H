#include <fstream>
#include <iomanip>
#include <iostream>
#include "Database.h"
#include "String.h"
#include "Table.h"
using namespace std;

Database::Database(const String& name, int numTables) {
	// initialise members
	this->name = name;
	this->numTables = numTables;
	this->currentTable = nullptr;
	this->tableHead = nullptr;
	
	if (this->numTables > 0) {
		this->tableHead = new Table("Table_1");
		Table* table = this->tableHead;
		// create tables
		for (int i = 2; i <= this->numTables; i++) {
			String table_name = "Table_";
			// max numTables is 99
			if (i < 10) {
				table_name = table_name + (i + '0');
			} else {
				table_name = table_name + ((i / 10) + '0') + ((i % 10) + '0');
			}
			table->next = new Table(table_name);
			table = table->next;
		}
		table->next = nullptr;
	}
}

Database::Database(const String& filename) {
	ifstream ifs(filename.getStr());
	// initialise members
	ifs >> this->name;
	ifs >> this->numTables;
	this->currentTable = nullptr;
	this->tableHead = nullptr;
	
	if (this->numTables > 0) {
		String name;
		ifs >> name;
		Table* table = new Table(ifs, name);
		this->tableHead = table;
		// create tables
		for (int i = 2; i <= this->numTables; i++) {
			ifs >> name;
			table->next = new Table(ifs, name);
			table = table->next;
		}
		table->next = nullptr;
	}
	ifs.close();
}

Database::~Database() {
	if (this->numTables > 0) {
		Table* table = this->tableHead;
		Table* next_table = table;
		// delete tables from tableHead
		while (table != nullptr) {
			next_table = table->next;
			delete table;
			table = next_table;
		}
	}
	this->tableHead = nullptr;
	this->currentTable = nullptr;
}

bool Database::addTable(Table* table) {
	if (table == nullptr) {
		cout << "Table is a null pointer.\n";
		return false;
	} else if (findTable(table->getName()) != nullptr) {
		cout << "Table with given name already exists in the database.\n";
		return false;
	} else if (this->numTables == 0) {
		// add table after tableHead
		this->tableHead = table;
		this->numTables = 1;
		return true;
	} else {
		// add table after last table
		Table* last_table = this->tableHead;
		for (; last_table->next != nullptr; last_table = last_table->next);
		last_table->next = table;
		this->numTables++;
		return true;
	}
}

void Database::addTable(const String& name) {
	if (findTable(name) != nullptr) {
		cout << "Table with given name already exists in the database.\n";
	} else if (this->numTables == 0) {
		// add table after tableHead
		this->tableHead = new Table(name);
		this->numTables = 1;
	} else {
		// add table after last table
		Table* table = this->tableHead;
		for (; table->next != nullptr; table = table->next);
		table->next = new Table(name);
		this->numTables++;
	}
}

Table* Database::findTable(const String& name) const {
	for (Table* table = this->tableHead; table != nullptr; table = table->next) {
		if (table->getName() == name) {
			return table;
		}
	}
	return nullptr;
}

void Database::listTables() const {
	cout << "The tables currently existing in the database are:\n";
	for (Table* table = this->tableHead; table != nullptr; table = table->next) {
		cout << table->getName() << "\n";
	}
}

void Database::deleteTable(const String& name) {
	Table* table = findTable(name);
	if (table == nullptr) {
		cout << "No such table exists in the database.\n";
	} else if (this->numTables == 1) {
		delete table;
		this->tableHead = nullptr;
		this->numTables = 0;
	} else {
		// more than 1 table in database, point prev table to next table
		if (table == this->tableHead) {
			Table* next_table = table->next;
			delete table;
			this->tableHead = next_table;
		} else {
			Table* next_table = table->next;
			Table* prev_table = this->tableHead;
			for (; prev_table->next != table; prev_table = prev_table->next);
			prev_table->next = next_table;
			delete table;
		}
		this->numTables--;
	}
}

void Database::setCurrentTable(const String& name) {
	Table* table = findTable(name);
	this->currentTable = table;
	if (table == nullptr) {
		cout << "No such table exists in the database.\n";
	}
}

void Database::saveDatabase(const String& filename) const {
	ofstream ofs(filename.getStr());
	ofs << this->name << endl;
	ofs << this->numTables << endl;
	// iterate through each table
	for (Table* table = this->tableHead; table != nullptr; table = table->next) {
		ofs << table->getName() << endl;
		ofs << table->getNumCols() << endl;
		ofs << table->getNumRows() << endl;
		
		// save each table
		if (table->getNumCols() > 0) {
			// save the field names
			for (Field* field = table->getFieldHead(); field != nullptr; field = field->next) {
				if (field == table->getPrimaryKey()) {
					ofs << "*";
				}
				ofs << field->name << " " << (field->type == STRING);
				
				ofs << ((field->next == nullptr) ? "\n" : ", ");
			}
			// save all records
			for (int i = 0; i < table->getNumRows(); i++) {
				for (Field* field = table->getFieldHead(); field != nullptr; field = field->next) {
					ofs << field->column[i];
					ofs << ((field->next == nullptr) ? "\n" : ", ");
				}
			}
		}
	}
	ofs.close();
}

// bonus task
void Database::innerJoin(Table* table1, Table* table2) {
	if (table1 == nullptr or table2 == nullptr) {
		cout << "No such table exists in the database.\n";
	} else if (table1->getPrimaryKey()->type != table2->getPrimaryKey()->type) {
		cout << "Type mismatch between target fields.\n";
	} else {
		// initialise some variables
		Table* table = new Table(table1->getName() + "+" + table2->getName());
		Field* primary1 = table1->getPrimaryKey();
		Field* primary2 = table2->getPrimaryKey();
		Field* head1 = table1->getFieldHead();
		Field* head2 = table2->getFieldHead();
		
		// create primary field
		String primary_name = primary1->name + "+" + primary2->name;
		table->addField(0, primary_name, primary1->type);
		
		// add fields from table1
		for (Field* field1 = head1; field1 != nullptr; field1 = field1->next) {
			if (field1 != primary1) {
				table->addField(table->getNumCols(), field1->name, field1->type);
			}
		}
		// add fields from table2
		for (Field* field2 = head2; field2 != nullptr; field2 = field2->next) {
			if (field2 != primary2) {
				String field2_name = field2->name;
				// check if field2_name exist in field1
				for (Field* field1 = head1; field1 != nullptr; field1 = field1->next) {
					if (field2_name == field1->name) {
						field2_name = field2_name + "(T2)";
						break;
					}
				}
				table->addField(table->getNumCols(), field2_name, field2->type);
			}
		}
		
		// make array on heap to allow variable size
		String* record = new String[table1->getNumRows() + table2->getNumRows() - 1];
		// add records
		for (int i = 0; i < table1->getNumRows(); i++) {
			for (int j = 0; j < table2->getNumRows(); j++) {
				if (primary1->column[i] == primary2->column[j]) {
					int record_index = 0;
					// primary key value
					record[record_index++] = primary1->column[i];
					// iterate through fields and add to record
					for (Field* field1 = head1; field1 != nullptr; field1 = field1->next) {
						if (field1 != primary1) {
							record[record_index++] = field1->column[i];
						}
					}
					for (Field* field2 = head2; field2 != nullptr; field2 = field2->next) {
						if (field2 != primary2) {
							record[record_index++] = field2->column[j];
						}
					}
					table->addRecord(table->getNumRows(), record);
					break;
				}
			}
		}
		delete [] record;
		
		// add table to database
		this->addTable(table);
	}
}


// skeleton code below
void Database::printTable(Table* table) const {
	if (table == nullptr) {
		cout << "No such table exists in the database." << endl;
		return;
	}
	
	for (Field *cur = table->getFieldHead(); cur != nullptr; cur = cur->next) {
		cout << setw(15) << left;
		String curPrintName = (cur == table->getPrimaryKey() ? "*" : "") + cur->name + " " + (cur->type == INT ? "0" : "1");
		cout << curPrintName;
	}
	cout << endl;
	for (int i = 0; i < table->getNumRows(); ++i) {
		for (int j = 0; j < table->getNumCols(); ++j) {
			cout << setw(15) << left;
			cout << (*table)[j][i];
		}
		cout << endl;
	}
	return;
}