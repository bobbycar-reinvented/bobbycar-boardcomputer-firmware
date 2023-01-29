#pragma once

// 3rdparty lib includes
#include <menuitem.h>
#include <accessorinterface.h>

// local includes
#include "icons/checked.h"
#include "icons/checked_grey.h"
#include "icons/unchecked.h"
#include "icons/unchecked_grey.h"

namespace bobby {
class BobbyCheckboxIcon : public virtual espgui::MenuItemIconInterface, public virtual espgui::AccessorInterface<bool>
{
public:
    const espgui::MenuItemIcon *icon(bool selected) const override
    {
        if (selected)
            return getValue() ? &bobbyicons::checked_grey : &bobbyicons::unchecked_grey;
        else
            return getValue() ? &bobbyicons::checked : &bobbyicons::unchecked;
    }
};
} // namespace bobby
