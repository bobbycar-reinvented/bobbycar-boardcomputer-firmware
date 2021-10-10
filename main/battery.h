#pragma once

// local includes
#include "globals.h"
#include "cpputils.h"

#define BATTERY_CELLTYPE_22P 0
#define BATTERY_CELLTYPE_HG2 1
#define BATTERY_CELLTYPE_MH1 2
#define BATTERY_CELLTYPE_VTC5 3

float battery_percentage = 42.0;

std::string getBatteryPercentageString() {
    std::string output = fmt::format("Battery: {:.1f}%", battery_percentage);
    return output;
}

std::string getBatteryCellTypeString() {
    std::string output = "";
    switch (settings.battery.cellType) {
        case BATTERY_CELLTYPE_22P:
            output = "Cells: 22P";
            break;
        case BATTERY_CELLTYPE_HG2:
            output = "Cells: HG2";
            break;
        case BATTERY_CELLTYPE_MH1:
            output = "Cells: MH1";
            break;
        case BATTERY_CELLTYPE_VTC5:
            output = "Cells: VTC5";
            break;
        default:
            output = "Unkown cell type";
            break;
    }

    return output;
}
