#include "PlotCross.hpp"
#include "plotx/generator/Helper.hpp"
#include "plotx/infra/Config.hpp"
#include "plotx/math/PlotAABB.hpp"
#include <cmath>


namespace plotx {


PlotCross::PlotCross(int x, int z) : x(x), z(z) {
    auto const& cfg       = gConfig_.generator;
    int const&  roadWidth = cfg.roadWidth;

    int total = cfg.plotWidth + roadWidth;

    min = BlockPos{
        x * total + cfg.plotWidth,
        generator::WorldMinHeight,
        z * total + cfg.plotWidth,
    };
    max = BlockPos{
        min.x + roadWidth - 1,
        generator::WorldMaxHeight,
        min.z + roadWidth - 1,
    };
    valid_ = true;
}

PlotCross::PlotCross(BlockPos const& pos) {
    auto const& cfg       = gConfig_.generator;
    int const&  roadWidth = cfg.roadWidth;

    int total = cfg.plotWidth + roadWidth;

    auto dx = static_cast<double>(pos.x);
    auto dz = static_cast<double>(pos.z);

    // 计算全局坐标在哪个大区域内
    x = static_cast<int>(std::floor(dx / total));
    z = static_cast<int>(std::floor(dz / total));

    // 计算在大区域内的局部坐标
    int localX = static_cast<int>(std::floor(dx)) - (x * total);
    int localZ = static_cast<int>(std::floor(dz)) - (z * total);

    if (localX < cfg.plotWidth || localX > total - 1 || localZ < cfg.plotWidth || localZ > total - 1) {
        valid_ = false;
        x      = 0;
        z      = 0;
        return;
    }

    min = BlockPos{
        x * total + cfg.plotWidth,
        generator::WorldMinHeight,
        z * total + cfg.plotWidth,
    };
    max = BlockPos{
        min.x + roadWidth - 1,
        generator::WorldMaxHeight,
        min.z + roadWidth - 1,
    };
    valid_ = true;
}


std::string PlotCross::toString() const { return fmt::format("PlotCross({},{})\n{}", x, z, PlotAABB::toString()); }

bool PlotCross::isValid() const { return valid_; }

bool PlotCross::operator==(PlotCross const& other) const {
    return other.x == x && other.z == z && PlotAABB::operator==(other);
}


} // namespace plotx