#include <iostream>
#include <xtime.hpp>

using namespace std;

int main()
{
    xtime::DateTime iTime(9, 10, 2018);
    unsigned long long time = iTime.getUnixTime();

    cout << "wday " << xtime::getWday(time) << endl;
    return 0;
}
