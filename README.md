## xtime_cpp
Простая C++ библиотека  для работы с временем и датой

## Функции библиотеки:
+ Получить Unix-время из даты и стандартного времени
```
using namespace FunctionsForTime;
// дата 24.05.2018 время 23:59:59
unsigned long long unixEpoch = getUnixTime(24, 5, 2018, 23, 59, 59);
```
+ Класс для хранения времени
```
using namespace FunctionsForTime;

// Инициализируем датой 24.05.2018
cTime iTime(24,5,2018);

// Второй вариант инициализации с указанием времени
iTime = cTime(24,5,2018, 0, 0, 0);
// iTime = cTime(24,5,2018);

// Третий вариант инициализации (Инициализация с указанием unix-времени в формате ISO)
// iTime = cTime("2013-12-06T15:23:01+00:00");

// Или инициализируем Unix epoch или Unix time или POSIX time или Unix timestamp
unsigned long long unixEpoch = 1527120000;

iTime.setUnixTime(unixEpoch);

// Переменные класса cTime
iTime.day = 24; // день
iTime.month = 5; // месяц
iTime.year = 2018 // год
iTime.hour = 0; // час
iTime.minutes = 0; // минуты
iTime.seconds = 0; // секунды

// Получить Unix epoch или Unix time или POSIX time или Unix timestamp 
unixEpoch = iTime.getUnixTime();

// Вывести время и дату на экран
iTime.print();

// Получить дату и время в виде строки
std::string str = iTime.getStr(); // В строке будет 24.05.2018 00:00:00
```
+ Получить стандартное время
```
using namespace FunctionsForTime;

unsigned long long unixEpoch = 1527120000;
cTime iTime = getTime(unixEpoch);
```
+ Получить день недели
```
using namespace FunctionsForTime;

// Получить номер дня недели
int wday = getWday(24,5,2018);

if(wday == SUN) std::cout << "SUN" << std::endl; // Если функция вернула 0 или Воскресенье
else if(wday == MON) std::cout << "MON" << std::endl; // Если функция вернула 1 или Понедельник
else if(wday == TUS) std::cout << "TUS" << std::endl;
else if(wday == WED) std::cout << "WED" << std::endl;
else if(wday == FRI) std::cout << "FRI" << std::endl;
else if(wday == SAT) std::cout << "SAT" << std::endl;

unsigned long long unixEpoch = 1527120000;

// Второй вариант функции для определения дня недели
wday = getWday(1527120000);
```
+ Конвертировать строку в формате ISO в данные класса cTime
```
using namespace FunctionsForTime;

cTime iTime;
std::string strISOformattedUTCdatetime = "2013-12-06T15:23:01+00:00";
if(converISO(strISOformattedUTCdatetime, iTime) == true) {
  iTime.print();
}
```
+ Получить Unix-время компьютера
```
using namespace FunctionsForTime;

unsigned long long t = getUnixTime();
std::string str = getStrTime(); // В строке время будет предсталвено как в примере (24.05.2018 00:00:00)
```
