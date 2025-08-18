#pragma once
#include "plotx/events/IPlayerOnPlotMoveEvent.hpp"


namespace plotx::event {


class PlayerLeavePlotEvent final : public IPlayerOnPlotMoveEvent {
public:
    explicit PlayerLeavePlotEvent(
        Player*          player,
        Vec3 const&      currentPos,
        int const&       currentDimId,
        PlotCoord const& currentPlotCoord,
        int const&       lastDimId,
        PlotCoord const& lastPlotCoord
    );
};


} // namespace plotx::event