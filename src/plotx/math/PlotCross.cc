#include "PlotCross.hpp"
#include "plotx/generator/Helper.hpp"
#include "plotx/infra/Config.hpp"
#include "plotx/math/PlotAABB.hpp"
#include "plotx/math/WorldPos.hpp"
#include <cmath>


namespace plotx {


PlotCross::PlotCross(int x, int z) : x(x), z(z) {
    auto const& cfg       = gConfig_.generator;
    int const&  roadWidth = cfg.roadWidth;

    int total = cfg.plotWidth + roadWidth;

    min = WorldPos{
        x * total + cfg.plotWidth,
        generator::WorldMinHeight,
        z * total + cfg.plotWidth,
    };
    max = WorldPos{
        min.x + roadWidth - 1,
        generator::WorldMaxHeight,
        min.z + roadWidth - 1,
    };
    valid_ = true;
}

PlotCross::PlotCross(WorldPos const& pos) {
    auto const& cfg       = gConfig_.generator;
    int const&  roadWidth = cfg.roadWidth;

    int total = cfg.plotWidth + roadWidth;

    x = static_cast<int>(std::floor(pos.x / total));
    z = static_cast<int>(std::floor(pos.z / total));

    // 计算 min 和 max
    int localX = (int)std::floor(pos.x) - (x * total);
    int localZ = (int)std::floor(pos.z) - (z * total);

    if (localX < cfg.plotWidth || localX > total - 1 || localZ < cfg.plotWidth || localZ > total - 1) {
        valid_ = false;
        x      = 0;
        z      = 0;
        return;
    }

    min = WorldPos{
        x * total + cfg.plotWidth,
        generator::WorldMinHeight,
        z * total + cfg.plotWidth,
    };
    max = WorldPos{
        min.x + roadWidth - 1,
        generator::WorldMaxHeight,
        min.z + roadWidth - 1,
    };
    valid_ = true;
}


std::string PlotCross::toString() const { return fmt::format("PlotCross({},{})\n{}", x, z, PlotAABB::toString()); }

bool PlotCross::operator==(PlotCross const& other) const {
    return other.x == x && other.z == z && PlotAABB::operator==(other);
}


} // namespace plotx