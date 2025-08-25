#include "PlotX.hpp"

#include "ll/api/Config.h"
#include "ll/api/i18n/I18n.h"
#include "ll/api/io/LogLevel.h"
#include "ll/api/mod/RegisterHelper.h"
#include "plotx/core/PlotEventDriven.hpp"
#include "plotx/core/PlotRegistry.hpp"
#include "plotx/infra/Config.hpp"
#include <filesystem>
#include <memory>

#include "plotx/core/PlotCommand.hpp"
#include "plotx/script/InternalEngine.hpp"

namespace plotx {

PlotX::PlotX() : self_(*ll::mod::NativeMod::current()) {}
PlotX& PlotX::getInstance() {
    static PlotX instance;
    return instance;
}

bool PlotX::load() {
    auto& logger = getSelf().getLogger();
#ifdef PLOTX_DEBUG
    logger.setLevel(ll::io::LogLevel::Trace);
#endif

    logger.trace("Try to load i18n");
    if (auto i18n = ll::i18n::getInstance().load(getSelf().getLangDir()); !i18n) {
        logger.error("Failed to load i18n: ");
        i18n.error().log(logger);
    }

    logger.trace("Try to load config");
    loadConfig();

    logger.trace("Initialize PlotRegistry");
    registry_ = std::make_unique<PlotRegistry>(*this);

    logger.trace("Initialize InternalEngine");
    engine_ = std::make_unique<script::InternalEngine>(*this);

    return true;
}

bool PlotX::enable() {
    plotEventDriven_ = std::make_unique<PlotEventDriven>();

    PlotCommand::setup();

    return true;
}

bool PlotX::disable() {
    engine_.reset();

    plotEventDriven_.reset();
    registry_.reset();

    return true;
}


ll::mod::NativeMod& PlotX::getSelf() const { return self_; }

std::filesystem::path PlotX::getConfigPath() const { return getSelf().getConfigDir() / ConfigFileName; }

std::filesystem::path PlotX::getDatabasePath() const { return getSelf().getDataDir() / DatabaseDirName; }

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
