/* Classes example
 * August 5, 2011 (took you long enough), updated September 2021 */
#include <iostream>
using namespace std;

class foo {
	public:
	int x;
	void greet(void) {
		cout << "Welcome!" << endl;
	}
	void hello(void) {
		setnum(55);
		cout << "The number is " << x << endl;
	}
	private:
	void setnum(int y) {
		x = (y + 60);
	}
} bar;

class tin {
	public:
	void herp(void) {
		cout << "Pink Flo";
	}
	void derp(void) {
		cout << "yd Rules" << endl;
	}
} can;

int main(void) {
	foo bar;
	tin can;
	bar.greet();
	bar.hello();
	bar.x += 10;
	cout << "The number is now " << bar.x << endl;
	can.herp();
	can.derp();
	return 0;
}

