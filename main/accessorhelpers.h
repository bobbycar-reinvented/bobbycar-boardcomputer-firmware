#pragma once

// 3rdparty lib includes
#include <accessorinterface.h>

// local includes
#include "utils.h"
#include "newsettings.h"

//! Special type of RefAccessor that also saves settings after setValue()
template<typename T>
struct RefAccessorSaveSettings : public virtual espgui::RefAccessor<T>
{
    void setValue(T value) override { espgui::RefAccessor<T>::setValue(value); saveSettings(); };
};

template<typename T>
struct NewSettingsAccessor : public virtual espgui::AccessorInterface<T>
{
    virtual ConfigWrapper<T>& getConfig() const = 0;

    T getValue() const override { return getConfig().value; }
    void setValue(T value) override { configs.write_config(getConfig(), value); }
};
