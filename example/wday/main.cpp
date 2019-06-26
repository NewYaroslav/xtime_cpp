#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    xtime::DateTime iTime(9, 10, 2018);
    unsigned long long time = iTime.get_timestamp();

    cout << "wday " << xtime::get_weekday(time) << endl;

    cout << "minute day " << xtime::get_minute_day(xtime::get_unix_timestamp(1,1,2019,23,59,59)) << endl;

    return 0;
}
