#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    {
        xtime::Timer t;
        for(size_t i = 0; i < 5; ++i) {
            t.start_measurement();
            xtime::delay(1);
            t.stop_measurement();
        }
        std::cout << "average delay " << t.get_average_measurements() << std::endl;
    }
    {
        xtime::Timer t;
        xtime::delay(1);
        std::cout << "elapsed " << t.get_elapsed() << std::endl;
    }
    return 0;
}
