
#include <future>
#include <thread>
#include <iomanip>
#include <iostream>

#include <vector>



using namespace std;

class ThreadPool
{
    int num_threads{1};
    vector<thread*> workers;

public:
    ThreadPool()
    {
        num_threads = thread::hardware_concurrency()-1;
        cout << "Making: " << num_threads << "threads" << endl;
        for (int i = 0; i < num_threads; i ++)
        {
            workers.emplace_back(new thread);
        }
    }


};


double calculate_pi(const int& start, const int& end)
{
    double result = 0;
    for(int i = start; i < start + end; i++)
    {
        int sign = !(i & 1) * 2 - 1;
        double denom = 1. / (i * 2 + 1);
        result += sign * denom;
    }
    return result;
}


int main() {
    std::cout << "Hello, Threads!" << std::endl;
//
//create packaged tasks
    //packaged_task<double(int,int)> task(bind(calculate_pi, 0, 1E6));
    //future<double> result = task.get_future();
    promise<double> promise;
    auto do_work = [&promise](const int& start, const int& end){
        double result = calculate_pi(start, end);
        promise.set_value(result);
    };

    thread t1(do_work,0, 1000);
    t1.join();

    future<double> future = promise.get_future();
    cout << setprecision(16) << future.get()*4 << endl;


    //calculate_pi(0, 5);

    //ThreadPool threadpool;

    return 0;
}
