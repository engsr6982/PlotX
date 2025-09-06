#include "PlotCommand.hpp"

#include "ll/api/Expected.h"
#include "ll/api/command/Command.h"
#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "ll/api/command/Overload.h"

#include "mc/server/commands/CommandOrigin.h"
#include "mc/server/commands/CommandOutput.h"
#include "mc/world/level/block/VanillaBlockTypeIds.h"
#include "mc/world/level/block/registry/BlockTypeRegistry.h"

#include "plotx/core/PlotEventDriven.hpp"
#include "plotx/infra/Config.hpp"
#include "plotx/math/PlotCoord.hpp"
#include "plotx/math/PlotCross.hpp"
#include "plotx/math/PlotRoad.hpp"


namespace plotx {

void InstallDebugSubCommands(ll::command::CommandHandle& handle);

void PlotCommand::setup() {
    auto& cmd = ll::command::CommandRegistrar::getInstance().getOrCreateCommand("plotx", "PlotX Command");


#ifdef PLOTX_DEBUG
    InstallDebugSubCommands(cmd);
#endif
}

// Impl
void InstallDebugSubCommands(ll::command::CommandHandle& handle) {
    handle.overload().text("dbg").text("fill").execute([](CommandOrigin const& origin, CommandOutput& output) {
        if (origin.getOriginType() != CommandOriginType::Player) {
            output.error("This command can only be run by a player");
            return;
        }
        auto& player = *static_cast<Player*>(origin.getEntity());
        auto& pos    = player.getPosition();

        auto& block = BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::GoldBlock());

        if (auto coord = PlotCoord{pos}; coord.isValid()) {
            coord.fillLayer(gConfig_.generator.generatorHeight, block);
            output.success("Filled plot at {}", coord.toString());

        } else if (auto road = PlotRoad{pos}; road.isValid()) {
            road.fillLayer(gConfig_.generator.generatorHeight, block);
            output.success("Filled road at {}", road.toString());

        } else if (auto cross = PlotCross{pos}; cross.isValid()) {
            cross.fillLayer(gConfig_.generator.generatorHeight, block);
            output.success("Filled cross at {}", cross.toString());

        } else {
            output.error("Not in a plot");
        }
    });

    handle.overload().text("dbg").text("removeBorder").execute([](CommandOrigin const& origin, CommandOutput& output) {
        if (origin.getOriginType() != CommandOriginType::Player) {
            output.error("This command can only be run by a player");
            return;
        }
        auto& player = *static_cast<Player*>(origin.getEntity());
        auto& pos    = player.getPosition();

        auto coord = PlotCoord{pos};
        if (!coord.isValid()) {
            output.error("Not in a plot");
            return;
        }
        coord.removeBorder();
    });

    handle.overload().text("dbg").text("tryFixBorder").execute([](CommandOrigin const& origin, CommandOutput& output) {
        if (origin.getOriginType() != CommandOriginType::Player) {
            output.error("This command can only be run by a player");
            return;
        }
        auto& player = *static_cast<Player*>(origin.getEntity());
        auto& pos    = player.getPosition();

        auto coord = PlotCoord{pos};
        if (!coord.isValid()) {
            output.error("Not in a plot");
            return;
        }
        coord.tryFixBorder();
    });

    handle.overload()
        .text("dbg")
        .text("removeNeighbourBorder")
        .execute([](CommandOrigin const& origin, CommandOutput& output) {
            if (origin.getOriginType() != CommandOriginType::Player) {
                output.error("This command can only be run by a player");
                return;
            }
            auto& player = *static_cast<Player*>(origin.getEntity());
            auto& pos    = player.getPosition();

            auto road = PlotRoad{pos};
            if (!road.isValid()) {
                output.error("Not in a road");
                return;
            }
            road.removeNeighbourBorder();
        });
}


} // namespace plotx