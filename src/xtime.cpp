/*
* xtime_cpp - Library for work with time.
*
* Copyright (c) 2018 Yaroslav Barabanov. Email: elektroyar@yandex.ru
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
#include "string.h"
#include <ctime>

namespace xtime {

    xtime_timestamp get_unix_timestamp() {
        time_t rawtime;
        time(&rawtime);
        struct tm* ptm;

        ptm = gmtime(&rawtime);
        DateTime iTime(ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        return iTime.get_unix_timestamp();
    }

    xtime_timestamp get_unix_timestamp(int day, int month, int year, int hour, int minutes, int seconds) {
        xtime_timestamp _secs;
        long _mon, _year;
        long _days;
        _mon = month - 1;
        const long _TBIAS_YEAR = 1900;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        _year = year - _TBIAS_YEAR;
        _days = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[_mon] : lmos[_mon])) - 1;
        _days += 365 * _year;
        _days += day;
        const long _TBIAS_DAYS = 25567;
        _days -= _TBIAS_DAYS;
        _secs = 3600 * hour;
        _secs += 60 * minutes;
        _secs += seconds;
        _secs += _days * 86400;
        return _secs;
    }

    DateTime::DateTime() {};

    DateTime::DateTime(int day, int month, int year) {
        DateTime::day = day;
        DateTime::month = month;
        DateTime::year = year;
        DateTime::hour = 0;
        DateTime::minutes = 0;
        DateTime::seconds = 0;
    }

    DateTime::DateTime(int day, int month, int year, int hour, int minutes, int seconds) {
        DateTime::day = day;
        DateTime::month = month;
        DateTime::year = year;
        DateTime::hour = hour;
        DateTime::minutes = minutes;
        DateTime::seconds = seconds;
    }

    DateTime::DateTime(xtime_timestamp timestamp) {
        xtime_timestamp _secs;
        long _mon, _year;
        long _days;
        long i;

        _secs = timestamp;
        const long _TBIAS_DAYS = 25567;
        _days = _TBIAS_DAYS;

        _days += _secs / 86400; _secs = _secs % 86400;
        hour = _secs / 3600; _secs %= 3600;
        minutes = _secs / 60; seconds = _secs % 60;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        for (_year = _days / 365; _days < (i = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[0] : lmos[0]) + 365*_year)); ) { --_year; }
        _days -= i;
        const long _TBIAS_YEAR = 1900;
        year = _year + _TBIAS_YEAR;

        if(((_year) & 03) || ((_year) == 0)) {
            // mos
            for (_mon = 12; _days < mos[--_mon]; );
            month = _mon + 1;
            day = _days - mos[_mon] + 1;
        } else {
            for (_mon = 12; _days < lmos[--_mon]; );
            month = _mon + 1;
            day = _days - lmos[_mon] + 1;
        }
    }

    DateTime::DateTime(std::string str_iso_formatted_utc_datetime) {
        convert_iso(str_iso_formatted_utc_datetime, *this);
    }

    xtime_timestamp DateTime::get_unix_timestamp() {
        unsigned long long _secs;
        long _mon, _year;
        long _days;
        _mon = month - 1;
        const long _TBIAS_YEAR = 1900;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        _year = year - _TBIAS_YEAR;
        _days = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[_mon] : lmos[_mon])) - 1;
        _days += 365 * _year;
        _days += day;
        const long _TBIAS_DAYS = 25567;
        _days -= _TBIAS_DAYS;
        _secs = 3600 * hour;
        _secs += 60 * minutes;
        _secs += seconds;
        _secs += _days * 86400;
        return _secs;
    }

    void DateTime::set_unix_timestamp(unsigned long long timestamp) {
        unsigned long long _secs;
        long _mon, _year;
        long _days;
        long i;

        _secs = timestamp;
        const long _TBIAS_DAYS = 25567;
        _days = _TBIAS_DAYS;

        _days += _secs / 86400; _secs = _secs % 86400;
        hour = _secs / 3600; _secs %= 3600;
        minutes = _secs / 60; seconds = _secs % 60;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        for (_year = _days / 365; _days < (i = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[0] : lmos[0]) + 365*_year)); ) { --_year; }
        _days -= i;
        const long _TBIAS_YEAR = 1900;
        year = _year + _TBIAS_YEAR;

        if(((_year) & 03) || ((_year) == 0)) {
            // mos
            for (_mon = 12; _days < mos[--_mon]; );
            month = _mon + 1;
            day = _days - mos[_mon] + 1;
        } else {
            for (_mon = 12; _days < lmos[--_mon]; );
            month = _mon + 1;
            day = _days - lmos[_mon] + 1;
        }
    }

    void DateTime::print() {
        printf("%.2d.%.2d.%.4d %.2d:%.2d:%.2d\n",day,month,year,hour,minutes,seconds);
    }

    std::string DateTime::get_str_date_time() {
        char text[512];
        memset(text, 0, 512);
        sprintf(text,"%.2d.%.2d.%.4d %.2d:%.2d:%.2d",day,month,year,hour,minutes,seconds);
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

    bool convert_iso(std::string str_iso_formatted_utc_datetime, DateTime& t) {
        std::string& word = str_iso_formatted_utc_datetime;
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
        unsigned long long timestamp = t.get_unix_timestamp();
        if(word.substr(19, 1) == "+") timestamp -= offset;
        else if(word.substr(19, 1) == "-") timestamp += offset;
        t.set_unix_timestamp(timestamp);
        return true;
    }

    xtime_timestamp get_unix_timestamp(DateTime& timedata) {
        xtime_timestamp _secs;
        long _mon, _year;
        long _days;
        _mon = timedata.month - 1;
        const long _TBIAS_YEAR = 1900;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        _year = timedata.year - _TBIAS_YEAR;
        _days = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[_mon] : lmos[_mon])) - 1;
        _days += 365 * _year;
        _days += timedata.day;
        const long _TBIAS_DAYS = 25567;
        _days -= _TBIAS_DAYS;
        _secs = 3600 * timedata.hour;
        _secs += 60 * timedata.minutes;
        _secs += timedata.seconds;
        _secs += _days * 86400;
        return _secs;
    }

    DateTime convert_timestamp_to_datetime(xtime_timestamp timestamp) {
        DateTime outTime;
        xtime_timestamp _secs;
        long _mon, _year;
        long _days;
        long i;

        _secs = timestamp;
        const long _TBIAS_DAYS = 25567;
        _days = _TBIAS_DAYS;

        _days += _secs / 86400; _secs = _secs % 86400;
        outTime.hour = _secs / 3600; _secs %= 3600;
        outTime.minutes = _secs / 60; outTime.seconds = _secs % 60;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        for (_year = _days / 365; _days < (i = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[0] : lmos[0]) + 365*_year)); ) { --_year; }
        _days -= i;
        const long _TBIAS_YEAR = 1900;
        outTime.year = _year + _TBIAS_YEAR;

        if(((_year) & 03) || ((_year) == 0)) {
            // mos
            for (_mon = 12; _days < mos[--_mon]; );
            outTime.month = _mon + 1;
            outTime.day = _days - mos[_mon] + 1;
        } else {
            for (_mon = 12; _days < lmos[--_mon]; );
            outTime.month = _mon + 1;
            outTime.day = _days - lmos[_mon] + 1;
        }
        return outTime;
    }

    int get_weekday(int day, int month, int year) {
        int a, y, m, R;
        a = ( 14 - month ) / 12;
        y = year - a;
        m = month + 12 * a - 2;
        R = 7000 + ( day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12 );
        return R % 7;
    }

    int get_weekday(xtime_timestamp timestamp) {
        DateTime temp = convert_timestamp_to_datetime(timestamp);
        return get_weekday(temp.day, temp.month, temp.year);
    }

    void print_date_time(xtime_timestamp timestamp) {
        DateTime t(timestamp);
        t.print();
    }

    std::string get_str_unix_date_time() {
        DateTime t;
        t.set_unix_timestamp(get_unix_timestamp());
        return t.get_str_date_time();
    }

    bool is_day_off(xtime_timestamp timestamp) {
        int wday = get_weekday(timestamp);
        if(wday == xtime::SUN || wday == xtime::SAT) {
            return true;
        }
        return false;
    }

    bool is_leap_year(int year) {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return true;
        return false;
    }

    int get_num_days_month(int month, int year) {
        if(month > 12) return 0;
        const int numDays[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
        if(month == 2) {
            if(is_leap_year(year)) return 29;
            else return 28;
        } else {
            return numDays[month];
        }
    }

    xtime_timestamp convert_gmt_to_cet(xtime_timestamp gmt) {
        const xtime_timestamp ONE_HOUR = 3600;
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
                            if(iTime.hour >= NEW_SUMMER_HOUR) return gmt + ONE_HOUR * 2; // летнее время
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
                            if(iTime.hour >= NEW_SUMMER_HOUR) return gmt + ONE_HOUR; // зимнее время
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

    xtime_timestamp convert_cet_to_gmt(xtime_timestamp cet) {
        const xtime_timestamp ONE_HOUR = 3600;
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

    std::string get_str_unix_date_time(xtime_timestamp timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_date_time();
    }
}
