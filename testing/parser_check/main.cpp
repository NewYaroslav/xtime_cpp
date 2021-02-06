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

    cout << "parser check: 2017.12.21" << endl;
    bool is_convert6 = xtime::convert_str_to_timestamp("2017.12.21", timestamp);
    if(is_convert6) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;

    cout << "parser check: 21.09.2018" << endl;
    bool is_convert7 = xtime::convert_str_to_timestamp("21.09.2018", timestamp);
    if(is_convert7) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;

    cout << "parser check: 2020-09-27T01:25:08.000000Z" << endl;
    bool is_convert8 = xtime::convert_str_to_timestamp("2020-09-27T01:25:08.000000Z", timestamp);
    if(is_convert8) cout << "get_timestamp " << xtime::get_str_date_time(timestamp) << endl;
    else cout << "convert_str_to_timestamp error" << endl << endl;

    cout << "parser check (2): 2020-09-27T01:25:08.000000Z" << endl;
    xtime::DateTime date_time9;
    bool is_convert9 = xtime::convert_iso("2020-09-27T01:25:08.000000Z", date_time9);
    if(is_convert9) cout << "get_timestamp " << xtime::get_str_date_time(date_time9.get_timestamp()) << endl;
    else cout << "convert_iso error" << endl << endl;

    cout << "parser check (3): 2020-10-12T14:48:46.618757Z" << endl;
    xtime::DateTime date_time10;
    bool is_convert10 = xtime::convert_iso("2020-10-12T14:48:46.618757Z", date_time10);
    if(is_convert10) cout << "get_ftimestamp " << xtime::get_str_date_time_ms(date_time10.get_ftimestamp()) << endl;
    else cout << "convert_iso error" << endl << endl;

    cout << "parser check (4): 2020-12-09T17:21:00Z" << endl;
    xtime::DateTime date_time11;
    bool is_convert11 = xtime::convert_iso("2020-12-09T17:21:15Z", date_time11);
    if(is_convert11) cout << "get_ftimestamp " << xtime::get_str_date_time_ms(date_time11.get_ftimestamp()) << endl;
    else cout << "convert_iso error" << endl << endl;

    cout << "parser check (5): 2020-12-09T17:14:16.117642" << endl;
    xtime::DateTime date_time12;
    bool is_convert12 = xtime::convert_iso("2020-12-09T17:14:16.117642", date_time12);
    if(is_convert12) cout << "get_ftimestamp " << xtime::get_str_date_time_ms(date_time12.get_ftimestamp()) << endl;
    else cout << "convert_iso error" << endl << endl;

    cout << "parser check (6): 2017-10-19T15:45:44.941Z" << endl;
    xtime::DateTime date_time13;
    bool is_convert13 = xtime::convert_iso("2017-10-19T15:45:44.941Z", date_time13);
    if(is_convert13) cout << "get_ftimestamp " << xtime::get_str_date_time_ms(date_time13.get_ftimestamp()) << endl;
    else cout << "convert_iso error" << endl << endl;

    cout << "parser check (7):  2013-12-06T15:23:01+01:33" << endl;
    xtime::DateTime date_time14;
    bool is_convert14 = xtime::convert_iso("2013-12-06T15:23:01+01:33", date_time14);
    if(is_convert14) cout << "get_ftimestamp " << xtime::get_str_date_time_ms(date_time14.get_ftimestamp()) << endl;
    else cout << "convert_iso error" << endl << endl;

    cout << "parser check (8): 2017-10-19T15:45:44.941Z" << endl;
    cout << "get_ftimestamp " << xtime::get_str_date_time_ms(xtime::convert_iso("2017-10-19T15:45:44.941Z")) << endl;
    return 0;
}
