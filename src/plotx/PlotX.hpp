#pragma once

#include "ll/api/mod/NativeMod.h"
#include <filesystem>
#include <string_view>

#include "plotx/Global.hpp"
#include "plotx/core/PlotEventDriven.hpp"

namespace plotx {

class PlotX {
    PlotX();

public:
    bool load();

    bool enable();

    bool disable();

    [[nodiscard]] ll::mod::NativeMod& getSelf() const;

    PXAPI static PlotX& getInstance();

    PXNDAPI std::filesystem::path getConfigPath() const;
    PXAPI void                    loadConfig() const;
    PXAPI void                    saveConfig() const;

    PXNDAPI static int getDimensionId();

private:
    static constexpr std::string_view ConfigFileName = "config.json";
    static constexpr std::string_view DimensionName  = "plotx";

    ll::mod::NativeMod&              self_;
    std::unique_ptr<PlotEventDriven> plotEventDriven_;
};

} // namespace plotx
