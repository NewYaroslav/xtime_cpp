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

namespace FunctionsForTime {

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

}
