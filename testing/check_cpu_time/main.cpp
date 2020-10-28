#include <iostream>
#include <xtime_cpu_time.hpp>
#include <xtime.hpp>

using namespace std;

int main() {
    cout << "get_cpu_time " << xtime::get_cpu_time() << endl;
    xtime::delay(1);
    cout << "get_cpu_time " << xtime::get_cpu_time() << endl;
    return 0;
}
