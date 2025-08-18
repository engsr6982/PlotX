#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/Concepts.hpp"
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

    PXAPI bool operator==(PlotCoord const& pos) const;
};


} // namespace plotx