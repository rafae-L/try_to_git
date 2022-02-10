#include <iostream>
#include <chrono>
#include <cmath>

using namespace std::chrono;

class Timer {
public:
    Timer() {}
    ~Timer() {
        std::cout << duration_cast<std::chrono::microseconds>(steady_clock::now() - start).count() << std::endl;
    }

private:
    steady_clock::time_point start = steady_clock::now();
};


int main() {
    double result = 0.;
    {
        Timer t;
        for(auto i = 0u; i < 10000000u; i++) {
            result += std::sin(i) + std::cos(i);
        }
    }
    std::cout << "Result is " << result;
    return 0;
}
