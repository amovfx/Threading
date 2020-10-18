#include <iostream>
#include <thread>


using namespace std;

class App
{
private:
    const int ITERATIONS = 1E6;
    int count = 0;
    mutex mtx;

public:
    void operator()()
    {
        for (int i =0; i < ITERATIONS; i++)
        {
            const lock_guard<mutex> guard(mtx);
            count += 1;

        }
    }

    int getCount() const {
        return count;
    }

};

int main() {
    std::cout << "Hello, Mutex" << std::endl;

    App app;

    thread t1(ref(app));
    thread t2(ref(app));

    t1.join();
    t2.join();

    cout << app.getCount();
    return 0;
}
