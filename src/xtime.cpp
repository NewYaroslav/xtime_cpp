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
#include <ctime>
#include <thread>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sys/timeb.h>
#include <stdio.h>

namespace xtime {

    /* Дата автоматизации OLE реализована в виде числа с плавающей запятой,
     * неотъемлемым компонентом которого является число дней до
     * или после полуночи 30 декабря 1899 года,
     * а дробный компонент представляет время этого дня, деленное на 24.
     * Например, полночь 31 декабря 1899 представлен 1,0; 6 утра,
     * 1 января 1900 года представлено 2,25;
     * полночь 29 декабря 1899 года представлена -1,0;
     * и 6 часов утра 29 декабря 1899 года - -1,25.
     *
     * Базовая дата автоматизации OLE - полночь 30 декабря 1899 года.
     * Минимальная дата автоматизации OLE - полночь 1 января 0100 года.
     * Максимальная дата автоматизации OLE такая же,
    * как DateTime.MaxValue, последний момент 31 декабря 9999 года.
    */
    oadate_t convert_timestamp_to_oadate(const timestamp_t timestamp) {
        return (oadate_t)OADATE_UNIX_EPOCH + (oadate_t)timestamp / (oadate_t)SECONDS_IN_DAY;
    }

    oadate_t convert_ftimestamp_to_oadate(const ftimestamp_t timestamp) {
        return (oadate_t)OADATE_UNIX_EPOCH + (oadate_t)timestamp / (oadate_t)SECONDS_IN_DAY;
    }

    timestamp_t convert_oadate_to_timestamp(const oadate_t oadate) {
        if(oadate < OADATE_UNIX_EPOCH) return 0;
        return (timestamp_t)((oadate - (oadate_t)OADATE_UNIX_EPOCH) * (oadate_t)SECONDS_IN_DAY);
    }

    ftimestamp_t convert_oadate_to_ftimestamp(const oadate_t oadate) {
        if(oadate < OADATE_UNIX_EPOCH) return 0;
        return (ftimestamp_t)((oadate - (oadate_t)OADATE_UNIX_EPOCH) * (oadate_t)SECONDS_IN_DAY);
    }

    oadate_t get_oadate() {
        return convert_ftimestamp_to_oadate(get_ftimestamp());
    }

    oadate_t get_oadate(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour,
            const uint32_t minute,
            const uint32_t second,
            const uint32_t millisecond) {
        return convert_ftimestamp_to_oadate(get_ftimestamp(
            day,
            month,
            year,
            hour,
            minute,
            second,
            millisecond));
    }

    timestamp_t get_timestamp() {
        time_t rawtime;
        time(&rawtime);
        struct tm* ptm;

        ptm = gmtime(&rawtime);
        DateTime iTime(ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        return iTime.get_timestamp();
    }

    ftimestamp_t get_ftimestamp() {
        timestamp_t t = get_timestamp();
        timeb tb;
        ftime(&tb);
        return (ftimestamp_t)t + (ftimestamp_t)tb.millitm/1000.0;
    }

    uint32_t get_millisecond() {
        timeb tb;
        ftime(&tb);
        return tb.millitm;
    }

    timestamp_t get_timestamp(std::string value) {
        auto new_end = std::remove_if(value.begin(), value.end(), [](const char& c){
            return !std::isdigit(c);
        });
        value.erase(new_end, value.end());
        uint32_t digit = (uint32_t)value.size() - 1;
        timestamp_t t = 0;
        const timestamp_t factors[] = {
            1,10,100,
            1000,10000,100000,
            1000000,10000000,100000000,
            1000000000,10000000000,100000000000,
            1000000000000,10000000000000,100000000000000,
            1000000000000000,10000000000000000,100000000000000000,
            1000000000000000000};
        uint32_t start = value.size() > 19 ? (uint32_t)value.size() - 19 : 0;
        for(uint32_t d = start; d <= digit; ++d) {
            t += ((timestamp_t)(value[d] - '0') * factors[digit - d]);
        }
        return t;
    }

    ftimestamp_t get_ftimestamp(const std::string &value) {
        timestamp_t temp = get_timestamp(value);
        timestamp_t t = temp / 1000;
        return (double)(temp - t*1000)/1000.0 + (double)t;
    }

    timestamp_t get_timestamp(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour,
            const uint32_t minute,
            const uint32_t second) {
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
        _secs += SECONDS_IN_MINUTE * minute;
        _secs += second;
        _secs += _days * SECONDS_IN_DAY;
        return _secs;
    }

    ftimestamp_t get_ftimestamp(
        const uint32_t day,
        const uint32_t month,
        const uint32_t year,
        const uint32_t hour,
        const uint32_t minute,
        const uint32_t second,
        const uint32_t millisecond) {
        timestamp_t t = get_timestamp(day, month, year, hour, minute, second);
        return (double)t + (double)millisecond/1000.0;
    }

    DateTime::DateTime() :
        year(1970),
        millisecond(0),
        second(0),
        minute(0),
        hour(0),
        day(1),
        month(1) {
    };

    DateTime::DateTime(
            const uint32_t _day,
            const uint32_t _month,
            const uint32_t _year,
            const uint32_t _hour,
            const uint32_t _minute,
            const uint32_t _second,
            const uint32_t _millisecond) :
        year(_year),
        millisecond(_millisecond),
        second(_second),
        minute(_minute),
        hour(_hour),
        day(_day),
        month(_month) {
    }

    DateTime::DateTime(const timestamp_t timestamp) {
        set_timestamp(timestamp);
    }

    DateTime::DateTime(const ftimestamp_t ftimestamp) {
        set_ftimestamp(ftimestamp);
    }

    DateTime::DateTime(const std::string &str_iso_formatted_utc_datetime) {
        convert_iso(str_iso_formatted_utc_datetime, *this);
    }

    bool DateTime::is_correct() {
        return is_correct_date_time(day, month, year, hour, minute, second, millisecond);
    }

    timestamp_t DateTime::get_timestamp() {
        return xtime::get_timestamp(day, month, year, hour, minute, second);
    }

    ftimestamp_t DateTime::get_ftimestamp() {
        return xtime::get_ftimestamp(day, month, year, hour, minute, second, millisecond);
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
        minute = _secs / SECONDS_IN_MINUTE; second = _secs % SECONDS_IN_MINUTE;
        const long lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

        for(_year = _days / DAYS_IN_YEAR;
            _days < (i = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[0] : lmos[0]) + DAYS_IN_YEAR*_year));) {
            --_year;
        }
        _days -= i;
        const long _TBIAS_YEAR = 1900;
        year = _year + _TBIAS_YEAR;
        _mon = MONTHS_IN_YEAR;
        if(((_year) & 03) || ((_year) == 0)) {
            while(_days < mos[--_mon]) {};
            month = _mon + 1;
            day = _days - mos[_mon] + 1;
        } else {
            while(_days < lmos[--_mon]) {};
            month = _mon + 1;
            day = _days - lmos[_mon] + 1;
        }
    }

    void DateTime::set_ftimestamp(const ftimestamp_t ftimestamp) {
        const timestamp_t sec_timestamp = (timestamp_t)ftimestamp;
        set_timestamp(sec_timestamp);
        millisecond = (long)(((timestamp_t)(ftimestamp * 1000.0 + 0.5)) % 1000);
    }

    void DateTime::print() {
        printf("%.2d.%.2d.%.4d %.2d:%.2d:%.2d\n",
            (uint32_t)day,
            (uint32_t)month,
            (uint32_t)year,
            (uint32_t)hour,
            (uint32_t)minute,
            (uint32_t)second);
    }

    std::string DateTime::get_str_date_time() {
        char text[24] = {};
        sprintf(text,"%.2d.%.2d.%.4d %.2d:%.2d:%.2d",
            (uint32_t)day,
            (uint32_t)month,
            (uint32_t)year,
            (uint32_t)hour,
            (uint32_t)minute,
            (uint32_t)second);
        return std::string(text);
    }

    std::string DateTime::get_str_date_time_ms() {
        char text[32] = {};
        sprintf(text,"%.2d.%.2d.%.4d %.2d:%.2d:%.2d.%.3d",
            (uint32_t)day,
            (uint32_t)month,
            (uint32_t)year,
            (uint32_t)hour,
            (uint32_t)minute,
            (uint32_t)second,
            (uint32_t)millisecond);
        return std::string(text);
    }

    std::string DateTime::get_str_date() {
        char text[12] = {};
        sprintf(text,"%.2d.%.2d.%.4d", (uint32_t)day, (uint32_t)month, (uint32_t)year);
        return std::string(text);
    }

    std::string DateTime::get_str_time() {
        char text[10] = {};
        sprintf(text,"%.2d:%.2d:%.2d",
            (uint32_t)hour,
            (uint32_t)minute,
            (uint32_t)second);
        return std::string(text);
    }

    std::string DateTime::get_str_time_ms() {
        char text[16] = {};
        sprintf(text,"%.2d:%.2d:%.2d.%.3d",
            (uint32_t)hour,
            (uint32_t)minute,
            (uint32_t)second,
            (uint32_t)millisecond);
        return std::string(text);
    }

    uint32_t DateTime::get_weekday() {
        return xtime::get_weekday(day, month, year);
    }

    bool DateTime::is_leap_year() {
        return xtime::is_leap_year(year);
    }

    uint32_t DateTime::get_num_days_current_month() {
        return get_num_days_month(month, year);
    }

    void DateTime::set_end_month() {
        set_end_day();
        day = get_num_days_month(month, year);
    }


    oadate_t DateTime::get_oadate() {
        return xtime::get_oadate(
            day,
            month,
            year,
            hour,
            minute,
            second,
            millisecond);
    }

    void DateTime::set_oadate(const oadate_t oadate) {
        set_ftimestamp(xtime::convert_oadate_to_ftimestamp(oadate));
    }

    bool convert_iso(const std::string &str_iso_formatted_utc_datetime, DateTime& t) {
        const std::string &word = str_iso_formatted_utc_datetime;
        if(word.size() >= 26) {
            // находим дату и время
            t.year = std::atoi(word.substr(0, 4).c_str());
            t.month = std::atoi(word.substr(5, 2).c_str());
            t.day = std::atoi(word.substr(8, 2).c_str());
            t.hour = std::atoi(word.substr(11, 2).c_str());
            t.minute = std::atoi(word.substr(14, 2).c_str());
            t.second = std::atoi(word.substr(17, 2).c_str());
            int gh = std::atoi(word.substr(20, 2).c_str());
            int gm = std::atoi(word.substr(23, 2).c_str());
            int offset = gh * 3600 + gm * 60;
            timestamp_t timestamp = t.get_timestamp();
            if(word.substr(19, 1) == "+") timestamp -= offset;
            else if(word.substr(19, 1) == "-") timestamp += offset;
            t.set_timestamp(timestamp);
            return true;
        }
        return false;
    }

    uint32_t get_month(std::string month) {
        if(month.size() == 0) return 0;
        std::transform(month.begin(), month.end(), month.begin(), tolower);
        month[0] = toupper(month[0]);
        for(uint32_t i = 0; i < MONTHS_IN_YEAR; ++i) {
            std::string name_long = month_name_long[i];
            std::string name_short = month_name_short[i];
            if(month == name_long) return i + 1;
            if(month == name_short) return i + 1;
        }
        return 0;
    }

    bool convert_str_to_timestamp(std::string str, timestamp_t& t) {
        uint32_t day = 0, month = 0, year = 0, hour = 0, minute = 0, second = 0;
        str += "_";
        std::vector<std::string> output_list;
        std::size_t start_pos = 0;

        while(true) {
            std::size_t found_beg = str.find_first_of("/\\_:-., ", start_pos);
            if(found_beg != std::string::npos) {
                std::size_t len = found_beg - start_pos;
                if(len > 0)
                    output_list.push_back(str.substr(start_pos, len));
                start_pos = found_beg + 1;
            } else break;
        }

        if(output_list.size() >= 3) {
            if(output_list[0].size() >= 4) {
                // если год в самом начале
                year = std::atoi(output_list[0].c_str());
                month = std::atoi(output_list[1].c_str());
                day = std::atoi(output_list[2].c_str());
                if(output_list.size() == 6) {
                    hour = std::atoi(output_list[3].c_str());
                    minute = std::atoi(output_list[4].c_str());
                    second = std::atoi(output_list[5].c_str());
                }
            } else
            if(output_list[2].size() >= 4) {
                // если год в конце
                day = std::atoi(output_list[0].c_str());
                month = std::atoi(output_list[1].c_str());
                year = std::atoi(output_list[2].c_str());
                if(output_list.size() == 6) {
                    hour = std::atoi(output_list[3].c_str());
                    minute = std::atoi(output_list[4].c_str());
                    second = std::atoi(output_list[5].c_str());
                }
            } else
            if(output_list[2].size() == 2 && output_list.size() == 6) {
                hour = std::atoi(output_list[0].c_str());
                minute = std::atoi(output_list[1].c_str());
                second = std::atoi(output_list[2].c_str());
                if(output_list[5].size() >= 4 && output_list[4].size() == 2) {
                    day = std::atoi(output_list[3].c_str());
                    month = std::atoi(output_list[4].c_str());
                    year = std::atoi(output_list[5].c_str());
                } else
                if(output_list[5].size() == 2 && output_list[4].size() >= 3) {
                    day = std::atoi(output_list[3].c_str());
                    month = get_month(output_list[4]);
                    year = std::atoi(output_list[5].c_str()) + 2000;
                } else
                if(output_list[5].size() == 4 && output_list[4].size() >= 3) {
                    day = std::atoi(output_list[3].c_str());
                    month = get_month(output_list[4]);
                    year = std::atoi(output_list[5].c_str());
                } else
                if(output_list[5].size() == 2 && output_list[4].size() == 2) {
                    day = std::atoi(output_list[3].c_str());
                    month = std::atoi(output_list[4].c_str());
                    year = std::atoi(output_list[5].c_str()) + 2000;
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
        if(day >= 32 || day <= 0 || minute >= 60 ||
            second >= 60 || hour >= 24 ||
            year < 1970 || month > 12 || month <= 0) {
            return false;
        }

        t = get_timestamp(day, month, year, hour, minute, second);
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
        outTime.minute = _secs / SECONDS_IN_MINUTE;
        outTime.second = _secs % SECONDS_IN_MINUTE;
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

    uint32_t get_weekday(const uint32_t day, const uint32_t month, const uint32_t year) {
        uint32_t a, y, m, R;
        a = ( 14 - month ) / 12;
        y = year - a;
        m = month + 12 * a - 2;
        R = 7000 + ( day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12 );
        return R % 7;
    }

    void print_date_time(const timestamp_t &timestamp) {
        DateTime t(timestamp);
        t.print();
    }

    std::string get_str_date_time() {
        DateTime t;
        t.set_timestamp(get_timestamp());
        return t.get_str_date_time();
    }

    std::string get_str_date_time_ms() {
        DateTime t;
        t.set_ftimestamp(get_ftimestamp());
        return t.get_str_date_time_ms();
    }

    std::string get_str_time_ms() {
        DateTime t;
        t.set_ftimestamp(get_ftimestamp());
        return t.get_str_time_ms();
    }

    uint32_t get_num_days_month(const uint32_t month, const uint32_t year) {
        if(month > MONTHS_IN_YEAR)
            return 0;
        const uint32_t num_days[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
        if(month == FEB) {
            if(is_leap_year(year)) return 29;
            else return 28;
        } else {
            return num_days[month];
        }
    }

    uint32_t get_num_days_month(const timestamp_t timestamp) {
        const uint32_t num_days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        const uint32_t month = get_month(timestamp);
        if(month == FEB) {
            if(is_leap_year(get_year(timestamp))) return 29;
            else return 28;
        } else {
            return num_days[month];
        }
    }

    timestamp_t convert_gmt_to_cet(const timestamp_t gmt) {
        const timestamp_t ONE_HOUR = SECONDS_IN_HOUR;
        const uint8_t OLD_START_SUMMER_HOUR = 2;
        const uint8_t OLD_STOP_SUMMER_HOUR = 3;
        const uint8_t NEW_SUMMER_HOUR = 1;
        const uint8_t MONTH_MARSH = MAR;
        const uint8_t MONTH_OCTOBER = OCT;
        DateTime iTime(gmt);
        uint32_t maxDays = iTime.get_num_days_current_month();
        if(iTime.year < 2002) {
            // До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
            // а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return gmt + ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_MARSH, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if((iTime.hour + 1) >= OLD_START_SUMMER_HOUR) return gmt + ONE_HOUR * 2; // летнее время
                            return gmt + ONE_HOUR; // зимнее время
                        }
                        return gmt + ONE_HOUR; // зимнее время
                    }
                }
                return gmt + ONE_HOUR * 2; // летнее время
            } else
            if(iTime.month == MONTH_OCTOBER) {
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
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
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_MARSH, iTime.year);
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
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
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

    timestamp_t convert_gmt_to_msk(const timestamp_t gmt) {
        const timestamp_t gmt2 = gmt + 2 * SECONDS_IN_HOUR;
        const timestamp_t gmt3 = gmt + 3 * SECONDS_IN_HOUR;
        const timestamp_t gmt4 = gmt + 4 * SECONDS_IN_HOUR;

        const timestamp_t OCT_26_2014 = 1414281600;
        const timestamp_t MAR_27_2011 = 1301184000;
        const timestamp_t JAN_19_1992 = 695782800;
        const timestamp_t YEAR_1991 = 662688000;
        const timestamp_t OFFSET_HOUR1 = 23*SECONDS_IN_HOUR + 1;
        const timestamp_t OFFSET_HOUR2 = 22*SECONDS_IN_HOUR + 1;

        //int year4 = get_year(gmt4);
        //int month4 = get_month_year(gmt4);
        //int dayweek4 = get_weekday(gmt4);
        //int year3 = get_year(gmt4);
        //int month3 = get_month_year(gmt4);
        //int dayweek3 = get_weekday(gmt4);

        if(gmt4 >= OCT_26_2014) return gmt3;
        else
        if(gmt3 >= MAR_27_2011) return gmt4;
        else
        if(gmt2 >= JAN_19_1992) {
            timestamp_t last_timestamp_sunday2 = get_last_timestamp_sunday_month(gmt2);
            uint32_t month2 = get_month(gmt2);
            //uint32_t month3 = get_month_year(gmt3);
            uint32_t month4 = get_month(gmt4);
            if(month2 == MAR) {
                if(gmt2 < last_timestamp_sunday2) return gmt3;
                else return gmt4;
            } else
            if(month2 < MAR) return gmt3;
            else
            if(month4 == SEPT) {
                timestamp_t last_timestamp_sunday4 = get_last_timestamp_sunday_month(gmt4);
                if(gmt4 < (last_timestamp_sunday4 - OFFSET_HOUR1)) return gmt3;
                else return gmt4;
            } else
            if(month4 >= SEPT) return gmt3;
            else return gmt4;
        } else
        if(gmt3 >= YEAR_1991) {
            //timestamp_t last_timestamp_sunday2 = get_last_timestamp_sunday_month(gmt2);
            uint32_t month3 = get_month(gmt3);
            if(month3 == SEPT) {
                timestamp_t last_timestamp_sunday3 = get_last_timestamp_sunday_month(gmt3);
                if(gmt3 < (last_timestamp_sunday3 - OFFSET_HOUR2)) return gmt3;
                else return gmt4;
            } else
            if(month3 >= SEPT) return gmt2;
            else return gmt3;
        } else {
            timestamp_t last_timestamp_sunday3 = get_last_timestamp_sunday_month(gmt3);
            uint32_t month2 = get_month(gmt2);
            uint32_t month3 = get_month(gmt3);
            uint32_t month4 = get_month(gmt4);
            if(month3 == MAR) {
                if(gmt3 < last_timestamp_sunday3) return gmt3;
                else return gmt4;
            } else
            if(month2 < MAR) return gmt3;
            else
            if(month4 == SEPT) {
                timestamp_t last_timestamp_sunday4 = get_last_timestamp_sunday_month(gmt4);
                if(gmt4 < (last_timestamp_sunday4 - OFFSET_HOUR1)) return gmt3;
                else return gmt4;
            } else
            if(month4 >= SEPT) return gmt3;
            else return gmt4;
        }
    }

    timestamp_t convert_cet_to_gmt(const timestamp_t cet) {
        const timestamp_t ONE_HOUR = SECONDS_IN_HOUR;
        const uint32_t OLD_START_SUMMER_HOUR = 2;
        const uint32_t OLD_STOP_SUMMER_HOUR = 3;
        const uint32_t NEW_SUMMER_HOUR = 1;
        const uint32_t MONTH_MARSH = MAR;
        const uint32_t MONTH_OCTOBER = OCT;
        DateTime iTime(cet);
        uint32_t maxDays = iTime.get_num_days_current_month();

        if(iTime.year < 2002) {
            // До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
            // а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return cet - ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_MARSH, iTime.year);
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
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
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
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_MARSH, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour >= (NEW_SUMMER_HOUR + 2)) return cet - ONE_HOUR * 2; // летнее время
                            return cet - ONE_HOUR; // зимнее время
                        }
                        return cet - ONE_HOUR; // зимнее время
                    }
                }
                return cet - ONE_HOUR * 2; // летнее время
            } else
            if(iTime.month == MONTH_OCTOBER) {
                for(uint32_t d = maxDays; d >= iTime.day; d--) {
                    uint32_t _wday = get_weekday(d, MONTH_OCTOBER, iTime.year);
                    if(_wday == SUN) {
                        if(d == iTime.day) { // если сейчас воскресенье
                            if(iTime.hour >= (NEW_SUMMER_HOUR + 1)) return cet - ONE_HOUR; // зимнее время
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

    std::string get_str_date_time_ms(const ftimestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_date_time_ms();
    }

    std::string get_str_date(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_date();
    }

    std::string get_str_time(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_time();
    }

    std::string get_str_time_ms(const ftimestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.get_str_time_ms();
    }

    bool is_end_month(const timestamp_t timestamp) {
        DateTime iTime(timestamp);
        return iTime.day == iTime.get_num_days_current_month();
    }

    bool is_correct_date(const uint32_t day, const uint32_t month, const uint32_t year) {
        if(day < 1 || day > MAX_DAY_MONTH) return false;
        if(month > MONTHS_IN_YEAR || month < 1) return false;
        if(year < FIRST_YEAR_UNIX) return false;
        if(day > get_num_days_month(month, year)) return false;
        return true;
    }

    bool is_correct_time(
            const uint32_t hour,
            const uint32_t minute,
            const uint32_t second,
            const uint32_t millisecond) {
        if(hour > 23) return false;
        if(minute > 59) return false;
        if(second > 59) return false;
        if(millisecond > 999) return false;
        return true;
    }

    bool is_correct_date_time(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour,
            const uint32_t minute,
            const uint32_t second,
            const uint32_t millisecond) {
        if(!is_correct_date(day, month, year)) return false;
        if(!is_correct_time(hour, minute, second, millisecond)) return false;
        return true;
    }

    uint32_t get_day_month(const timestamp_t timestamp) {
        uint32_t day_year = get_day_year(timestamp);
        const uint8_t JAN_AND_FEB_DAY = 60;
        // таблица для обычного года, не високосного
        const uint8_t TABLE_DAY_OF_YEAR[] = {
            0,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,    // 31 январь
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,             // 28 февраль
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,    // 31 март
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,       // 30 апрель
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
        };
        if(is_leap_year(get_year(timestamp))) {
            if(day_year == JAN_AND_FEB_DAY) return TABLE_DAY_OF_YEAR[day_year - 1] + 1;
            else if(day_year > JAN_AND_FEB_DAY) return TABLE_DAY_OF_YEAR[day_year - 1];
        }
        return TABLE_DAY_OF_YEAR[day_year];
    }

    uint32_t get_month(const timestamp_t timestamp) {
        uint32_t day_year = get_day_year(timestamp);
        const unsigned char JAN_AND_FEB_DAY_LEAP_YEAR = 60;
        const unsigned char TABLE_DAY_OF_YEAR[] = {
            0,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  // 31 январь
            2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,        // 28 февраль
            3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,  // 31 март
            4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,    // 30 апрель
            5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
            6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
            7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
            9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
            10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
            11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
            12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
        };
        return (is_leap_year(get_year(timestamp)) && day_year >= JAN_AND_FEB_DAY_LEAP_YEAR) ? TABLE_DAY_OF_YEAR[day_year - 1] : TABLE_DAY_OF_YEAR[day_year];
    }

    void delay_ms(const uint64_t milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void delay(const uint64_t seconds) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    void for_minutes(
            const timestamp_t min_timestamp,
            const timestamp_t max_timestamp,
            std::function<void(const timestamp_t timestamp)> f) {
        for(timestamp_t t = min_timestamp; t < max_timestamp; t += SECONDS_IN_MINUTE) {
            f(t);
        }
    }

    void for_hours(
            const timestamp_t min_timestamp,
            const timestamp_t max_timestamp,
            std::function<void(const timestamp_t timestamp)> f) {
        for(timestamp_t t = min_timestamp; t < max_timestamp; t += SECONDS_IN_HOUR) {
            f(t);
        }
    }

    void for_days(
            const timestamp_t min_timestamp,
            const timestamp_t max_timestamp,
            std::function<void(const timestamp_t timestamp)> f) {
        for(timestamp_t t = min_timestamp; t < max_timestamp; t += SECONDS_IN_DAY) {
            f(t);
        }
    }
}
