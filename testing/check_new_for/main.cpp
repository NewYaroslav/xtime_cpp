#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    xtime::for_minutes(
            xtime::get_timestamp(1,1,2019),
            xtime::get_timestamp(1,2,2019),
            [&](const xtime::timestamp_t &timestamp){
        std::cout << xtime::get_str_date_time(timestamp) << std::endl;
    });
    return 0;
}
