#include "demosmenu.h"

// 3rdparty lib includes
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/menus/mainmenu.h"

// local includes
#include "utils.h"

namespace {
constexpr char TEXT_DEMOS[] = "Demos";
constexpr char TEXT_STARFIELD[] = "Starfield";
constexpr char TEXT_PINGPONG[] = "PingPong";
constexpr char TEXT_SPIRO[] = "Spiro";
constexpr char TEXT_GAMEOFLIFE[] = "GameOfLife";
constexpr char TEXT_BACK[] = "Back";
} // namespace

DemosMenu::DemosMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STARFIELD>,  SwitchScreenAction<StarfieldDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_PINGPONG>,   SwitchScreenAction<PingPongDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SPIRO>,      SwitchScreenAction<SpiroDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GAMEOFLIFE>, SwitchScreenAction<GameOfLifeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string DemosMenu::text() const
{
    return TEXT_DEMOS;
}

void DemosMenu::back()
{
    espgui::switchScreen<MainMenu>();
}
