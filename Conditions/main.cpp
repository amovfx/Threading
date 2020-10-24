#include <chrono>
#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;

int main() {
    condition_variable cv;
    mutex mtx;
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        //this lock happens second.
        unique_lock<mutex> lock(mtx);
        //ready = true;
        lock.unlock();
        cv.notify_one();

    });


    //this lock happens first.
    unique_lock<mutex> lock(mtx);
    //while(!ready)
    //{
        //doesnt return untill cv.notify_one() is called. This reliquishes the lock. On notify_one, the lock is required.
    cv.wait(lock);
    //}
    t1.join();
    std::cout << "Hello, Waiting for threads!" << std::endl;
    return 0;
}
