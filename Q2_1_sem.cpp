#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t semaphore;

void runMeFirst() {
    cout << "Run me first" << endl;
    sem_post(&semaphore); // Signal that runMeFirst has finished
}

void runMeSecond() {
    sem_wait(&semaphore); // Wait for runMeFirst to finish
    cout << "I run second" << endl;
}

int main() {
    sem_init(&semaphore, 0, 0); // Initialize semaphore

    thread t1(runMeFirst);
    thread t2(runMeSecond);

    t1.join();
    t2.join();

    sem_destroy(&semaphore); // Destroy semaphore

    return 0;
}
