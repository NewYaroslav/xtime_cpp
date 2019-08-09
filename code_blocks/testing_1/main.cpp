#include <iostream>
#include <xtime.hpp>

using namespace std;

int main() {
    xtime::DateTime iStartTime(27,10,2018, 23, 0, 0);
    iStartTime = xtime::DateTime(iStartTime.get_timestamp());
    xtime::timestamp_t time_data = 0;
    //xtime::convert_str_to_timestamp("27_10_2018-23:0:0", time_data);
    std::cout << xtime::convert_str_to_timestamp("2018-11-30 20:30:00", time_data) << std::endl;
    std::cout << "convert_str_to_timestamp: " << xtime::get_str_date_time(time_data) << std::endl;

    xtime::timestamp_t cetTime = iStartTime.get_timestamp();
    for(xtime::timestamp_t t0 = cetTime; t0 < cetTime + xtime::SECONDS_IN_MINUTE*240; t0 += xtime::SECONDS_IN_MINUTE) {
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

    xtime::timestamp_t lastGmt = xtime::get_timestamp();
    while(1) {
        xtime::timestamp_t unix = xtime::get_timestamp();
        if(unix != lastGmt) {
            std::cout << "pc gmt: " << unix << " " << xtime::get_str_date_time() << "\r";
            lastGmt = unix;
        }
    }
    return 0;
}
