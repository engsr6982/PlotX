#pragma once

#include "ll/api/mod/NativeMod.h"

namespace plotx {

class PlotX {
    PlotX();

public:
    static PlotX& getInstance();

    bool load();

    bool enable();

    bool disable();

    bool unload();

    [[nodiscard]] ll::mod::NativeMod& getSelf() const;

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace plotx
