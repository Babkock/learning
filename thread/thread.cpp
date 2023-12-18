#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

static void print(int n, const string &str) {
    string msg = to_string(n) + " : " + str;
    cout << msg << endl;
}

int main(void) {
    vector<string> things = {
        "Uno Uno",
        "Dos Dos",
        "Tres Tres",
        "Quatro Cinco",
        "Cinco Cinco"
    };
    vector<thread> threads;

    for (int i = 0; i < things.size(); i++)
        threads.push_back(thread(print, i, things[i]));

    for (auto &th : threads)
        th.join();
    return 0;
}

