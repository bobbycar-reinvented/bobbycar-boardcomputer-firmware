#include "statistics.h"

namespace bobby::statistics {

ContainerType raw_gas, raw_brems, gas, brems, avgSpeed, avgSpeedKmh, sumCurrent, frontVoltage, backVoltage, frontLeftCurrent, frontRightCurrent, backLeftCurrent, backRightCurrent,
#ifdef FEATURE_BMS
    bmsVoltage, bmsCurrent, bmsPower,
#endif
    rssi;

void pushStats()
{
    if (bobby::raw_gas)
        statistics::raw_gas.push_back(*bobby::raw_gas);
    if (bobby::raw_brems)
        statistics::raw_brems.push_back(*bobby::raw_brems);
    if (bobby::gas)
        statistics::gas.push_back(*bobby::gas);
    if (bobby::brems)
        statistics::brems.push_back(*bobby::brems);
    statistics::avgSpeed.push_back(bobby::avgSpeed);
    statistics::avgSpeedKmh.push_back(bobby::avgSpeedKmh);
    statistics::sumCurrent.push_back(bobby::sumCurrent);
    if (controllers.front.feedbackValid)
    {
        statistics::frontVoltage.push_back(controllers.front.getCalibratedVoltage());
        statistics::frontLeftCurrent.push_back(fixCurrent(controllers.front.feedback.left.dcLink));
        statistics::frontRightCurrent.push_back(fixCurrent(controllers.front.feedback.right.dcLink));
    }
    if (controllers.back.feedbackValid)
    {
        statistics::backVoltage.push_back(controllers.back.getCalibratedVoltage());
        statistics::backLeftCurrent.push_back(fixCurrent(controllers.back.feedback.left.dcLink));
        statistics::backRightCurrent.push_back(fixCurrent(controllers.back.feedback.right.dcLink));
    }
#ifdef FEATURE_BMS
    statistics::bmsVoltage.push_back(bms::voltage);
    statistics::bmsCurrent.push_back(bms::current);
    statistics::bmsPower.push_back(bms::power);
#endif
    if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
    {
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            statistics::rssi.push_back(result->rssi);
    }
}
} // namespace bobby::statistics
