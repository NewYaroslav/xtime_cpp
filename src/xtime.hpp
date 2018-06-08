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

#ifndef XTIME_HPP_INCLUDED
#define XTIME_HPP_INCLUDED

//functions for working with time
namespace FunctionsForTime {

    /** \brief Получить Unix-время из даты и стандартного времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \return Unix-время
     */
    unsigned long long getUnixTime(int day, int month, int year, int hour, int minutes, int seconds);

    /** \brief Класс для хранения времени
     */
    class cTime {
        public:
        char seconds;   /**< секунды */
        char minutes;   /**< минуты */
        char hour;      /**< час */
        char day;       /**< день */
        char month;     /**< месяц */
        short year;     /**< год */

        /** \brief Конструктор класса без начальной инициализации времени
         */
        cTime();

        /** \brief Инициализация с указанием времени
         * Секунды, минуты и час будут инициализированы нулевым значением
         * \param day день
         * \param month месяц
         * \param year год
         */
        cTime(int day, int month, int year);

        /** \brief Инициализация с указанием времени и даты
         * \param day день
         * \param month месяц
         * \param year год
         * \param hour час
         * \param minutes минуты
         * \param seconds секунды
         */
        cTime(int day, int month, int year, int hour, int minutes, int seconds);

        /** \brief Инициализация с указанием unix-времени
         * \param timestamp unix-время
         */
        cTime(unsigned long long timestamp);

        /** \brief Получить Unix-время
         * \return Unix-время
         */
        unsigned long long getUnixTime();

        /** \brief Установить unix-время
         * \param timestamp unix-время
         */
        void setUnixTime(unsigned long long timestamp);
    };

    /** \brief Получить unix время
     * \param timedata стандартное время
     * \return unix время
     */
    unsigned long long getUnixTime(cTime& timedata);

    /** \brief Получить стандартное время
     * \param timestamp unix время
     * \return стандартное время
     */
    cTime getTime(unsigned long long timestamp);

    enum eWday {
        SUN = 0,    /**< Воскресенье */
        MON,        /**< Понедельник */
        TUS,        /**< Вторник */
        WED,        /**< Среда */
        THU,        /**< Четверг */
        FRI,        /**< Пятница */
        SAT,        /**< Суббота */
    };

    /** \brief Получить день недели
     * \param day день
     * \param month месяц
     * \param year год
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    int getWday(int day, int month, int year);

    /** \brief Получить день недели
     * \param unix Unix-время
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    int getWday(unsigned long long unix);

}

#endif // XTIME_HPP_INCLUDED
