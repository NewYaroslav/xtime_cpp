#include <iostream>
#include <xtime.hpp>
#include <stdio.h>
#include <time.h>

using namespace std;

int main()
{
    double seconds = 0;
    for(uint32_t i = 0; i < 100000; ++i) {
        clock_t start = clock();
        xtime::timestamp_t timestamp = xtime::get_timestamp();
        clock_t end = clock();
        seconds += (double)(end - start);
    }
    seconds /= 100000.0;
    seconds /= CLOCKS_PER_SEC;
    std::cout << "seconds " << seconds << std::endl;
    xtime::timestamp_t timestamp = xtime::get_timestamp(1,1,2019);
    xtime::oadate_t oadate = xtime::convert_timestamp_to_oadate(timestamp);
    cout << "oadate " << oadate << endl;
    cout << "timestamp " << timestamp << endl;
    cout << "date " << xtime::get_str_date_time(xtime::convert_oadate_to_timestamp(oadate)) << endl;
    xtime::timestamp_t stop_timestamp = xtime::get_timestamp(31,12,9999);
    cout << "31.12.9999 oadate " << xtime::convert_timestamp_to_oadate(stop_timestamp) << endl;
    cout << "31.12.9999 oadate " << xtime::get_oadate(31,12,9999) << endl;
    cout.precision(12);
    xtime::timestamp_t last_timestamp = xtime::get_timestamp();
    while(true) {
        if(xtime::get_timestamp() > last_timestamp) {
            std::cout << "oadate " << xtime::get_ole_automation_date() << std::endl;
            last_timestamp = xtime::get_timestamp();
        }
    }
    return 0;
}
