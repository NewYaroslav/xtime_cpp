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
#include <array>

namespace xtime {
    /* для того, чтобы можно было работать и после 19 января 2038 года,
     * используем 64 бит, а не 32 бит
     */
    typedef uint64_t timestamp_t;           ///< Целочисленный тип метки врмени
    /* для работы с миллисекундами */
    typedef double ftimestamp_t;            ///< Тип метки времени с плавающей точкой
    typedef double oadate_t;                ///< Тип даты автоматизации (OADate) с плавающей точкой
    const oadate_t OADATE_MAX = 9223372036854775807; ///< Максимально возможное значение даты автоматизации (OADate)

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
        DAYS_IN_WEEK = 7,                   ///< Количество дней в неделе
        DAYS_IN_LEAP_YEAR = 366,            ///< Количество дней в високосом году
        DAYS_IN_YEAR = 365,                 ///< Количество дней в году
        DAYS_IN_4_YEAR = 1461,              ///< Количество дней за 4 года
        FIRST_YEAR_UNIX = 1970,             ///< Год начала UNIX времени
        MAX_DAY_MONTH = 31,                 ///< Максимальное количество дней в месяце
        OADATE_UNIX_EPOCH = 25569,          ///< Дата автоматизации OLE с момента эпохи UNIX
    };

    /// Скоращенные имена дней неделии
    enum {
        SUN = 0,    ///< Воскресенье
        MON,        ///< Понедельник
        TUS,        ///< Вторник
        WED,        ///< Среда
        THU,        ///< Четверг
        FRI,        ///< Пятница
        SAT,        ///< Суббота
    };

    /// Скоращенные имена месяцев
    enum {
        JAN = 1,    ///< Январь
        FEB,        ///< Февраль
        MAR,        ///< Март
        APR,        ///< Апрель
        MAY,        ///< Май
        JUNE,       ///< Июнь
        JULY,       ///< Июль
        AUG,        ///< Август
        SEPT,       ///< Сентябрь
        OCT,        ///< Октябрь
        NOV,        ///< Ноябрь
        DEC,        ///< Декабрь
    };

    const std::array<std::string, MONTHS_IN_YEAR> month_name_long = {
        "January","February","March",
        "April","May","June",
        "July","August","September",
        "October","November","December",
    };

    const std::array<std::string, MONTHS_IN_YEAR> month_name_short = {
        "Jan","Feb","Mar",
        "Apr","May","June",
        "July","Aug","Sept",
        "Oct","Nov","Dec",
    };

    /** \brief Получить дату автоматизации OLE из метки времени
     * \param timestamp Метка времени
     * \return Дата автоматизации OLE
     */
    oadate_t convert_timestamp_to_oadate(const timestamp_t &timestamp);

    /** \brief Получить дату автоматизации OLE из метки времени c плавающей точкой
     * \param timestamp Метка времени c плавающей точкой
     * \return Дата автоматизации OLE
     */
    oadate_t convert_ftimestamp_to_oadate(const ftimestamp_t &timestamp);

    /** \brief Преобразовать дату автоматизации OLE в метку времени
     * \param oadate Дата автоматизации OLE
     * \return Метка времени
     */
    timestamp_t convert_oadate_to_timestamp(const oadate_t &oadate);

    /** \brief Преобразовать дату автоматизации OLE в метку времени  плавающей точкой
     * \param oadate Дата автоматизации OLE
     * \return Метка времени с плавающей точкой
     */
    ftimestamp_t convert_oadate_to_ftimestamp(const oadate_t &oadate);

    /** \brief Получить дату автоматизации OLE
     * \return дата автоматизации OLE
     */
    oadate_t get_oadate();

    /** \brief Получить дату автоматизации OLE
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \param milliseconds миллисекунды
     * \return дата автоматизации OLE
     */
    oadate_t get_oadate(
        const uint32_t &day,
        const uint32_t &month,
        const uint32_t &year,
        const uint32_t &hour = 0,
        const uint32_t &minutes = 0,
        const uint32_t &seconds = 0,
        const uint32_t &milliseconds = 0);

    #define get_ole_automation_date get_oadate

    /** \brief Получить время и дату в виде строки
     * Формат строки: DD.MM.YYYY HH:MM:SS
     * \param timestamp метка времен
     * \return строка, содержащая время и дату
     */
    std::string get_str_date_time(const timestamp_t &timestamp);

    /** \brief Получить время и дату в виде строки
     * Формат строки: DD.MM.YYYY HH:MM:SS
     * \param timestamp метка времен
     * \return строка, содержащая время и дату
     */
    std::string get_str_date_time_ms(const ftimestamp_t &timestamp);

    /** \brief Получить дату в виде строки
     * Формат строки: DD.MM.YYYY
     * \param timestamp метка времен
     * \return строка, содержащая дату
     */
    std::string get_str_date(const timestamp_t &timestamp);

    /** \brief Получить время в виде строки
     * Формат строки: HH:MM:SS
     * \param timestamp метка времен
     * \return строка, содержащая время
     */
    std::string get_str_time(const timestamp_t &timestamp);

    /** \brief Получить время с миллисекундами в виде строки
     * Формат строки: HH:MM:SS.fff
     * \param timestamp метка времен
     * \return строка, содержащая время
     */
    std::string get_str_time_ms(const ftimestamp_t &timestamp);

    /** \brief Получить время и дату компьютера в виде строки
     * Формат строки: DD.MM.YYYY HH:MM:SS
     * Данная функция напечатает UTC/GMT время
     * \param timestamp unix время
     * \return строка, содержащая время
     */
    std::string get_str_date_time();

    /** \brief Получить время с миллисекундами и дату компьютера в виде строки
     * Формат строки: DD.MM.YYYY HH:MM:SS.fff
     * Данная функция напечатает UTC/GMT время
     * \param timestamp unix время
     * \return строка, содержащая время
     */
    std::string get_str_date_time_ms();

    /** \brief Получить время компьютера в виде строки с миллисекундами
     * Формат строки: DD.MM.YYYY HH:MM:SS
     * Данная функция напечатает UTC/GMT время
     * \param timestamp unix время
     * \return строка, содержащая время
     */
    std::string get_str_time_ms();

    /** \brief Получить миллисекунду
     * \return миллисекунда
     */
    uint32_t get_milliseconds();

    /** \brief Получить метку времени компьютера
     * \return метка времен
     */
    timestamp_t get_timestamp();

    /** \brief Получить метку времени
     * \param value строковое представление числа
     * \return метка времен
     */
    timestamp_t get_timestamp(std::string value);

    /** \brief Получить метку времени
     * \param value строковое представление числа
     * \return метка времен
     */
    ftimestamp_t get_ftimestamp(const std::string &value);

    /** \brief Получить метку времени компьютера с миллисекундами
     * \return метка времен
     */
    ftimestamp_t get_ftimestamp();

    /** \brief Получить метку времени из даты и стандартного времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \return метка времени
     */
    timestamp_t get_timestamp(
        const uint32_t &day,
        const uint32_t &month,
        const uint32_t &year,
        const uint32_t &hour = 0,
        const uint32_t &minutes = 0,
        const uint32_t &seconds = 0);

    /** \brief Получить метку времени с миллисекундами из даты и стандартного времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \param milliseconds миллисекунды
     * \return метка времени
     */
    ftimestamp_t get_ftimestamp(
        const uint32_t &day,
        const uint32_t &month,
        const uint32_t &year,
        const uint32_t &hour = 0,
        const uint32_t &minutes = 0,
        const uint32_t &seconds = 0,
        const uint32_t &milliseconds = 0);

    /** \brief Класс для хранения времени
     */
    class DateTime {
        public:
        uint32_t year;          /**< год */
        uint32_t milliseconds;  /**< микросекунды */
        uint8_t seconds;        /**< секунды */
        uint8_t minutes;        /**< минуты */
        uint8_t hour;           /**< час */
        uint8_t day;            /**< день */
        uint8_t month;          /**< месяц */

        bool is_correct();

        /** \brief Установить начало дня
         * Данная функция устанавливает час, минуту и секунду дня в 0
         */
        inline void set_beg_day() {
            milliseconds = 0;
            seconds = 0;
            minutes = 0;
            hour = 0;
        }

        /** \brief Установить конец дня
         */
        inline void set_end_day() {
            milliseconds = 999;
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
         * \param milliseconds миллисекунды
         */
        DateTime(
            const uint32_t &day,
            const uint32_t &month,
            const uint32_t &year,
            const uint32_t &hour = 0,
            const uint32_t &minutes = 0,
            const uint32_t &seconds = 0,
            const uint32_t &milliseconds = 0);

        /** \brief Инициализация с указанием unix-времени
         * \param timestamp метка времени
         */
        DateTime(const timestamp_t &timestamp);

        /** \brief Инициализация с указанием unix-времени
         * \param timestamp метка времени
         */
        DateTime(const ftimestamp_t &ftimestamp);

        /** \brief Инициализация с указанием unix-времени в формате ISO
         * Пример формата ISO: 2013-12-06T15:23:01+00:00
         * \param str_iso_formatted_utc_datetime время UTC в формате ISO
         */
        DateTime(const std::string &str_iso_formatted_utc_datetime);

        /** \brief Получить метку времени
         * \return timestamp
         */
        timestamp_t get_timestamp();

        /** \brief Получить метку времени с миллисекундами
         * \return timestamp
         */
        ftimestamp_t get_ftimestamp();

        /** \brief Установить время
         * \param timestamp метка времени
         */
        void set_timestamp(const timestamp_t &timestamp);

        /** \brief Установить время с миллисекундами
         * \param timestamp метка времени
         */
        void set_ftimestamp(const ftimestamp_t &ftimestamp);

        /** \brief Вывести время и дату на экран
         */
        void print();

        /** \brief Получить дату и время в виде строки
         * Формат строки: DD.MM.YYYY HH:MM:SS
         * \return строка, содержащая дату и время
         */
        std::string get_str_date_time();

        /** \brief Получить дату и время в виде строки
         * Формат строки: DD.MM.YYYY HH:MM:SS
         * \return строка, содержащая дату и время
         */
        std::string get_str_date_time_ms();

        /** \brief Получить дату в виде строки
         * Формат строки: DD.MM.YYYY
         * \return строка, содержащая дату
         */
        std::string get_str_date();

        /** \brief Получить время в виде строки
         * Формат строки: HH:MM:SS
         * \return строка, содержащая время
         */
        std::string get_str_time();

        /** \brief Получить время в виде строки
         * Формат строки: HH:MM:SS
         * \return строка, содержащая время
         */
        std::string get_str_time_ms();

        /** \brief Получить день недели
         * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
         */
        uint32_t get_weekday();

        /** \brief Проверка високосного года
         * \return вернет true, если год високосный
         */
        bool is_leap_year();

        /** \brief Получить количество дней в текущем месяце
         * \return количество дней
         */
        uint32_t get_num_days_current_month();

        /** \brief Получить дату автоматизации OLE
         * \return дата автоматизации OLE
         */
        oadate_t get_oadate();

        /** \brief Установить дату автоматизации OLE
         * \param oadate Дата автоматизации OLE
         */
        void set_oadate(const oadate_t &oadate);
    };

    /** \brief Конвертировать строку в формате ISO в данные класса DateTime
     * \param str_iso_formatted_utc_datetime строка в формате ISO, например 2013-12-06T15:23:01+00:00
     * \param t класс времени и даты DateTime, который будет заполнен.
     * \return вернет true если преобразование завершилось успешно
     */
    bool convert_iso(const std::string &str_iso_formatted_utc_datetime, DateTime& t);

    /** \brief Получить день недели
     * \param day день
     * \param month месяц
     * \param year год
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    uint32_t get_weekday(const uint32_t &day, const uint32_t &month, const uint32_t &year);

    /** \brief Получить день недели
     * \param timestamp метка времени
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    inline uint32_t get_weekday(const timestamp_t &timestamp) {
        return ((timestamp/SECONDS_IN_DAY + THU) % DAYS_IN_WEEK);
    }

    /** \brief Получить номер месяца по названию
     * \param month Имя месяца
     * \return номер месяца
     */
    uint32_t get_month(std::string month);

    /** \brief Получить день месяца
     * \param timestamp метка времени
     * \return день месяца
     */
    uint32_t get_day_month(const timestamp_t &timestamp);

    /** \brief Преобразует строку, полученную функцией get_str_date_time или методом get_str_date_time
     * обратно в timestamp
     * Также данная функция поддерживает форматы времени:
     * HH:MM:SS DD MM YY Пример: 20:25:00, 29 Aug 19
     * HH:MM:SS DD MM YY Пример: 20:25:00, 29 Aug 2019
     * HH:MM:SS DD.MM.YYYY Пример: 00:59:59 30.08.2019
     * HH:MM:SS DD-MM-YYYY Пример: 00:59:59 30-08-2019
     * YYYY-MM-DD hh:mm:ss Пример: 2013-02-25 18:25:10
     * YYYY.MM.DD hh:mm:ss Пример: 2013.02.25 18:25:10
     * YYYY.MM.DD Пример: 2013.02.25
     * DD.MM.YYYY Пример: 21.09.2018
     * \param str время в формате строки, например
     * \param t метка времени
     * \return вернет true если преобразование завершилось успешно
     */
    bool convert_str_to_timestamp(std::string str, timestamp_t& t);

    /** \brief Преобразовать unix-время в класс DateTime
     * \param timestamp метка времени
     * \return класс DateTime
     */
    DateTime convert_timestamp_to_datetime(const timestamp_t &timestamp);

    /** \brief Напечатать дату и время
     * \param timestamp метка времени
     */
    void print_date_time(const timestamp_t &timestamp);

    /** \brief Получить количество дней в месяце
     * \param month месяц
     * \param year год
     * \return количество дней в месяце
     */
    uint32_t get_num_days_month(const uint32_t &month, const uint32_t &year);

    /** \brief Получить количество дней в месяце
     * \param timestamp метка времени
     * \return количество дней в месяце
     */
    uint32_t get_num_days_month(const timestamp_t &timestamp);

    /** \brief Переводит время GMT во время CET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt метка времени, время GMT
     * \return время CET
     */
    timestamp_t convert_gmt_to_cet(const timestamp_t &gmt);

    /** \brief Переводит время GMT во время EET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt метка времени, время GMT
     * \return время EET
     */
    timestamp_t convert_gmt_to_eet(const timestamp_t &gmt);

    /** \brief Переводит время GMT во время MSK
     * \param gmt метка времени, время GMT
     * \return время MSK
     */
    timestamp_t convert_gmt_to_msk(const timestamp_t &gmt);

    /** \brief Переводит время CET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param cet метка времени c измененым часовым поясом, время CET
     * \return время GMT
     */
    timestamp_t convert_cet_to_gmt(const timestamp_t &cet);

    /** \brief Переводит время EET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param eet метка времени c измененым часовым поясом, время EET
     * \return время GMT
     */
    timestamp_t convert_eet_to_gmt(const timestamp_t &eet);

    /** \brief Переводит время MSK во время GMT
     * \param msk метка времени c измененым часовым поясом, время MSK
     * \return время GMT
     */
    timestamp_t convert_msk_to_gmt(const timestamp_t &msk);

    /** \brief Проверить начало получаса
     * \param timestamp метка времени
     * \return вернет true, если начало получаса
     */
    inline bool is_beg_half_hour(const timestamp_t &timestamp) {
        return timestamp % SECONDS_IN_HALF_HOUR == 0;
    }

    /** \brief Проверить начало часа
     * \param timestamp метка времени
     * \return вернет true, если начало часа
     */
    inline bool is_beg_hour(const timestamp_t &timestamp) {
        return timestamp % SECONDS_IN_HOUR == 0;
    }

    /** \brief Проверить начало дня
     * \param timestamp метка времени
     * \return вернет true, если начало дня
     */
    inline bool is_beg_day(const timestamp_t &timestamp) {
        return timestamp % SECONDS_IN_DAY == 0;
    }

    /** \brief Проверить начало недели
     * Если день воскресенье, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp метка времени
     * \return вернет true, если начало недели
     */
    inline bool is_beg_week(const timestamp_t &timestamp){
        return get_weekday(timestamp) == SUN;
    }

    /** \brief Проверить начало месяца
     * Если первый день месяца, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp метка времени
     * \return вернет true, если начало месяца
     */
    inline bool is_beg_month(timestamp_t timestamp) {
        return get_day_month(timestamp) == 1;
    }

    /** \brief Проверить конец месяца
     * Если последний день месяца, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp временная метка
     * \return вернет true, если конец месяца
     */
    bool is_end_month(const timestamp_t &timestamp);

    /** \brief Проверить корректность даты
     * \param day день
     * \param month месяц
     * \param year год
     * \return вернет true, если заданная дата возможна
     */
    bool is_correct_date(const uint32_t &day, const uint32_t &month, const uint32_t &year);

    /** \brief Проверить корректность времени
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \param milliseconds миллисекунды
     * \return вернет true, если заданное время корректно
     */
    bool is_correct_time(
        const uint32_t &hour,
        const uint32_t &minutes = 0,
        const uint32_t &seconds = 0,
        const uint32_t &milliseconds = 0);

    /** \brief Проверить корректность даты и времени
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \param milliseconds миллисекунды
     * \return вернет true, если заданное время корректно
     */
    bool is_correct_date_time(
        const uint32_t &day,
        const uint32_t &month,
        const uint32_t &year,
        const uint32_t &hour = 0,
        const uint32_t &minutes = 0,
        const uint32_t &seconds = 0,
        const uint32_t &milliseconds = 0);

    /** \brief Получить метку времени в начале дня
     * Данная функция обнуляет часы, минуты и секунды
     * \param timestamp метка времени
     * \return временная метка в начале дня
     */
    inline timestamp_t get_first_timestamp_day(const timestamp_t &timestamp) {
        return timestamp - (timestamp % SECONDS_IN_DAY);
    }

    /** \brief Получить метку времени в конце дня
     * Данная функция устанавливает час 23, минута 59 и секунда 59
     * \param timestamp метка времени
     * \return временная метка в конце дня
     */
    inline timestamp_t get_last_timestamp_day(const timestamp_t &timestamp) {
        return timestamp - (timestamp % SECONDS_IN_DAY) + SECONDS_IN_DAY - 1;
    }

    /** \brief Получить метку времени в начале часа
     * Данная функция обнуляет минуты и секунды
     * \param timestamp метка времени
     * \return временная метка в начале часа
     */
    inline timestamp_t get_first_timestamp_hour(const timestamp_t &timestamp) {
        return timestamp - (timestamp % SECONDS_IN_HOUR);
    }

    /** \brief Получить метку времени в конце часа
     * Данная функция обнуляет минуты и секунды
     * \param timestamp метка времени
     * \return временная метка в конце часа
     */
    inline timestamp_t get_last_timestamp_hour(const timestamp_t &timestamp) {
        return timestamp - (timestamp % SECONDS_IN_HOUR) + SECONDS_IN_HOUR - 1;
    }

    /** \brief Получить метку времени в начале минуты
     * Данная функция обнуляет секунды
     * \param timestamp метка времени
     * \return временная метка в начале минуты
     */
    inline timestamp_t get_first_timestamp_minute(const timestamp_t &timestamp) {
        return timestamp - (timestamp % SECONDS_IN_MINUTE);
    }

    /** \brief Получить метку времени в конце минуты
     * Данная функция обнуляет секунды
     * \param timestamp метка времени
     * \return временная метка в конце минуты
     */
    inline timestamp_t get_last_timestamp_minute(const timestamp_t &timestamp) {
        return timestamp - (timestamp % SECONDS_IN_MINUTE) + SECONDS_IN_MINUTE - 1;
    }

    /** \brief Проверить выходной день (суббота и воскресение)
     * \param timestamp метка времени
     * \return вернет true если выходной день
     */
    inline bool is_day_off(const timestamp_t &timestamp) {
        uint32_t wday = get_weekday(timestamp);
        if(wday == xtime::SUN || wday == xtime::SAT) return true;
        return false;
    }

    /** \brief Проверить выходной день (суббота и воскресение)
     * \param day день с начала отсчета Unix-времени
     * \return вернет true если выходной день
     */
    inline bool is_day_off_for_day(const uint32_t &day) {
        uint32_t wday = (day + THU) % DAYS_IN_WEEK;
        if(wday == xtime::SUN || wday == xtime::SAT) return true;
        return false;
    }

    /** \brief Проверка високосного года
     * \param year год
     * \return вернет true, если год високосный
     */
    inline bool is_leap_year(const uint32_t &year) {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return true;
        return false;
    }

    /** \brief Получить минуту дня
     * Данная функция вернет от 0 до 1439 (минуту дня)
     * \param timestamp метка времени
     * \return минута дня
     */
    inline uint32_t get_minute_day(const timestamp_t &timestamp) {
            return (timestamp / SECONDS_IN_MINUTE) % MINUTES_IN_DAY;
    }

    /** \brief Получить час дня
     * Данная функция вернет от 0 до 23 (час дня)
     * \param timestamp метка времени
     * \return час дня
     */
    inline uint32_t get_hour_day(const timestamp_t &timestamp) {
            return (timestamp / SECONDS_IN_HOUR) % HOURS_IN_DAY;
    }

    /** \brief Получить секунду минуты
     * Данная функция вернет от 0 до 59 (секунда минуты)
     * \param timestamp метка времени
     * \return секунда минуты
     */
    inline uint32_t get_second_minute(const timestamp_t &timestamp) {
            return timestamp % SECONDS_IN_MINUTE;
    }

    /** \brief Получить секунду часа
     * Данная функция вернет от 0 до 3599 (секунда часа)
     * \param timestamp метка времени
     * \return секунда часа
     */
    inline uint32_t get_second_hour(const timestamp_t &timestamp) {
            return timestamp % SECONDS_IN_HOUR;
    }

    /** \brief Получить секунду дня
     * Данная функция вернет от 0 до 86399 (секунда дня)
     * \param timestamp метка времени
     * \return секунда дня
     */
    inline uint32_t get_second_day(const timestamp_t &timestamp) {
            return timestamp % SECONDS_IN_DAY;
    }

    /** \brief Получить день
     * Данная функция вернет день, начиная с начала UNIX времени
     * \param timestamp метка времени
     * \return день с начала UNIX времени
     */
    inline uint32_t get_day(const timestamp_t &timestamp) {
            return (timestamp / SECONDS_IN_DAY);
    }

    /** \brief Получить временную метку начала года
     * \param year год
     * \return временная метка начала года
     */
    inline timestamp_t get_timestamp_beg_year(const uint32_t &year) {
        uint32_t diff = (year - FIRST_YEAR_UNIX);
        if(diff < 0) return 0;
        timestamp_t t = (diff / 4) * SECONDS_IN_4_YEAR;
        uint32_t temp = diff % 4;
        if(temp == 0) return t;
        else if(temp == 1) return t + SECONDS_IN_YEAR;
        else if(temp == 2) return t + (2*SECONDS_IN_YEAR);
        return t + (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR);
    }

    /** \brief Получить год
     * Данная функция вернет год указанной временной метки
     * \param timestamp временная метка
     * \return год UNIX времени
     */
    inline uint32_t get_year(const timestamp_t &timestamp) {
        uint32_t year = FIRST_YEAR_UNIX + 4 * (timestamp / SECONDS_IN_4_YEAR);
        timestamp_t t = timestamp % SECONDS_IN_4_YEAR;
        if(t < SECONDS_IN_YEAR) return year;
        else if(t < (2*SECONDS_IN_YEAR)) return year + 1;
        else if(t < (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR)) return year + 2;
        return year + 3;
    }

    /** \brief Получить день года
     * \param timestamp метка времени
     * \return день года
     */
    inline uint32_t get_day_year(const timestamp_t &timestamp) {
        uint32_t year = get_year(timestamp);
        return get_day(timestamp) - get_day(get_timestamp_beg_year(year)) + 1;
    }

    /** \brief Получить месяц года
     * \param timestamp метка времени
     * \return месяц года
     */
    inline uint32_t get_month(const timestamp_t &timestamp) {
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

    /** \brief Получить последнюю метку времени текущего месяца
     * \param timestamp Метка времени
     * \return Последняя метка времени текущего месяца
     */
    inline timestamp_t get_last_timestamp_month(const timestamp_t &timestamp) {
        uint32_t days_month = get_num_days_month(timestamp);
        uint32_t day = get_day_month(timestamp);
        timestamp_t timestamp_new = get_last_timestamp_day(timestamp);
        uint32_t offset = days_month - day;
        timestamp_new += offset * SECONDS_IN_DAY;
        return timestamp_new;
    }

    /** \brief Получить последнюю метку времени последнего воскресения текущего месяца
     * \param timestamp Метка времениm
     * \return Последняя метка времени текущего последнего воскресения текущего месяца
     */
    inline timestamp_t get_last_timestamp_sunday_month(const timestamp_t &timestamp) {
        timestamp_t last_timestamp = get_last_timestamp_month(timestamp);
        uint32_t weekday = get_weekday(timestamp);
        last_timestamp -= weekday * SECONDS_IN_DAY;
        return last_timestamp;
    }

    /** \brief Получить количество дней в текущем году
     * \param timestamp временная метка
     * \return дней в текущем году
     */
    inline uint32_t get_day_in_year(const timestamp_t &timestamp) {
        if(is_leap_year(get_year(timestamp))) return DAYS_IN_LEAP_YEAR;
        return DAYS_IN_YEAR;
    }

    /** \brief Получить метку времени начала дня от начала unix-времени
     * \param day день с начала unix-времени
     * \return метка времени
     */
    inline timestamp_t get_first_timestamp_for_day(const uint32_t &day) {
        return day * SECONDS_IN_DAY;
    }

    /** \brief Получить метку времени начала предыдущего дня
     * \param timestamp Метка времени текущего дня
     * \return метка времени начала предыдущего дня
     */
    inline timestamp_t get_first_timestamp_previous_day(const timestamp_t &timestamp) {
        return get_first_timestamp_day(timestamp) - SECONDS_IN_DAY;
    }

}

#endif // XTIME_HPP_INCLUDED
