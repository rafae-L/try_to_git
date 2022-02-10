#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

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
    std::vector<double> trash;


    std::cout << "[1] Simple actions in every step" << std::endl;
    std::cout << "Main time is: "; {
        Timer<microseconds> main_time;
        for (auto i = 0u; i < N; i++)
            result += (std::sin(i) + std::cos(i));
    }

    trash.push_back(result);
    result = 0.;

    std::cout << "Time with actions is: "; {
        Timer<microseconds > t;
        for (auto i = 0u; i < N; i++) {
            t.Resume();

            result += (std::sin(i) + std::cos(i));

            t.Pause();
        }
    }

    trash.push_back(result);
    result = 0.;

    auto M = 1000u;

    std::cout << std::endl << "[2] Hard actions in every step" << std::endl;
    std::cout << "Main time is: "; {
        Timer<microseconds> main_time;
        for (auto i = 0u; i < M; i++)
            for(int j = 0u; j < M; j++)
                result += (std::sin(i) + std::cos(i));
    }

    trash.push_back(result);
    result = 0.;

    std::cout << "Time with actions is: "; {
        Timer<microseconds > t;
        for (auto i = 0u; i < M; i++) {
            t.Resume();

            for(int j = 0u; j < M; j++)
                result += (std::sin(i) + std::cos(i));

            t.Pause();
        }
    }


    return 0;
}
