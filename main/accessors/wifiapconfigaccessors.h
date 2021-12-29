#pragma once

// system includes
#include <string>

// 3rdparty lib includes
#include <accessorinterface.h>
#include <espwifiutils.h>

class WifiApEnabledAccessor : public virtual espgui::AccessorInterface<bool>
{
public:
    bool getValue() const override;
    void setValue(bool value) override;
};

//class WifiApDisableWhenOnlineAccessor : public virtual espgui::AccessorInterface<bool>
//{
//public:
//    bool getValue() const override;
//    void setValue(bool value) override;
//};
