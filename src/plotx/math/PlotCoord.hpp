#pragma once
#include "WorldPos.hpp"
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
    PXAPI explicit PlotCoord(WorldPos const& pos);

    template <HasXYZ_v T>
    explicit PlotCoord(T const& pos) : PlotCoord{WorldPos{pos}} {}

    PXNDAPI std::string toString() const;

    PXAPI bool operator==(PlotCoord const& pos) const;
};


} // namespace plotx