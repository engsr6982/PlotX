#include "PlotX.hpp"

#include "ll/api/Config.h"
#include "ll/api/mod/RegisterHelper.h"
#include "plotx/infra/Config.hpp"
#include <filesystem>

namespace plotx {

PlotX::PlotX() : mSelf(*ll::mod::NativeMod::current()) {}
PlotX& PlotX::getInstance() {
    static PlotX instance;
    return instance;
}

bool PlotX::load() {
    loadConfig();

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


ll::mod::NativeMod& PlotX::getSelf() const { return mSelf; }

std::filesystem::path PlotX::getConfigPath() const { return getSelf().getConfigDir() / ConfigFileName; }

void PlotX::loadConfig() const {
    auto path = getConfigPath();
    if (!std::filesystem::exists(path) || !ll::config::loadConfig(gConfig_, path)) {
        saveConfig();
    }
}
void PlotX::saveConfig() const {
    auto path = getConfigPath();
    if (!ll::config::saveConfig(gConfig_, path)) {
        getSelf().getLogger().error("Failed to save config to {}", path);
    }
}


} // namespace plotx

LL_REGISTER_MOD(plotx::PlotX, plotx::PlotX::getInstance());
