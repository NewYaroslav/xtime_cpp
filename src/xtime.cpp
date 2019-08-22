/*
* xtime_cpp - Library for work with time.
*
* Copyright (c) 2018 Elektro Yar. Email: git.electroyar@gmail.com
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "xtime.hpp"
#include "stdio.h"
#include <ctime>
#include <vector>

namespace xtime {

    timestamp_t get_timestamp() {
        time_t rawtime;
        time(&rawtime);
        struct tm* ptm;

        ptm = gmtime(&rawtime);
        DateTime iTime(ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        return iTime.get_timestamp();
    }

    timestamp_t get_timestamp(const int day, const int month, const int year, const int hour, const int minutes, const int seconds) {
        timestamp_t _secs;
        long _mon, _year;
        long long _days; // для предотвращения проблемы 2038 года переменная должна быть больше 32 бит
        _mon = month - 1;
        const long _TBIAS_YEAR = 1900;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        _year = year - _TBIAS_YEAR;
        _days = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[_mon] : lmos[_mon])) - 1;
        _days += DAYS_IN_YEAR * _year;
        _days += day;
        const long _TBIAS_DAYS = 25567;
        _days -= _TBIAS_DAYS;
        _secs = SECONDS_IN_HOUR * hour;
        _secs += SECONDS_IN_MINUTE * minutes;
        _secs += seconds;
        _secs += _days * SECONDS_IN_DAY;
        return _secs;
    }

    DateTime::DateTime() {
        DateTime::day = 1;
        DateTime::month = 1;
        DateTime::year = 1970;
        DateTime::hour = 0;
        DateTime::minutes = 0;
        DateTime::seconds = 0;
    };

    DateTime::DateTime(
            const int day,
            const int month,
            const int year,
            const int hour,
            const int minutes,
            const int seconds) {
        DateTime::day = day;
        DateTime::month = month;
        DateTime::year = year;
        DateTime::hour = hour;
        DateTime::minutes = minutes;
        DateTime::seconds = seconds;
    }

    DateTime::DateTime(const timestamp_t timestamp) {
        set_timestamp(timestamp);
    }

    DateTime::DateTime(const std::string str_iso_formatted_utc_datetime) {
        convert_iso(str_iso_formatted_utc_datetime, *this);
    }

    timestamp_t DateTime::get_timestamp() {
        return xtime::get_timestamp(day, month, year, hour, minutes, seconds);
    }

    void DateTime::set_timestamp(const timestamp_t timestamp) {
        timestamp_t _secs;
        long _mon, _year;
        long long _days;
        long i;

        _secs = timestamp;
        const long _TBIAS_DAYS = 25567;
        _days = _TBIAS_DAYS;

        _days += _secs / SECONDS_IN_DAY; _secs = _secs % SECONDS_IN_DAY;
        hour = _secs / SECONDS_IN_HOUR; _secs %= SECONDS_IN_HOUR;
        minutes = _secs / SECONDS_IN_MINUTE; seconds = _secs % SECONDS_IN_MINUTE;
        const long lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        for(_year = _days / DAYS_IN_YEAR;
            _days < (i = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[0] : lmos[0]) + DAYS_IN_YEAR*_year));) {
            --_year;
        }
        _days -= i;
        const long _TBIAS_YEAR = 1900;
        year = _year + _TBIAS_YEAR;

        if(((_year) & 03) || ((_year) == 0)) {
            _mon = MONTHS_IN_YEAR;
            while(_days < mos[--_mon]) {
                month = _mon + 1;
            }
            day = _days - mos[_mon] + 1;
        } else {
            _mon = MONTHS_IN_YEAR;
            while(_days < lmos[--_mon]) {
                month = _mon + 1;
            }
            day = _days - lmos[_mon] + 1;
        }
    }

    void DateTime::print() {
        printf("%.2d.%.2d.%.4d %.2d:%.2d:%.2d\n",
            (int)day,
            (int)month,
            (int)year,
            (int)hour,
            (int)minutes,
            (int)seconds);
    }

    std::string DateTime::get_str_date_time() {
        char text[24] = {};
        sprintf(text,"%.2d.%.2d.%.4d %.2d:%.2d:%.2d",
            (int)day,
            (int)month,
            (int)year,
            (int)hour,
            (int)minutes,
            (int)seconds);
        return std::string(text);
    }

    std::string DateTime::get_str_date() {
        char text[12] = {};
        sprintf(text,"%.2d.%.2d.%.4d", (int)day, (int)month, (int)year);
        return std::string(text);
    }

    std::string DateTime::get_str_time() {
        char text[10] = {};
        sprintf(text,"%.2d:%.2d:%.2d",hour,minutes,seconds);
        return std::string(text);
    }

    int DateTime::get_weekday() {
        return xtime::get_weekday(day, month, year);
    }

    bool DateTime::is_leap_year() {
        return xtime::is_leap_year(year);
    }

    int DateTime::get_num_days_current_month() {
        return get_num_days_month(month, year);
    }

    void DateTime::set_end_month() {
        set_end_day();
        day = get_num_days_month(month, year);
    }

    bool convert_iso(const std::string str_iso_formatted_utc_datetime, DateTime& t) {
        const std::string& word = str_iso_formatted_utc_datetime;
        if(word.size() >= 26) {
            // находим дату и время
            t.year = atoi(word.substr(0, 4).c_str());
            t.month = atoi(word.substr(5, 2).c_str());
            t.day = atoi(word.substr(8, 2).c_str());
            t.hour = atoi(word.substr(11, 2).c_str());
            t.minutes = atoi(word.substr(14, 2).c_str());
            t.seconds = atoi(word.substr(17, 2).c_str());
            int gh = atoi(word.substr(20, 2).c_str());
            int gm = atoi(word.substr(23, 2).c_str());
            int offset = gh * 3600 + gm * 60;
            timestamp_t timestamp = t.get_timestamp();
            if(word.substr(19, 1) == "+") timestamp -= offset;
            else if(word.substr(19, 1) == "-") timestamp += offset;
            t.set_timestamp(timestamp);
            return true;
        }
        return false;
    }

    bool convert_str_to_timestamp(std::string str, timestamp_t& t) {
        int day = 0, month = 0, year = 0, hour = 0, minutes = 0, seconds = 0;
        str += "_";
        std::vector<std::string> output_list;
        std::size_t start_pos = 0;
        while(true) {
            std::size_t found_beg = str.find_first_of("/\\_:-. ", start_pos);
            if(found_beg != std::string::npos) {
                std::size_t len = found_beg - start_pos;
                if(len > 0)
                    output_list.push_back(str.substr(start_pos, len));
                start_pos = found_beg + 1;
            } else break;
        }

        if(output_list.size() >= 3) {
            if(output_list[0].size() >= 4) {
                year = atoi(output_list[0].c_str());
                month = atoi(output_list[1].c_str());
                day = atoi(output_list[2].c_str());
            } else
            if(output_list[2].size() >= 4) {
                day = atoi(output_list[0].c_str());
                month = atoi(output_list[1].c_str());
                year = atoi(output_list[2].c_str());
            } else {
                hour = atoi(output_list[0].c_str());
                minutes = atoi(output_list[1].c_str());
                seconds = atoi(output_list[2].c_str());
                if(output_list.size() == 6) {
                    day = atoi(output_list[0].c_str());
                    month = atoi(output_list[1].c_str());
                    year = atoi(output_list[2].c_str());
                } else {
                    return false;
                }
            }
            if(output_list.size() == 6) {
                hour = atoi(output_list[3].c_str());
                minutes = atoi(output_list[4].c_str());
                seconds = atoi(output_list[5].c_str());
            }
        } else {
            return false;
        }
        if(day >= 32 || day <= 0 || minutes >= 60 ||
            seconds >= 60 || hour >= 24 ||
            year < 1970 || month > 12 || month <= 0) {
            return false;
        }

        t = get_timestamp(day, month, year, hour, minutes, seconds);
        return true;
    }

    DateTime convert_timestamp_to_datetime(const timestamp_t timestamp) {
        DateTime outTime;
        timestamp_t _secs;
        long _mon, _year;
        long long _days;
        long i;

        _secs = timestamp;
        const long _TBIAS_DAYS = 25567;
        _days = _TBIAS_DAYS;

        _days += _secs / SECONDS_IN_DAY; _secs = _secs % SECONDS_IN_DAY;
        outTime.hour = _secs / SECONDS_IN_HOUR; _secs %= SECONDS_IN_HOUR;
        outTime.minutes = _secs / SECONDS_IN_MINUTE;
        outTime.seconds = _secs % SECONDS_IN_MINUTE;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        for (_year = _days / DAYS_IN_YEAR; _days < (i = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[0] : lmos[0]) + DAYS_IN_YEAR*_year)); ) { --_year; }
        _days -= i;
        const long _TBIAS_YEAR = 1900;
        outTime.year = _year + _TBIAS_YEAR;

        if(((_year) & 03) || ((_year) == 0)) {
            // mos
            for(_mon = MONTHS_IN_YEAR; _days < mos[--_mon];);
            outTime.month = _mon + 1;
            outTime.day = _days - mos[_mon] + 1;
        } else {
            for(_mon = MONTHS_IN_YEAR; _days < lmos[--_mon];);
            outTime.month = _mon + 1;
            outTime.day = _days - lmos[_mon] + 1;
        }
        return outTime;
    }

    int get_weekday(const int day, const int month, const int year) {
        int a, y, m, R;
        a = ( 14 - month ) / 12;
        y = year - a;
        m = month + 12 * a - 2;
        R = 7000 + ( day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12 );
        return R % 7;
    }

    void print_date_time(const timestamp_t timestamp) {
        DateTime t(timestamp);
        t.print();
    }

    std::string get_str_date_time() {
        DateTime t;
        t.set_timestamp(get_timestamp());
        return t.get_str_date_time();
    }

    int get_num_days_month(const int month, const int year) {
        if(month > MONTHS_IN_YEAR)
            return 0;
        const int num_days[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
        if(month == FEB) {
            if(is_leap_year(year)) return 29;
            else return 28;
        } else {
            return num_days[month];
        }
    }

    int get_num_days_month(const timestamp_t timestamp) {
        const int num_days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        const int month = get_month_year(timestamp);
        if(month == FEB) {
            if(is_leap_year(get_year(timestamp))) return 29;
            else return 28;
        } else {
            return num_days[month];
        }
    }

    timestamp_t convert_gmt_to_cet(const timestamp_t gmt) {
        const timestamp_t ONE_HOUR = SECONDS_IN_HOUR;
        const int OLD_START_SUMMER_HOUR = 2;
        const int OLD_STOP_SUMMER_HOUR = 3;
        const int NEW_SUMMER_HOUR = 1;
        const int MONTH_MARSH = 3;
        const int MONTH_OCTOBER = 10;
        DateTime iTime(gmt);
        int maxDays = iTime.get_num_days_current_month();
        if(iTime.year < 2002) {
            // До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
            // а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return gmt + ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_MARSH, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour + 1 >= OLD_START_SUMMER_HOUR) return gmt + ONE_HOUR * 2; // летнее время
                            return gmt + ONE_HOUR; // зимнее время
                        }
                        return gmt + ONE_HOUR; // зимнее время
                    }
                }
                return gmt + ONE_HOUR * 2; // летнее время
            } else
            if(iTime.month == MONTH_OCTOBER) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour + 2 >= OLD_STOP_SUMMER_HOUR) return gmt + ONE_HOUR; // зимнее время
                            return gmt + ONE_HOUR; // зимнее время
                        }
                        return gmt + ONE_HOUR * 2; // летнее время
                    }
                }
                return gmt + ONE_HOUR; // зимнее время
            }
            return gmt + ONE_HOUR; // зимнее время
        } else {
            // Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                    return gmt + ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_MARSH, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour >= NEW_SUMMER_HOUR)
                                return gmt + ONE_HOUR * 2; // летнее время
                            return gmt + ONE_HOUR; // зимнее время
                        }
                        return gmt + ONE_HOUR; // зимнее время
                    }
                }
                return gmt + ONE_HOUR * 2; // летнее время
            } else
            if(iTime.month == MONTH_OCTOBER) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour >= NEW_SUMMER_HOUR)
                                return gmt + ONE_HOUR; // зимнее время
                            return gmt + ONE_HOUR * 2; // летнее время
                        }
                        return gmt + ONE_HOUR * 2; // летнее время
                    }
                }
                return gmt + ONE_HOUR; // зимнее время
            }
            return gmt + ONE_HOUR; // зимнее время
        }
        return gmt + ONE_HOUR; // зимнее время
    }

    timestamp_t convert_gmt_to_eet(const timestamp_t gmt) {
        return convert_gmt_to_cet(gmt) + SECONDS_IN_HOUR;
    }

    timestamp_t convert_cet_to_gmt(const timestamp_t cet) {
        const timestamp_t ONE_HOUR = SECONDS_IN_HOUR;
        const int OLD_START_SUMMER_HOUR = 2;
        const int OLD_STOP_SUMMER_HOUR = 3;
        const int NEW_SUMMER_HOUR = 1;
        const int MONTH_MARSH = 3;
        const int MONTH_OCTOBER = 10;
        DateTime iTime(cet);
        int maxDays = iTime.get_num_days_current_month();

        if(iTime.year < 2002) {
            // До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
            // а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return cet - ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_MARSH, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour >= OLD_START_SUMMER_HOUR) return cet - ONE_HOUR * 2; // летнее время
                            return cet - ONE_HOUR; // зимнее время
                        }
                        return cet - ONE_HOUR; // зимнее время
                    }
                }
                return cet - ONE_HOUR * 2; // летнее время
            } else
            if(iTime.month == MONTH_OCTOBER) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour >= OLD_STOP_SUMMER_HOUR) return cet - ONE_HOUR; // зимнее время
                            return cet - ONE_HOUR; // зимнее время
                        }
                        return cet - ONE_HOUR * 2; // летнее время
                    }
                }
                return cet - ONE_HOUR; // зимнее время
            }
            return cet - ONE_HOUR; // зимнее время
        } else {
            // Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return cet - ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_MARSH, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour - 2 >= NEW_SUMMER_HOUR) return cet - ONE_HOUR * 2; // летнее время
                            return cet - ONE_HOUR; // зимнее время
                        }
                        return cet - ONE_HOUR; // зимнее время
                    }
                }
                return cet - ONE_HOUR * 2; // летнее время
            } else
            if(iTime.month == MONTH_OCTOBER) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour - 1 >= NEW_SUMMER_HOUR) return cet - ONE_HOUR; // зимнее время
                            return cet - ONE_HOUR * 2; // летнее время
                        }
                        return cet - ONE_HOUR * 2; // летнее время
                    }
                }
                return cet - ONE_HOUR; // зимнее время
            }
            return cet - ONE_HOUR; // зимнее время
        }
        return cet - ONE_HOUR; // зимнее время
    }

    timestamp_t convert_eet_to_gmt(const timestamp_t eet) {
        return convert_cet_to_gmt(eet - SECONDS_IN_HOUR);
    }

    std::string get_str_date_time(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_date_time();
    }

    std::string get_str_date(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_date();
    }

    std::string get_str_time(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_time();
    }

    bool is_beg_half_hour(const timestamp_t timestamp) {
        return timestamp % SECONDS_IN_HALF_HOUR == 0 ? true : false;
    }

    bool is_beg_hour(const timestamp_t timestamp) {
        return timestamp % SECONDS_IN_HOUR == 0 ? true : false;
    }

    bool is_beg_day(const timestamp_t timestamp) {
        return timestamp % SECONDS_IN_DAY == 0 ? true : false;
    }

    bool is_beg_week(const timestamp_t timestamp) {
        return get_weekday(timestamp) == SUN ? true : false;
    }

    bool is_beg_month(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return (iTime.day == 1) ? true : false;
    }

    bool is_end_month(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return (iTime.day == iTime.get_num_days_current_month()) ? true : false;
    }

    bool is_correct_date(const int day, const int month, const int year) {
        if(day < 1 || day > MAX_DAY_MONTH) return false;
        if(month > MONTHS_IN_YEAR || month < 1) return false;
        if(year < FIRST_YEAR_UNIX) return false;
        if(day > get_num_days_month(month, year)) return false;
        return true;
    }

    bool is_correct_time(const int hour, const int minutes, const int seconds) {
        if(hour < 0 || hour > 23) return false;
        if(minutes < 0 || minutes > 59) return false;
        if(seconds < 0 || seconds > 59) return false;
        return true;
    }

    bool is_correct_date_time(
            const int day,
            const int month,
            const int year,
            const int hour,
            const int minutes,
            const int seconds) {
        if(!is_correct_date(day, month, year)) return false;
        if(!is_correct_time(hour, minutes, seconds)) return false;
        return true;
    }
}
