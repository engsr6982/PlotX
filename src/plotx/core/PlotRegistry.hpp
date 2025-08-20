#pragma once
#include "ll/api/data/KeyValueDB.h"
#include "ll/api/io/Logger.h"
#include "mc/platform/UUID.h"
#include "plotx/Global.hpp"
#include "plotx/core/PlotHandle.hpp"
#include "plotx/infra/IntEncoder.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace plotx {

class PlotX;

// 地皮注册表
class PlotRegistry final {
    std::unique_ptr<ll::data::KeyValueDB>                      db_;     // 数据库
    std::vector<std::string>                                   admins_; // 管理员
    std::unordered_map<EncodedID, std::shared_ptr<PlotHandle>> plots_;  // 地皮
    mutable std::shared_mutex                                  mutex_;  // 读写锁

    void _upgradeDatabase(ll::io::Logger& logger);
    void _loadAdmins(ll::io::Logger& logger);
    void _loadPlots(ll::io::Logger& logger);

public:
    PLOTX_DISALLOW_COPY_AND_MOVE(PlotRegistry);
    explicit PlotRegistry(PlotX& plotx);
    ~PlotRegistry();

    PXAPI bool isAdmin(mce::UUID const& uuid) const;
    PXAPI bool isAdmin(std::string const& uuid) const;

    PXAPI void addAdmin(mce::UUID const& uuid);
    PXAPI void removeAdmin(mce::UUID const& uuid);


public:
    static constexpr std::string_view VersionKey    = "_version_"; // 版本号
    static constexpr std::string_view AdminsKey     = "admins";    // 管理员
    static constexpr std::string_view PlotKeyPrefix = "plot_";     // 地皮
};


} // namespace plotx