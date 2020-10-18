#include <iostream>
#include <thread>


using namespace std;

int main() {
    std::cout << "Hello, Mutex" << std::endl;

    const int ITERATIONS = 1E6;
    int count = 0;

    mutex mtx;

    auto fn =  [&]() {
        for (int i =0; i < ITERATIONS; i++)
        {
            mtx.lock();
            count += 1;
            mtx.unlock();
        }
    };

    thread t1(fn);
    thread t2(fn);

    t1.join();
    t2.join();

    cout << count;
    return 0;
}
