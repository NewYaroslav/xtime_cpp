#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{

    std::cout << xtime::get_str_date(xtime::get_week_start_first_timestamp(xtime::get_timestamp(1,1,2019))) << std::endl;
    std::cout << xtime::get_weekday(xtime::get_week_start_first_timestamp(xtime::get_timestamp(1,1,2019))) << std::endl;
    xtime::delay_ms(5000);
    std::cout << xtime::get_str_date(xtime::get_week_end_first_timestamp(xtime::get_timestamp(1,1,2019))) << std::endl;
    std::cout << xtime::get_weekday(xtime::get_week_end_first_timestamp(xtime::get_timestamp(1,1,2019))) << std::endl;
    xtime::delay_ms(5000);
    std::cout << xtime::get_str_date(xtime::get_first_timestamp_next_day(xtime::get_timestamp(1,1,2019), 14)) << std::endl;
    xtime::delay_ms(5000);
    return 0;
}
