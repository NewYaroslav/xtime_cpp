#include <xtime.hpp>
#include <iostream>

using namespace std;

int main()
{
    xtime::DateTime iTime(9, 10, 2018);
    xtime::timestamp_t time = iTime.get_timestamp();

    cout << "get_timestamp " << xtime::get_timestamp(31,12,2019,0,0,0) << endl;
    cout << "get_timestamp " << xtime::get_timestamp(31,12,2019,0) << endl;
    cout << "get_timestamp " << xtime::get_timestamp(1,3,4000) << endl;
    cout << "get_str_date_time " << xtime::get_str_date_time(xtime::get_timestamp(1,1,4000,22,55,56)) << endl;

    cout << "--------------------------------------" << endl;
    xtime::DateTime iBigTime(9, 10, 4000, 22,55,56);
    cout << "get_str_date_time for 4000 year " << iBigTime.get_str_date_time() << endl;
    cout << "get_timestamp 4000 year " << iBigTime.get_timestamp() << endl;
    xtime::DateTime iBigTime2(iBigTime.get_timestamp());
    cout << "DateTime.get_timestamp() in get_str_date_time 4000 year " << xtime::get_str_date_time(iBigTime2.get_timestamp()) << endl;

    cout << "--------------------------------------" << endl;

    cout << "get_timestamp " << xtime::get_timestamp(31,12,2016,22,55,56) << endl;
    cout << "get_str_date_time " << xtime::get_str_date_time(xtime::get_timestamp(31,12,2016,22,55,56)) << endl;
    cout << "get_str_time " << xtime::get_str_time(xtime::get_timestamp(31,12,2016,22,55,56)) << endl;
    cout << "--------------------------------------" << endl;

    cout << "get_str_date " << xtime::get_str_date(xtime::get_start_minute(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    cout << "get_str_time " << xtime::get_str_time(xtime::get_start_minute(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;

    cout << "wday " << xtime::get_weekday(time) << endl;

    cout << "minute day " << xtime::get_minute_day(xtime::get_timestamp(1,1,2019,23,359,59)) << endl;

    cout << "is beg day " << xtime::is_beg_day(xtime::get_timestamp(1,1,2019,0,0,0)) << endl;
    cout << "is beg half hour " << xtime::is_beg_half_hour(xtime::get_timestamp(1,1,2019,0,30,0)) << endl;
    cout << "is end month " << xtime::is_end_month(xtime::get_timestamp(31,1,2019,0,30,0)) << endl;

    cout << "get minute day " << xtime::get_minute_day(xtime::get_timestamp(31,1,2019,0,30,0)) << endl;
    cout << "get hour day " << xtime::get_hour_day(xtime::get_timestamp(31,1,2019,3,30,0)) << endl;

    cout << "get year " << xtime::get_year(xtime::get_timestamp(31,12,2019,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_timestamp(31,12,2018,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_timestamp(31,12,2017,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_timestamp(31,12,2016,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_timestamp(31,12,2015,0,0,0)) << endl;
    cout << "get year " << xtime::get_year(xtime::get_timestamp(31,12,2014,0,0,0)) << endl;

    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_timestamp(1,1,2016,0,0,0)) << endl;
    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_timestamp(1,1,2015,0,0,0)) << endl;
    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_timestamp(1,1,2014,0,0,0)) << endl;
    cout << "get_day_in_year " << xtime::get_day_in_year(xtime::get_timestamp(1,1,2013,0,0,0)) << endl;

    cout << "get_timestamp " << xtime::get_timestamp(1,1,2013,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2013) << endl;

    cout << "get_timestamp " << xtime::get_timestamp(1,1,2012,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2012) << endl;

    cout << "get_timestamp " << xtime::get_timestamp(1,1,2011,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2011) << endl;

    cout << "get_timestamp " << xtime::get_timestamp(1,1,2010,0,0,0) << endl;
    cout << "get_timestamp_beg_year " << xtime::get_timestamp_beg_year(2010) << endl;

    cout << "get_day_year " << xtime::get_day_year(xtime::get_timestamp(1,1,2013,0,0,0)) << endl;
    cout << "get_day_year " << xtime::get_day_year(xtime::get_timestamp(15,1,2013,0,0,0)) << endl;
    cout << "get_day_year " << xtime::get_day_year(xtime::get_timestamp(16,10,2013,0,0,0)) << endl;
    cout << "get_day_year " << xtime::get_day_year(xtime::get_timestamp(31,12,2016,0,0,0)) << endl;

    cout << "get_start_day " << xtime::get_str_date_time(xtime::get_start_day(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    cout << "get_start_hour " << xtime::get_str_date_time(xtime::get_start_hour(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    cout << "get_start_minute " << xtime::get_str_date_time(xtime::get_start_minute(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    return 0;
}
