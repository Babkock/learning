/* Hash map example
 * November 18, 2023 */
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(void) {
	unordered_map<string, int> mymap {
		{"Uno", 1},
		{"Dos", 2},
		{"Tres", 3},
		{"Quatro", 4},
		{"Cinco", 5},
	};

	cout << "Printing mymap:" << endl;

	for (const auto& x: mymap) {
		string s = x.first;
		int v = x.second;

		cout << "mymap[" << s << "] = " << v << endl;
	}

	return 0;
}

