#pragma once
#include "plotx/events/IPlayerOnPlotMoveEvent.hpp"


namespace plotx::event {


class PlayerEnterPlotEvent final : public IPlayerOnPlotMoveEvent {
public:
    explicit PlayerEnterPlotEvent(
        Player*          player,
        Vec3 const&      currentPos,
        int const&       currentDimId,
        PlotCoord const& currentPlotCoord,
        int const&       lastDimId,
        PlotCoord const& lastPlotCoord
    );
};


} // namespace plotx::event