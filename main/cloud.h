#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <wrappers/websocket_client.h>
#include <cpptypesafeenum.h>
#include <espchrono.h>

extern espcpputils::websocket_client cloudClient;
extern bool cloudStarted;
extern espchrono::millis_clock::time_point lastCreateTry;
extern espchrono::millis_clock::time_point lastStartTry;
extern std::string cloudBuffer;

#define CloudModeValues(x) \
    x(INACTIVE) \
    x(STATISTICS) \
    x(REMOTE_DISPLAY) \
    x(STATISTICS_AND_REMOTE_DISPLAY)
DECLARE_TYPESAFE_ENUM(CloudMode, : uint8_t, CloudModeValues)

void createCloud();
void destroyCloud();
void startCloud();

void initCloud();
void updateCloud();
void cloudCollect();
void cloudSend();
void cloudSendDisplay(std::string_view data);

std::string getLoginMessage();
