/* File reader
 * January 11, 2012, updated October 2021 */
#include <iostream>
#include <fstream>
using namespace std;

/* read.c and read.cpp work the same way
 * they each print the contents of each file given to them */
int main(int argc, char *argv[]) {
	if (!argv[1]) {
		cerr << "USAGE: " << argv[0] << " [input]" << endl;
		return 1;
	}
	if (argc > 1) {
		ifstream *in = new ifstream[argc];
		char y;
		
		for (int x = 1; x < argc; x++) {
			in[x-1].open(argv[x]);
			if (!in[x-1]) {
				in[x-1].close();
				cerr << "ERROR: '" << argv[x] << "' File not found" << endl;
				delete[] in;
				return 2;
			}

			while (in[x-1].get(y))
				cout.put(y);
			in[x-1].close();
		}

		delete[] in;
	}
	else if (argc == 1) {
		ifstream *in = new ifstream();
		in->open(argv[1]);
	
		if (!in) {
			cerr << "ERROR: '" << argv[1] << "' File not found" << endl;
			delete in;
			return 2;
		}

		char x;
		while (in->get(x))	// fails on EOF
			cout.put(x);
		in->close();
		delete in;
	}

	return 0;
}

