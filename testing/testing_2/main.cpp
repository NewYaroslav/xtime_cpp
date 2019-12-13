#include <xtime.hpp>
#include <iostream>

using namespace std;

int main()
{
    // 20:25:00, 29 Aug парсим
    xtime::timestamp_t timestamp;
    bool is_convert = xtime::convert_str_to_timestamp("20:25:00, 29 Aug", timestamp);
    if(is_convert) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl;
    else cout << "convert_str_to_timestamp error" << endl;

    cout << "get_month " << xtime::get_month("Aug") << endl;
    cout << "get_second_minute " << xtime::get_second_minute(xtime::get_timestamp(1,1,2017,2,3,6)) << endl;
    cout << "get_last_timestamp_day " << xtime::get_str_date_time(xtime::get_last_timestamp_day(xtime::get_timestamp(1,1,2017,2,3,6))) << endl;

    cout << "--------------------------------------" << endl;
    cout << "get_timestamp " << xtime::get_timestamp(31,12,2016) << endl; // 1483142400
    cout << "get_str_date_time " << xtime::get_str_date(xtime::get_timestamp(31,12,2016)) << endl;
    cout << "get_str_date_time " << xtime::get_str_date(xtime::get_timestamp(1,1,2017)) << endl;
    cout << "get_str_date_time " << xtime::get_str_date(xtime::get_timestamp(2,1,2017)) << endl;
    cout << "get_str_date_time " << xtime::get_str_date(xtime::get_timestamp(3,1,2017)) << endl;
    cout << "get_str_date_time " << xtime::get_str_date(xtime::get_timestamp(4,1,2017)) << endl;
    cout << "get_str_date_time " << xtime::get_str_date(xtime::get_timestamp(5,1,2017)) << endl;
    cout << "--------------------------------------" << endl;

    cout << "get_weekday " << xtime::get_weekday(24,3,2018) << endl; // Суббота
    cout << "get_weekday " << xtime::get_weekday(xtime::get_timestamp(25,3,2018)) << endl; // Воскресенье
    cout << "get_weekday " << xtime::get_weekday(xtime::get_timestamp(26,3,2018)) << endl; // Понедельник

    cout << "is_day_off " << xtime::is_day_off(xtime::get_timestamp(24,3,2018)) << endl;
    cout << "is_day_off " << xtime::is_day_off(xtime::get_timestamp(25,3,2018)) << endl;
    cout << "is_day_off " << xtime::is_day_off(xtime::get_timestamp(26,3,2018)) << endl;

    cout << "--------------------------------------" << endl;

    cout << "is_leap_year " << xtime::is_leap_year(xtime::get_year(xtime::get_timestamp(29,2,2016))) << endl;
    cout << "get_month " << xtime::get_month(xtime::get_timestamp(29,2,2016)) << endl;
    cout << "get_month " << xtime::get_month(xtime::get_timestamp(1,3,2016)) << endl;

    cout << "is_leap_year " << xtime::is_leap_year(xtime::get_year(xtime::get_timestamp(28,2,2015))) << endl;
    cout << "get_month " << xtime::get_month(xtime::get_timestamp(28,2,2015)) << endl;
    cout << "get_month " << xtime::get_month(xtime::get_timestamp(1,3,2015)) << endl;
    cout << "get_month " << xtime::get_month(xtime::get_timestamp(31,12,2015)) << endl;
    cout << "get_num_days_month " << xtime::get_num_days_month(xtime::get_timestamp(31,12,2015)) << endl;
    cout << "--------------------------------------" << endl;
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

    cout << "get_str_date " << xtime::get_str_date(xtime::get_first_timestamp_minute(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    cout << "get_str_time " << xtime::get_str_time(xtime::get_first_timestamp_minute(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;

    cout << "--------------------------------------" << endl;
    xtime::DateTime iTime(9, 10, 2018);
    xtime::timestamp_t time = iTime.get_timestamp();
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

    cout << "get_first_timestamp_day " << xtime::get_str_date_time(xtime::get_first_timestamp_day(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    cout << "get_first_timestamp_hour " << xtime::get_str_date_time(xtime::get_first_timestamp_hour(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;
    cout << "get_first_timestamp_minute " << xtime::get_str_date_time(xtime::get_first_timestamp_minute(xtime::get_timestamp(31,12,2016,22,55,56))) << endl;

    cout << "get_minute_hour " << xtime::get_minute_hour(xtime::get_timestamp(31,12,2016,0,33,0)) << endl;
    return 0;
}
