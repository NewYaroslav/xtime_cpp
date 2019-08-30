#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    cout << "parser check: 20:25:00, 29 Aug 19" << endl;
    // 20:25:00, 29 Aug парсим
    xtime::timestamp_t timestamp;
    bool is_convert = xtime::convert_str_to_timestamp("20:25:00, 29 Aug 19", timestamp);
    if(is_convert) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;

    cout << "parser check: Aug" << endl;
    cout << "get_month " << xtime::get_month("Aug") << endl;

    cout << "parser check: 00:59:59 30.08.2019" << endl;
    bool is_convert2 = xtime::convert_str_to_timestamp("00:59:59 30.08.2019", timestamp);
    if(is_convert2) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;;

    cout << "parser check: 2013-02-25 18:25:10" << endl;
    bool is_convert3 = xtime::convert_str_to_timestamp("2013-02-25 18:25:10", timestamp);
    if(is_convert3) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;

    cout << "parser check: 01/01/1973 01:00:00" << endl;
    bool is_convert4 = xtime::convert_str_to_timestamp("01/01/1973 01:00:00", timestamp);
    if(is_convert4) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;

    cout << "parser check: 00:59:59 30.08.19" << endl;
    bool is_convert5 = xtime::convert_str_to_timestamp("00:59:59 30.08.19", timestamp);
    if(is_convert5) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;
    return 0;
}
