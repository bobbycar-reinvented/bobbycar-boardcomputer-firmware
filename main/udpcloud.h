#pragma once

// system includes
#include <optional>
#include <string>

// Little "flash" on statusdisplay when udp stuff is happening
extern bool visualSendUdpPacket;

void udpCloudInit();
void udpCloudUpdate();

std::optional<std::string> buildUdpCloudJson();
void sendUdpCloudPacket();
