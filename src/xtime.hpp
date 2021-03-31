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
#include <chrono>
#include <functional>
#include <algorithm>

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

    /// Различные периоды
    enum {
        MILLISECONDS_IN_SECOND = 1000,		///< Количество миллисекунд в одной секунде
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
		MINUTES_IN_WEEK = 10080,            ///< Количество минут в одной неделе
		MINUTES_IN_MONTH = 40320,           ///< Количество минут в одном месяце
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

    template<class T>
    struct Period {
        T start;
        T stop;

        Period() : start(0), stop(0) {};

        Period(T &a, T &b) : start(a), stop(b) {};

        Period(const T &a, const T &b) : start(a), stop(b) {};
    };

    typedef Period<uint64_t> period_t;  ///< Целочисленный тип периода времени
    typedef Period<double> fperiod_t;   ///< Тип периода времени с плавающей точкой

    const std::array<std::string, MONTHS_IN_YEAR> month_name_long = {
        "January","February","March",
        "April","May","June",
        "July","August","September",
        "October","November","December",
    }; /**< Длинные имена месяцев */

    const std::array<std::string, MONTHS_IN_YEAR> month_name_short = {
        "Jan","Feb","Mar",
        "Apr","May","June",
        "July","Aug","Sept",
        "Oct","Nov","Dec",
    }; /**< Сокращенные имена месяцев */

    const std::array<std::string, DAYS_IN_WEEK> weekday_name_short = {
        "SUN",
        "MON",
        "TUS",
        "WED",
        "THU",
        "FRI",
        "SAT",
    }; /**< Сокращенные имена дней недели */

    /** \brief Получить миллисекунду
     * \return миллисекунда
     */
    uint32_t get_millisecond();

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
     * \param minute минуты
     * \param second секунды
     * \return метка времени
     */
    constexpr inline timestamp_t get_timestamp(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour = 0,
            const uint32_t minute = 0,
            const uint32_t second = 0) noexcept {
        long _mon = month - 1;
        const long _TBIAS_YEAR = 1900;
        const long	lmos[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        const long	mos[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        long _year = year - _TBIAS_YEAR;
        // для предотвращения проблемы 2038 года переменная должна быть больше 32 бит
        long long _days = (((_year - 1) / 4) + ((((_year) & 03) || ((_year) == 0)) ? mos[_mon] : lmos[_mon])) - 1;
        _days += DAYS_IN_YEAR * _year;
        _days += day;
        const long _TBIAS_DAYS = 25567;
        _days -= _TBIAS_DAYS;
        timestamp_t _secs = SECONDS_IN_HOUR * hour;
        _secs += SECONDS_IN_MINUTE * minute;
        _secs += second;
        _secs += _days * SECONDS_IN_DAY;
        return _secs;
    }

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
    constexpr inline ftimestamp_t get_ftimestamp(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour = 0,
            const uint32_t minute = 0,
            const uint32_t second = 0,
            const uint32_t millisecond = 0) noexcept {
        timestamp_t t = get_timestamp(day, month, year, hour, minute, second);
        return (double)t + (double)millisecond/1000.0;
    }

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

    /** \brief Получить дату автоматизации OLE из метки времени
     * \param timestamp Метка времени
     * \return Дата автоматизации OLE
     */
    constexpr inline oadate_t convert_timestamp_to_oadate(const timestamp_t timestamp) noexcept {
		return (const oadate_t)OADATE_UNIX_EPOCH + (const oadate_t)timestamp / (const oadate_t)SECONDS_IN_DAY;
	}

    /** \brief Получить дату автоматизации OLE из метки времени c плавающей точкой
     * \param timestamp Метка времени c плавающей точкой
     * \return Дата автоматизации OLE
     */
    constexpr inline oadate_t convert_ftimestamp_to_oadate(const ftimestamp_t timestamp) noexcept {
        return (const oadate_t)OADATE_UNIX_EPOCH + (const oadate_t)timestamp / (const oadate_t)SECONDS_IN_DAY;
    }

    /** \brief Преобразовать дату автоматизации OLE в метку времени
     * \param oadate Дата автоматизации OLE
     * \return Метка времени
     */
    constexpr inline timestamp_t convert_oadate_to_timestamp(const oadate_t oadate) noexcept {
        if(oadate < (const oadate_t)OADATE_UNIX_EPOCH) return 0;
        return (timestamp_t)((oadate - (oadate_t)OADATE_UNIX_EPOCH) * (oadate_t)SECONDS_IN_DAY);
    }

    /** \brief Преобразовать дату автоматизации OLE в метку времени  плавающей точкой
     * \param oadate Дата автоматизации OLE
     * \return Метка времени с плавающей точкой
     */
    constexpr inline ftimestamp_t convert_oadate_to_ftimestamp(const oadate_t oadate) noexcept {
        if(oadate < (const oadate_t)OADATE_UNIX_EPOCH) return 0;
        return (ftimestamp_t)((oadate - (oadate_t)OADATE_UNIX_EPOCH) * (oadate_t)SECONDS_IN_DAY);
    }

    /** \brief Получить дату автоматизации OLE
     * \return дата автоматизации OLE
     */
    inline oadate_t get_oadate() noexcept {
        return convert_ftimestamp_to_oadate(get_ftimestamp());
    }

    /** \brief Получить дату автоматизации OLE
     * \param day день
     * \param month месяц
     * \param year год
     * \param hour час
     * \param minute минуты
     * \param second секунды
     * \param millisecond миллисекунды
     * \return дата автоматизации OLE
     */
    constexpr inline oadate_t get_oadate(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour = 0,
            const uint32_t minute = 0,
            const uint32_t second = 0,
            const uint32_t millisecond = 0) noexcept {
        return convert_ftimestamp_to_oadate(get_ftimestamp(
            day,
            month,
            year,
            hour,
            minute,
            second,
            millisecond));
    }

    #define get_ole_automation_date get_oadate

    /** \brief Получить время и дату в виде строки
     * Формат строки: DD.MM.YYYY HH:MM:SS
     * Если не указать метку времени, данная функция вернет строку с UTC/GMT временем компьютера
     * \param timestamp метка времен
     * \return строка, содержащая время и дату
     */
    std::string get_str_date_time(const timestamp_t timestamp = get_timestamp());

    /** \brief Получить время и дату в виде строки
     * Формат строки: DD.MM.YYYY HH:MM:SS.sss
     * Если не указать метку времени, данная функция вернет строку с UTC/GMT временем компьютера
     * \param timestamp метка времен
     * \return строка, содержащая время и дату
     */
    std::string get_str_date_time_ms(const ftimestamp_t timestamp = get_ftimestamp());

    /** \brief Получить дату в виде строки
     * Формат строки: DD.MM.YYYY
     * Если не указать метку времени, данная функция вернет строку с UTC/GMT временем компьютера
     * \param timestamp метка времен
     * \return строка, содержащая дату
     */
    std::string get_str_date(const timestamp_t timestamp = get_timestamp());

    /** \brief Получить время в виде строки
     * Формат строки: HH:MM:SS или HH:MM
     * Если не указать метку времени, данная функция вернет строку с UTC/GMT временем компьютера
     * \param timestamp метка времен
     * \param is_use_seconds Флаг, который добавляет секунды
     * \return строка, содержащая время
     */
    std::string get_str_time(const timestamp_t timestamp = get_timestamp(), const bool is_use_seconds = true);

    /** \brief Получить время с миллисекундами в виде строки
     * Формат строки: HH:MM:SS.sss
     * Если не указать метку времени, данная функция вернет строку с UTC/GMT временем компьютера
     * \param timestamp метка времен
     * \return строка, содержащая время
     */
    std::string get_str_time_ms(const ftimestamp_t timestamp = get_ftimestamp());

    /** \brief Получить строку в формате ISO 8601
     * Функция возвращает строку с временем и датой,
     * сформированную по стандарту ISO 8601,
     * в котором строка имеет следующий формат: YYYY-MM-DDThh:mm:ss.sssZ.
     * Если установлен часовой пояс, то буква "Z" заменяется значением +hh:mm или -hh.mm
     * \param timestamp Метка времен
     * \param offset Смещение в секундах, определяет часовой пояс.
     * \return Строка, содержащая время
     */
    std::string get_str_iso_8601(const xtime::ftimestamp_t timestamp, const int64_t offset = 0);

    /** \brief Преобразовать метку времени в строку с пользовательскими настройками преобразования
     * В качестве параметров функция принимает следующие аргументы:
     * %YYYY - год
     * %YY - последние два числа года
     * %Y - год, без ограничений в 4 символа
     * %MM - месяц
     * %DD - день месяца
     * %hh - час дня
     * %mm - минуты часа
     * %ss - секунды
     * %sss - миллисекунды
     * %W - день недели (число)
     * %w - день недели (скоращенное имя)
     * \param mode Строка с параметрами пользователя, например "%YYYY-%MM-%DD"
     * \param timestamp Метка времени
     * \return Вернет строку в формате, заданным пользователем
     */
    std::string to_string(const std::string &mode, const xtime::ftimestamp_t timestamp = get_ftimestamp());

    /** \brief Класс для хранения времени
     */
    class DateTime {
    public:
        uint32_t year;          /**< год */
        uint32_t millisecond;   /**< миллисекунды */
        uint8_t second;         /**< секунды */
        uint8_t minute;         /**< минуты */
        uint8_t hour;           /**< час */
        uint8_t day;            /**< день */
        uint8_t month;          /**< месяц */

        bool is_correct();

        /** \brief Установить начало дня
         * Данная функция устанавливает час, минуту и секунду дня в 0
         */
        inline void set_beg_day() {
            millisecond = 0;
            second = 0;
            minute = 0;
            hour = 0;
        }

        /** \brief Установить конец дня
         */
        inline void set_end_day() {
            millisecond = 999;
            second = 59;
            minute = 59;
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
         * \param minute минуты
         * \param second секунды
         * \param millisecond миллисекунды
         */
        DateTime(
            const uint32_t day,
            const uint32_t month,
            const uint32_t year,
            const uint32_t hour = 0,
            const uint32_t minute = 0,
            const uint32_t second = 0,
            const uint32_t millisecond = 0);

        /** \brief Инициализация с указанием unix-времени
         * \param timestamp метка времени
         */
        DateTime(const timestamp_t timestamp);

        /** \brief Инициализация с указанием unix-времени
         * \param timestamp метка времени
         */
        DateTime(const ftimestamp_t ftimestamp);

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
        void set_timestamp(const timestamp_t timestamp);

        /** \brief Установить время с миллисекундами
         * \param timestamp метка времени
         */
        void set_ftimestamp(const ftimestamp_t ftimestamp);

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
         * \param is_use_seconds Флаг, включает использование секунд
         * \return строка, содержащая время
         */
        std::string get_str_time(const bool is_use_seconds = true);

        /** \brief Получить время в виде строки
         * Формат строки: HH:MM:SS.sss
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
        void set_oadate(const oadate_t oadate);
    };

    /** \brief Таймер для измерений задержек
     */
    class Timer {
    private:
        /* steady_clock представляет собой монотонные часы.
         * Точки времени на этих часах не могут уменьшаться по мере того,
         * как физическое время движется вперед,
         * и время между тактами этих часов остается постоянным.
         * Эти часы не связаны со временем настенных часов
         * (например, это может быть время с момента последней перезагрузки)
         * и больше всего подходят для измерения интервалов.
         */
        using clock_t = std::chrono::steady_clock;
        using second_t = std::chrono::duration<double, std::ratio<1>>;

        std::chrono::time_point<clock_t> start_time;
        double sum = 0;
        uint64_t counter = 0;
    public:
        Timer() : start_time(clock_t::now()) {}

        /** \brief Сбросить значение таймера
         *
         * Данный метод нужно применять только вместе с методом elapsed()
         * При использовании метода
         * get_average_measurements() сбрасывать таймер не нужно!
         */
        inline void reset() {
            start_time = clock_t::now();
        }

        /** \brief Получить замер времени
         * \return Время в секундах с момента инициализации класса или после reset()
         */
        inline double get_elapsed() const {
            return std::chrono::duration_cast<second_t>(clock_t::now() - start_time).count();
        }

        /** \brief Сбросить все замеры
         *
         * Данный метод обнуляет сумму замеров и их количество
         */
        inline void reset_measurement() {
            sum = 0;
            counter = 0;
        }

        /** \brief Начать замер
         *
         * Данный метод использовать вместе с методами stop_measurement()
         * и get_average_measurements()
         */
        inline void start_measurement() {
            reset();
        }

        /** \brief Остановить замер
         *
         * Данный метод использовать вместе с методами start_measurement()
         * и get_average_measurements()
         */
        inline void stop_measurement() {
            sum += get_elapsed();
            ++counter;
        }

        /** \brief Получить результаты замеров
         *
         * Данный метод использовать вместе с методами start_measurement()
         * и stop_measurement(). Метод возвращает средний результат замеров
         * \return Среднее время замеров в секундах
         */
        inline double get_average_measurements() const {
            return sum / (double)counter;
        }
    };

    /** \brief Конвертировать строку в формате ISO в данные класса DateTime
     * \param str_datetime строка в формате ISO, например 2013-12-06T15:23:01+00:00
     * \param t класс времени и даты DateTime, который будет заполнен.
     * \return вернет true если преобразование завершилось успешно
     */
    bool convert_iso(
        const std::string &str_datetime,
        DateTime& t);

    /** \brief Конвертировать строку в формате ISO в метку времени с дробной частью
     * \param str_datetime строка в формате ISO, например 2013-12-06T15:23:01+00:00
     * \return Вернет метку времени, если преобразование завершилось успешно, или 0 в случае провала
     */
    xtime::ftimestamp_t convert_iso(const std::string &str_datetime);

    /** \brief Получить день недели
     * \param day день
     * \param month месяц
     * \param year год
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    uint32_t get_weekday(
        const uint32_t day,
        const uint32_t month,
        const uint32_t year);

    /** \brief Получить день недели
     * \param timestamp метка времени
     * \return день недели (SUN = 0, MON = 1, ... SAT = 6)
     */
    constexpr inline uint32_t get_weekday(const timestamp_t timestamp) noexcept {
        return ((timestamp / SECONDS_IN_DAY + THU) % DAYS_IN_WEEK);
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
    uint32_t get_day_month(const timestamp_t timestamp = get_timestamp());

    /** \brief Преобразует строку в timestamp
     *
     * Данная функция поддерживает форматы времени:
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
    DateTime convert_timestamp_to_datetime(const timestamp_t timestamp = get_timestamp());

    /** \brief Напечатать дату и время
     * \param timestamp метка времени
     */
    void print_date_time(const timestamp_t timestamp = get_timestamp());

    /** \brief Получить количество дней в месяце
     * \param month месяц
     * \param year год
     * \return количество дней в месяце
     */
    uint32_t get_num_days_month(const uint32_t month, const uint32_t year);

    /** \brief Получить количество дней в месяце
     * \param timestamp метка времени
     * \return количество дней в месяце
     */
    uint32_t get_num_days_month(const timestamp_t timestamp = get_timestamp());

    /** \brief Переводит время GMT во время CET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt метка времени, время GMT
     * \return время CET
     */
    timestamp_t convert_gmt_to_cet(const timestamp_t gmt);

    /** \brief Переводит время GMT во время EET
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param gmt метка времени, время GMT
     * \return время EET
     */
    timestamp_t convert_gmt_to_eet(const timestamp_t gmt);

    /** \brief Переводит время GMT во время MSK
     * \param gmt метка времени, время GMT
     * \return время MSK
     */
    timestamp_t convert_gmt_to_msk(const timestamp_t gmt);

    /** \brief Переводит время CET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param cet метка времени c измененым часовым поясом, время CET
     * \return время GMT
     */
    timestamp_t convert_cet_to_gmt(const timestamp_t cet);

    /** \brief Переводит время EET во время GMT
     * До 2002 года в Европе переход на летнее время осуществлялся в последнее воскресенье марта в 2:00 переводом часов на 1 час вперёд
     * а обратный переход осуществлялся в последнее воскресенье октября в 3:00 переводом на 1 час назад
     * Начиная с 2002 года, согласно директиве ЕС(2000/84/EC) в Европе переход на летнее время осуществляется в 01:00 по Гринвичу.
     * \param eet метка времени c измененым часовым поясом, время EET
     * \return время GMT
     */
    timestamp_t convert_eet_to_gmt(const timestamp_t eet);

    /** \brief Переводит время MSK во время GMT
     * \param msk метка времени c измененым часовым поясом, время MSK
     * \return время GMT
     */
    timestamp_t convert_msk_to_gmt(const timestamp_t msk);

    /** \brief Проверить начало получаса
     * \param timestamp метка времени
     * \return вернет true, если начало получаса
     */
    inline bool is_beg_half_hour(const timestamp_t timestamp = get_timestamp()) {
        return timestamp % SECONDS_IN_HALF_HOUR == 0;
    }

    /** \brief Проверить начало часа
     * \param timestamp метка времени
     * \return вернет true, если начало часа
     */
    inline bool is_beg_hour(const timestamp_t timestamp = get_timestamp()) {
        return timestamp % SECONDS_IN_HOUR == 0;
    }

    /** \brief Проверить начало дня
     * \param timestamp метка времени
     * \return вернет true, если начало дня
     */
    inline bool is_beg_day(const timestamp_t timestamp = get_timestamp()) {
        return (timestamp % SECONDS_IN_DAY == 0);
    }

    /** \brief Проверить начало недели
     * Если день воскресенье, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp метка времени
     * \return вернет true, если начало недели
     */
    inline bool is_beg_week(const timestamp_t timestamp = get_timestamp()){
        return get_weekday(timestamp) == SUN;
    }

    /** \brief Проверить начало месяца
     * Если первый день месяца, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp метка времени
     * \return вернет true, если начало месяца
     */
    inline bool is_beg_month(timestamp_t timestamp = get_timestamp()) {
        return get_day_month(timestamp) == 1;
    }

    /** \brief Проверить конец месяца
     * Если последний день месяца, функция вернет true
     * \warning Данная функция проверят только день! Она не проверяет секунды, минуты, часы
     * \param timestamp метка времени
     * \return вернет true, если конец месяца
     */
    bool is_end_month(const timestamp_t timestamp = get_timestamp());

    /** \brief Проверить корректность даты
     * \param day день
     * \param month месяц
     * \param year год
     * \return вернет true, если заданная дата возможна
     */
    bool is_correct_date(const uint32_t day, const uint32_t month, const uint32_t year);

    /** \brief Проверить корректность времени
     * \param hour час
     * \param minutes минуты
     * \param seconds секунды
     * \param milliseconds миллисекунды
     * \return вернет true, если заданное время корректно
     */
    bool is_correct_time(
        const uint32_t hour,
        const uint32_t minutes = 0,
        const uint32_t seconds = 0,
        const uint32_t milliseconds = 0);

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
        const uint32_t day,
        const uint32_t month,
        const uint32_t year,
        const uint32_t hour = 0,
        const uint32_t minute = 0,
        const uint32_t second = 0,
        const uint32_t millisecond = 0);

    /** \brief Получить метку времени в начале года
     *
     * Данная функция обнуляет дни, месяцы, часы, минуты и секунды
     * \param timestamp метка времени
     * \return Метка времени начала года
     */
    inline timestamp_t get_first_timestamp_year(const timestamp_t timestamp) noexcept {
        timestamp_t t = timestamp % SECONDS_IN_4_YEAR;
        if(t < SECONDS_IN_YEAR) return timestamp - t;
        else if(t < (2*SECONDS_IN_YEAR)) return timestamp + SECONDS_IN_YEAR - t;
        else if(t < (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR)) return timestamp + (2*SECONDS_IN_YEAR) - t;
        return timestamp + (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR) - t;
    }

    /** \brief Получить метку времени в конце года
     *
     * Данная функция находит последнюю метку времени текущего года
     * \param timestamp метка времени
     * \return Метка времени конца года
     */
    inline timestamp_t get_last_timestamp_year(const timestamp_t timestamp = get_timestamp()) noexcept {
        timestamp_t t = timestamp % SECONDS_IN_4_YEAR;
        if(t < SECONDS_IN_YEAR) return timestamp + SECONDS_IN_YEAR - t - 1;
        else if(t < (2*SECONDS_IN_YEAR)) return timestamp + (2*SECONDS_IN_YEAR) - t - 1;
        else if(t < (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR)) return timestamp + (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR) - t - 1;
        return timestamp + (3*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR) - t - 1;
    }

    /** \brief Получить метку времени в начале дня
     *
     * Данная функция вернет метку времени в начале дня.
     * Функция обнуляет часы, минуты и секунды
     * \param timestamp метка времени
     * \return метка времени в начале дня
     */
    inline timestamp_t get_first_timestamp_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return timestamp - (timestamp % SECONDS_IN_DAY);
    }

    /** \brief Получить метку времени в конце дня
     * Данная функция устанавливает час 23, минута 59 и секунда 59
     * \param timestamp метка времени
     * \return метка времени в конце дня
     */
    inline timestamp_t get_last_timestamp_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return timestamp - (timestamp % SECONDS_IN_DAY) + SECONDS_IN_DAY - 1;
    }

    /** \brief Получить метку времени в начале часа
     * Данная функция обнуляет минуты и секунды
     * \param timestamp метка времени
     * \return метка времени в начале часа
     */
    inline timestamp_t get_first_timestamp_hour(const timestamp_t timestamp = get_timestamp()) noexcept {
        return timestamp - (timestamp % SECONDS_IN_HOUR);
    }

    /** \brief Получить метку времени в конце часа
     * Данная функция обнуляет минуты и секунды
     * \param timestamp метка времени
     * \return метка времени в конце часа
     */
    inline timestamp_t get_last_timestamp_hour(const timestamp_t timestamp = get_timestamp()) noexcept {
        return timestamp - (timestamp % SECONDS_IN_HOUR) + SECONDS_IN_HOUR - 1;
    }

    /** \brief Получить метку времени в начале минуты
     * Данная функция обнуляет секунды
     * \param timestamp Метка времени
     * \return Метка времени в начале минуты
     */
    inline timestamp_t get_first_timestamp_minute(const timestamp_t timestamp = get_timestamp()) noexcept {
        return timestamp - (timestamp % SECONDS_IN_MINUTE);
    }

    /** \brief Получить метку времени в конце минуты
     * Данная функция обнуляет секунды
     * \param timestamp Метка времени
     * \return Метка времени в конце минуты
     */
    inline timestamp_t get_last_timestamp_minute(const timestamp_t timestamp = get_timestamp()) noexcept {
        return timestamp - (timestamp % SECONDS_IN_MINUTE) + SECONDS_IN_MINUTE - 1;
    }

    /** \brief Получить метку времени в начале периода
     *
     * \param period Период
     * \param timestamp Метка времени
     * \return Метка времени в начале периода
     */
    inline timestamp_t get_first_timestamp_period(const uint32_t period, const timestamp_t timestamp  = get_timestamp()) noexcept {
        return timestamp - (timestamp % period);
    }

    /** \brief Получить метку времени в конце периода
     *
     * \param period Период
     * \param timestamp Метка времени
     * \return Метка времени в конце периода
     */
    inline timestamp_t get_last_timestamp_period(const uint32_t period, const timestamp_t timestamp  = get_timestamp()) noexcept {
        return timestamp - (timestamp % period) + period - 1;
    }

    /** \brief Проверить выходной день (суббота и воскресение)
     * \param timestamp метка времени
     * \return вернет true если выходной день
     */
    inline bool is_day_off(const timestamp_t timestamp = get_timestamp()) noexcept {
        uint32_t wday = get_weekday(timestamp);
        if(wday == xtime::SUN || wday == xtime::SAT) return true;
        return false;
    }

    /** \brief Проверить день с начала отсчета Unix-времени на выходной день
     * \param day день с начала отсчета Unix-времени
     * \return вернет true если выходной день
     */
    inline bool is_day_off_for_day(const uint32_t day) noexcept {
        uint32_t wday = (day + THU) % DAYS_IN_WEEK;
        if(wday == xtime::SUN || wday == xtime::SAT) return true;
        return false;
    }

    /** \brief Проверка високосного года
     * \param year год
     * \return вернет true, если год високосный
     */
    inline bool is_leap_year(const uint32_t year) noexcept {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) return true;
        return false;
    }

    /** \brief Получить минуту дня
     *
     * Данная функция вернет от 0 до 1439 (минуту дня)
     * \param timestamp метка времени
     * \return минута дня
     */
    inline uint32_t get_minute_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)((timestamp / SECONDS_IN_MINUTE) % MINUTES_IN_DAY);
    }

    /** \brief Получить минуту часа
     *
     * Данная функция вернет от 0 до 59
     * \param timestamp метка времени
     * \return Минута часа
     */
    inline uint32_t get_minute_hour(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)((timestamp / SECONDS_IN_MINUTE) % MINUTES_IN_HOUR);
    }

    /** \brief Получить час дня
     * Данная функция вернет от 0 до 23 (час дня)
     * \param timestamp метка времени
     * \return час дня
     */
    inline uint32_t get_hour_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)((timestamp / SECONDS_IN_HOUR) % HOURS_IN_DAY);
    }

    /** \brief Получить секунду минуты
     * Данная функция вернет от 0 до 59 (секунда минуты)
     * \param timestamp метка времени
     * \return секунда минуты
     */
    inline uint32_t get_second_minute(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)(timestamp % SECONDS_IN_MINUTE);
    }

    /** \brief Получить секунду часа
     * Данная функция вернет от 0 до 3599 (секунда часа)
     * \param timestamp метка времени
     * \return секунда часа
     */
    inline uint32_t get_second_hour(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)(timestamp % SECONDS_IN_HOUR);
    }

    /** \brief Получить секунду дня
     * Данная функция вернет от 0 до 86399 (секунда дня)
     * \param timestamp метка времени
     * \return секунда дня
     */
    inline uint32_t get_second_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)(timestamp % SECONDS_IN_DAY);
    }

    /** \brief Получить день
     * Данная функция вернет день, начиная с начала UNIX времени
     * \param timestamp метка времени
     * \return день с начала UNIX времени
     */
    inline uint32_t get_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return (uint32_t)(timestamp / SECONDS_IN_DAY);
    }

    /** \brief Получить метку времени начала года
     * \param year год
     * \return метка времени начала года
     */
    inline timestamp_t get_timestamp_beg_year(const uint32_t year) noexcept {
        uint32_t diff = (year - FIRST_YEAR_UNIX);
        timestamp_t t = (diff / 4) * SECONDS_IN_4_YEAR;
        uint32_t temp = diff % 4;
        if(temp == 0) return t;
        else if(temp == 1) return t + SECONDS_IN_YEAR;
        else if(temp == 2) return t + (2*SECONDS_IN_YEAR);
        return t + (2*SECONDS_IN_YEAR + SECONDS_IN_LEAP_YEAR);
    }

     /** \brief Получить метку времени дня UINX-времени
     * \param unix_day день с начала UNIX-времени
     * \return метка времени начала дня с момента начала UNIX-времени
     */
    inline timestamp_t get_timestamp_day(const uint32_t unix_day) noexcept {
        return (timestamp_t)unix_day * SECONDS_IN_DAY;
    }

    /** \brief Получить год
     * Данная функция вернет год указанной метки времени
     * \param timestamp метка времени
     * \return год UNIX времени
     */
    inline uint32_t get_year(const timestamp_t timestamp = get_timestamp()) noexcept {
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
    inline uint32_t get_day_year(const timestamp_t timestamp = get_timestamp()) noexcept {
        uint32_t year = get_year(timestamp);
        return get_day(timestamp) - get_day(get_timestamp_beg_year(year)) + 1;
    }

    /** \brief Получить месяц года
     * \param timestamp метка времени
     * \return месяц года
     */
    uint32_t get_month(const timestamp_t timestamp);

    /** \brief Получить метку времени в начале текущего месяца
     * \param timestamp Метка времени
     * \return Метка времени в начале текущего месяца
     */
    inline timestamp_t get_first_timestamp_month(const timestamp_t timestamp = get_timestamp()) noexcept {
        uint32_t day = get_day_month(timestamp);
        timestamp_t timestamp_new = get_first_timestamp_day(timestamp);
        timestamp_new -= (day - 1) * SECONDS_IN_DAY;
        return timestamp_new;
    }

    /** \brief Получить последнюю метку времени текущего месяца
     * \param timestamp Метка времени
     * \return Последняя метка времени текущего месяца
     */
    inline timestamp_t get_last_timestamp_month(const timestamp_t timestamp = get_timestamp()) noexcept {
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
    inline timestamp_t get_last_timestamp_sunday_month(const timestamp_t timestamp = get_timestamp()) noexcept {
        timestamp_t last_timestamp = get_last_timestamp_month(timestamp);
        uint32_t weekday = get_weekday(timestamp);
        last_timestamp -= weekday * SECONDS_IN_DAY;
        return last_timestamp;
    }

    /** \brief Получить количество дней в текущем году
     * \param timestamp метка времени
     * \return дней в текущем году
     */
    inline uint32_t get_day_in_year(const timestamp_t timestamp = get_timestamp()) noexcept {
        if(is_leap_year(get_year(timestamp))) return DAYS_IN_LEAP_YEAR;
        return DAYS_IN_YEAR;
    }

    /** \brief Получить метку времени начала дня от начала unix-времени
     * \param day день с начала unix-времени
     * \return метка времени
     */
    inline timestamp_t get_first_timestamp_for_day(const uint32_t day) noexcept {
        return day * SECONDS_IN_DAY;
    }

    /** \brief Получить метку времени начала предыдущего дня
     * \param timestamp Метка времени текущего дня
     * \return метка времени начала предыдущего дня
     */
    inline timestamp_t get_first_timestamp_previous_day(const timestamp_t timestamp = get_timestamp()) noexcept {
        return get_first_timestamp_day(timestamp) - SECONDS_IN_DAY;
    }


    /** \brief Получить метку времени начала дня начала недели
     *
     * Данная функция найдет метку времемени начала дня начала недели.
     * Это соответствует началу воскресенья.
     * \param timestamp Метка времени
     * \return вернет метку времени начала недели.
     */
    inline timestamp_t get_week_start_first_timestamp(const timestamp_t timestamp = get_timestamp()) noexcept {
        return get_first_timestamp_day(timestamp) -
            (timestamp_t)get_weekday(timestamp) * SECONDS_IN_DAY;
    }

    /** \brief Получить метку времени начала дня конца недели
     *
     * Данная функция найдет метку времемени начала дня конца недели.
     * Это соответствует началу дня субботы.
     * \param timestamp Метка времени
     * \return вернет метку времени начала недели.
     */
    inline timestamp_t get_week_end_first_timestamp(const timestamp_t timestamp = get_timestamp()) noexcept {
        return get_first_timestamp_day(timestamp) +
            (timestamp_t)(SAT - get_weekday(timestamp)) * SECONDS_IN_DAY;
    }

    /** \brief Получить метку времени начала дня через указанное количество дней
     *
     * Данная функция полезна, если нужно найти метку времени начала дня через указанное количество дней.
     * \param timestamp Текущая метка времени
     * \param days Количество дней спустя
     * \return вернет метку времени начала дня через указанное количество дней
     */
    inline timestamp_t get_first_timestamp_next_day(
            const timestamp_t timestamp,
            const uint32_t days) noexcept {
        return get_first_timestamp_day(timestamp) +
            ((timestamp_t)days * SECONDS_IN_DAY);
    }

    /** \brief Задержка на указанное количество миллисекунд
     * \param milliseconds количество миллисекунд
     */
    void delay_ms(const uint64_t milliseconds);

    /** \brief Задержка на указанное количество секунд
     * \param seconds количество секунд
     */
    void delay(const uint64_t seconds);

    /** \brief Цикл для минут
     *
     * Данная функция пройдет все метки времени от минимальной до максимальной.
     * В цикле используется условие НЕ БОЛЬШЕ МАКСИМАЛЬНОЙ МЕТКИ ВРЕМЕННИ.
     * \param min_timestamp Минимальная метка времени
     * \param max_timestamp Максимальная метка времени
     */
    void for_minutes(
            const timestamp_t min_timestamp,
            const timestamp_t max_timestamp,
            std::function<void(const timestamp_t timestamp)> f);

    /** \brief Цикл для часов
     *
     * Данная функция пройдет все метки времени от минимальной до максимальной.
     * В цикле используется условие НЕ БОЛЬШЕ МАКСИМАЛЬНОЙ МЕТКИ ВРЕМЕННИ.
     * \param min_timestamp Минимальная метка времени
     * \param max_timestamp Максимальная метка времени
     */
    void for_hours(
            const timestamp_t min_timestamp,
            const timestamp_t max_timestamp,
            std::function<void(const timestamp_t timestamp)> f);

    /** \brief Цикл для дней
     *
     * Данная функция пройдет все метки времени от минимальной до максимальной.
     * В цикле используется условие НЕ БОЛЬШЕ МАКСИМАЛЬНОЙ МЕТКИ ВРЕМЕННИ.
     * \param min_timestamp Минимальная метка времени
     * \param max_timestamp Максимальная метка времени
     */
    void for_days(
            const timestamp_t min_timestamp,
            const timestamp_t max_timestamp,
            std::function<void(const timestamp_t timestamp)> f);

    /** \brief Проверить пересечение периодов
     * \param a Первый период
     * \param b Второй период
     * \return Вернет true, если есть пересечение периодов
     */
    template<class PERIOD_TYPE>
    constexpr inline bool intersection_periods(
            const PERIOD_TYPE &a,
            const PERIOD_TYPE &b) noexcept {
        return ((a.start <= b.start && b.start <= a.stop) ||
            (a.start <= b.stop && b.stop <= a.stop));
    }

    /** \brief Проверить вложенность периодов
     * \param test_period   Тестируемый период
     * \param main_period   Основной период, который может включать в себя тестируемый период
     * \return Вернет true, если тестируемый период умещается в основной перпиод
     */
    template<class PERIOD_TYPE>
    constexpr inline bool internal_period(
            const PERIOD_TYPE &test_period,
            const PERIOD_TYPE &main_period) noexcept {
        return (test_period.start >= main_period.start &&
            test_period.stop <= main_period.stop);
    }

    /** \brief Отсортировать контейнер с периодами
     *
     * Контейнер должен содержать периоды типа period_t или fperiod_t
     * \param periods Неотсортированный контейнер с периодами
     */
    template<class PERIOD_CONTAINER_TYPE>
    constexpr inline void sort_periods(PERIOD_CONTAINER_TYPE &periods) noexcept {
        typedef typename PERIOD_CONTAINER_TYPE::value_type period_type;
        if (periods.size() <= 1) return;
        if (!std::is_sorted(
            periods.begin(),
            periods.end(),
            [](const period_type & a, const period_type & b) {
                return a.start < b.start;
            })) {
            std::sort(periods.begin(), periods.end(),
            [](const period_type & a, const period_type & b) {
                return a.start < b.start;
            });
        }
    }

    /** \brief Найти период в контейнере
     *
     * Данная функция вернет указатель на элемент в заранее отсортированном конейтенере с периодами
     * \param periods   Отсортированный контейнер с периодами
     * \param timestamp Метка времени
     * \return Указатель на элемент отсортированного контейнера с периодами или на конец контейнера, если период не найден
     */
    template<class PERIOD_CONTAINER_TYPE, class TIMESTAMP_TYPE>
    constexpr inline auto find_period(const PERIOD_CONTAINER_TYPE &periods, const TIMESTAMP_TYPE timestamp) noexcept {
        typedef typename PERIOD_CONTAINER_TYPE::value_type period_type;
        if (periods.empty()) return periods.end();
        auto it = std::lower_bound(
                periods.begin(),
                periods.end(),
                timestamp,
                [](const period_type & l, const TIMESTAMP_TYPE timestamp) {
                    return  l.start < timestamp;
                });
        if ((it == periods.begin() || it != periods.end()) && it->start == timestamp) return it;
        if (it != periods.begin()) {
            auto prev_it = std::prev(it, 1);
            if (prev_it->start <= timestamp && prev_it->stop >= timestamp) return prev_it;
        }
        return periods.end();
    }

    /** \brief Объединить пересекающиеся периоды
     * \param periods   Отсортированный контейнер с периодами
     * \return Вернет true, если есть объединенные периоды
     */
    template<class PERIOD_CONTAINER_TYPE>
    inline bool merge_periods(PERIOD_CONTAINER_TYPE &periods) noexcept {
        typedef typename PERIOD_CONTAINER_TYPE::value_type period_type;
        size_t i = 0;
        bool changed = false;
        while(i < periods.size()) {
            size_t j = i + 1;
            while(j < periods.size()) {
                if (intersection_periods(periods[i], periods[j])) {
                    /* периоды пересекаются, склеиваем их */
                    period_type new_period(
                        std::min(periods[i].start, periods[j].start),
                        std::max(periods[i].stop, periods[j].stop));
                    periods[i] = new_period;
                    periods.erase(periods.begin() + j);
                    changed = true;
                } else {
                    ++j;
                }
            } // while(j < all_periods.size())
            ++i;
        } // while(i < all_periods.size())
        return changed;
    }

    /** \brief Объединить пересекающиеся периоды
     * \param periods           Отсортированный контейнер с периодами
     * \param insert_periods    Массив периодов, которые были добавлены
     * \param remove_periods    Массив периодов, которые были удалены
     * \return Вернет true, если есть объединенные периоды
     */
    template<class PERIOD_CONTAINER_TYPE_1,
        class PERIOD_CONTAINER_TYPE_2,
        class PERIOD_CONTAINER_TYPE_3>
    inline bool merge_periods(
            PERIOD_CONTAINER_TYPE_1 &periods,
            PERIOD_CONTAINER_TYPE_2 &insert_periods,
            PERIOD_CONTAINER_TYPE_3 &remove_periods) noexcept {
        typedef typename PERIOD_CONTAINER_TYPE_1::value_type period_type;
        size_t i = 0;
        bool changed = false;
        while(i < periods.size()) {
            size_t j = i + 1;
            while(j < periods.size()) {
                if (intersection_periods(periods[i], periods[j])) {
                    /* периоды пересекаются, склеиваем их */
                    period_type new_period(
                        std::min(periods[i].start, periods[j].start),
                        std::max(periods[i].stop, periods[j].stop));
                    remove_periods.insert(remove_periods.end(), periods[i]);
                    remove_periods.insert(remove_periods.end(), periods[j]);
                    insert_periods.insert(insert_periods.end(), new_period);
                    periods[i] = new_period;
                    periods.erase(periods.begin() + j);
                    changed = true;
                } else {
                    ++j;
                }
            } // while(j < all_periods.size())
            ++i;
        } // while(i < all_periods.size())
        return changed;
    }
}

#endif // XTIME_HPP_INCLUDED
