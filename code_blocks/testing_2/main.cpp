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

    cout << "get minute day " << xtime::get_minute_day(xtime::get_unix_timestamp(31,1,2019,0,30,0)) << endl;
    cout << "get hour day " << xtime::get_hour_day(xtime::get_unix_timestamp(31,1,2019,3,30,0)) << endl;

    cout << "get year " << xtime::get_year(xtime::get_unix_timestamp(31,12,2019,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_unix_timestamp(31,12,2018,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_unix_timestamp(31,12,2017,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_unix_timestamp(31,12,2016,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_unix_timestamp(31,12,2015,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_unix_timestamp(31,12,2014,0,0,0)) << endl;

    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_unix_timestamp(1,1,2016,0,0,0)) << endl;
    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_unix_timestamp(1,1,2015,0,0,0)) << endl;
    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_unix_timestamp(1,1,2014,0,0,0)) << endl;
    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_unix_timestamp(1,1,2013,0,0,0)) << endl;

    cout << "get_unix_timestamp " << xtime::get_unix_timestamp(1,1,2013,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2013) << endl;

    cout << "get_unix_timestamp " << xtime::get_unix_timestamp(1,1,2012,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2012) << endl;

    cout << "get_unix_timestamp " << xtime::get_unix_timestamp(1,1,2011,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2011) << endl;

    cout << "get_unix_timestamp " << xtime::get_unix_timestamp(1,1,2010,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2010) << endl;

    cout << "get_day_year " << xtime::get_day_year(xtime::get_unix_timestamp(1,1,2013,0,0,0)) << endl;
    cout << "get_day_year " << xtime::get_day_year(xtime::get_unix_timestamp(15,1,2013,0,0,0)) << endl;
    cout << "get_day_year " << xtime::get_day_year(xtime::get_unix_timestamp(16,10,2013,0,0,0)) << endl;
    cout << "get_day_year " << xtime::get_day_year(xtime::get_unix_timestamp(31,12,2016,0,0,0)) << endl;
    return 0;
}
