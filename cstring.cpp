#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main() {
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
		cout << "faggot.\n";
	return 0;
}
