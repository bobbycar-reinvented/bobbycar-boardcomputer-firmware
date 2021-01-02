#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/loadsettingsaction.h"
#include "actions/savesettingsaction.h"
#include "actions/erasenvsaction.h"
#include "actions/switchscreenaction.h"
#include "actions/dummyaction.h"
#include "actions/toggleboolaction.h"
#include "icons/lock.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "debugcolorhelpers.h"

// forward declares
namespace {
class MainMenu;
class FrontCommandDebugMenu;
class BackCommandDebugMenu;
class FrontLeftMotorStateDebugMenu;
class FrontRightMotorStateDebugMenu;
class BackLeftMotorStateDebugMenu;
class BackRightMotorStateDebugMenu;
class FrontFeedbackDebugMenu;
class BackFeedbackDebugMenu;
class FrontLeftMotorFeedbackDebugMenu;
class FrontRightMotorFeedbackDebugMenu;
class BackLeftMotorFeedbackDebugMenu;
class BackRightMotorFeedbackDebugMenu;
class DynamicDebugMenu;
} // namespace

namespace {
class DebugMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEBUG>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public ContainerMenuDefinition
{
public:
    DebugMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_LOADSETTINGS>,         LoadSettingsAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SAVESETTINGS>,         SaveSettingsAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ERASENVS>,             EraseNvsAction>>();
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                   DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTCOMMAND>,         SwitchScreenAction<FrontCommandDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKCOMMAND>,          SwitchScreenAction<BackCommandDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                   DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTLEFTCOMMAND>,     SwitchScreenAction<FrontLeftMotorStateDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTRIGHTCOMMAND>,    SwitchScreenAction<FrontRightMotorStateDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKLEFTCOMMAND>,      SwitchScreenAction<BackLeftMotorStateDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKRIGHTCOMMAND>,     SwitchScreenAction<BackRightMotorStateDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                   DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTFEEDBACK>,        SwitchScreenAction<FrontFeedbackDebugMenu>, FrontFeedbackColor<TFT_WHITE>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKFEEDBACK>,         SwitchScreenAction<BackFeedbackDebugMenu>, BackFeedbackColor<TFT_WHITE>>>();
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                   DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTLEFTFEEDBACK>,    SwitchScreenAction<FrontLeftMotorFeedbackDebugMenu>, FrontFeedbackColor<TFT_WHITE>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTRIGHTFEEDBACK>,   SwitchScreenAction<FrontRightMotorFeedbackDebugMenu>, FrontFeedbackColor<TFT_WHITE>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKLEFTFEEDBACK>,     SwitchScreenAction<BackLeftMotorFeedbackDebugMenu>, BackFeedbackColor<TFT_WHITE>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKRIGHTFEEDBACK>,    SwitchScreenAction<BackRightMotorFeedbackDebugMenu>, BackFeedbackColor<TFT_WHITE>>>();
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                   DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DYNAMICMENU>,          SwitchScreenAction<DynamicDebugMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                 SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
