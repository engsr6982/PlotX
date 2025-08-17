#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/Concepts.hpp"
#include "plotx/math/PlotAABB.hpp"
#include "plotx/math/WorldPos.hpp"


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
    PXAPI explicit PlotCross(WorldPos const& pos);

    template <HasXYZ_v T>
    explicit PlotCross(T const& pos) : PlotCross(WorldPos{pos}) {}

    PXNDAPI std::string toString() const;

    PXAPI bool operator==(PlotCross const& other) const;
};


} // namespace plotx