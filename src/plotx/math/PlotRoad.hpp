#pragma once
#include "plotx/Global.hpp"
#include "plotx/math/PlotAABB.hpp"


namespace plotx {


class PlotRoad : public PlotAABB {
public:
    int  x{}, z{};        // 坐标可能重复(因为非正方形无法使用xz准确表示)
    bool isTransverse_{}; // 是否横向 (道路有横向和纵向，以面朝东方x±为准，横向为 z±, 纵向为 x±)
    bool valid_{false};   // 是否有效

    PlotRoad() = default;
    PXAPI explicit PlotRoad(int x, int z, bool isTransverse);
    PXAPI explicit PlotRoad(BlockPos const& pos);

    /**
     * @brief 是否横向
     */
    PXNDAPI bool isTransverse() const;

    /**
     * @brief 是否纵向
     */
    PXNDAPI bool isLongitudinal() const;

    PXNDAPI bool isValid() const;

    PXNDAPI std::string toString() const;

    /**
     * 移除道路相邻两边地皮的边框
     */
    PXAPI void removeNeighbourBorder() const;

    PXAPI bool operator==(PlotRoad const& other) const;
};


} // namespace plotx