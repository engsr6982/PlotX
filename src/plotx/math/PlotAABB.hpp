#pragma once
#include "mc/world/level/BlockPos.h"
#include "plotx/Global.hpp"
#include <vector>


namespace plotx {


class PlotAABB {
public:
    BlockPos min{}, max{};

    PlotAABB() = default;
    PXAPI explicit PlotAABB(BlockPos const& min, BlockPos const& max);

    PXNDAPI std::string toString() const;

    PXNDAPI BlockPos getMin() const;
    PXNDAPI BlockPos getMax() const;

    /**
     * 检查一个点是否在 AABB 的边上
     */
    PXNDAPI bool isOnEdge(BlockPos const& pos) const;

    /**
     * 检查一个点是否在 AABB 内部
     */
    PXNDAPI bool contains(BlockPos const& pos) const;

    /**
     * 获取AABB的边（平面）
     * 示例（俯视视图）：
     *
     *   z ↑
     *     │  ┌───────┐
     *     │  │       │
     *     │  │       │
     *     │  └───────┘
     *     └───────────────→ x
     */
    PXNDAPI std::vector<BlockPos> getEdges(int y) const;

    PXAPI bool operator==(PlotAABB const& other) const;
};


} // namespace plotx