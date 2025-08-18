#include "PlotRoad.hpp"
#include "fmt/color.h"
#include "plotx/generator/Helper.hpp"
#include "plotx/infra/Config.hpp"
#include "plotx/math/PlotAABB.hpp"
#include "plotx/math/WorldDirection.hpp"
#include <cmath>


namespace plotx {


PlotRoad::PlotRoad(int x, int z, bool isTransverse) : x(x), z(z), isTransverse_(isTransverse) {
    auto const& cfg = gConfig_.generator;

    int total = cfg.plotWidth + cfg.roadWidth;
    if (isTransverse_) {
        // 横向面朝东方
        min = BlockPos{x * total + cfg.plotWidth, generator::WorldMinHeight, z * total};
        max = BlockPos{min.x + cfg.roadWidth - 1, generator::WorldMaxHeight, min.z + cfg.plotWidth - 1};
    } else {
        // 纵向面朝南方
        min = BlockPos{x * total, generator::WorldMinHeight, z * total + cfg.plotWidth};
        max = BlockPos{min.x + cfg.plotWidth - 1, generator::WorldMaxHeight, min.z + cfg.plotWidth - 1};
    }
    valid_ = true;
}

PlotRoad::PlotRoad(BlockPos const& pos) {
    auto const& cfg = gConfig_.generator;

    int total = cfg.plotWidth + cfg.roadWidth;

    x = static_cast<int>(std::floor(pos.x / total));
    z = static_cast<int>(std::floor(pos.z / total));

    double localX = std::fmod(pos.x, total);
    double localZ = std::fmod(pos.z, total);
    if (localX < 0) localX += total;
    if (localZ < 0) localZ += total;

    if (localX >= cfg.plotWidth && localX < total && localZ < cfg.plotWidth) {
        // 纵向道路
        min = BlockPos{x * total + cfg.plotWidth, generator::WorldMinHeight, z * total};
        max = BlockPos{min.x + cfg.roadWidth - 1, generator::WorldMaxHeight, min.z + cfg.plotWidth - 1};

    } else if (localZ >= cfg.plotWidth && localZ < total && localX < cfg.plotWidth) {
        // 横向道路
        min = BlockPos{x * total, generator::WorldMinHeight, z * total + cfg.plotWidth};
        max = BlockPos{min.x + cfg.plotWidth - 1, generator::WorldMaxHeight, min.z + cfg.roadWidth - 1};

    } else {
        // 不在道路上
        valid_ = false;
        x      = 0;
        z      = 0;
    }
}


bool PlotRoad::isTransverse() const { return isTransverse_; }

bool PlotRoad::isLongitudinal() const { return !isTransverse_; }

WorldDirection PlotRoad::getWorldDirection() const {
    return isTransverse_ ? WorldDirection::East : WorldDirection::South;
}

std::string PlotRoad::toString() const {
    static constexpr auto EastStr  = "East";
    static constexpr auto SouthStr = "South";
    return fmt::format("{}({}, {})\n{}", isTransverse_ ? EastStr : SouthStr, x, z, PlotAABB ::toString());
}

bool PlotRoad::isValid() const { return valid_; }

bool PlotRoad::operator==(PlotRoad const& other) const {
    return x == other.x && z == other.z && isTransverse_ == other.isTransverse_ && PlotAABB::operator==(other);
}


} // namespace plotx