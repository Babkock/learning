/* File writer by Tanner Babcock
 * January 11, 2012 */
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	if (!argv[1]) {
		cerr << "USAGE: " << argv[0] << " [output]\n";
		return 1;
	}
	// ofstream out(argv[1]);
	ofstream out;
	out.open(argv[1]);
	char x;
	while (cin.get(x))	// fails on EOF
		out.put(x);
	out.close();
	return 0;
}

