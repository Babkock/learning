/* Classes example by Tanner Babcock
 * August 5, 2011 (took you long enough) */
#include <iostream>

class foo {
	public:
	int x;
	void greet(void) {
		std::cout << "Welcome!\n";
	}
	void hello(void) {
		setnum(55);
		std::cout << "The number is " << x << "\n";
	}
	private:
	void setnum(int y) {
		x = (y + 60);
	}
} bar;

class tin {
	public:
	void herp(void) {
		std::cout << "Pink Flo";
	}
	void derp(void) {
		std::cout << "yd Rules\n";
	}
} can;

int main() {
	foo bar;
	tin can;
	bar.greet();
	bar.hello();
	bar.x += 10;
	std::cout << "The number is now " << bar.x << "\n";
	can.herp();
	can.derp();
	return 0;
}
