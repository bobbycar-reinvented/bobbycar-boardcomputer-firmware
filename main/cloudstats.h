#pragma once

// system includes
#include <optional>
#include <string>

namespace bobby::cloudstats {
std::optional<std::string> buildCloudJson();
void updateDependencies();
void udpNeedsConstruction(bool needsConstruction);
void espnowNeedsConstruction(bool needsConstruction);
} // namespace bobby::cloudstats
