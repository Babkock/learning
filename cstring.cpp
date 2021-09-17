/* String comparer
 * 2011 or 2012, updated September 2021 */
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

int main(void) {
	int x;
	char tmp[6];
	string str;
	cout << "Enter \"size 5\": ";
	getline(cin, str);

	sscanf(str.c_str(), "%s %d", tmp, &x);
	if (strcmp(tmp, "size") == 0)
		cout << "Congratulations, ";
	else
		cout << "Fuck you, ";
	if (x == 5)
		cout << "brother.\n";
	else
		cout << "asshole.\n";
	return 0;
}

