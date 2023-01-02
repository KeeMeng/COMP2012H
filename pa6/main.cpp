#include <iostream>
#include <limits>
#include "Database.h"
#include "String.h"

using namespace std;

void printDBMenu() {
	cout << "==========================================================\n";
	cout << "   Welcome to the Relational Database Management System\n";
	cout << "==========================================================\n";
	cout << "Please make your choice:\n";
	cout << "1. Create New Database\n";
	cout << "2. Modify Existing Database\n";
	cout << "3. Exit" << endl;
}

void printTableMenu() {
	cout << "==========================================================\n";
	cout << "   Welcome to the Relational Database Management System\n";
	cout << "==========================================================\n";
	cout << "Please make your choice:\n";
	cout << "1. Add Table\n";
	cout << "2. List Tables\n";
	cout << "3. Delete Table\n";
	cout << "4. Print Table\n";
	cout << "5. Modify Table\n";
	cout << "6. Save Database\n";
	cout << "7. Inner Join Tables\n";
	cout << "8. Exit" << endl;
}

void printModifyMenu(Database *db) {
	cout << "==========================================================\n";
	cout << "   Welcome to the Relational Database Management System\n";
	cout << "==========================================================\n";
	cout << db->getCurrentTable()->getName() << '\n';
	cout << "========================\n";
	db->printTable(db->getCurrentTable());
	cout << "========================\n\n";
	cout << "Please make your choice:\n";
	cout << "1. Add Record\n";
	cout << "2. Add Field\n";
	cout << "3. Delete Record\n";
	cout << "4. Modify Record\n";
	cout << "5. Set Primary Key\n";
	cout << "6. Reorder Columns\n";
	cout << "7. Delete Field\n";
	cout << "8. Sort Table\n";
	cout << "9. Rename Table\n";
	cout << "10. Exit" << endl;
}

int main() {
	Database *database = nullptr;
	int choice = 0;
	do {
		do {
			printDBMenu();
			cin >> choice;
		} while (choice < 1 || choice > 3);
		if (choice == 1) {
			cout << "Please name your Database: \n";
			String name;
			getline(cin, name, '\n');
			cout << "Enter the number of tables to add to the Database: \n";
			int numTables;
			cin >> numTables;
			database = new Database(name, numTables);
		} else if (choice == 2) {
			cout << "Enter the name of the file to load the database from: \n";
			String filename;
			getline(cin, filename, '\n');
			database = new Database(filename);
		} else if (choice == 3) {
			break;
		}
		bool breakflag;
		do {
			breakflag = true;
			printTableMenu();
			cin >> choice;
			switch (choice) {
				case 1:
				{
					cout << "Enter table name: \n";
					String name;
					getline(cin, name, '\n');
					database->addTable(name);
					break;
				}
				case 2:
				{
					database->listTables();
					break;
				}
				case 3:
				{

					if (!database->getNumTables())
					{
						cout << "Cannot delete table from database with no tables." << endl;
						continue;
					}

					cout << "Enter name of table to delete: \n";
					String name;
					getline(cin, name, '\n');
					database->deleteTable(name);
					break;
				}
				case 4:
				{
					cout << "Enter name of table to be read: \n";
					String name;
					getline(cin, name, '\n');
					database->printTable(database->findTable(name));
					break;
				}
				case 5:
				{
					if (!database->getNumTables())
					{
						cout << "Cannot modify table in database with no tables." << endl;
						continue;
					}

					cout << "Enter name of table to modify: \n";
					String name;
					getline(cin, name, '\n');
					bool breakflag = true;
					database->setCurrentTable(name);
					if (database->getCurrentTable() == nullptr) {
						continue;
					}
					do {
						printModifyMenu(database);
						int choice;
						cin >> choice;
						switch (choice) {
							case 1:
							{
								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot insert record into table with no fields." << endl;
									continue;
								}

								cout << "Input the index at which you would like to insert the data \n";
								int index;
								cin >> index;
								cout << "This table has " << database->getCurrentTable()->getNumCols() << " fields.\n";
								cout << "Enter data to fill into the record: \n";
								String *record = new String[database->getCurrentTable()->getNumCols()];
								for (int i = 0; i < database->getCurrentTable()->getNumCols(); ++i)
								{
									getline(cin, record[i], '\n');
									if (record[i] == "null") {
										record[i] = "";
									}
								}
								database->getCurrentTable()->addRecord(index, record);
								delete[] record;
								break;
							}
							case 2:
							{
								int index;
								String name;
								int type;
								cout << "Enter the index of the field: \n";
								cin >> index;
								cout << "Enter the name of the field: \n";
								getline(cin, name, '\n');
								cout << "Enter the type of the field (0 for int and 1 for String): \n";
								cin >> type;
								database->getCurrentTable()->addField(index, name, static_cast<TYPE>(type));
								break;
							}
							case 3:
							{

								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot delete record from table with no fields." << endl;
									continue;
								}

								int index;
								cout << "Enter row index of record to delete: \n";
								cin >> index;
								database->getCurrentTable()->deleteRecord(index);
								break;
							}
							case 4:
							{
								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot modify data in table with no fields." << endl;
									continue;
								}

								int row, column;
								cout << "Enter row and column indices of cell to modify: \n";
								cin >> row;
								cin >> column;
								cout << "Enter data to write into cell: \n";
								String data;
								getline(cin, data, '\n');
								database->getCurrentTable()->modifyRecord(row, column, data);
								break;
							}
							case 5:
							{

								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot set primary key in table with no fields." << endl;
									continue;
								}

								cout << "Enter name of field to be set as primary key: \n";
								String name;
								getline(cin, name, '\n');
								database->getCurrentTable()->setPrimaryKey(name);
								break;
							}
							case 6:
							{

								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot reorder fields of a table with no fields." << endl;
									continue;
								}

								cout << "Enter name of field to be relocated: \n";
								String name;
								getline(cin, name, '\n');
								cout << "Enter column index to relocate field to: \n";
								int index;
								cin >> index;
								database->getCurrentTable()->setColumnIndex(index, name);
								break;
							}
							case 7:
							{

								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot delete field in table with no fields." << endl;
									continue;
								}

								cout << "Enter name of field to be deleted: \n";
								String name;
								getline(cin, name, '\n');
								database->getCurrentTable()->deleteField(name);
								break;
							}
							case 8:
							{

								if (!database->getCurrentTable()->getNumCols())
								{
									cout << "Cannot sort table with no fields." << endl;
									continue;
								}

								cout << "Enter name of field to sort by: \n";
								String name;
								getline(cin, name, '\n');
								database->getCurrentTable()->sortTable(database->getCurrentTable()->findField(name));
								break;
							}
							case 9:
							{
								cout << "Enter a new name for the current table: \n";
								String name;
								getline(cin, name, '\n');
								database->getCurrentTable()->setName(name);
								break;
							}
							case 10:
							{
								breakflag = false;
								break;
							}
						}
					} while (breakflag);
					break;
				}
				case 6:
				{
					cout << "Enter the name of the file to store the database in: \n";
					String name;
					ws(cin);
					getline(cin, name, '\n');
					database->saveDatabase(name);
					break;
				}
				case 7:
				{

					if (database->getNumTables() < 2)
					{
						cout << "Need at least 2 tables in database to perform merge operation." << endl;
						continue;
					}

					cout << "Enter name of first table to merge: \n";
					String tableName1;
					getline(cin, tableName1, '\n');
					Table *table1 = database->findTable(tableName1);
					cout << "Enter name of second table to merge: \n";
					String tableName2;
					getline(cin, tableName2, '\n');
					Table *table2 = database->findTable(tableName2);
					database->innerJoin(table1, table2);
					if (table1 != nullptr && table2 != nullptr)
					{
						Table *merge = database->findTable(table1->getName() + "+" + table2->getName());
						if (merge != nullptr)
							database->printTable(merge);
					}
					break;
				}
				case 8:
				{
					breakflag = false;
					break;
				}
			}
		} while (breakflag);
		delete database;
	} while (true);
}
