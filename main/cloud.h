#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <wrappers/websocket_client.h>
#include <espchrono.h>

// local includes
#include "bobbytypesafeenum.h"

namespace bobby::cloud {

extern espcpputils::websocket_client cloudClient;
extern bool cloudStarted;
extern espchrono::millis_clock::time_point lastCreateTry;
extern espchrono::millis_clock::time_point lastStartTry;
extern std::string cloudBuffer;

void createCloud();

void destroyCloud();

void startCloud();

void initCloud();

void updateCloud();

void cloudCollect();

void cloudSend();

std::string getLoginMessage();

} // namespace bobby::cloud
