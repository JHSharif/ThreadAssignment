#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t sem_first, sem_second;

void runMeFirst() {
    cout << "Run me first" << endl;
    sem_post(&sem_first); // Signal that runMeFirst has finished
}

void runMeSecond() {
    sem_wait(&sem_first); // Wait for runMeFirst to finish
    cout << "I run second" << endl;
    sem_post(&sem_second); // Signal that runMeSecond has finished
}

void runMeThird() {
    sem_wait(&sem_second); // Wait for runMeSecond to finish
    cout << "I run third" << endl;
}

int main() {
    sem_init(&sem_first, 0, 0); // Initialize semaphores
    sem_init(&sem_second, 0, 0);

    thread t1(runMeFirst);
    thread t2(runMeSecond);
    thread t3(runMeThird);

    t1.join();
    t2.join();
    t3.join();

    sem_destroy(&sem_first); // Destroy semaphores
    sem_destroy(&sem_second);

    return 0;
}
