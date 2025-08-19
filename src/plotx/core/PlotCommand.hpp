#pragma once
#include "plotx/Global.hpp"


namespace plotx {


struct PlotCommand {
    PlotCommand() = delete;

    PXAPI static void setup();
};


} // namespace plotx