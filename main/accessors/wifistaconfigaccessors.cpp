#include "wifistaconfigaccessors.h"

// local includes
#include "newsettings.h"

using namespace espgui;

bool WifiStaEnabledAccessor::getValue() const { return configs.wifiStaEnabled.value; }
void WifiStaEnabledAccessor::setValue(bool value) { configs.write_config(configs.wifiStaEnabled, value); }

std::string WifiStaConfigSsidAccessor::getValue() const { return configs.wifi_configs[m_index].ssid.value; }
void WifiStaConfigSsidAccessor::setValue(std::string value) { configs.write_config(configs.wifi_configs[m_index].ssid, value); }

std::string WifiStaConfigKeyAccessor::getValue() const { return configs.wifi_configs[m_index].key.value; }
void WifiStaConfigKeyAccessor::setValue(std::string value) { configs.write_config(configs.wifi_configs[m_index].key, value); }

bool WifiStaConfigUseStaticIpAccessor::getValue() const { return configs.wifi_configs[m_index].useStaticIp.value; }
void WifiStaConfigUseStaticIpAccessor::setValue(bool value) { configs.write_config(configs.wifi_configs[m_index].useStaticIp, value); }

wifi_stack::ip_address_t WifiStaConfigStaticIpAccessor::getValue() const { return configs.wifi_configs[m_index].staticIp.value; }
void WifiStaConfigStaticIpAccessor::setValue(wifi_stack::ip_address_t value) { configs.write_config(configs.wifi_configs[m_index].staticIp, value); }

wifi_stack::ip_address_t WifiStaConfigStaticSubnetAccessor::getValue() const { return configs.wifi_configs[m_index].staticSubnet.value; }
void WifiStaConfigStaticSubnetAccessor::setValue(wifi_stack::ip_address_t value) { configs.write_config(configs.wifi_configs[m_index].staticSubnet, value); }

wifi_stack::ip_address_t WifiStaConfigStaticGatewayAccessor::getValue() const { return configs.wifi_configs[m_index].staticGateway.value; }
void WifiStaConfigStaticGatewayAccessor::setValue(wifi_stack::ip_address_t value) { configs.write_config(configs.wifi_configs[m_index].staticGateway, value); }

bool WifiStaConfigUseStaticDnsAccessor::getValue() const { return configs.wifi_configs[m_index].useStaticDns.value; }
void WifiStaConfigUseStaticDnsAccessor::setValue(bool value) { configs.write_config(configs.wifi_configs[m_index].useStaticDns, value); }

wifi_stack::ip_address_t WifiStaConfigStaticDns0Accessor::getValue() const { return configs.wifi_configs[m_index].staticDns0.value; }
void WifiStaConfigStaticDns0Accessor::setValue(wifi_stack::ip_address_t value) { configs.write_config(configs.wifi_configs[m_index].staticDns0, value); }

wifi_stack::ip_address_t WifiStaConfigStaticDns1Accessor::getValue() const { return configs.wifi_configs[m_index].staticDns1.value; }
void WifiStaConfigStaticDns1Accessor::setValue(wifi_stack::ip_address_t value) { configs.write_config(configs.wifi_configs[m_index].staticDns1, value); }

wifi_stack::ip_address_t WifiStaConfigStaticDns2Accessor::getValue() const { return configs.wifi_configs[m_index].staticDns2.value; }
void WifiStaConfigStaticDns2Accessor::setValue(wifi_stack::ip_address_t value) { configs.write_config(configs.wifi_configs[m_index].staticDns2, value); }
