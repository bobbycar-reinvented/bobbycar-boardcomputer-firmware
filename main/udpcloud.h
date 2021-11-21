#pragma once
#include <string>

// Little "flash" on statusdisplay when udp stuff is happening
extern bool visualSendUdpPacket;

void spamUdpBroadcast();
std::string buildUdpCloudJson();
void sendUdpCloudPacket();
