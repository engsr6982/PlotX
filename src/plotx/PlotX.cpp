#include "PlotX.h"

#include "ll/api/mod/RegisterHelper.h"

namespace plotx {

PlotX::PlotX() : mSelf(*ll::mod::NativeMod::current()) {}
PlotX& PlotX::getInstance() {
    static PlotX instance;
    return instance;
}

bool PlotX::load() {
    getSelf().getLogger().debug("Loading...");
    // Code for loading the mod goes here.
    return true;
}

bool PlotX::enable() {
    getSelf().getLogger().debug("Enabling...");
    // Code for enabling the mod goes here.
    return true;
}

bool PlotX::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

bool PlotX::unload() {}


ll::mod::NativeMod& PlotX::getSelf() const { return mSelf; }


} // namespace plotx

LL_REGISTER_MOD(plotx::PlotX, plotx::PlotX::getInstance());
