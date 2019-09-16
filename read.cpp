/* File reader by Tanner Babcock
 * January 11, 2012 */
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	if (!argv[1]) {
		cerr << "USAGE: " << argv[0] << " [input]\n";
		return 1;
	}
	// ofstream out(argv[1]);
	ifstream in;
	in.open(argv[1]);
	
	if (!in) {
		cerr << "ERROR: File not found\n";
		return 2;
	}
	char x;
	while (in.get(x))	// fails on EOF
		cout.put(x);
	return 0;
}
