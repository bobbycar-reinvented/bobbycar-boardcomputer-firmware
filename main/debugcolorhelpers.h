#pragma once

// 3rdparty lib includes
#include <colorinterface.h>
#include <tftcolors.h>

// local includes
#include "globals.h"

namespace bobby::debug {

template<typename Tcontroller, int TsuccessColor>
class FeedbackColor : public virtual ColorInterface
{
public:
    int color() const override
    {
        return Tcontroller::get().feedbackValid ? TsuccessColor : espgui::TFT_RED;
    }
};

template<int TsuccessColor>
using FrontFeedbackColor = FeedbackColor<bobby::FrontControllerGetter, TsuccessColor>;

template<int TsuccessColor>
using BackFeedbackColor = FeedbackColor<bobby::BackControllerGetter, TsuccessColor>;

} // namespace bobby::debug
