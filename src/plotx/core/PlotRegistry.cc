#include "PlotRegistry.hpp"
#include "ll/api/data/KeyValueDB.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "plotx/PlotX.hpp"
#include "plotx/core/PlotHandle.hpp"
#include "plotx/core/PlotRegistry.hpp"
#include "plotx/data/StorageStructure.hpp"
#include "plotx/infra/IntEncoder.hpp"
#include "plotx/infra/Reflection.hpp"
#include <algorithm>
#include <filesystem>
#include <mutex>
#include <shared_mutex>
#include <string>


namespace plotx {


PlotRegistry::PlotRegistry(PlotX& plotx) {
    auto& logger = plotx.getSelf().getLogger();
    auto  dir    = plotx.getDatabasePath();
    bool  isNew  = !std::filesystem::exists(dir);

    std::unique_lock<std::shared_mutex> lock{mutex_};
    db_ = std::make_unique<ll::data::KeyValueDB>(dir);
    if (isNew) {
        db_->set(VersionKey, std::to_string(PlotRecordVersion));
    }

    if (!db_->has(VersionKey)) {
        throw std::runtime_error("PlotRegistry: Invalid database version");
    }

    auto version = std::stoi(*db_->get(VersionKey));
    if (version > PlotRecordVersion) {
        throw std::runtime_error("PlotRegistry: Database version is newer than supported");
    }

    if (version < PlotRecordVersion) {
        _upgradeDatabase(logger);
    }

    _loadAdmins(logger);
    _loadPlots(logger);
}

PlotRegistry::~PlotRegistry() {}


void PlotRegistry::_upgradeDatabase(ll::io::Logger& logger) {
    db_->set(VersionKey, std::to_string(PlotRecordVersion));
    // TODO: Implement database upgrade
}

void PlotRegistry::_loadAdmins(ll::io::Logger& logger) {
    auto admins = db_->get(AdminsKey);
    if (!admins) {
        logger.info("No admins found in database");
        return;
    }

    auto parsed = nlohmann::json::parse(*admins);
    reflection::json2struct(admins_, parsed);

    logger.info("Loaded {} admins from database", admins_.size());
}

void PlotRegistry::_loadPlots(ll::io::Logger& logger) {
    for (auto const& [k, v] : db_->iter()) {
        if (!k.starts_with(PlotKeyPrefix)) {
            continue;
        }

        auto json = nlohmann::json::parse(v);
        auto ptr  = PlotHandle::load(json);
        if (!ptr) {
            logger.error("Failed to load plot from database: {}", k);
            continue;
        }

        plots_.emplace(IntEncoder::encode(ptr->getCoord().x, ptr->getCoord().z), std::move(ptr));
    }

    logger.info("Loaded {} plots from database", plots_.size());
}


bool PlotRegistry::isAdmin(mce::UUID const& uuid) const { return isAdmin(uuid.asString()); }
bool PlotRegistry::isAdmin(std::string const& uuid) const {
    std::shared_lock<std::shared_mutex> lock{mutex_};
    return std::find(admins_.begin(), admins_.end(), uuid) != admins_.end();
}

void PlotRegistry::addAdmin(mce::UUID const& uuid) {
    if (isAdmin(uuid)) {
        return;
    }
    std::unique_lock<std::shared_mutex> lock{mutex_};
    admins_.emplace_back(uuid.asString());
}
void PlotRegistry::removeAdmin(mce::UUID const& uuid) {
    if (!isAdmin(uuid)) {
        return;
    }
    std::unique_lock<std::shared_mutex> lock{mutex_};
    admins_.erase(std::remove(admins_.begin(), admins_.end(), uuid.asString()), admins_.end());
}


} // namespace plotx