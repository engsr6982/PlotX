#include "PlotX.hpp"

#include "ll/api/Config.h"
#include "ll/api/mod/RegisterHelper.h"
#include "plotx/core/PlotEventDriven.hpp"
#include "plotx/infra/Config.hpp"
#include <filesystem>

namespace plotx {

PlotX::PlotX() : self_(*ll::mod::NativeMod::current()) {}
PlotX& PlotX::getInstance() {
    static PlotX instance;
    return instance;
}

bool PlotX::load() {
    loadConfig();

    return true;
}

bool PlotX::enable() {
    plotEventDriven_ = std::make_unique<PlotEventDriven>();

    return true;
}

bool PlotX::disable() {
    plotEventDriven_.reset();

    return true;
}


ll::mod::NativeMod& PlotX::getSelf() const { return self_; }

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

int PlotX::getDimensionId() {
#ifdef PLOTX_OVERWORLD
    return 0;
#else
    // TODO: impl
#endif
}


} // namespace plotx

LL_REGISTER_MOD(plotx::PlotX, plotx::PlotX::getInstance());
