#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    xtime::timestamp_t timestamp[10];
    cout << "check 2019" << endl;
    // 20:25:00, 29 Aug парсим
    timestamp[0] = xtime::get_timestamp(1,1,2019);
    timestamp[1] = xtime::get_timestamp(28,2,2019);
    timestamp[2] = xtime::get_timestamp(1,3,2019);
    for(uint32_t i = 0; i < 3; ++i) {
        cout << xtime::get_str_date_time(timestamp[i]) << endl;
        cout << "get_month " << xtime::get_month(timestamp[i]) << endl;
        cout << "get_day_month " << xtime::get_day_month(timestamp[i]) << endl;
        cout << endl;
    }

    timestamp[3] = xtime::get_timestamp(1,1,2016);
    timestamp[4] = xtime::get_timestamp(29,2,2016);
    timestamp[5] = xtime::get_timestamp(1,3,2016);
    timestamp[6] = xtime::get_timestamp(30,3,2016);
    cout << "check 2016" << endl;
    for(uint32_t i = 3; i <= 6; ++i) {
        cout << xtime::get_str_date_time(timestamp[i]) << endl;
        cout << "get_month_year " << xtime::get_month(timestamp[i]) << endl;
        cout << "get_day_month " << xtime::get_day_month(timestamp[i]) << endl;
        cout << endl;
    }

    cout << "check 01.2016" << endl;
    for(int i = 1; i <= 31; ++i) {
        xtime::timestamp_t timestamp = xtime::get_timestamp(i,1,2016);
        cout << "get_day_month " << xtime::get_day_month(timestamp) << endl;
    }
    cout << "check 02.2016" << endl;
    for(int i = 1; i <= 29; ++i) {
        xtime::timestamp_t timestamp = xtime::get_timestamp(i,2,2016);
        cout << "get_day_month " << xtime::get_day_month(timestamp) << endl;
    }
    cout << "check 03.2016" << endl;
    for(int i = 1; i <= 31; ++i) {
        xtime::timestamp_t timestamp = xtime::get_timestamp(i,3,2016);
        cout << "get_day_month " << xtime::get_day_month(timestamp) << endl;
    }
    for(int i = 1; i <= 31; ++i) {
        xtime::timestamp_t timestamp = xtime::get_timestamp(i,1,2016);
        cout << "get_month " << xtime::get_month(timestamp) << endl;
    }
    return 0;
}
