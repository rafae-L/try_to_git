#include <iostream>
#include <chrono>
#include <cmath>

using namespace std::chrono;

template<typename T>
class Timer {
public:
    Timer() {}

    ~Timer() {
        steady_clock::time_point finish = steady_clock::now();

        std::cout << duration_cast<T>( current_foray + finish - start).count()  << std::endl;
    }

    void Pause(){
        steady_clock::time_point interval = steady_clock::now();

        if(is_clock_work) {
            current_foray += interval - start;
            is_clock_work = false;
        }
    }

    void Resume(){
        if(!is_clock_work)
        {
            is_clock_work = true;
            start = steady_clock::now();
        }
    }

private:
    std::chrono::nanoseconds current_foray = std::chrono::nanoseconds(0);
    steady_clock::time_point start = steady_clock::now();
    bool is_clock_work = true;
};


int main() {
    double result = 0.;
    auto N = 1000000u;

    std::cout << "Main time is: "; {
        Timer<microseconds> main_time;
        for (auto i = 0u; i < N; i++)
            result += (std::sin(i) + std::cos(i));
    }

    std::cout << result << std::endl;

    result = 0.;
    std::cout << "Time with actions is: "; {
        Timer<microseconds > t;
        for (auto i = 0u; i < N; i++) {
            t.Resume();

            result += (std::sin(i) + std::cos(i));

            t.Pause();
        }
    }

    std::cout << result << std::endl;

    return 0;
}
