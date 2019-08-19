#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {

    xtime::timestamp_t last_gmt = xtime::get_timestamp();
    while(1) {
        xtime::timestamp_t unix = xtime::get_timestamp();
        if(unix != last_gmt) {
            std::cout << "pc gmt: " << unix << " " << xtime::get_str_date_time() << "\r";
            last_gmt = unix;
        }
    }
    return 0;
}
