#pragma once

#include "ll/api/mod/NativeMod.h"
#include "plotx/Global.hpp"
#include <filesystem>
#include <string_view>

namespace plotx {

class PlotX {
    PlotX();

public:
    static PlotX& getInstance();

    bool load();

    bool enable();

    bool disable();

    [[nodiscard]] ll::mod::NativeMod& getSelf() const;

    PXNDAPI std::filesystem::path getConfigPath() const;
    PXAPI void                    loadConfig() const;
    PXAPI void                    saveConfig() const;

private:
    static constexpr std::string_view ConfigFileName = "config.json";

    ll::mod::NativeMod& mSelf;
};

} // namespace plotx
