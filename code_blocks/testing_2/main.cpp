#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    xtime::DateTime iTime(9, 10, 2018);
    unsigned long long time = iTime.get_timestamp();

    cout << "wday " << xtime::get_weekday(time) << endl;

    cout << "minute day " << xtime::get_minute_day(xtime::get_unix_timestamp(1,1,2019,23,59,59)) << endl;

    cout << "is beg day " << xtime::is_beg_day(xtime::get_unix_timestamp(1,1,2019,0,0,0)) << endl;
    cout << "is beg half hour " << xtime::is_beg_half_hour(xtime::get_unix_timestamp(1,1,2019,0,30,0)) << endl;
    cout << "is end month " << xtime::is_end_month(xtime::get_unix_timestamp(31,1,2019,0,30,0)) << endl;
    return 0;
}
