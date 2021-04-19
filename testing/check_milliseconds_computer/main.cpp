#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    std::cout << "get_str_date_time_ms: " << xtime::get_str_date_time_ms(xtime::get_ftimestamp()) << "\n";
    std::cout << "get_str_time_ms:      " << xtime::get_str_time_ms(xtime::get_ftimestamp()) << "\n";
    std::cout << "get_str_time_ms:      " << xtime::get_str_time_ms(xtime::get_ftimestamp(1,2,2007,23,5,8,567)) << "\n";
    std::cout << "get_timestamp:        " << xtime::get_timestamp("1567798104660") << "\n";
    //1567798104 -2019 19:28:24 GMT
    std::cout << "get_str_date_time_ms: " << xtime::get_str_date_time_ms(xtime::get_ftimestamp("1567798104660")) << "\n";
    std::cout << "get_millisecond:      " << xtime::get_millisecond() << "\n";
    xtime::ftimestamp_t last_gmt = xtime::get_ftimestamp();
    xtime::DateTime iDateTime(last_gmt);
    std::cout << "pc gmt: " << iDateTime.get_str_time_ms() << "\n";

    while (true) {
        xtime::ftimestamp_t ftimestamp = xtime::get_ftimestamp();
        xtime::timestamp_t timestamp_ms = xtime::get_timestamp_ms();
        if(ftimestamp - last_gmt > 0.1) {
            std::cout << "pc gmt: " << ftimestamp << " " << xtime::get_str_date_time_ms() << " ms: " << timestamp_ms << "\r";
            last_gmt = ftimestamp;
        }
    }
    return 0;
}
