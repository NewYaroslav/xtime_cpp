#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    xtime::timestamp_t timestamp[5];

    timestamp[0] = xtime::get_timestamp(1,1,2019);
    timestamp[1] = xtime::get_timestamp(1,2,2018);
    timestamp[2] = xtime::get_timestamp(28,2,2017);
    timestamp[3] = xtime::get_timestamp(1,3,2016);
    timestamp[4] = xtime::get_timestamp(1,3,2015);

    for(uint32_t i = 0; i < 5; ++i) {
        cout << xtime::get_str_date_time(timestamp[i]) << endl;
        cout << "get_day " << xtime::get_day(timestamp[i]) << endl;
        cout << "get_year " << xtime::get_year(timestamp[i]) << endl;
        cout << "get_day_year " << xtime::get_day_year(timestamp[i]) << endl;
        cout << endl;
    }

    return 0;
}
