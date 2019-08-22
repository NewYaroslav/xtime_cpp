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

#ifndef XTIME_HPP_INCLUDED
#define XTIME_HPP_INCLUDED

#include <string>

namespace xtime {
    // для того, чтобы можно было работать и после 19 января 2038 года, используем 64 бит, а не 32 бит
    typedef unsigned long long timestamp_t;
    const double AVERAGE_DAYS_IN_YEAR = 365.25; ///< Среднее количество дней за год

    /// Количество секунд в минуте, часе и т.д.
    enum {
        SECONDS_IN_MINUTE = 60,	            ///< Количество секунд в одной минуте
        SECONDS_IN_HALF_HOUR = 1800,        ///< Количество секунд в получасе
        SECONDS_IN_HOUR = 3600,	            ///< Количество секунд в одном часе
        SECONDS_IN_DAY = 86400,	            ///< Количество секунд в одном дне
        SECONDS_IN_YEAR = 31536000,	        ///< Количество секунд за год
        SECONDS_IN_LEAP_YEAR = 31622400,	///< Количество секунд за високосный год
        AVERAGE_SECONDS_IN_YEAR = 31557600, ///< Среднее количество секунд за год
        SECONDS_IN_4_YEAR = 126230400,	    ///< Количество секунд за 4 года
        MINUTES_IN_HOUR = 60,               ///< Количество минут в одном часе
        MINUTES_IN_DAY = 1440,              ///< Количество минут в одном дне
        HOURS_IN_DAY = 24,                  ///< Количество часов в одном дне
        MONTHS_IN_YEAR = 12,                ///< Количество месяцев в году
        DAYS_IN_LEAP_YEAR = 366,            ///< Количество дней в високосом году
        DAYS_IN_YEAR = 365,                 ///< Количество дней в году
        DAYS_IN_4_YEAR = 1461,              ///< Количество дней за 4 года
        FIRST_YEAR_UNIX = 1970,             ///< Год начала UNIX времени
        MAX_DAY_MONTH = 31,                 ///< Максимальное количество дней в месяце
    };

    /** \brief Получить время и дату в виде строки
     * \return строка, содержащая время и дату
     */
    std::string get_str_date_time(const timestamp_t timestamp);

    /** \brief Получить дату в виде строки
     * \return строка, содержащая дату
     */
    std::string get_str_date(const timestamp_t timestamp);

    /** \brief Получить время в виде строки
     * \return строка, содержащая время
     */
    std::string get_str_time(const timestamp_t timestamp);

    /** \brief Получить время и дату компьютера в виде строки
     * Данная функция напечатает UTC/GMT время
     * \param timestamp unix время
     * \return строка, содержащая время
     */
    std::string get_str_date_time();

    /** \brief Получить Unix-время компьютера
     * \return Unix-время
     */
    timestamp_t get_timestamp();

    /** \brief Получить unix-время из даты и стандартного времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \return Unix-время
     */
    timestamp_t get_timestamp(
        const int day,
        const int month,
        const int year,
        const int hour = 0,
        const int minutes = 0,
        const int seconds = 0);

    /** \brief Класс для хранения времени
     */
    class DateTime {
            public:
            char seconds;   /**< секунды */
            char minutes;   /**< минуты */
            char hour;      /**< час */
            char day;       /**< день */
            char month;     /**< месяц */
            long year;      /**< год */

            /** \brief Установить начало дня
             * Данная функция устанавливает час, минуту и секунду дня в 0
             */
            inline void set_beg_day() {
                    seconds = 0;
                    minutes = 0;
                    hour = 0;
            }

            /** \brief Установить конец дня
             */
            inline void set_end_day() {
                    seconds = 59;
                    minutes = 59;
                    hour = 23;
            }

            /** \brief Установить начало месяца
             */
            inline void set_beg_month() {
                    set_beg_day();
                    day = 1;
            }

            /** \brief Установить конец месяца
             */
            void set_end_month();

            /** \brief Конструктор класса без начальной инициализации времени
             */
            DateTime();

            /** \brief Инициализация с указанием времени и даты
             * \param day день
             * \param month месяц
             * \param year год
             * \param hour час
             * \param minutes минуты
             * \param seconds секунды
             */
            DateTime(
                const int day,
                const int month,
                const int year,
                const int hour = 0,
                const int minutes = 0,
                const int seconds = 0);

            /** \brief Инициализация с указанием unix-времени
             * \param timestamp unix-время
             */
            DateTime(const timestamp_t timestamp);

            /** \brief Инициализация с указанием unix-времени в формате ISO
             * Пример формата ISO: 2013-12-06T15:23:01+00:00
             * \param str_iso_formatted_utc_datetime время UTC в формате ISO
             */
            DateTime(const std::string str_iso_formatted_utc_datetime);

            /** \brief Получить время
             * \return timestamp
             */
            timestamp_t get_timestamp();

            /** \brief Установить время
             * \param timestamp unix-время
             */
            void set_timestamp(const timestamp_t timestamp);

            /** \brief Вывести время и дату на экран
             */
            void print();

            /** \brief Получить дату и время в виде строки
             * \return строка, содержащая дату и время
             */
            std::string get_str_date_time();

            /** \brief Получить дату в виде строки
             * \return строка, содержащая дату
             */
            std::string get_str_date();

            /** \brief Получить время в виде строки
             * \return строка, содержащая время
             */
            std::string get_str_time();

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
     * \return вернет true если преобразование завершилось успешно
     */
    bool convert_iso(const std::string str_iso_formatted_utc_datetime, DateTime& t);

    /** \brief Преобразует строку, полученную функцией get_str_date_time или методом get_str_date_time
     * обратно в timestamp
     * \param str время в формате строки, например
     * \param t временная метка
     * \return вернет true если преобразование завершилось успешно
     */
    bool convert_str_to_timestamp(std::string str, timestamp_t& t);

    /** \brief Преобразовать unix-время в класс DateTime
     * \param timestamp unix-время
     * \return класс DateTime
     */
    DateTime convert_timestamp_to_datetime(const timestamp_t timestamp);

    /// Скоращенные имена дней неделии
    enum eWday {
        SUN = 0,    ///< Воскресенье
        MON,        ///< Понедельник
        TUS,        ///< Вторник
        WED,        ///< Среда
        THU,        ///< Четверг
        FRI,        ///< Пятница
        SAT,        ///< Суббота
    };

    /** \brief Получить день недели
     * \param day день
     * \param month месяц
     * \param year год
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    int get_weekday(const int day, const int month, const int year);

    /** \brief Получить день недели
     * \param timestamp Unix-время
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    int get_weekday(const timestamp_t timestamp);

    /** \brief Напечатать дату и время
     * \param timestamp Unix-время
     */
    void print_date_time(const timestamp_t timestamp);

    /** \brief Проверить, приходится ли данна дата на выходной день (суббота и воскресение)
     * \param timestamp Unix-время
     * \return вернет true если выходной день
     */
    bool is_day_off(const timestamp_t timestamp);

    /** \brief Проверка високосного года
     * \param year год
     * \return вернет true, если год високосный
     */
    bool is_leap_year(const int year);

    /** \brief Получить количество дней в месяце
     * \param month месяц
     * \param year год
     * \return количество дней в месяце
     */
    int get_num_days_month(const int month, const int year);

    /** \brief Переводит время GMT во время CET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt Время GMT
     * \return время CET
     */
    timestamp_t convert_gmt_to_cet(const timestamp_t gmt);

    /** \brief Переводит время GMT во время EET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt Время GMT
     * \return время EET
     */
    timestamp_t convert_gmt_to_eet(const timestamp_t gmt);

    /** \brief Переводит время CET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param cet Время CET
     * \return время GMT
     */
    timestamp_t convert_cet_to_gmt(const timestamp_t cet);

    /** \brief Переводит время EET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param eet Время EET
     * \return время GMT
     */
    timestamp_t convert_eet_to_gmt(const timestamp_t eet);

    /** \brief Получить минуту дня
     * Данная функция вернет от 0 до 1439 (минуту дня)
     * \param timestamp временная метка
     * \return минута дня
     */
    inline int get_minute_day(const timestamp_t timestamp) {
            return (timestamp / 60) % MINUTES_IN_DAY;
    }

    /** \brief Получить час дня
     * Данная функция вернет от 0 до 23 (час дня)
     * \param timestamp временная метка
     * \return час дня
     */
    inline int get_hour_day(const timestamp_t timestamp) {
            return (timestamp / SECONDS_IN_HOUR) % HOURS_IN_DAY;
    }

    /** \brief Получить секунду дня
     * Данная функция вернет от 0 до 86399 (секунда дня)
     * \param timestamp временная метка
     * \return секунда дня
     */
    inline int get_second_day(const timestamp_t timestamp) {
            return timestamp % SECONDS_IN_DAY;
    }

    /** \brief Получить день
     * Данная функция вернет день, начиная с начала UNIX времени
     * \param timestamp временная метка
     * \return день с начала UNIX времени
     */
    inline int get_day(const timestamp_t timestamp) {
            return (timestamp / SECONDS_IN_DAY);
    }

    /** \brief Получить год
     * Данная функция вернет год указанной временной метки
     * \param timestamp временная метка
     * \return год UNIX времени
     */
    inline int get_year(const timestamp_t timestamp) {
            int year = FIRST_YEAR_UNIX + 4 * (timestamp / SECONDS_IN_4_YEAR);
            timestamp_t t = timestamp % SECONDS_IN_4_YEAR;
            if(t < SECONDS_IN_YEAR) return year;
            else if(t < (2*SECONDS_IN_YEAR)) return year + 1;
            else if(t < (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR)) return year + 2;
            return year + 3;
    }

    /** \brief Получить количество дней в текущем году
     * \param timestamp временная метка
     * \return дней в текущем году
     */
    inline int get_day_in_year(const timestamp_t timestamp) {
        if(is_leap_year(get_year(timestamp))) return DAYS_IN_LEAP_YEAR;
        return DAYS_IN_YEAR;
    }

    /** \brief Получить временную метку начала года
     * \param year год
     * \return временная метка начала года
     */
    inline timestamp_t get_timestamp_beg_year(const int year) {
        int diff = (year - FIRST_YEAR_UNIX);
        if(diff < 0) return 0;
        timestamp_t t = (diff / 4) * SECONDS_IN_4_YEAR;
        int temp = diff % 4;
        if(temp == 0) return t;
        else if(temp == 1) return t + SECONDS_IN_YEAR;
        else if(temp == 2) return t + (2*SECONDS_IN_YEAR);
        return t + (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR);
    }

    /** \brief Получить день года
     * \param timestamp временная метка
     * \return день года
     */
    inline int get_day_year(const timestamp_t timestamp) {
        int year = get_year(timestamp);
        return get_day(timestamp) - get_day(get_timestamp_beg_year(year)) + 1;
    }

    /** \brief Проверить начало получаса
     * \param timestamp временная метка
     * \return вернет true, если начало получаса
     */
    bool is_beg_half_hour(const timestamp_t timestamp);

    /** \brief Проверить начало часа
     * \param timestamp временная метка
     * \return вернет true, если начало часа
     */
    bool is_beg_hour(const timestamp_t timestamp);

    /** \brief Проверить начало дня
     * \param timestamp временная метка
     * \return вернет true, если начало дня
     */
    bool is_beg_day(const timestamp_t timestamp);

    /** \brief Проверить начало недели
     * Если день воскресенье, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp временная метка
     * \return вернет true, если начало недели
     */
    bool is_beg_week(const timestamp_t timestamp);

    /** \brief Проверить начало месяца
     * Если первый день месяца, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp временная метка
     * \return вернет true, если начало месяца
     */
    bool is_beg_month(timestamp_t timestamp);

    /** \brief Проверить конец месяца
     * Если последний день месяца, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp временная метка
     * \return вернет true, если конец месяца
     */
    bool is_end_month(const timestamp_t timestamp);

    /** \brief Проверить корректность даты
     * \param day день
     * \param month месяц
     * \param year год
     * \return вернет true, если заданная дата возможна
     */
    bool is_correct_date(const int day, const int month, const int year);

    /** \brief Проверить корректность времени
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \return вернет true, если заданное время корректно
     */
    bool is_correct_time(const int hour, const int minutes = 0, const int seconds = 0);

    /** \brief Проверить корректность даты и времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \return вернет true, если заданное время корректно
     */
    bool is_correct_date_time(
        const int day,
        const int month,
        const int year,
        const int hour = 0,
        const int minutes = 0,
        const int seconds = 0);

    /** \brief Получить временную метку в начале дня
     * Данная функция обнуляет часы, минуты и секунды
     * \param timestamp временная метка
     * \return временная метка в начале дня
     */
    inline timestamp_t get_start_day(const timestamp_t timestamp) {
        return timestamp - (timestamp % SECONDS_IN_DAY);
    }

    /** \brief Получить временную метку в начале часа
     * Данная функция обнуляет минуты и секунды
     * \param timestamp временная метка
     * \return временная метка в начале часа
     */
    inline timestamp_t get_start_hour(const timestamp_t timestamp) {
        return timestamp - (timestamp % SECONDS_IN_HOUR);
    }

    /** \brief Получить временную метку в начале минуты
     * Данная функция обнуляет секунды
     * \param timestamp временная метка
     * \return временная метка в начале минуты
     */
    inline timestamp_t get_start_minute(const timestamp_t timestamp) {
        return timestamp - (timestamp % SECONDS_IN_MINUTE);
    }
}

#endif // XTIME_HPP_INCLUDED
