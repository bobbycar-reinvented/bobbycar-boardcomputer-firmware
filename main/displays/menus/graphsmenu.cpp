#include "graphsmenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "graphdisplay.h"
#include "splitgraphdisplay.h"

// local includes
#include "displays/bobbygraphdisplay.h"
#include "displays/bobbysplitgraphdisplay.h"
#include "utils.h"
#include "statistics.h"
#include "displays/menus/mainmenu.h"

namespace {
constexpr char TEXT_GRAPHS[] = "Graphs";
constexpr char TEXT_GAS[] = "Gas";
constexpr char TEXT_BREMS[] = "Brems";
constexpr char TEXT_POTIS[] = "Potis";
constexpr char TEXT_AVGSPEED[] = "Avg. speed";
constexpr char TEXT_AVGSPEEDKMH[] = "Avg. speed KMH";
constexpr char TEXT_SUMCURRENT[] = "Sum current";
constexpr char TEXT_FRONTVOLTAGE[] = "Front voltage";
constexpr char TEXT_BACKVOLTAGE[] = "Back voltage";
constexpr char TEXT_VOLTAGES[] = "Voltages";
constexpr char TEXT_BMSVOLTAGE[] = "BMS voltage";
constexpr char TEXT_BMSCURRENT[] = "BMS current";
constexpr char TEXT_BMSPOWER[] = "BMS power";
constexpr char TEXT_SUMCURRENTSCOMPARISON[] = "Sum currents comparison";
constexpr char TEXT_MOTORCURRENTS[] = "Motor currents";
constexpr char TEXT_RSSI[] = "RSSI";
constexpr char TEXT_BACK[] = "Back";

using GasGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_GAS>,
    espgui::SingleGraphAccessor<GasStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using BremsGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BREMS>,
    espgui::SingleGraphAccessor<BremsStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using PotisGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<2>,
    espgui::StaticText<TEXT_POTIS>,
    espgui::DualGraphAccessor<GasStatistics, BremsStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using PotisSplitGraphDisplay = espgui::makeComponent<
    BobbySplitGraphDisplay<1, 1>,
    espgui::StaticText<TEXT_POTIS>,
    espgui::SingleTopGraphAccessor<GasStatistics>,
    espgui::SingleBottomGraphAccessor<BremsStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;

using AvgSpeedGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_AVGSPEED>,
    espgui::SingleGraphAccessor<AvgSpeedStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using AvgSpeedKmhGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_AVGSPEEDKMH>,
    espgui::SingleGraphAccessor<AvgSpeedKmhStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;

using SumCurrentGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_SUMCURRENT>,
    espgui::SingleGraphAccessor<SumCurrentStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;

using FrontVoltageGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_FRONTVOLTAGE>,
    espgui::SingleGraphAccessor<FrontVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using BackVoltageGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BACKVOLTAGE>,
    espgui::SingleGraphAccessor<BackVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using VoltagesGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<2>,
    espgui::StaticText<TEXT_VOLTAGES>,
    espgui::DualGraphAccessor<FrontVoltageStatistics, BackVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using VoltagesSplitGraphDisplay = espgui::makeComponent<
    BobbySplitGraphDisplay<1, 1>,
    espgui::StaticText<TEXT_VOLTAGES>,
    espgui::SingleTopGraphAccessor<FrontVoltageStatistics>,
    espgui::SingleBottomGraphAccessor<BackVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;

#ifdef FEATURE_BMS
using BmsVoltageGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BMSVOLTAGE>,
    espgui::SingleGraphAccessor<BmsVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using BmsCurrentGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BMSCURRENT>,
    espgui::SingleGraphAccessor<BmsCurrentStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using BmsPowerGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BMSPOWER>,
    espgui::SingleGraphAccessor<BmsPowerStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
using SumCurrentsComparisonGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<2>,
    espgui::StaticText<TEXT_SUMCURRENTSCOMPARISON>,
    DualGraphAccessor<SumCurrentStatistics, BmsCurrentStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
#endif

class MotorCurrentsStatistics : public virtual espgui::GraphAccessorInterface<4>
{
    std::array<std::reference_wrapper<const statistics::ContainerType>, 4> getBuffers() const override
    {
        return {FrontLeftCurrentStatistics{}.getBuffer(), FrontRightCurrentStatistics{}.getBuffer(), BackLeftCurrentStatistics{}.getBuffer(), BackRightCurrentStatistics{}.getBuffer()};
    }
};
using MotorCurrentsGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<4>,
    espgui::StaticText<TEXT_MOTORCURRENTS>,
    MotorCurrentsStatistics,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;

using RssiGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_RSSI>,
    espgui::SingleGraphAccessor<RssiStatistics>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<GraphsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<GraphsMenu>>
>;
} // namespace

GraphsMenu::GraphsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GAS>,                   SwitchScreenAction<GasGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BREMS>,                 SwitchScreenAction<BremsGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POTIS>,                 SwitchScreenAction<PotisGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POTIS>,                 SwitchScreenAction<PotisSplitGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_AVGSPEED>,              SwitchScreenAction<AvgSpeedGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_AVGSPEEDKMH>,           SwitchScreenAction<AvgSpeedKmhGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SUMCURRENT>,            SwitchScreenAction<SumCurrentGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTVOLTAGE>,          SwitchScreenAction<FrontVoltageGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKVOLTAGE>,           SwitchScreenAction<BackVoltageGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGES>,              SwitchScreenAction<VoltagesGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGES>,              SwitchScreenAction<VoltagesSplitGraphDisplay>>>();
#ifdef FEATURE_BMS
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMSVOLTAGE>,            SwitchScreenAction<BmsVoltageGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMSCURRENT>,            SwitchScreenAction<BmsCurrentGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMSPOWER>,              SwitchScreenAction<BmsPowerGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SUMCURRENTSCOMPARISON>, SwitchScreenAction<SumCurrentsComparisonGraphDisplay>>>();
#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOTORCURRENTS>,         SwitchScreenAction<MotorCurrentsGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_RSSI>,                  SwitchScreenAction<RssiGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string GraphsMenu::text() const
{
    return TEXT_GRAPHS;
}

void GraphsMenu::back()
{
    espgui::switchScreen<MainMenu>();
}
