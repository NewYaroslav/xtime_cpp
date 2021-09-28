# xtime

**Проект перенесен в новый репозиторий с новым именем [ztime](https://github.com/NewYaroslav/ztime-cpp)**

![logo](doc/logo.png)
> boost::posix_time, std, boost ::chrono... надо учиться эффективно использовать чужие велосипеды, иначе легко завязнуть в своих...

Простая **C++11** библиотека  для работы с меткой времени (*timestamp*) и "понятной датой" (*human readable date*)

## Описание

Зачем нужна эта библиотека? Данная библиотека поможет в случаях, когда есть необходимость часто использовать метку времени и искать данные, имеющие взаимосвязь с разными промежутками времени.
Например, когда нужно перебирать данные, у которых  индекс элемента - метка времени, данная библиотека может очень пригодится, она позволит легко получить из метки времени час или минуту дня, найти метку времени начала текущего месяца или найти последний день месяца, получить день недели или текущий год, **фазу Луны** и т.д.
Данная библиотека позволяет удобно и быстро работать с меткой времени (*timestamp*), юлианским днем (*JD или JDN*), датой автоматизации (*OADate*) и "понятной датой" (*human readable date*). 

Например: 

* Можно преобразовать дату в timestamp или сделать обратную операцию 
* Можно получить реальное GMT время компьютера
* Можно преобразовать GMT в CET и обратно, с учетом истории изменений перехода на летнее и зимнее время
* Получить секунду часа, секунду дня, день недели, количество дней в месяце, день месяца, день года, день с начала UNIX времени, год и т.д.
* Можно преобразовать UINX время в OLE Automation Date и обратно
* Можно получить синхронизированное время с интернетом
* Можно узнать фазу Луны, найти следующее новолуние
* И многое другое

Смотрите файлы *xtime.hpp*, *xtime_cpu_time.hpp*, *xtime_sync.hpp*. Они содежрут подробные комментарии функций, классов и их методов.
Для хранения и преобразования меток времени используется тип данных *uint64*, поэтому у данной библиотеки нет [проблемы 2038 года](https://en.wikipedia.org/wiki/Year_2038_problem)

Синхронизированное время реализовано в файле *xtime_sync.hpp* и для его работы вам понадобится *curl* с поддержкой *https*. Примеры есть в папке *code_blocks*. 
Для сокращения времени запуска примера советую использовать готовые сборки *curl*, например: [https://github.com/NewYaroslav/curl-7.60.0-win64-mingw](https://github.com/NewYaroslav/curl-7.60.0-win64-mingw). Время синхронизируется при помощи [https://time.is/](https://time.is/), Time.is отображает точное, официальное атомное время в любом часовом поясе.

Примеры использования различных функций и классов можно найти в папке *testing*.

## Как установить?

Просто добавьте файл *xtime.cpp* в свой проект. Подключите заголовочный файл *xtime.hpp*, а также, если нужно, *xtime_cpu_time.hpp*, *xtime_sync.hpp*.
Дальше просто используйте! 

## Типы данных

* **timestamp_t** 	- Тип длиной 64 бита для хранения метки времени
* **ftimestamp_t** 	- Тип с плавающей точкой длиной 64 бита для хранения метки времени с дробной частью секунд
* **oadate_t** 		- Тип даты автоматизации (OADate) с плавающей точкой
* **period_t** 		- Тип периода, две переменные 64 бита для хранения меток времени
* **fperiod_t**		- Тип периода, две переменные с плавающей точкой длиной 64 бита для хранения меток времени

## Перечисления и константы

```cpp
    const timestamp_t TIMESTAMP_MAX = 0xFFFFFFFFFFFFFFFF;   ///< Максимально возможное значение для типа timestamp_t
    const oadate_t OADATE_MAX = 9223372036854775807;        ///< Максимально возможное значение даты автоматизации (OADate)
    const double AVERAGE_DAYS_IN_YEAR = 365.25;             ///< Среднее количество дней за год
	
    /// Различные периоды
    enum {
        MILLISECONDS_IN_SECOND = 1000,		///< Количество миллисекунд в одной секунде
        MILLISECONDS_IN_MINUTE = 60000,		///< Количество миллисекунд в одной минуте
        MILLISECONDS_IN_HALF_HOUR = 1800000,///< Количество миллисекунд в получасе
        MILLISECONDS_IN_HOUR = 3600000,     ///< Количество миллисекунд в часе
        MILLISECONDS_IN_DAY = 86400000,     ///< Количество миллисекунд в одном дне
		SECONDS_IN_MINUTE = 60,	            ///< Количество секунд в одной минуте
        SECONDS_IN_HALF_HOUR = 1800,        ///< Количество секунд в получасе
        SECONDS_IN_HOUR = 3600,	            ///< Количество секунд в часе
        SECONDS_IN_DAY = 86400,	            ///< Количество секунд в дне
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
	
	/// Фазы Луны
    enum {
        WAXING_CRESCENT_MOON,
        FIRST_QUARTER_MOON,
        WAXING_GIBBOUS_MOON,
        FULL_MOON,
        WANING_GIBBOUS_MOON,
        LAST_QUARTER_MOON,
        WANING_CRESCENT_MOON,
        NEW_MOON,
    };

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
```

## Функции и методы

### Методы класса MoonPhase

* void init(const xtime::ftimestamp_t timestamp)			- Инициализация переменных класса, касаемых возраста, фазы луны и т.д.
* void phasehunt(const xtime::timestamp_t timestamp) 		- Расчитать даты различных фаз Луны
* bool is_new_moon(const xtime::ftimestamp_t timestamp) 	- Проверить новолуние
* bool is_full_moon(const xtime::ftimestamp_t timestamp) 	- Проверить полнолуние
* double calc_phase_v3(const xtime::ftimestamp_t timestamp) - Посчитать Фазу Луны, основываясь на датах новолуния
* uint32_t get_moon_minute(const xtime::ftimestamp_t timestamp)	- Получить Лунную минуту (от 0 до 42523)

### Методы класса DateTime

* set_beg_day() - установить начало дня
* set_end_day() - установить конец дня
* set_beg_month() - установить начало месяца (00:00)
* set_end_month() - установить конец месяца
* timestamp_t get_timestamp() - получить метку времени
* ftimestamp_t get_ftimestamp() - получить метку времени с плавающей запятой
* set_timestamp(const timestamp_t &timestamp) - установить метку времени
* set_ftimestamp(const ftimestamp_t &ftimestamp) - установить метку времени с плавающей запятой
* print() - напечатать время на экране
* std::string get_str_date_time() - получить время и дату в виде строки
* std::string get_str_date_time_ms() - получить время, миллисекунды и дату в виде строки
* std::string get_str_date() - получить дату в виде строки
* std::string get_str_time() - получить время в виде строки
* uint32_t get_weekday() - получить день недели
* is_leap_year() - получить флаг високосного года (если год високосный, вернет true)
* uint32_t get_num_days_current_month() - получить кол-во дней в текущшем месяце
* set_oadate() - Установить дату автоматизации OLE
* oadate_t get_oadate() - Получить дату автоматизации OLE

### Получение времени компьютера

* uint32_t get_millisecond() 		- Получить миллисекунды
* timestamp_t get_timestamp() 		- Получить метку времени
* timestamp_t get_timestamp_ms()	- Получить метку времени в миллисекундах
* ftimestamp_t get_ftimestamp() 	- Получить метку времени с плавающей запятой
* oadate_t get_oadate() 			- Получить дату автоматизации OLE

### Преобразование времени в строку или вывод на экран

* std::string to_string(const std::string &mode, const xtime::ftimestamp_t timestamp) - Преобразовать время и дату в строку с пользовательскими настройками.

В качестве параметров функция принимает следующие аргументы:

**%YYYY** - год

**%YY** - последние два числа года

**%Y** - год, без ограничений в 4 символа

**%MM** - месяц (число)

**%M** - месяц (скоращенное имя)

**%DD** - день месяца

**%hh** - час дня

**%mm** - минуты часа

**%ss** - секунды

**%sss** - миллисекунды

**%W** - день недели (число)

**%w** - день недели (скоращенное имя)


Пример:

```cpp
cout << "to_string " << xtime::to_string("%YYYY-%MM-%DD",xtime::get_timestamp(31,12,2016,22,55,56)) << endl;
cout << "to_string " << xtime::to_string("%DD-%MM-%YYYY %hh:%mm:%ss",xtime::get_timestamp(31,12,2016,22,55,56)) << endl;
cout << "to_string " << xtime::to_string("%hh:%mm",xtime::get_timestamp(31,12,2016,22,55,56)) << endl;
cout << "to_string " << xtime::to_string("%hh:%mm.%sss",xtime::get_ftimestamp(31,12,2016,22,55,56,567)) << endl;
```

* std::string get_str_iso_8601(const xtime::ftimestamp_t timestamp, const int64_t offset) - Получить строку в формате ISO 8601

* std::string get_str_date_time(const timestamp_t timestamp) - Получить время и дату в виде строки из метки времени 

(Формат строки: DD.MM.YYYY HH:MM:SS)

* std::string get_str_date_time_ms(const ftimestamp_t timestamp) - Получить время и дату в виде строки из метки времени
 
(Формат строки: DD.MM.YYYY HH:MM:SS.fff)

* std::string get_str_date(const timestamp_t timestamp) - Получить время и дату в виде строки из метки времени 

(Формат строки: DD.MM.YYYY)

* std::string get_str_time(const timestamp_t timestamp) - Получить время и дату в виде строки из метки времени
 
(Формат строки: HH:MM:SS)

* std::string get_str_time_ms(const ftimestamp timestamp) - Получить время и дату в виде строки из метки времени
 
(Формат строки: HH:MM:SS.fff)

* std::string get_str_date_time() - Получить время и дату компьютера в виде строки 

(Формат строки: DD.MM.YYYY HH:MM:SS)

* std::string get_str_date_time_ms() - Получить время и дату компьютера в виде строки 

(Формат строки: DD.MM.YYYY HH:MM:SS.fff)

* print_date_time(const timestamp_t timestamp) - Напечатать дату и время метки времени 

(Формат строки: DD.MM.YYYY HH:MM:SS)

### Преобразование строки в метку времени или секунду дня

* xtime::timestamp_t to_timestamp(std::string str_datetime)							- (Рекомендовано) Преобразует строку даты и времени в timestamp
* int to_second_day(std::string str_time)											- (Рекомендовано) Преобразует строку времени в секунду дня
* xtime::ftimestamp_t convert_iso_to_ftimestamp(const std::string &str_datetime) 	- Конвертировать строку в формате ISO в метку времени
* bool convert_iso(const std::string &str_datetime, DateTime& t) 					- Конвертировать строку в формате ISO в данные класса DateTime
* bool convert_str_to_timestamp(std::string str, timestamp_t& t) 					- Преобразует строку в timestamp

Функции *convert_str_to_timestamp, to_timestamp, to_second_day* подерживают следующий список разделителей чисел (/\_:-.,<пробел>) 

Функции *convert_str_to_timestamp, to_timestamp* способны распрасить время и дату и поддерживает следующие форматы времени:

	- HH:MM:SS DD MM YY Пример: 20:25:00, 29 Aug 19
	- HH:MM:SS DD MM YY Пример: 20:25:00, 29 Aug 2019
	- HH:MM:SS DD.MM.YYYY Пример: 00:59:59 30.08.2019
	- HH:MM:SS DD-MM-YYYY Пример: 00:59:59 30-08-2019
	- YYYY-MM-DD hh:mm:ss Пример: 2013-02-25 18:25:10
	- YYYY.MM.DD hh:mm:ss Пример: 2013.02.25 18:25:10
	- YYYY.MM.DD Пример: 2013.02.25
	- DD.MM.YYYY Пример: 21.09.2018
	
Функция *to_timestamp* также поддерживает:

	- YYYY-MM-DD hh:mm	Пример: 2013-02-25 18:25
	- YYYY.MM.DD hh:mm	Пример: 2013.02.25 18:25
	- DD-MM-YYYY hh:mm	Пример: 25-02-2013 18:25	
	- DD.MM.YYYY hh:mm	Пример: 25.02.2013 18:25
	
Функция *to_second_day* оддерживает:

	- HH:MM:SS	Пример: 20:25:00
	- HH:MM		Пример: 20:25
	- HH		Пример: 20
	
### Различные преобразования

* oadate_t convert_timestamp_to_oadate(const timestamp_t &timestamp) 	- Получить дату автоматизации OLE из метки времени
* oadate_t convert_ftimestamp_to_oadate(const ftimestamp_t &timestamp) 	- Получить дату автоматизации OLE из метки времени c плавающей точкой
* timestamp_t convert_oadate_to_timestamp(const oadate_t &oadate) 		- Преобразовать дату автоматизации OLE в метку времени
* ftimestamp_t convert_oadate_to_ftimestamp(const oadate_t &oadate) 	- Преобразовать дату автоматизации OLE в метку времени  плавающей точкой
* double convert_gregorian_to_julian_date(const ftimestamp_t &timestamp)			- Преобразовать метку времени в Юлианский день
* double convert_gregorian_to_modified_julian_day(const ftimestamp_t &timestamp)	- Преобразовать метку времени в модифицированный юлианский день

### Перевод времени из одной вреемнной зоны в другую

* timestamp_t convert_gmt_to_cet(const timestamp_t &gmt) - Переводит время GMT во время CET
* timestamp_t convert_gmt_to_eet(const timestamp_t &gmt) - Переводит время GMT во время EET
* timestamp_t convert_gmt_to_msk(const timestamp_t &gmt) - *Пока не поддерживается*
* timestamp_t convert_cet_to_gmt(const timestamp_t &cet) - Переводит время CET во время GMT
* timestamp_t convert_eet_to_gmt(const timestamp_t &eet) - Переводит время EET во время GMT
* timestamp_t convert_msk_to_gmt(const timestamp_t &msk) - *Пока не поддерживается*

### Проверки различных условий

* bool is_beg_half_hour(const timestamp_t timestamp) 	- Проверить начало получаса
* bool is_beg_hour(const timestamp_t timestamp) 		- Проверить начало часа
* bool is_beg_day(const timestamp_t timestamp) 			- Проверить начало дня
* bool is_beg_week(const timestamp_t timestamp) 		- Проверить начало недели
* bool is_beg_month(timestamp_t timestamp)				- Проверить начало месяца (Данная функция проверят только день! Она не проверяет секунды, минуты, часы)
* bool is_end_month(const timestamp_t timestamp) 													- Проверить конец месяца (Данная функция проверят только день! Она не проверяет секунды, минуты, часы)
* bool is_correct_date(const uint32_t day, const uint32_t month, const uint32_t year) 				- Проверить корректность даты
* bool is_correct_time(const uint32_t hour, const uint32_t minute = 0, const uint32_t second = 0) 	- Проверить корректность времени
* bool is_correct_date_time(const uint32_t day, const uint32_t month, const uint32_t year, const uint32_t hour = 0,  const uint32_t minute = 0, const uint32_t second = 0) 	- Проверить корректность даты и времени
* bool is_day_off(const timestamp_t timestamp) 											- Проверить выходной день (суббота и воскресение)
* bool is_day_off_for_day(const uint32_t day) 											- Проверить день с начала отсчета Unix-времени на выходной день (суббота и воскресение)
* bool is_leap_year(const uint32_t year) 												- Проверка високосного года
* bool is_day_of_month(const uint32_t day, const uint32_t month, const uint32_t year) 	- Проверка корректность дня месяца

### Различные преобразования и вычисления

* timestamp_t get_first_timestamp_year(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени в начале года
* timestamp_t get_last_timestamp_year(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени в конце года
* timestamp_t get_first_timestamp_month(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени в начале текущего месяца
* timestamp_t get_last_timestamp_month(const timestamp_t timestamp = get_timestamp()) 		- Получить последнюю метку времени текущего месяца
* timestamp_t get_first_timestamp_day(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени в начале дня
* timestamp_t get_last_timestamp_day(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени в конце дня
* timestamp_t get_first_timestamp_hour(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени в начале часа
* timestamp_t get_first_timestamp_minute(const timestamp_t timestamp = get_timestamp()) 	- Получить метку времени в начале минуты
* timestamp_t get_first_timestamp_previous_day(const timestamp_t timestamp = get_timestamp()) - Получить метку времени начала предыдущего дня
* timestamp_t get_timestamp_beg_year(const uint32_t year) - Получить метку времени начала года
* timestamp_t get_last_timestamp_sunday_month(const timestamp_t timestamp = get_timestamp()) 	- Получить последнюю метку времени последнего воскресения текущего месяца
* timestamp_t get_week_start_first_timestamp(const timestamp_t timestamp = get_timestamp()) 	- Получить метку времени начала дня начала недели
* timestamp_t get_week_end_first_timestamp(const timestamp_t timestamp = get_timestamp()) 		- Получить метку времени начала дня конца недели
* timestamp_t get_first_timestamp_next_day(const timestamp_t timestamp, const uint32_t days) 	- Получить метку времени начала дня через указанное количество дней
* timestamp_t get_first_timestamp_for_day(const uint32_t day) 	- Получить метку времени начала дня от начала unix-времени
* timestamp_t get_timestamp_day(const uint32_t unix_day) 		- Получить метку времени дня UINX-времени

* uint32_t get_num_days_month(const uint32_t month, const uint32_t year) 	- Получить количество дней в месяце
* uint32_t get_num_days_month(const timestamp_t timestamp) 					- Получить количество дней в месяце
* uint32_t get_weekday(const uint32_t day, const uint32_t month, const uint32_t year) - Получить день недели
* uint32_t get_weekday(const timestamp_t timestamp = get_timestamp()) 		- Получить день недели
* uint64_t get_minute(const timestamp_t timestamp = get_timestamp()) 		- Получить минуту с начала UNIX
* uint32_t get_minute_day(const timestamp_t timestamp = get_timestamp()) 	- Получить минуту дня
* uint32_t get_minute_hour(const timestamp_t timestamp = get_timestamp()) 	- Получить минуту часа
* uint32_t get_hour_day(const timestamp_t timestamp = get_timestamp()) 		- Получить час дня
* uint32_t get_second_day(const timestamp_t timestamp = get_timestamp()) 	- Получить секунду дня
* uint32_t get_second_minute(const timestamp_t timestamp = get_timestamp()) - Получить секунду минуты
* uint32_t get_day(const timestamp_t timestamp = get_timestamp()) 	- Получить день
* uint32_t get_year(const timestamp_t timestamp = get_timestamp()) 	- Получить год
* uint32_t get_day_year(const timestamp_t timestamp = get_timestamp()) 		- Получить день года
* uint32_t get_month(const timestamp_t timestamp = get_timestamp()) 		- Получить месяц года
* uint32_t get_day_in_year(const timestamp_t timestamp = get_timestamp()) 	- Получить количество дней в текущем году
* uint32_t get_day_month(const timestamp_t timestamp = get_timestamp()) 	- Получить день месяца
* uint32_t get_first_timestamp_period(const uint32_t period, const timestamp_t timestamp  = get_timestamp()) 	- Получить метку времени в начале периода
* uint32_t get_last_timestamp_period(const uint32_t period, const timestamp_t timestamp  = get_timestamp()) 	- Получить метку времени в конце периода

### Задержка

* void delay_ms(const uint64_t milliseconds) - Задержка на указанное количество миллисекунд
* void delay(const uint64_t seconds) - Задержка на указанное количество секунд

### Замер времени выполнения

Класс **Timer** предоставляет следующие методы:

```C++

/** \brief Сбросить значение таймера
 *
 * Данный метод нужно применять только вместе с методом elapsed()
 * При использовании метода
 * get_average_measurements() сбрасывать таймер не нужно!
 */
inline void reset();

/** \brief Получить замер времени
 * \return Время в секундах с момента инициализации класса или после reset()
 */
inline double get_elapsed();

/** \brief Сбросить все замеры
 *
 * Данный метод обнуляет сумму замеров и их количество
 */
inline void reset_measurement();

/** \brief Начать замер
 *
 * Данный метод использовать вместе с методами stop_measurement()
 * и get_average_measurements()
 */
inline void start_measurement();

/** \brief Остановить замер
 *
 * Данный метод использовать вместе с методами start_measurement()
 * и get_average_measurements()
 */
inline void stop_measurement();

/** \brief Получить результаты замеров
 *
 * Данный метод использовать вместе с методами start_measurement()
 * и stop_measurement(). Метод возвращает средний результат замеров
 * \return Среднее время замеров в секундах
 */
inline double get_average_measurements();
```

## Быстрый обзор

+ Получить синхронизированное *UTC* время

```C++
#include <iostream>
#include <xtime_sync.hpp>

uint32_t main() {
    std::cout << "Hello world!" << std::endl;
    xtime::TimeSync iTimeSync;
    while(!iTimeSync.is_time_sync()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    };

    double last_utc = iTimeSync.get_ftimestamp();
    while(true) {
        double real_utc = iTimeSync.get_ftimestamp();
        double pc_utc = xtime::get_ftimestamp();
        if(real_utc - last_utc > 0.1) {
            std::cout << "accuracy: " << iTimeSync.get_accuracy() << " sync utc: " << xtime::get_str_time_ms(real_utc) << " pc utc: " << xtime::get_str_time_ms(pc_utc) << "\r";
            last_utc = real_utc;
        }
    };
    return 0;
}
```

На экране увидим:

![sync](doc/sync.png)

+ Получить Unix-время из даты и стандартного времени

```C++
using namespace xtime;
// дата 24.05.2018 время 23:59:59
xtime::timestamp_t epoch = get_timestamp(24, 5, 2018, 23, 59, 59);
```
+ Класс для хранения времени

```C++
using namespace xtime;

// Инициализируем датой 24.05.2018
DateTime iTime(24,5,2018);

// Второй вариант инициализации с указанием времени
iTime = DateTime(24,5,2018, 0, 0, 0);
// iTime = DateTime(24,5,2018);

// Третий вариант инициализации (Инициализация с указанием unix-времени в формате ISO)
// iTime = DateTime("2013-12-06T15:23:01+00:00");

// Или инициализируем Unix epoch или Unix time или POSIX time или Unix timestamp
xtime::timestamp_t unix_epoch = 1527120000;

iTime.set_timestamp(unix_epoch);

// Переменные класса DateTime
iTime.day = 24; 	// день
iTime.month = 5; 	// месяц
iTime.year = 2018 	// год
iTime.hour = 0; 	// час
iTime.minute = 0; 	// минуты
iTime.second = 0; 	// секунды

// Получить Unix epoch или Unix time или POSIX time или Unix timestamp 
unix_epoch = iTime.get_timestamp();

// Вывести время и дату на экран
iTime.print();

// Получить дату и время в виде строки
std::string str = iTime.get_str_date_time(); // В строке будет 24.05.2018 00:00:00
```

+ Получить стандартное время

```C++
using namespace xtime;

xtime::timestamp_t unix_epoch = 1527120000;
DateTime iTime = convert_timestamp_to_datetime(unix_epoch);
```

+ Получить день недели

```C++
using namespace xtime;

// Получить номер дня недели
uint32_t wday = get_weekday(24,5,2018);

if(wday == SUN) std::cout << "SUN" << std::endl; // Если функция вернула 0 или Воскресенье
else if(wday == MON) std::cout << "MON" << std::endl; // Если функция вернула 1 или Понедельник
else if(wday == TUS) std::cout << "TUS" << std::endl;
else if(wday == WED) std::cout << "WED" << std::endl;
else if(wday == FRI) std::cout << "FRI" << std::endl;
else if(wday == SAT) std::cout << "SAT" << std::endl;

xtime::timestamp_t unix_epoch = 1527120000;

// Второй вариант функции для определения дня недели
wday = get_weekday(unix_epoch);

// Получить день недели через функцию класса DateTime
DateTime iTime(24,5,2018);
wday = iTime.get_weekday();
```
+ Конвертировать строку в формате ISO в данные класса DateTime

```C++
using namespace xtime;

DateTime iTime;
std::string strISOformattedUTCdatetime = "2013-12-06T15:23:01+00:00";
if(convert_iso(strISOformattedUTCdatetime, iTime) == true) {
  iTime.print();
}
```

+ Перевод времени CET во время GMT и обратно с учетом перехода на зимнее время

```C++
using namespace xtime;
// получаем время GMT для примера
DateTime startTime(20,3,2018);

xtime::timestamp_t startGMT = startTime.get_timestamp();
// переводим время GMT во время CET
DateTime realCET(convert_gmt_to_cet(startGMT));
realCET.print();
// переводим время CET во время GMT
DateTime realGMT(convert_cet_to_gmt(realCET.get_timestamp()));
realGMT.print();
```
+ Получить Unix-время компьютера

```C++
using namespace xtime;

xtime::timestamp_t t = get_timestamp();
std::string str = get_str_date_time(); // В строке время будет предсталвено как в примере (24.05.2018 00:00:00)
```

+ Получить количество дней в месяце и день года

```C++
using namespace xtime;

uint32_t month = 2;
uint32_t year = 2018;
std::cout << get_num_days_month(month, year) << std::endl;

DateTime iTime(20,3,2018);

// Получить количество дней в текущем (март) месяце
std::cout << iTime.get_num_days_current_month() << std::endl;
// Получить день года
std::cout << get_day_year(iTime.get_timestamp()) << std::endl;

```

+ Проверка високосного года

```C++
using namespace xtime;

uint32_t year = 2018;
if(is_leap_year(year)) {
	// если год високосный, то условие сработает
}

DateTime iTime(20,3,2018);

if(iTime.is_leap_year()) {
	// если год високосный, то условие сработает
}
```

+ Получение метки времени начала дня

```C++
using namespace xtime;

xtime::timestamp_t t = get_timestamp();
t = get_first_timestamp_day(t);

```

+ OLE Automation Date (Дата автоматизации OLE)

```C++
xtime::timestamp_t timestamp = xtime::get_timestamp(1,1,2019);
xtime::oadate_t oadate = xtime::convert_timestamp_to_oadate(timestamp);
cout << "oadate " << oadate << endl;
cout << "timestamp " << timestamp << endl;
cout << "date " << xtime::get_str_date_time(xtime::convert_oadate_to_timestamp(oadate)) << endl;
xtime::timestamp_t stop_timestamp = xtime::get_timestamp(31,12,9999);
cout << "31.12.9999 oadate " << xtime::convert_timestamp_to_oadate(stop_timestamp) << endl;
cout << "31.12.9999 oadate " << xtime::get_oadate(31,12,9999) << endl;
cout.precision(12);
xtime::timestamp_t last_timestamp = xtime::get_timestamp();
while(true) {
	if(xtime::get_timestamp() > last_timestamp) {
		std::cout << "oadate " << xtime::get_ole_automation_date() << std::endl;
		last_timestamp = xtime::get_timestamp();
	}
}
```

