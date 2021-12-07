#pragma once

// 3rd party includes
#include <menudisplay.h>
#include <texts.h>
#ifdef FEATURE_OTA

namespace SelectBuildServerBranch {
    class CurrentBranch : public virtual espgui::TextInterface
    {
    public:
        std::string text() const override;
    };

    class BranchMenuItem : public espgui::MenuItem
    {
    public:
        std::string text() const override;
        void setName(std::string &&name);
        void setName(const std::string &name);

        void triggered() override;
    private:
        std::string m_name;
    };

    class ClearBranchAction : public virtual espgui::ActionInterface
    {
    public:
        void triggered() override;
    };
}

class SelectBuildserverBranchMenu :
        public espgui::MenuDisplay,
        public espgui::StaticText<TEXT_SELECT_BRANCH>
{
    using Base = espgui::MenuDisplay;
public:
    SelectBuildserverBranchMenu();
    void buildMenuRequestError(std::string error);
    void update() override;
    void back() override;
};

#endif
