/* Async fizzbuzz
 * Tanner Babcock
 * November 19, 2023 */
#define _GLIBCXX_USE_NANOSLEEP
#include <iostream>
#include <string>
#include <thread>

static void callback(const std::string& data) {
	std::cout << "Callback called with: " << data << std::endl;
}

static void task(int time) {
	std::this_thread::sleep_for(std::chrono::seconds(time));
	callback("async task done");
}

int main(void) {
	std::thread *bt = new std::thread(task, 1);
	std::cout << "async task started" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	for (int x = 0; x < 100; x++) {
		if (x % 5 == 0)
			std::cout << "buzz";
		if (x % 3 == 0)
			std::cout << "fizz";
		else if (x % 5 != 0)
			std::cout << x;
		std::cout << std::endl;
	}
	std::cout << "main done" << std::endl;
	bt->join();
	delete bt;
	return 0;
}

