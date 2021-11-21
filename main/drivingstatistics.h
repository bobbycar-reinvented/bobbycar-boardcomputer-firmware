#pragma once

// system includes
#include <string>
#include <chrono>

struct DrivingStatistics
{
    float meters_driven;
    std::chrono::milliseconds currentDrivingTime;
    double totalMeters;
    uint32_t last_cm_written;
    float wh_used;
    float batteryWhEstimate;
};

extern DrivingStatistics drivingStatistics;

void calculateStatistics();
float getAvgWhPerKm();
std::string getEfficiencyClassString();
uint16_t getEfficiencyClassColor();
std::string get_current_driving_time_string();
