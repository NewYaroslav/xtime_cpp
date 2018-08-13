#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    FunctionsForTime::cTime iStartTime(27,10,2018, 23, 0, 0);
    unsigned long long cetTime = iStartTime.getUnixTime();
    const unsigned long long DAY_SEC = 86400;
    const unsigned long long HOUR_SEC = 3600;
    const unsigned long long MINUTE_SEC = 60;
    for(unsigned long long t0 = cetTime; t0 < cetTime + MINUTE_SEC*240; t0 += MINUTE_SEC) {
       FunctionsForTime::cTime iGmtTime(FunctionsForTime::convertCetToGmt(t0));
       FunctionsForTime::cTime iCetTime(t0);
       std::cout << "cet: " << iCetTime.getStr() << " gmt: " << iGmtTime.getStr() << std::endl;
    }
    //
    std::cout << "example: " << std::endl;

    FunctionsForTime::cTime iExampleTime1(3,8,2008, 14, 30, 0);
    //FunctionsForTime::cTime iExampleTime2(8,8,2008, 14, 30, 0);

    std::cout << "gmt: " << iExampleTime1.getStr() << std::endl;
    FunctionsForTime::cTime iExampleTime2(FunctionsForTime::convertGmtToCet(iExampleTime1.getUnixTime()));
    std::cout << "cet: " << iExampleTime2.getStr() << std::endl;
    FunctionsForTime::cTime iExampleTime3(FunctionsForTime::convertCetToGmt(iExampleTime2.getUnixTime()));
    std::cout << "gmt: " << iExampleTime3.getStr() << std::endl;
    return 0;
}
