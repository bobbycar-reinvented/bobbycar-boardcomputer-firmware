#include "presets.h"
#include "macros_bobbycar.h"

namespace presets {
StringSettings makeDefaultStringSettings()
{
#ifdef FEATURE_OTA
    using ConfiguredOtaServer = StringSettings::ConfiguredOtaServer;
#endif

    return {
#ifdef FEATURE_OTA
        .otaUrl = {},
#endif
#ifdef FEATURE_GARAGE
        .garageUrl = {},
#endif
#ifdef FEATURE_NTP
        .timeServer = "europe.pool.ntp.org",
#endif
#ifdef FEATURE_OTA
        .otaServers = std::array<ConfiguredOtaServer, 5> {
            ConfiguredOtaServer { .name = {}, .url = {} },
            ConfiguredOtaServer { .name = {}, .url = {} },
            ConfiguredOtaServer { .name = {}, .url = {} },
            ConfiguredOtaServer { .name = {}, .url = {} },
            ConfiguredOtaServer { .name = {}, .url = {} },
//            ConfiguredOtaServer { .name = {}, .url = {} },
//            ConfiguredOtaServer { .name = {}, .url = {} },
//            ConfiguredOtaServer { .name = {}, .url = {} },
//            ConfiguredOtaServer { .name = {}, .url = {} },
//            ConfiguredOtaServer { .name = {}, .url = {} },
        },
        .otaServerUrl = {},
#endif
#ifdef FEATURE_OTA
        .otaServerBranch = {},
#endif
        .webserver_password = {},
    };
}
} // namespace presets
