/* Minimum and maximum by Tanner Babcock
 * January 26, 2012 */
#include <iostream>
#include <string>
using namespace std;

int main() {
	int x, y, arr[10];
	int min = 0, max = 0;
	float avg, z;
	cout << "Enter 10 integers:\n";
	for (x = 0; x < 10; x++)
		cin >> arr[x];
	for (x = 0; x < 10; x++) {
		if (x == 0)
			min = arr[x];
		for (y = 0; y < 10; y++) {
			if (arr[y] > max)
				max = arr[y];
			if (arr[y] < min)
				min = arr[y];
		}
	}
	cout << "Minimum: " << min << endl;
	cout << "Maximum: " << max << endl;
	for (x = 0; x < 9; x++)
		z += arr[x];
	avg = (z / 10);
	cout << "Average: " << avg << endl;
	return 0;
}
