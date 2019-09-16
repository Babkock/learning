/* Echo command equivalent by Tanner Babcock
 * June 30, 2010 */
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	int x;
	for (x = 1; x < argc; x++) {
		cout << argv[x];
		if (x != (argc - 1)) cout << " ";
	}
	cout << endl;
	return 0;
}
