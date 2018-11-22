## xtime
Простая C++ библиотека  для работы с временем и датой

### Резюме

Данная библиотека позволяет удобно и быстро работать с временем. Например, можно легко преобразовать дату в timestamp, или сделать обратную операцию. Можно легко получить реальное GMT время, преобразовать GMT в CET и обратно, узнать день недели, количество дней в месяце и т.д.

### Как установить?
Просто добавьте файлы xtime.hpp и xtime.cpp в свой проект

### Быстрый обзор интерфейса
+ Получить Unix-время из даты и стандартного времени
```C++
using namespace xtime;
// дата 24.05.2018 время 23:59:59
xtime::xtime_timestamp unixEpoch = get_unix_timestamp(24, 5, 2018, 23, 59, 59);
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
unsigned long long unixEpoch = 1527120000;

iTime.set_timestamp(unixEpoch);

// Переменные класса DateTime
iTime.day = 24; // день
iTime.month = 5; // месяц
iTime.year = 2018 // год
iTime.hour = 0; // час
iTime.minutes = 0; // минуты
iTime.seconds = 0; // секунды

// Получить Unix epoch или Unix time или POSIX time или Unix timestamp 
unixEpoch = iTime.get_timestamp();

// Вывести время и дату на экран
iTime.print();

// Получить дату и время в виде строки
std::string str = iTime.get_str_date_time(); // В строке будет 24.05.2018 00:00:00
```
+ Получить стандартное время
```C++
using namespace xtime;

xtime::xtime_timestamp unixEpoch = 1527120000;
DateTime iTime = convert_timestamp_to_datetime(unixEpoch);
```
+ Получить день недели
```C++
using namespace xtime;

// Получить номер дня недели
int wday = get_weekday(24,5,2018);

if(wday == SUN) std::cout << "SUN" << std::endl; // Если функция вернула 0 или Воскресенье
else if(wday == MON) std::cout << "MON" << std::endl; // Если функция вернула 1 или Понедельник
else if(wday == TUS) std::cout << "TUS" << std::endl;
else if(wday == WED) std::cout << "WED" << std::endl;
else if(wday == FRI) std::cout << "FRI" << std::endl;
else if(wday == SAT) std::cout << "SAT" << std::endl;

xtime::xtime_timestamp unixEpoch = 1527120000;

// Второй вариант функции для определения дня недели
wday = get_weekday(unixEpoch);

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
xtime::xtime_timestamp startGMT = startTime.get_unix_timestamp();
// переводим время GMT во время CET
DateTime realCET(convert_gmt_to_cet(startGMT));
realCET.print();
// переводим время CET во время GMT
DateTime realGMT(convert_cet_to_gmt(realCET.get_unix_timestamp()));
realGMT.print();
```
+ Получить Unix-время компьютера
```C++
using namespace xtime;

unsigned long long t = get_unix_timestamp();
std::string str = get_str_unix_date_time(); // В строке время будет предсталвено как в примере (24.05.2018 00:00:00)
```
+ Получить количество дней в месяце
```C++
using namespace xtime;

int month = 2;
int year = 2018;
std::cout << get_num_days_month(month, year) << std::endl;

DateTime iTime(20,3,2018);

// Получить количество дней в текущем (март) месяце
std::cout << iTime.get_num_days_current_month() << std::endl;
```
+ Проверка високосного года
```C++
using namespace xtime;

int year = 2018;
if(is_leap_year(year)) {
	// если год високосный, то условие сработает
}

DateTime iTime(20,3,2018);

if(iTime.is_leap_year()) {
	// если год високосный, то условие сработает
}
```

### Автор

Elektro Yar [electroyar2@gmail.com](electroyar2@gmail.com)


