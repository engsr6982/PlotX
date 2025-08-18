#include "PlotCoord.hpp"
#include "fmt/format.h"
#include "plotx/generator/Helper.hpp"
#include "plotx/infra/Config.hpp"
#include "plotx/math/PlotAABB.hpp"
#include <cmath>


namespace plotx {

PlotCoord::PlotCoord(int x, int z) : x(x), z(z) {
    auto const& cfg = gConfig_.generator;

    int total = cfg.plotWidth + cfg.roadWidth;
    min       = BlockPos{x * total, generator::WorldMinHeight, z * total};
    max       = BlockPos{min.x + cfg.plotWidth - 1, generator::WorldMaxHeight, min.z + cfg.plotWidth - 1};
    valid_    = true;
}

PlotCoord::PlotCoord(BlockPos const& pos) {
    auto const& cfg       = gConfig_.generator;
    auto const& plotWidth = cfg.plotWidth;
    auto const& roadWidth = cfg.roadWidth;

    auto const total = cfg.plotWidth + roadWidth;

    // 计算地皮全局坐标
    x = static_cast<int>(std::floor(pos.x / total));
    z = static_cast<int>(std::floor(pos.z / total));

    // 计算地皮范围
    auto localX = static_cast<int>(std::floor(pos.x)) % total;
    auto localZ = static_cast<int>(std::floor(pos.z)) % total;
    if (localX < 0) localX += total;
    if (localZ < 0) localZ += total;

    if (localX >= plotWidth || localZ >= plotWidth) {
        valid_ = false;
        x      = 0;
        z      = 0;
    } else {
        min    = BlockPos{x * total, generator::WorldMinHeight, z * total};
        max    = BlockPos{min.x + plotWidth - 1, generator::WorldMaxHeight, min.z + plotWidth - 1};
        valid_ = true;
    }
}

std::string PlotCoord::toString() const { return fmt::format("PlotCoord({}, {})\n{}", x, z, PlotAABB::toString()); }

bool PlotCoord::operator==(PlotCoord const& pos) const { return pos.x == x && pos.z == z && PlotAABB::operator==(pos); }


} // namespace plotx