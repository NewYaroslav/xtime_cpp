#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    xtime::DateTime iStartTime(27,10,2018, 23, 0, 0);
    unsigned long long cetTime = iStartTime.getUnixTime();
    const unsigned long long DAY_SEC = 86400;
    const unsigned long long HOUR_SEC = 3600;
    const unsigned long long MINUTE_SEC = 60;
    for(unsigned long long t0 = cetTime; t0 < cetTime + MINUTE_SEC*240; t0 += MINUTE_SEC) {
       xtime::cTime iGmtTime(xtime::convertCetToGmt(t0));
       xtime::cTime iCetTime(t0);
       std::cout << "cet: " << iCetTime.getStr() << " gmt: " << iGmtTime.getStr() << std::endl;
    }
    //
    std::cout << "example: " << std::endl;

    xtime::cTime iExampleTime1(3,8,2008, 14, 30, 0);
    //xtime::cTime iExampleTime2(8,8,2008, 14, 30, 0);

    std::cout << "gmt: " << iExampleTime1.getStr() << std::endl;
    xtime::cTime iExampleTime2(xtime::convertGmtToCet(iExampleTime1.getUnixTime()));
    std::cout << "cet: " << iExampleTime2.getStr() << std::endl;
    xtime::cTime iExampleTime3(xtime::convertCetToGmt(iExampleTime2.getUnixTime()));
    std::cout << "gmt: " << iExampleTime3.getStr() << std::endl;

    unsigned long long lastGmt = xtime::getUnixTime();
    while(1) {
        unsigned long long unix = xtime::getUnixTime();
        if(unix != lastGmt) {
            std::cout << "pc gmt: " << unix << "\r";
            lastGmt = unix;
        }
    }
    return 0;
}
