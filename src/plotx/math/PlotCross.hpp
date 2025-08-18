#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/Concepts.hpp"
#include "plotx/math/PlotAABB.hpp"


namespace plotx {


/**
 * 地皮路口
 */
class PlotCross : public PlotAABB {
public:
    int  x{}, z{};
    bool valid_ = false;

    PlotCross() = default;
    PXAPI explicit PlotCross(int x, int z);
    PXAPI explicit PlotCross(BlockPos const& pos);

    PXNDAPI std::string toString() const;

    PXNDAPI bool isValid() const;

    PXAPI bool operator==(PlotCross const& other) const;
};


} // namespace plotx