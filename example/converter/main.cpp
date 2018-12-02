#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    xtime::DateTime iStartTime(27,10,2018, 23, 0, 0);
    xtime::timestamp_type cetTime = iStartTime.get_timestamp();
    for(xtime::timestamp_type t0 = cetTime; t0 < cetTime + xtime::SEC_MINUTE*240; t0 += xtime::SEC_MINUTE) {
       xtime::DateTime iGmtTime(xtime::convert_cet_to_gmt(t0));
       xtime::DateTime iCetTime(t0);
       std::cout << "cet: " << iCetTime.get_str_date_time() << " gmt: " << iGmtTime.get_str_date_time() << std::endl;
    }
    //
    std::cout << "example: " << std::endl;

    xtime::DateTime iExampleTime1(3,8,2008, 14, 30, 0);
    //xtime::cTime iExampleTime2(8,8,2008, 14, 30, 0);

    std::cout << "gmt: " << iExampleTime1.get_str_date_time() << std::endl;
    xtime::DateTime iExampleTime2(xtime::convert_gmt_to_cet(iExampleTime1.get_timestamp()));
    std::cout << "cet: " << iExampleTime2.get_str_date_time() << std::endl;
    xtime::DateTime iExampleTime3(xtime::convert_cet_to_gmt(iExampleTime2.get_timestamp()));
    std::cout << "gmt: " << iExampleTime3.get_str_date_time() << std::endl;

    unsigned long long lastGmt = xtime::get_unix_timestamp();
    while(1) {
        unsigned long long unix = xtime::get_unix_timestamp();
        if(unix != lastGmt) {
            std::cout << "pc gmt: " << unix << "\r";
            lastGmt = unix;
        }
    }
    return 0;
}
