#pragma once
#include "plotx/Global.hpp"
#include "plotx/math/WorldPos.hpp"
#include <vector>


namespace plotx {


class PlotAABB {
public:
    WorldPos min{}, max{};

    PlotAABB() = default;
    PXAPI explicit PlotAABB(WorldPos const& min, WorldPos const& max);

    PXNDAPI std::string toString() const;

    PXNDAPI WorldPos getMin() const;
    PXNDAPI WorldPos getMax() const;

    /**
     * 检查一个点是否在 AABB 的边上
     */
    PXNDAPI bool isOnEdge(WorldPos const& pos) const;

    /**
     * 检查一个点是否在 AABB 内部
     */
    PXNDAPI bool contains(WorldPos const& pos) const;

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
    PXNDAPI std::vector<WorldPos> getEdges(int y) const;

    PXAPI bool operator==(PlotAABB const& other) const;
};


} // namespace plotx