#include <iostream>
#include <xtime_sync.hpp>

int main() {
    std::cout << "Hello world!" << std::endl;
    xtime::TimeSync iTimeSync(0.6);
    while(!iTimeSync.is_time_sync()) {
        std::chrono::seconds sec(1);
        std::this_thread::sleep_for(sec);
    };

    double last_utc = iTimeSync.get_timestamp_ms();
    while(true) {
        double real_utc = iTimeSync.get_timestamp_ms();
        double pc_utc = xtime::get_timestamp_ms();
        if(real_utc - last_utc > 0.1) {
            std::cout << "accuracy: " << iTimeSync.get_accuracy() << " sync utc: " << xtime::get_str_time_ms(real_utc) << " pc utc: " << xtime::get_str_time_ms(pc_utc) << "\r";
            last_utc = real_utc;
        }
    };
    return 0;
}

