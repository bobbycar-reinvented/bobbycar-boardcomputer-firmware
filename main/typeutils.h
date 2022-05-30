#pragma once

namespace typeutils {
    using namespace std;
template<typename T>
struct t_to_str
{
    t_to_str() = delete;
    ~t_to_str() = delete;

    static const char *str;
};

template<typename T>
const char *t_to_str<T>::str = "unknown";

#define DEFINE_FOR_TYPE2(TYPE, STR) \
    template<> const char *t_to_str<TYPE>::str = #STR; \
    template<> const char *t_to_str<TYPE const&>::str = #STR; \
    template<> const char *t_to_str<std::optional<TYPE>>::str = "std::optional<" #STR ">"; \
    template<> const char *t_to_str<std::optional<TYPE> const&>::str = "std::optional<" #STR ">"; \
    template<> const char *t_to_str<ConfigWrapper<TYPE>>::str = #STR; \
    template<> const char *t_to_str<ConfigWrapper<TYPE> const&>::str = #STR; \
    template<> const char *t_to_str<ConfigWrapperLegacy<TYPE>>::str = #STR; \
    template<> const char *t_to_str<ConfigWrapperLegacy<TYPE> const&>::str = #STR;

#define DEFINE_FOR_TYPE(TYPE) DEFINE_FOR_TYPE2(TYPE, TYPE)
DEFINE_FOR_TYPE(bool)
DEFINE_FOR_TYPE(int8_t)
DEFINE_FOR_TYPE(uint8_t)
DEFINE_FOR_TYPE(int16_t)
DEFINE_FOR_TYPE(uint16_t)
DEFINE_FOR_TYPE(int32_t)
DEFINE_FOR_TYPE(uint32_t)
DEFINE_FOR_TYPE(int64_t)
DEFINE_FOR_TYPE(uint64_t)
DEFINE_FOR_TYPE(long)
DEFINE_FOR_TYPE(unsigned long)
DEFINE_FOR_TYPE(float)
DEFINE_FOR_TYPE(double)
DEFINE_FOR_TYPE(string)
DEFINE_FOR_TYPE(sntp_sync_mode_t)
DEFINE_FOR_TYPE(espchrono::DayLightSavingMode)
DEFINE_FOR_TYPE(OtaAnimationModes)
DEFINE_FOR_TYPE(LedstripAnimation)
DEFINE_FOR_TYPE(HandbremseMode)
DEFINE_FOR_TYPE(BobbyQuickActions)
DEFINE_FOR_TYPE(CloudMode)
DEFINE_FOR_TYPE(BatteryCellType)
DEFINE_FOR_TYPE(wifi_auth_mode_t)
DEFINE_FOR_TYPE(wifi_stack::mac_t)
DEFINE_FOR_TYPE(wifi_stack::ip_address_t)
DEFINE_FOR_TYPE(espchrono::milliseconds32)
DEFINE_FOR_TYPE(espchrono::minutes32)
#undef DEFINE_FOR_TYPE
} // namespace typeutils
