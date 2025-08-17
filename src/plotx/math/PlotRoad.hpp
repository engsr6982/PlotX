#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/Concepts.hpp"
#include "plotx/math/PlotAABB.hpp"
#include "plotx/math/WorldDirection.hpp"
#include "plotx/math/WorldPos.hpp"


namespace plotx {


class PlotRoad : public PlotAABB {
public:
    int  x{}, z{};        // 坐标可能重复(因为非正方形无法使用xz准确表示)
    bool isTransverse_{}; // 是否横向 (道路有横向和纵向，以面朝东方x±为准，横向为 z±, 纵向为 x±)
    bool valid_{false};   // 是否有效

    PlotRoad() = default;
    PXAPI explicit PlotRoad(int x, int z, bool isTransverse);

    PXAPI explicit PlotRoad(WorldPos const& pos);

    template <HasXYZ_v T>
    explicit PlotRoad(T const& pos) : PlotRoad(WorldPos{pos}) {}

    /**
     * @brief 是否横向
     */
    PXNDAPI bool isTransverse() const;

    /**
     * @brief 是否纵向
     */
    PXNDAPI bool isLongitudinal() const;

    /**
     * @brief 获取世界方向
     * @note 以面朝东方为准，看到的横向道路为 East, 纵向为 South
     */
    PXNDAPI WorldDirection getWorldDirection() const;

    PXNDAPI std::string toString() const;

    PXAPI bool operator==(PlotRoad const& other) const;
};


} // namespace plotx