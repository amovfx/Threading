#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

int main() {
    std::cout << "Hello, Wait!" << std::endl;
    atomic<bool> ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(1000));
        ready = true;
    });

    t1.join();

    //naieve implementatioin
    while(!ready)
    {
        this_thread::sleep_for(chrono::milliseconds(100));

    }
    cout << "Ready: " << ready << endl;

    return 0;
}
