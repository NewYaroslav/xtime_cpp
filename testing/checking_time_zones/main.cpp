#include <xtime.hpp>
#include <iostream>

using namespace std;

int main()
{
    /* До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * Проверить можно тут: https://time.is/ru/compare/0200_29_Mar_2009_in_EET/UTC
     */
    cout << "GMT " << xtime::get_str_date_time(xtime::get_timestamp(27, 3, 2009, 2, 0, 0)) << endl;
    cout << "CET " << xtime::get_str_date_time(xtime::convert_gmt_to_cet(xtime::get_timestamp(27, 3, 2009, 2, 0, 0))) << endl;
    cout << "EET " << xtime::get_str_date_time(xtime::convert_gmt_to_eet(xtime::get_timestamp(27, 3, 2009, 2, 0, 0))) << endl;
    cout << "********************************************************************************" << endl;
    cout << "EET & CET  " << xtime::get_str_date_time(xtime::get_timestamp(27, 3, 2009, 2, 0, 0)) << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(27, 3, 2009, 1, 0, 0)) << endl;
    cout << "CET TO GMT " << xtime::get_str_date_time(xtime::convert_cet_to_gmt(xtime::get_timestamp(27, 3, 2009, 2, 0, 0))) << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(27, 3, 2009, 0, 0, 0)) << endl;
    cout << "EET TO GMT " << xtime::get_str_date_time(xtime::convert_eet_to_gmt(xtime::get_timestamp(27, 3, 2009, 2, 0, 0))) << endl;
    cout << "********************************************************************************" << endl;
    // проверяем перевод часов в марте
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(29, 3, 2009, 0, 0, 0)) << endl;
    cout << "CET TO GMT " << xtime::get_str_date_time(xtime::convert_cet_to_gmt(xtime::get_timestamp(29, 3, 2009, 1, 0, 0))) << endl;
    cout << "time changes" << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(29, 3, 2009, 1, 0, 0)) << endl;
    cout << "CET TO GMT " << xtime::get_str_date_time(xtime::convert_cet_to_gmt(xtime::get_timestamp(29, 3, 2009, 3, 0, 0))) << endl;
    cout << "" << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(29, 3, 2009, 0, 0, 0)) << endl;
    cout << "EET TO GMT " << xtime::get_str_date_time(xtime::convert_eet_to_gmt(xtime::get_timestamp(29, 3, 2009, 2, 0, 0))) << endl;
    cout << "time changes" << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(29, 3, 2009, 1, 0, 0)) << endl;
    cout << "EET TO GMT " << xtime::get_str_date_time(xtime::convert_eet_to_gmt(xtime::get_timestamp(29, 3, 2009, 4, 0, 0))) << endl;
    cout << "" << endl;
    cout << "********************************************************************************" << endl;
    // проверяем перевод часов в октябре
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(25, 10, 2009, 23, 0, 0)) << endl;
    cout << "CET TO GMT " << xtime::get_str_date_time(xtime::convert_cet_to_gmt(xtime::get_timestamp(25, 10, 2009, 1, 0, 0))) << endl;
    cout << "time changes" << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(25, 10, 2009, 1, 0, 0)) << endl;
    cout << "CET TO GMT " << xtime::get_str_date_time(xtime::convert_cet_to_gmt(xtime::get_timestamp(25, 10, 2009, 2, 0, 0))) << endl;
    cout << "" << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(25, 10, 2009, 23, 0, 0)) << endl;
    cout << "EET TO GMT " << xtime::get_str_date_time(xtime::convert_eet_to_gmt(xtime::get_timestamp(25, 10, 2009, 2, 0, 0))) << endl;
    cout << "time changes" << endl;
    cout << "CHECK GMT  " << xtime::get_str_date_time(xtime::get_timestamp(25, 10, 2009, 1, 0, 0)) << endl;
    cout << "EET TO GMT " << xtime::get_str_date_time(xtime::convert_eet_to_gmt(xtime::get_timestamp(25, 10, 2009, 3, 0, 0))) << endl;
    cout << "" << endl;
    cout << "********************************************************************************" << endl;
    cout << "GMT " << xtime::get_str_date_time(xtime::get_timestamp()) << endl;
    std::system("pause");
    return 0;
}
