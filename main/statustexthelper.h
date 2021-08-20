#pragma once

// local includes
#include "textinterface.h"
#include "globals.h"
#include "utils.h"

namespace {
template<const char *Ttext, typename Ttype, Ttype *Tptr, typename TreturnType, TreturnType (Ttype::*Tmethod)()>
class StatusTextHelper : public virtual TextInterface
{
public:
    std::string text() const override { using std::to_string; using ::to_string; return Ttext + to_string((Tptr->*Tmethod)()); }
};

template<const char *Ttext, typename TreturnType, TreturnType (*Tmethod)()>
class StaticStatusTextHelper : public virtual TextInterface
{
public:
    std::string text() const override { using std::to_string; using ::to_string; return Ttext + to_string(Tmethod()); }
};
}
