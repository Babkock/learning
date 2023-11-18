/* C++ list
 * November 18, 2023 */
#include <iostream>
#include <list>
#include <string>
#include <cstdio>
using namespace std;

class Color {
private:
	short red;
	short green;
	short blue;
	string name;

public:
	Color(void) {
		red = 0;
		green = 0;
		blue = 0;
		cout << "Constructed color" << endl;
	}
	Color(int r) {
		red = (short)r;
		green = 0;
		blue = 0;
		cout << "Constructed color" << endl;
	}
	Color(int r, int g, int b) {
		red = (short)r;
		green = (short)g;
		blue = (short)b;
		cout << "Constructed color" << endl;
	}
	Color(string n, int r, int g, int b) {
		name = n;
		red = (short)r;
		green = (short)g;
		blue = (short)b;
		cout << "Constructed color " << n << endl;
	}
	~Color(void) {
		if (!name.empty())
			cout << "Destroyed color " << name << endl;
		else
			cout << "Destroyed color" << endl;
	}

	void print(void) {
		cout << "Red: " << red << endl;
		cout << "Green: " << green << endl;
		cout << "Blue: " << blue << endl;
		if (!name.empty()) {
			cout << name << endl;
		}
	}

	void printHex(void) {
		printf("%x %x %x\n", red, green, blue);
		cout << name << endl;
	}
};

int main(void) {
	list<Color> li;
	li.push_back(Color("gray", 50, 50, 50));
	li.push_back(Color("purple", 255, 60, 255));
	li.push_back(Color("red", 255, 0, 0));
	cout << endl;

	for (Color c : li) {
		c.printHex();
	}
	cout << endl;

	li.clear();
	li.push_back(Color("yellow", 255, 255, 0));
	li.push_back(Color("blue", 0, 10, 255));
	for (Color c : li) {
		c.printHex();
	}
	cout << endl;

	return 0;
}

