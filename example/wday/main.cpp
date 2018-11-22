#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    xtime::DateTime iTime(9, 10, 2018);
    unsigned long long time = iTime.get_timestamp();

    cout << "wday " << xtime::get_weekday(time) << endl;
    return 0;
}
