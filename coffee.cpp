/* Coffee by Tanner Babcock
 * June 30, 2010 */
#include <iostream>
#include <cstdlib>
using namespace std;

int total(int y) {
	float x = (y * 2.99);
	cout << "Your total is $" << x << endl;
	return x;
}

int main(int argc, char *argv[]) {
	int y;
	if (!argv[1]) {
		cout << "How many cups of coffee would you like? ";
		cin >> y;
		total(y);
		return 0;
	}
	y = (atoi(argv[1]));
	total(y);
	return 0;
}
