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

#include <string>

//functions for working with time
namespace xtime {

    typedef unsigned long long xtime_timestamp;

    /** \brief Получить время и дату в виде строки
     * \return строка, содержащая время
     */
    std::string get_str_unix_date_time(xtime_timestamp timestamp);

    /** \brief Получить время и дату компьютера в виде строки
     * \param timestamp unix время
     * \return строка, содержащая время
     */
    std::string get_str_unix_date_time();

    /** \brief Получить Unix-время компьютера
     * \return Unix-время
     */
    xtime_timestamp get_unix_timestamp();

    /** \brief Получить Unix-время из даты и стандартного времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \return Unix-время
     */
    xtime_timestamp get_unix_timestamp(int day, int month, int year, int hour, int minutes, int seconds);

    /** \brief Класс для хранения времени
     */
    class DateTime {
        public:
        char seconds;   /**< секунды */
        char minutes;   /**< минуты */
        char hour;      /**< час */
        char day;       /**< день */
        char month;     /**< месяц */
        short year;     /**< год */

        /** \brief Конструктор класса без начальной инициализации времени
         */
        DateTime();

        /** \brief Инициализация с указанием времени
         * Секунды, минуты и час будут инициализированы нулевым значением
         * \param day день
         * \param month месяц
         * \param year год
         */
        DateTime(int day, int month, int year);

        /** \brief Инициализация с указанием времени и даты
         * \param day день
         * \param month месяц
         * \param year год
         * \param hour час
         * \param minutes минуты
         * \param seconds секунды
         */
        DateTime(int day, int month, int year, int hour, int minutes, int seconds);

        /** \brief Инициализация с указанием unix-времени
         * \param timestamp unix-время
         */
        DateTime(xtime_timestamp timestamp);

        /** \brief Инициализация с указанием unix-времени в формате ISO
         * Пример формата ISO: 2013-12-06T15:23:01+00:00
         * \param str_iso_formatted_utc_datetime время UTC в формате ISO
         */
        DateTime(std::string str_iso_formatted_utc_datetime);

        /** \brief Получить Unix-время
         * \return Unix-время
         */
        xtime_timestamp get_unix_timestamp();

        /** \brief Установить unix-время
         * \param timestamp unix-время
         */
        void set_unix_timestamp(xtime_timestamp timestamp);

        /** \brief Вывести время и дату на экран
         */
        void print();

        /** \brief Получить дату и время в виде строки
         * \return строка, содержащая дату и время
         */
        std::string get_str_date_time();

        /** \brief Получить день недели
         * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
         */
        int get_weekday();

        /** \brief Проверка високосного года
         * \return вернет true, если год високосный
         */
        bool is_leap_year();

        /** \brief Получить количество дней в текущем месяце
         * \return количество дней
         */
        int get_num_days_current_month();
    };

    /** \brief Конвертировать строку в формате ISO в данные класса DateTime
     * \param str_iso_formatted_utc_datetime строка в формате ISO, например 2013-12-06T15:23:01+00:00
     * \param t класс времени и даты DateTime, который будет заполнен.
     * \return вернет true
     */
    bool convert_iso(std::string str_iso_formatted_utc_datetime, DateTime& t);

    /** \brief Получить unix время
     * \param timedata стандартное время
     * \return unix время
     */
    xtime_timestamp get_unix_timestamp(DateTime& timedata);

    /** \brief Преобразовать unix-время в класс DateTime
     * \param timestamp unix-время
     * \return класс DateTime
     */
    DateTime convert_timestamp_to_datetime(xtime_timestamp timestamp);

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
    int get_weekday(int day, int month, int year);

    /** \brief Получить день недели
     * \param timestamp Unix-время
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    int get_weekday(xtime_timestamp timestamp);

    /** \brief Напечатать дату и время
     * \param timestamp Unix-время
     */
    void print_date_time(xtime_timestamp timestamp);

    /** \brief Проверить, приходится ли данна дата на выходной день (суббота и воскресение)
     * \param timestamp Unix-время
     * \return вернет true если выходной день
     */
    bool is_day_off(xtime_timestamp timestamp);

    /** \brief Проверка високосного года
     * \param year год
     * \return вернет true, если год високосный
     */
    bool is_leap_year(int year);

    /** \brief Получить количество дней в месяце
     * \param month месяц
     * \param year год
     * \return количество дней в месяце
     */
    int get_num_days_month(int month, int year);

    /** \brief Переводит время GMT во время CET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt Время GMT
     * \return время CET
     */
    xtime_timestamp convert_gmt_to_cet(xtime_timestamp gmt);

    /** \brief Переводит время CET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param cet Время CET
     * \return время GMT
     */
    xtime_timestamp convert_cet_to_gmt(xtime_timestamp cet);
}

#endif // XTIME_HPP_INCLUDED
