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

namespace FunctionsForTime {

    unsigned long long getUnixTime() {
        time_t rawtime;
        time(&rawtime);
        return (unsigned long long)rawtime;
    }

    unsigned long long getUnixTime(int day, int month, int year, int hour, int minutes, int seconds) {
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

    cTime::cTime() {};

    cTime::cTime(int day, int month, int year) {
        cTime::day = day;
        cTime::month = month;
        cTime::year = year;
        cTime::hour = 0;
        cTime::minutes = 0;
        cTime::seconds = 0;
    }

    cTime::cTime(int day, int month, int year, int hour, int minutes, int seconds) {
        cTime::day = day;
        cTime::month = month;
        cTime::year = year;
        cTime::hour = hour;
        cTime::minutes = minutes;
        cTime::seconds = seconds;
    }

    cTime::cTime(unsigned long long timestamp) {
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

    cTime::cTime(std::string strISOformattedUTCdatetime) {
        converISO(strISOformattedUTCdatetime, *this);
    }

    unsigned long long cTime::getUnixTime() {
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

    void cTime::setUnixTime(unsigned long long timestamp) {
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

    void cTime::print() {
        printf("%.2d.%.2d.%.4d %.2d:%.2d:%.2d\n",day,month,year,hour,minutes,seconds);
    }

    std::string cTime::getStr() {
        char text[512];
        memset(text, 0, 512);
        sprintf(text,"%.2d.%.2d.%.4d %.2d:%.2d:%.2d",day,month,year,hour,minutes,seconds);
        return std::string(text);
    }

    int cTime::getWday() {
        return FunctionsForTime::getWday(day, month, year);
    }

    bool cTime::isLeapYear() {
        return FunctionsForTime::isLeapYear(year);
    }

    int cTime::getNumDaysCurrentMonth() {
        return getNumDaysMonth(month, year);
    }

    bool converISO(std::string strISOformattedUTCdatetime, cTime& t) {
        std::string& word = strISOformattedUTCdatetime;
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
        unsigned long long timestamp = t.getUnixTime();
        if(word.substr(19, 1) == "+") timestamp -= offset;
        else if(word.substr(19, 1) == "-") timestamp += offset;
        t.setUnixTime(timestamp);
        return true;
    }

    unsigned long long getUnixTime(cTime& timedata) {
        unsigned long long _secs;
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

    cTime getTime(unsigned long long timestamp) {
        cTime outTime;
        unsigned long long _secs;
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

    int getWday(int day, int month, int year) {
        int a, y, m, R;
        a = ( 14 - month ) / 12;
        y = year - a;
        m = month + 12 * a - 2;
        R = 7000 + ( day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12 );
        return R % 7;
    }

    int getWday(unsigned long long unix) {
        cTime temp = getTime(unix);
        return getWday(temp.day, temp.month, temp.year);
    }

    void printDateAndTime(unsigned long long unix) {
        cTime t(unix);
        t.print();
    }

    std::string getStrTime() {
        cTime t;
        t.setUnixTime(getUnixTime());
        return t.getStr();
    }

    bool isDayOff(unsigned long long unix) {
        int wday = getWday(unix);
        if(wday == FunctionsForTime::SUN || wday == FunctionsForTime::SAT) {
            return true;
        }
        return false;
    }

    bool isLeapYear(int year) {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return true;
        return false;
    }

    int getNumDaysMonth(int month, int year) {
        if(month > 12) return 0;
        const int numDays[13] = {0,31,30,31,30,31,30,31,31,30,31,30,31};
        if(month == 2) {
            if(isLeapYear(year)) return 29;
            else return 28;
        } else {
            return numDays[month];
        }
    }

    unsigned long long convertGmtToCet(unsigned long long gmt) {
        const unsigned long long ONE_HOUR = 3600;
        const int OLD_START_SUMMER_HOUR = 2;
        const int OLD_STOP_SUMMER_HOUR = 3;
        const int NEW_SUMMER_HOUR = 1;
        const int MONTH_MARSH = 3;
        const int MONTH_OCTOBER = 10;
        cTime iTime(gmt);
        int maxDays = iTime.getNumDaysCurrentMonth();
        if(iTime.year < 2002) {
            // До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
            // а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return gmt + ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = getWday(d, MONTH_MARSH, iTime.year);
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
                    int _wday = getWday(d, MONTH_OCTOBER, iTime.year);
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
                    int _wday = getWday(d, MONTH_MARSH, iTime.year);
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
                    int _wday = getWday(d, MONTH_OCTOBER, iTime.year);
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

    unsigned long long convertCetToGmt(unsigned long long cet) {
        const unsigned long long ONE_HOUR = 3600;
        const int OLD_START_SUMMER_HOUR = 2;
        const int OLD_STOP_SUMMER_HOUR = 3;
        const int NEW_SUMMER_HOUR = 1;
        const int MONTH_MARSH = 3;
        const int MONTH_OCTOBER = 10;
        cTime iTime(cet);
        int maxDays = iTime.getNumDaysCurrentMonth();

        if(iTime.year < 2002) {
            // До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
            // а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
            if(iTime.month > MONTH_MARSH && iTime.month < MONTH_OCTOBER) { // летнее время
                return cet - ONE_HOUR * 2;
            } else
            if(iTime.month == MONTH_MARSH) {
                for(int d = maxDays; d >= iTime.day; d--) {
                    int _wday = getWday(d, MONTH_MARSH, iTime.year);
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
                    int _wday = getWday(d, MONTH_OCTOBER, iTime.year);
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
                    int _wday = getWday(d, MONTH_MARSH, iTime.year);
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
                    int _wday = getWday(d, MONTH_OCTOBER, iTime.year);
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
}
