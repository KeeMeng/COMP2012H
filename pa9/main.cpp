#include <iostream>
#include <random>
#include "skiplist.hpp"
#include "object.hpp"

using namespace std;

const string IDX = "Test Case ";
const string NAME = ": ";
const string LINE = "--------------------------------------------------";

minstd_rand pa9_rand;

int square(int x) {return x*x;}

bool posi(int x) {return x >= 0;}

int main() {
	

	// int test;
	// cin >> test;
	
	for (int test = 1; test <= 23; test++) {
		pa9_rand = minstd_rand(2012);
		if (test == 1) {
			Skiplist<int, int>::Node node;
			string name = "Part I - Testing Node<int, int>() default constructor";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			cout << "levels: " << node.levels << endl;
			bool n = true;
			for (int i = 0; i < node.levels; i++)
				n &= (node.nexts[i] == nullptr);
			cout << "is nullptr: " << boolalpha << n << endl;

		} else if (test == 2) {
			Skiplist<int, int>::Node node(2, 1, 2);
			string name = "Part I - Testing Node<int, int>() other constructor";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			cout << "key: " << node.key << endl;
			cout << "value: " << node.value << endl;
			cout << "levels: " << node.levels << endl;
			bool n = true;
			for (int i = 0; i < node.levels; i++)
				n &= (node.nexts[i] == nullptr);
			cout << "is nullptr: " << boolalpha << n << endl;

		} else if (test == 3) {
			Skiplist<int, int> sl;
			string name = "Part I - Testing Skiplist<int, int>() default constructor";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			sl.print_full();

		} else if (test == 4) {
			Skiplist<char, int> sl;
			string name = "Part I - Testing update() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;

			for (int i = 65; i < 75; i++)
				sl.update(i, i);

			cout << "After update:" << endl;
			sl.print_full();
			
		} else if (test == 5) {
			Skiplist<char, int> sl;
			string name = "Part I - Testing get() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 65; i < 75; i++)
				sl.update(i, i);
			
			int rtn;
			bool a = sl.get('F', rtn);
			
			cout << "contains: " << boolalpha << a << endl;
			cout << "value: " << rtn << endl;

		} else if (test == 6) {
			Skiplist<char, int> sl;
			string name = "Part I - Testing remove() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 65; i < 71; i++)
				sl.update(i, i);

			cout << "contains: " << boolalpha << sl.remove('E') << endl;
			cout << "After remove:" << endl;
			sl.print_full();

		} else if (test == 7) {
			Skiplist<int, int> sl1;
			string name = "Part I - Testing Skiplist() copy constructor";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 5; i < 10; i++)
				sl1.update(i, i);
			
			Skiplist<int, int> sl2(sl1);
			// sl1.print_full();
			sl2.print_full();

		} else if (test == 8) {
			Skiplist<int, int> sl1, sl2;
			string name = "Part I - Testing operator=() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 5; i < 10; i++)
				sl1.update(i, i);
			
			for (int i = 5; i < 10; i++)
				sl2.update(i+1, i+1);
			// sl2.print_full();
			// sl2.print();
			// cout << "==============" << endl;
			
			sl2 = sl1;
			// sl1.print_full();
			// sl1.print();
			sl2.print_full();
			// sl2.print();

		} else if (test == 9) {
			Skiplist<char, int> sl;
			string name = "Part I - Testing size() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 65; i < 70; i++)
				sl.update(i, i);
			
			cout << "size: " << sl.size() << endl;

		} else if (test == 10) {
			Skiplist<char, int> sl;
			string name = "Part I - Testing empty() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 65; i < 70; i++)
				sl.update(i, i);
			
			cout << "empty: " << boolalpha << sl.empty() << endl;

		} else if (test == 11) {
			Skiplist<char, int> sl;
			string name = "Part I - Testing print() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			for (int i = 65; i < 70; i++)
				sl.update(i, i);
			
			sl.print();

		} else if (test == 12) {
			Skiplist<int, int> sl;
			string name = "Part I - Testing map() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			sl.update(1, 1);
			sl.update(3, 3);
			sl.update(7, 7);
		
			cout << "Mapped: ";
			sl.map(square).print();

			cout << "Original: ";
			sl.print();

		} else if (test == 13) {
			Skiplist<int, int> sl;
			string name = "Part I - Testing filter() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			sl.update(1, 1);
			sl.update(2, -5);
			sl.update(3, 8);
			sl.update(4, -10);

			cout << "Filtered: ";
			sl.filter(posi).print();

			cout << "Original: ";
			sl.print();

		} else if (test == 14) {
			Skiplist<int, int> sl1, sl2;
			string name = "Part I - Testing operator+() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			sl1.update(1, 1);
			sl1.update(2, 2);
			sl1.update(3, 3);

			sl2.update(4, 4);

			(sl1 + sl2).print();

		} else if (test == 15) {
			object a = 1;
			string name = "Part II - Testing object() conversion constructor";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
				
			cout << "value: " << a.cast_back<int>() << endl;

		} else if (test == 16) {
			object a = 10;
			string name = "Part II - Testing object() copy constructor";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			object b = a;
			cout << "value: " << b.cast_back<int>() << endl;
			
		} else if (test == 17) {
			object a = 10;
			string name = "Part II - Testing object operator=() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			object b;
			b = a;
			cout << "value: " << b.cast_back<int>() << endl;
			
		} else if (test == 18) {
			object a = 1;
			string name = "Part II - Testing object type() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			cout << "type is int: " << boolalpha << (a.type() == typeid(int)) << endl;
			
		} else if (test == 19) {
			object a = 100;
			string name = "Part II - Testing object cast_back() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			
			cout << "cast back to int: " << a.cast_back<int>() << endl;
			
		} else if (test == 20) {
			// Just for fun, this is not in the actual test case.
			// You can have fun with this if you have implemented Part I&II!
			string name = "Part III - Testing objects in skiplist";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			Skiplist<int, object> multi_map;
			
			object a = 10;
			object b = 20;
			object c = string("thirty");
			object d = 40.0;
			
			
			multi_map.update(1, a);
			multi_map.update(2, b);
			multi_map.update(4, d);
			multi_map.update(3, c);
			
			multi_map.print();
			
			/* ... */
		} else if (test == 21) {
			object a = 10;
			object b = 5;
			string name = "Bonus I - Testing operator+() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			object c = a + b;
			cout << "c value: " << c.cast_back<int>() << endl;
			object d = a + a;
			cout << "d value: " << d.cast_back<int>() << endl;
		} else if (test == 22) {
			string name = "Bonus II - Testing operator==() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			cout << "10 == 5: " << boolalpha << (object(10) == object(5)) << endl;
			cout << "10 == 10: " << boolalpha << (object(10) == object(10)) << endl;
			cout << "10 == 15: " << boolalpha << (object(10) == object(15)) << endl;
			cout << "1 == 1.0: " << boolalpha << (object(1) == object(1.0)) << endl;
		} else if (test == 23) {
			string name = "Bonus III - Testing operator<<() function";
			cout << IDX << test << NAME << name << endl
				 << LINE << endl;
			object a = string("hello");
			object b = 10;
			cout << "a is: " << a << endl;
			cout << "b is: " << b << endl;
		}
		cout << endl;
	}

	return 0;
}