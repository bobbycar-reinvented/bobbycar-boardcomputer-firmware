#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class StarfieldDisplay;
class PingPongDisplay;
class SpiroDisplay;
class GameOfLifeDisplay;
class MainMenu;
} // namespace

namespace {
class DemosMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEMOS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public ContainerMenuDefinition
{
public:
    DemosMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_STARFIELD>,  SwitchScreenAction<StarfieldDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_PINGPONG>,   SwitchScreenAction<PingPongDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SPIRO>,      SwitchScreenAction<SpiroDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_GAMEOFLIFE>, SwitchScreenAction<GameOfLifeDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
