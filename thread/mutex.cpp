/* Job queue with mutex
 * July 10, 2022
 * Compile with:
 * g++ -pthread -std=c++11 mutex.cpp */
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

struct job { int num; };
bool closed = false;

std::deque<job> jobList;
std::mutex jobMutex;
std::condition_variable jobCondition;
std::atomic<int> threadsRunning;

/* thread-safe cout */
struct tcout {
    tcout() :lock(mutex) {}

    template <typename T>
    tcout& operator<< (T&& t) {
        std::cout << t;
        return *this;
    }

    static std::mutex mutex;
    std::unique_lock<std::mutex> lock;
};
std::mutex tcout::mutex;

void addJobs(void) {
    static int num = 0;
    job current = { num++ };
    std::unique_lock<std::mutex> lock(jobMutex);
    jobList.push_back(current);

    jobCondition.notify_one();
    lock.unlock();
}

/* Pass the parameter by giving another argument
 * to the thread constructor */
void work(int seconds) {
    job current;
    threadsRunning++;
    while (true) {
        std::unique_lock<std::mutex> lock(jobMutex);
        if (jobList.empty()) {
            threadsRunning--;
            jobCondition.wait(lock, [] { return !jobList.empty() || closed; });
            threadsRunning++;
        }
        if (jobList.empty())
            break;
        current = jobList.front();
        jobList.pop_front();
        lock.unlock();

        if ((current.num % 2) == 0)
            tcout() << "\tJob " << current.num << " waiting " << seconds << " seconds...\n";
        else
            tcout() << "Job " << current.num << " waiting " << seconds << " seconds...\n";
        sleep(seconds);

        std::this_thread::sleep_for(std::chrono::milliseconds(rand() * 1000 / RAND_MAX));
        if ((current.num % 2) == 0)
            tcout() << "\tJob " << current.num << " complete!\n";
        else
            tcout() << "Job " << current.num << " complete!\n";
    }
    threadsRunning--;
}

int main(int argc, char *argv[]) {
    int res;
    if (argc < 2) {
        std::cout << "Number of threads to use (20 max): ";
        std::cin >> res;
        if (res < 1 || res > 20) {
            std::cerr << "Can only have up to 20 threads" << std::endl;
            return 1;
        }
    }
    else if (argc < 3) {
        res = atoi(argv[1]);
        if (res < 1 || res > 20) {
            std::cerr << "Can only have up to 20 threads" << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "USAGE: " << argv[0] << " [number of threads]" << std::endl;
        return 2;
    }

    std::thread jobThreads[res];

    for (int i = 0; i < res; i++) {
        jobThreads[i] = std::thread(work, i+1);
    }
    for (int i = 0; i < 100; i++) {
        addJobs();
    }
    {
        std::unique_lock<std::mutex> lock(jobMutex);
        closed = true;
        jobCondition.notify_all();
    }
    for (int i = 0; i < res; i++) {
        jobThreads[i].join();
    }
    return 0;
}

