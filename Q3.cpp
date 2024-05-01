#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>
using namespace std;

struct requestStructure {
    int request_id;
    string ip_address;
    string page_requested;
};

queue<requestStructure> msg_queue;
mutex mtx;
condition_variable cv;
int request_counter = 0;

string webPages[10] = {"google.com", "yahoo.com", "bing.com", "amazon.com", "facebook.com", 
                       "twitter.com", "instagram.com", "reddit.com", "linkedin.com", "netflix.com"};

void listen() {
    while (true) {
        this_thread::sleep_for(chrono::seconds(rand() % 3 + 1));
        requestStructure req;
        req.request_id = ++request_counter;
        req.ip_address = "";
        req.page_requested = webPages[rand() % 10];

        {
            lock_guard<mutex> lock(mtx);
            msg_queue.push(req);
        }

        cv.notify_one();
    }
}

void do_request(int thread_id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !msg_queue.empty(); });

        requestStructure req = msg_queue.front();
        msg_queue.pop();

        lock.unlock();

        {
            lock_guard<mutex> cout_lock(mtx);
            cout << "Thread " << thread_id << " completed request " << req.request_id 
                 << " requesting webpage " << req.page_requested << endl;
        }
    }
}

int main() {
    srand(time(nullptr));

    thread listener(listen);

    const int num_threads = 5;
    thread threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = thread(do_request, i + 1);
    }

    listener.join();

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    return 0;
}
