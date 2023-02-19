#include "graphsmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <graphdisplay.h>
#include <splitgraphdisplay.h>

// local includes
#include "guihelpers/bobbygraphdisplay.h"
#include "guihelpers/bobbysplitgraphdisplay.h"
#include "icons/back.h"
#include "statistics.h"

namespace bobby {

namespace {
constexpr char TEXT_GRAPHS[] = "Graphs";
constexpr char TEXT_RAW_GAS[] = "Raw Gas";
constexpr char TEXT_RAW_BREMS[] = "Raw Brems";
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

using RawGasGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_RAW_GAS>,
    espgui::SingleGraphAccessor<statistics::RawGasStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using RawBremsGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_RAW_BREMS>,
    espgui::SingleGraphAccessor<statistics::RawBremsStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using GasGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_GAS>,
    espgui::SingleGraphAccessor<statistics::GasStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using BremsGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_BREMS>,
    espgui::SingleGraphAccessor<statistics::BremsStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using PotisGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<2>,
    espgui::StaticTitle<TEXT_POTIS>,
    espgui::DualGraphAccessor<statistics::GasStatistics, statistics::BremsStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using PotisSplitGraphDisplay = espgui::makeComponent<
    BobbySplitGraphDisplay<1, 1>,
    espgui::StaticTitle<TEXT_POTIS>,
    espgui::SingleTopGraphAccessor<statistics::GasStatistics>,
    espgui::SingleBottomGraphAccessor<statistics::BremsStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using AvgSpeedGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_AVGSPEED>,
    espgui::SingleGraphAccessor<statistics::AvgSpeedStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using AvgSpeedKmhGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_AVGSPEEDKMH>,
    espgui::SingleGraphAccessor<statistics::AvgSpeedKmhStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using SumCurrentGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_SUMCURRENT>,
    espgui::SingleGraphAccessor<statistics::SumCurrentStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using FrontVoltageGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_FRONTVOLTAGE>,
    espgui::SingleGraphAccessor<statistics::FrontVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using BackVoltageGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_BACKVOLTAGE>,
    espgui::SingleGraphAccessor<statistics::BackVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using VoltagesGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<2>,
    espgui::StaticTitle<TEXT_VOLTAGES>,
    espgui::DualGraphAccessor<statistics::FrontVoltageStatistics, statistics::BackVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using VoltagesSplitGraphDisplay = espgui::makeComponent<
    BobbySplitGraphDisplay<1, 1>,
    espgui::StaticTitle<TEXT_VOLTAGES>,
    espgui::SingleTopGraphAccessor<statistics::FrontVoltageStatistics>,
    espgui::SingleBottomGraphAccessor<statistics::BackVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

#ifdef FEATURE_BMS
using BmsVoltageGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BMSVOLTAGE>,
    espgui::SingleGraphAccessor<BmsVoltageStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using BmsCurrentGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BMSCURRENT>,
    espgui::SingleGraphAccessor<BmsCurrentStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using BmsPowerGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticText<TEXT_BMSPOWER>,
    espgui::SingleGraphAccessor<BmsPowerStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using SumCurrentsComparisonGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<2>,
    espgui::StaticText<TEXT_SUMCURRENTSCOMPARISON>,
    DualGraphAccessor<SumCurrentStatistics, BmsCurrentStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
#endif

class MotorCurrentsStatistics : public virtual espgui::GraphAccessorInterface<4>
{
    std::array<std::reference_wrapper<const statistics::ContainerType>, 4> getBuffers() const override
    {
        return {
            statistics::FrontLeftCurrentStatistics{}.getBuffer(),
            statistics::FrontRightCurrentStatistics{}.getBuffer(),
            statistics::BackLeftCurrentStatistics{}.getBuffer(),
            statistics::BackRightCurrentStatistics{}.getBuffer()
        };
    }
};
using MotorCurrentsGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<4>,
    espgui::StaticTitle<TEXT_MOTORCURRENTS>,
    MotorCurrentsStatistics,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using RssiGraphDisplay = espgui::makeComponent<
    BobbyGraphDisplay<1>,
    espgui::StaticTitle<TEXT_RSSI>,
    espgui::SingleGraphAccessor<statistics::RssiStatistics>,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

GraphsMenu::GraphsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_RAW_GAS>,               PushScreenAction<RawGasGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_RAW_BREMS>,             PushScreenAction<RawBremsGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GAS>,                   PushScreenAction<GasGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BREMS>,                 PushScreenAction<BremsGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POTIS>,                 PushScreenAction<PotisGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POTIS>,                 PushScreenAction<PotisSplitGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_AVGSPEED>,              PushScreenAction<AvgSpeedGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_AVGSPEEDKMH>,           PushScreenAction<AvgSpeedKmhGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SUMCURRENT>,            PushScreenAction<SumCurrentGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTVOLTAGE>,          PushScreenAction<FrontVoltageGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKVOLTAGE>,           PushScreenAction<BackVoltageGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGES>,              PushScreenAction<VoltagesGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_VOLTAGES>,              PushScreenAction<VoltagesSplitGraphDisplay>>>();
#ifdef FEATURE_BMS
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMSVOLTAGE>,            PushScreenAction<BmsVoltageGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMSCURRENT>,            PushScreenAction<BmsCurrentGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMSPOWER>,              PushScreenAction<BmsPowerGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SUMCURRENTSCOMPARISON>, PushScreenAction<SumCurrentsComparisonGraphDisplay>>>();
#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOTORCURRENTS>,         PushScreenAction<MotorCurrentsGraphDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_RSSI>,                  PushScreenAction<RssiGraphDisplay>>>();
}

std::string GraphsMenu::title() const
{
    return TEXT_GRAPHS;
}

void GraphsMenu::back()
{
    espgui::popScreen();
}

} // namespace bobby
