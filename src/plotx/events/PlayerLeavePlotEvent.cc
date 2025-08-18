#include "PlayerLeavePlotEvent.hpp"

namespace plotx::event {


PlayerLeavePlotEvent::PlayerLeavePlotEvent(
    Player*          player,
    Vec3 const&      currentPos,
    int const&       currentDimId,
    PlotCoord const& currentPlotCoord,
    int const&       lastDimId,
    PlotCoord const& lastPlotCoord
)
: IPlayerOnPlotMoveEvent(player, currentPos, currentDimId, currentPlotCoord, lastDimId, lastPlotCoord) {}


} // namespace plotx::event