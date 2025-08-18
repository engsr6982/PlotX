#pragma once
#include "ll/api/coro/InterruptableSleep.h"
#include "ll/api/event/ListenerBase.h"
#include "mc/deps/core/math/Vec3.h"
#include "mc/platform/UUID.h"
#include "mc/world/actor/player/Player.h"
#include <unordered_map>
#include <vector>


namespace plotx {

class PlotCoord;

/**
 * @brief 事件驱动
 * @note 驱动地皮的进出事件
 */
class PlotEventDriven {
    std::unordered_map<mce::UUID, int>            dimids_{};
    std::unordered_map<mce::UUID, PlotCoord>      coords_{};
    std::vector<Player*>                          players_{};
    ll::event::ListenerPtr                        connectListener_{nullptr};
    ll::event::ListenerPtr                        disconnectListener_{nullptr};
    std::shared_ptr<ll::coro::InterruptableSleep> sleep_{nullptr};
    std::shared_ptr<std::atomic<bool>>            quit_{nullptr};

public:
    PlotEventDriven();
    ~PlotEventDriven();

    void tick();
    void updateTip(Player* player, Vec3 const& pos, PlotCoord const& coord) const;
};


} // namespace plotx