/* File copier by Tanner Babcock
 * January 11, 2012,
 * updated November 2, 2023 */
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	if (!argv[1]) {
		cerr << "USAGE: " << argv[0] << " [inputfile] [outputfile]" << endl;
		return 1;
	}

	ifstream *in = new ifstream();
	in->open(argv[1]);

	if (!in) {
		cerr << "ERROR: Input file '" << argv[1] << "' does not exist" << endl;
		return 2;
	}

	ofstream *out = new ofstream();
	out->open(argv[2]);

	char x;
	while (in->get(x))
		out->put(x);

	out->close();
	in->close();
	delete out;
	delete in;
	return 0;
}

