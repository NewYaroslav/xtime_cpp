#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    std::cout << "check: " << xtime::get_str_date_time_ms(xtime::get_timestamp_ms()) << "\n";
    std::cout << "check: " << xtime::get_str_time_ms(xtime::get_timestamp_ms()) << "\n";
    std::cout << "check: " << xtime::get_str_time_ms(xtime::get_timestamp_ms(1,2,2007,23,5,8,567)) << "\n";
    std::cout << "check: " << xtime::get_timestamp("1567798104660") << "\n";
    //1567798104 -2019 19:28:24 GMT
    std::cout << "check: " << xtime::get_str_date_time_ms(xtime::get_timestamp_ms("1567798104660")) << "\n";

    double last_gmt = xtime::get_timestamp_ms();
    xtime::DateTime iDateTime(last_gmt);
    std::cout << "pc gmt: " << iDateTime.get_str_time_ms() << "\n";

    while(1) {
        double unix = xtime::get_timestamp_ms();
        if(unix - last_gmt > 0.1) {
            std::cout << "pc gmt: " << unix << " " << xtime::get_str_date_time_ms() << "\r";
            last_gmt = unix;
        }
    }
    return 0;
}
