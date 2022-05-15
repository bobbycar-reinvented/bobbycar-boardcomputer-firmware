#include "mainmenu.h"

// 3rdparty lib includes
#include <actions/pushscreenaction.h>
#include <actions/popscreenaction.h>
#include <icons/back.h>
#include <tftinstance.h>

// local includes
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/ledstripmenu.h"
#include "actions/modesettingsaction.h"
#include "displays/menus/profilesmenu.h"
#include "displays/menus/graphsmenu.h"
#include "displays/menus/batterymenu.h"
#include "displays/powersupplydisplay.h"
#include "displays/menus/bmsmenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/manageprofilesmenu.h"
#include "displays/menus/mosfetsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/greenpassmenu.h"
#include "displays/lockscreen.h"
#include "displays/menus/garagemenu.h"
#include "displays/menus/otamenu.h"
#include "displays/poweroffdisplay.h"
#include "displays/menus/statisticsmenu.h"
#include "displays/confiscationdisplay.h"
#include "actions/rebootaction.h"
#include "displays/menus/debugmenu.h"
#include "icons/battery.h"
#include "icons/modes.h"
#include "icons/presets.h"
#include "icons/graph.h"
#ifdef FEATURE_BMS
#include "icons/bms.h"
#endif
#include "icons/settings.h"
#include "icons/lock.h"
#include "icons/demos.h"
#include "icons/update.h"
#include "icons/neopixel.h"
#include "icons/poweroff.h"
#include "icons/reboot.h"
#include "icons/statistics.h"
#include "icons/greenpass.h"
#include "icons/time.h"
#include "displays/statusdisplay.h"

namespace {
constexpr char TAG[] = "BOBBY";

constexpr char TEXT_MAINMENU[] = "Main menu";
constexpr char TEXT_STATUS[] = "Status";
constexpr char TEXT_LEDSTRIP[] = "Ledstrip";
constexpr char TEXT_STATISTICSMENU[] = "Statistics";
constexpr char TEXT_SELECTMODE[] = "Select mode";
constexpr char TEXT_MODESETTINGS[] = "Mode settings";
constexpr char TEXT_PRESETS[] = "Presets";
constexpr char TEXT_PROFILES[] = "Profiles";
constexpr char TEXT_GRAPHS[] = "Graphs";
constexpr char TEXT_POWERSUPPLY[] = "Powersupply";
constexpr char TEXT_BMS[] = "BMS";
constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_GREENPASS[] = "Green Pass";
constexpr char TEXT_LOCKVEHICLE[] = "Lock vehicle";
constexpr char TEXT_MOSFETS[] = "Mosfets";
constexpr char TEXT_DEMOS[] = "Demos";
constexpr char TEXT_GARAGE[] = "Garage";
constexpr char TEXT_UPDATE[] = "Update";
constexpr char TEXT_POWEROFF[] = "Poweroff";
constexpr char TEXT_REBOOT[] = "Reboot";
constexpr char TEXT_DEBUG[] = "Debug";
constexpr char TEXT_BATTERY[] = "Battery";
constexpr char TEXT_BATTERYDEBUG[] = "Bat Debug Menu";
constexpr char TEXT_CONFISCATIONMODE[] = "Confiscation Mode";
constexpr char TEXT_TOGGLECLOUDDEBUG[] = "Cloud Debug";
constexpr char TEXT_MANAGEPROFILESMENU[] = "Manage Profiles";

} // namespace

MainMenu::MainMenu()
{
    using namespace espgui;

    // constructMenuItem<makeComponent<MenuItem, mainmenu::CurrentTimeText,     DummyAction, StaticMenuItemIcon<&bobbyicons::time>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATUS>,       PushScreenAction<StatusDisplay>, StaticMenuItemIcon<&espgui::icons::back>>>();
    if (configs.feature.ledstrip.isEnabled.value())
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LEDSTRIP>,     PushScreenAction<LedstripMenu>,   StaticMenuItemIcon<&bobbyicons::neopixel>>>();
    }
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATISTICSMENU>, PushScreenAction<StatisticsMenu>, StaticMenuItemIcon<&bobbyicons::statistics>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTMODE>,   PushScreenAction<SelectModeMenu>, StaticMenuItemIcon<&bobbyicons::modes>>>();
    if (SHOWITEM)   { constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODESETTINGS>, ModeSettingsAction>>(); }
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BATTERY>,      PushScreenAction<BatteryMenu>, StaticMenuItemIcon<&bobbyicons::battery>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETTINGS>,     PushScreenAction<SettingsMenu>, StaticMenuItemIcon<&bobbyicons::settings>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GREENPASS>,    PushScreenAction<GreenPassMenu>, StaticMenuItemIcon<&bobbyicons::greenpass>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LOCKVEHICLE>,  PushScreenAction<Lockscreen>, StaticMenuItemIcon<&bobbyicons::lock>>>();
    if (configs.feature.garage.isEnabled.value() && configs.feature.esp_now.isEnabled.value())
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GARAGE>,       PushScreenAction<GarageMenu>>>();
    }
    if (configs.feature.ota.isEnabled.value())
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UPDATE>,       PushScreenAction<OtaMenu>, StaticMenuItemIcon<&bobbyicons::update>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GRAPHS>,       PushScreenAction<GraphsMenu>, StaticMenuItemIcon<&bobbyicons::graph>>>();
#if defined(FEATURE_CAN) && defined(FEATURE_POWERSUPPLY)
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POWERSUPPLY>,  PushScreenAction<PowerSupplyDisplay>>>();
#endif
#ifdef FEATURE_MOSFETS
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFETS>,      PushScreenAction<MosfetsMenu>>>();
#endif
#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BMS>,          PushScreenAction<BmsMenu>, StaticMenuItemIcon<&bobbyicons::bms>>>();
#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEMOS>,        PushScreenAction<DemosMenu>, StaticMenuItemIcon<&bobbyicons::demos>>>();
    if (SHOWITEM)   { constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_PROFILES>,     PushScreenAction<ProfilesMenu>, StaticMenuItemIcon<&bobbyicons::presets>>>(); }
    if (SHOWITEM)   { constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MANAGEPROFILESMENU>,PushScreenAction<ManageProfilesMenu>, StaticMenuItemIcon<&bobbyicons::presets>>>(); }
    if (SHOWITEM)   { constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEBUG>,        PushScreenAction<DebugMenu>>>(); }
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POWEROFF>,     PushScreenAction<PoweroffDisplay>, StaticMenuItemIcon<&bobbyicons::poweroff>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CONFISCATIONMODE>, PushScreenAction<ConfiscationDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_REBOOT>,       RebootAction, StaticMenuItemIcon<&bobbyicons::reboot>>>();
//#ifdef MAINMENU_PLUGIN
    // GMEN1
//#endif
}

std::string MainMenu::text() const
{
    return TEXT_MAINMENU;
}

void MainMenu::back()
{
    espgui::popScreen();
}
