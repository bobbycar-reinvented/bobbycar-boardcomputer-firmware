#pragma once

#include <WString.h>

namespace {
class TextInterface;
class MenuDisplay;
class ChangeValueDisplayInterface;
}

namespace {
class ConfirmInterface {
public:
    virtual void confirm() {}
};

class BackInterface {
public:
    virtual void back() {}
};

template<typename T>
class ConfirmActionInterface : public virtual ConfirmInterface
{
    T m_action;

public:
    void confirm() override { m_action.triggered(); }
};

template<typename T>
class BackActionInterface : public virtual BackInterface
{
    T m_action;

public:
    void back() override { m_action.triggered(); }
};

class Display : public virtual ConfirmInterface, public virtual BackInterface {
public:
    virtual ~Display() = default;

    virtual void start() {};
    virtual void initScreen() {};
    virtual void update() {};
    virtual void redraw() {};
    virtual void stop() {}

    virtual void rotate(int offset) {}

    virtual TextInterface *asTextInterface() { return nullptr; }
    virtual const TextInterface *asTextInterface() const { return nullptr; }

    virtual MenuDisplay *asMenuDisplay() { return nullptr; }
    virtual const MenuDisplay *asMenuDisplay() const { return nullptr; }

    virtual ChangeValueDisplayInterface *asChangeValueDisplayInterface() { return nullptr; }
    virtual const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const { return nullptr; }
};
}
