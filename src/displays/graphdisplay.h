#pragma once

#include "demodisplay.h"
#include "actions/switchscreenaction.h"
#include "textinterface.h"
#include "widgets/label.h"
#include "widgets/graph.h"
#include "globals.h"
#include "statistics.h"

namespace {
class GraphsMenu;
}

namespace {
template<size_t COUNT>
class MultiStatisticsInterface
{
public:
    virtual std::array<std::reference_wrapper<const statistics::ContainerType>, COUNT> getBuffers() const = 0;
};

class MultiStatisticsSingleImpl : public virtual MultiStatisticsInterface<1>, public virtual BufferAccessorInterface
{
public:
    std::array<std::reference_wrapper<const statistics::ContainerType>, 1> getBuffers() const
    {
        return {getBuffer()};
    }
};

template<size_t COUNT>
class GraphDisplay : public DemoDisplay, public SwitchScreenAction<GraphsMenu>, public virtual TextInterface, public BackActionInterface<SwitchScreenAction<GraphsMenu>>, public virtual MultiStatisticsInterface<COUNT>
{
    using Base = DemoDisplay;

public:
    void initScreen() override;
    void redraw() override;

private:
    static constexpr int screenHeight = 320, topMargin = 40, bottomMargin = 10, labelOffset = -5;
    static constexpr int graphHeight = screenHeight-topMargin-bottomMargin;

    Label m_titleLabel{5, 5}; // 230, 25

    Graph<200, COUNT> m_graph{0, 40, 270};
};

template<size_t COUNT>
void GraphDisplay<COUNT>::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_titleLabel.start();
    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    m_graph.start(static_cast<const MultiStatisticsInterface<COUNT> &>(*this).getBuffers());
}

template<size_t COUNT>
void GraphDisplay<COUNT>::redraw()
{
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    m_titleLabel.redraw(text());

    m_graph.redraw(static_cast<const MultiStatisticsInterface<COUNT> &>(*this).getBuffers());
}
}
