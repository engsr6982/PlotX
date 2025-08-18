#include "PlotAABB.hpp"
#include "fmt/format.h"
#include <vector>


namespace plotx {


PlotAABB::PlotAABB(BlockPos const& min, BlockPos const& max) : min(min), max(max) {}

std::string PlotAABB::toString() const { return fmt::format("PlotAABB({}, {})", min.toString(), max.toString()); }

BlockPos PlotAABB::getMin() const { return min; }
BlockPos PlotAABB::getMax() const { return max; }

bool PlotAABB::isOnEdge(BlockPos const& pos) const {
    bool onXEdge = pos.x == min.x || pos.x == max.x;
    bool onZEdge = pos.z == min.z || pos.z == max.z;

    bool withinXRange = pos.x >= min.x && pos.x <= max.x;
    bool withinZRange = pos.z >= min.z && pos.z <= max.z;

    return (onXEdge && withinXRange) || (onZEdge && withinZRange);
}

bool PlotAABB::contains(BlockPos const& pos) const {
    return pos.x >= min.x && pos.x <= max.x && pos.z >= min.z && pos.z <= max.z;
}

std::vector<BlockPos> PlotAABB::getEdges(int y) const {
    std::vector<BlockPos> edges;
    for (int x = min.x; x <= max.x; ++x) {
        edges.emplace_back(x, y, min.z);
        edges.emplace_back(x, y, max.z);
    }
    for (int z = min.z + 1; z < max.z; ++z) {
        edges.emplace_back(min.x, y, z);
        edges.emplace_back(max.x, y, z);
    }
    return edges;
}

bool PlotAABB::operator==(PlotAABB const& other) const { return other.min == min && other.max == max; }

} // namespace plotx