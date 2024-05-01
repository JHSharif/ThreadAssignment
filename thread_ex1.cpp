#include <iostream>
#include <thread>
using namespace std;

bool stop = true;

void thread1() {
    cout << "I am thread 1\n";
    stop = false;
}

void thread2() {
    while (stop);
    cout << "I am thread2\n";
}

void thread3(int &c) {
    for (int i = 0; i < 100; i++)
        c++;
}

void thread4(int &c) {
    for (int i = 0; i < 100; i++)
        c++;
}

int main() {
    thread t1, t2, t3, t4;
    int counter = 0;

    t1 = thread(thread1);
    t2 = thread(thread2);
    t3 = thread(thread3, ref(counter));
    t4 = thread(thread4, ref(counter));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
