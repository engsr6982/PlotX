#pragma once
#include "plotx/Global.hpp"
#include "plotx/math/PlotAABB.hpp"

namespace plotx {


class PlotCoord : public PlotAABB {
public:
    int  x{}, z{};      // x, z 坐标
    bool valid_{false}; // 是否有效

    PlotCoord() = default;
    PXAPI explicit PlotCoord(int x, int z);
    PXAPI explicit PlotCoord(BlockPos const& pos);

    PXNDAPI std::string toString() const;

    PXNDAPI bool isValid() const;

    /**
     * 尝试修正边框(修复边框方块缺失)
     */
    PXAPI void tryFixBorder() const;

    /**
     * 删除边框
     */
    PXAPI void removeBorder() const;

    /**
     * 移除地皮边框的4个角
     */
    PXAPI void removeBorderCorners() const;

    PXAPI bool operator==(PlotCoord const& pos) const;
};


} // namespace plotx