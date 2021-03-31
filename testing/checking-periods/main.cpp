#include <iostream>
#include <xtime.hpp>
#include <deque>

using namespace std;

int main() {
    xtime::period_t period;
    xtime::fperiod_t fperiod;

    period.start = xtime::get_timestamp();
    period.stop = period.start + xtime::SECONDS_IN_DAY;

    fperiod.start = xtime::get_ftimestamp();
    fperiod.stop = fperiod.start + xtime::SECONDS_IN_DAY;

    std::cout << "period #1: "
        << xtime::get_str_date_time(period.start)
        << " - "
        << xtime::get_str_date_time(period.stop) << std::endl;

    std::cout << "fperiod #1: "
        << xtime::get_str_date_time_ms(fperiod.start)
        << " - "
        << xtime::get_str_date_time_ms(fperiod.stop) << std::endl;
    std::cout << std::endl;

    std::deque<xtime::period_t> periods;
    periods.push_back(xtime::period_t(xtime::get_timestamp(1,1,2021), xtime::get_timestamp(1,3,2021)));
    periods.push_back(xtime::period_t(xtime::get_timestamp(1,1,2018), xtime::get_timestamp(1,2,2018)));
    periods.push_back(xtime::period_t(xtime::get_timestamp(1,1,2019), xtime::get_timestamp(1,2,2019)));
    periods.push_back(xtime::period_t(xtime::get_timestamp(2,2,2019), xtime::get_timestamp(1,3,2019)));
    periods.push_back(xtime::period_t(xtime::get_timestamp(1,2,2018), xtime::get_timestamp(1,3,2018)));

    std::cout << "array periods:" << std::endl;
    for(auto p : periods) {
        std::cout
        << xtime::get_str_date_time(p.start)
        << " - "
        << xtime::get_str_date_time(p.stop) << std::endl;
    }
    std::cout << std::endl;

    std::cout << "sort periods:" << std::endl;
    sort_periods(periods);

    for(auto p : periods) {
        std::cout
        << xtime::get_str_date_time(p.start)
        << " - "
        << xtime::get_str_date_time(p.stop) << std::endl;
    }
    std::cout << std::endl;

    std::deque<xtime::period_t> periods2(periods);
    std::deque<xtime::period_t> insert_periods;
    std::deque<xtime::period_t> remove_periods;
    merge_periods(periods);

    merge_periods(periods2, insert_periods, remove_periods);
    std::cout << "merge periods:" << std::endl;
    for(auto p : periods) {
        std::cout
        << xtime::get_str_date_time(p.start)
        << " - "
        << xtime::get_str_date_time(p.stop) << std::endl;
    }
    std::cout << "insert periods:" << std::endl;
    for(auto p : insert_periods) {
        std::cout
        << xtime::get_str_date_time(p.start)
        << " - "
        << xtime::get_str_date_time(p.stop) << std::endl;
    }
    std::cout << "remove periods:" << std::endl;
    for(auto p : remove_periods) {
        std::cout
        << xtime::get_str_date_time(p.start)
        << " - "
        << xtime::get_str_date_time(p.stop) << std::endl;
    }
    std::cout << std::endl;

    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(31,12,2018,23,59,59);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(31,12,2017,23,59,59);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(1,1,2018);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(1,1,2019);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(1,2,2019);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(1,2,2019,0,0,1);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(1,3,2021,0,0,0);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        const xtime::timestamp_t timestamp = xtime::get_timestamp(1,3,2021,0,0,1);
        std::cout << "find period for date: " << xtime::get_str_date_time(timestamp) << std::endl;
        auto it = xtime::find_period(periods, timestamp);
        if (it == periods.end()) std::cout << "not found period for date: " << xtime::get_str_date_time(timestamp) << std::endl << std::endl;
        else std::cout << "found period: "
            << xtime::get_str_date_time(it->start)
            << " - "
            << xtime::get_str_date_time(it->stop) << std::endl << std::endl;
    }
    {
        xtime::period_t period1(xtime::get_timestamp(1,1,2020),xtime::get_timestamp(1,1,2021));
        xtime::period_t period2(xtime::get_timestamp(1,1,2019),xtime::get_timestamp(1,1,2020));
        xtime::period_t period3(xtime::get_timestamp(1,1,2022),xtime::get_timestamp(1,1,2023));
        xtime::period_t period4(xtime::get_timestamp(1,1,2018),xtime::get_timestamp(1,2,2019));
        std::cout << "period #1: "
            << xtime::get_str_date_time(period1.start)
            << " - "
            << xtime::get_str_date_time(period1.stop) << std::endl;
        std::cout << "period #2: "
            << xtime::get_str_date_time(period2.start)
            << " - "
            << xtime::get_str_date_time(period2.stop) << std::endl;
        std::cout << "period #3: "
            << xtime::get_str_date_time(period3.start)
            << " - "
            << xtime::get_str_date_time(period3.stop) << std::endl;
        std::cout << "period #4: "
            << xtime::get_str_date_time(period3.start)
            << " - "
            << xtime::get_str_date_time(period3.stop) << std::endl;
        std::cout << "intersection periods (1,2): " << xtime::intersection_periods(period1, period2) << std::endl;
        std::cout << "intersection periods (2,3): " << xtime::intersection_periods(period2, period3) << std::endl;
        std::cout << "intersection periods (1,3): " << xtime::intersection_periods(period1, period3) << std::endl;
        std::cout << "intersection periods (2,4): " << xtime::intersection_periods(period2, period4) << std::endl;

    }
    return 0;
}
