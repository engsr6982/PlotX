#pragma once
#include "mc/deps/ecs/WeakEntityRef.h"
#include "mc/deps/ecs/gamerefs_entity/EntityContext.h"
#include "mc/deps/game_refs/WeakRef.h"
#include "mc/platform/UUID.h"
#include "mc/server/ServerPlayer.h"
#include "mc/world/actor/player/Player.h"
#include "plotx/script/api/minecraft/defs.hpp"
#include "qjspp/Binding.hpp"
#include "qjspp/JsEngine.hpp"
#include "qjspp/JsScope.hpp"
#include "qjspp/Values.hpp"
#include <memory>

#include "qjspp/TypeConverter.hpp"

// forward declarations
namespace plotx::script::api::inline minecraft {
extern qjspp::ClassDefine const PlayerDef_;
extern qjspp::ClassDefine const UUIDDef_;
extern qjspp::ClassDefine const BlockPosDef_;
extern qjspp::ClassDefine const Vec3Def_;
} // namespace plotx::script::api::inline minecraft

namespace plotx::script {

inline qjspp::Object newInstanceOfGameWeak(qjspp::ClassDefine const& def, Player* player) {
    auto& engine = qjspp::JsScope::currentEngineChecked();
    struct Control {
        WeakRef<EntityContext> player_;
        explicit Control(Player* pl) : player_{pl->getWeakEntity()} {}
    };
    auto control = std::make_unique<Control>(player);
    auto wrap    = qjspp::WrappedResource::make(
        control.release(),
        [](void* res) -> void* {
            auto control = static_cast<Control*>(res);
            auto player  = control->player_.tryUnwrap<Player>();
            if (player) return static_cast<void*>(player);
            return nullptr;
        },
        [](void*) -> void {
            // The game weak ref is not owned by the engine, so we don't need to do anything
        }
    );
    return engine.newInstance(def, std::move(wrap));
}

} // namespace plotx::script


namespace qjspp {


template <>
struct TypeConverter<Player> {
    static Value toJs(Player* player) {
        return plotx::script::newInstanceOfGameWeak(plotx::script::api::PlayerDef_, player);
    }
    static Value toJs(Player& player) { return toJs(&player); }

    static Player* toCpp(Value const& value) {
        if (!value.isObject()) {
            return nullptr;
        }
        return JsScope::currentEngineChecked().getNativeInstanceOf<Player>(
            value.asObject(),
            plotx::script::api::PlayerDef_
        );
    }
};
static_assert(internal::IsTypeConverterAvailable_v<Player>);


template <>
struct TypeConverter<ServerPlayer> : TypeConverter<Player> {};
static_assert(internal::IsTypeConverterAvailable_v<ServerPlayer>);

template <>
struct TypeConverter<mce::UUID> {
    static Value toJs(mce::UUID uuid) { // 值传递，创建一个副本
        auto unique = std::make_unique<mce::UUID>(uuid);
        return JsScope::currentEngineChecked().newInstanceOfUnique(plotx::script::api::UUIDDef_, std::move(unique));
    }

    static mce::UUID* toCpp(Value const& value) {
        if (!value.isObject()) {
            return nullptr;
        }
        return JsScope::currentEngineChecked().getNativeInstanceOf<mce::UUID>(
            value.asObject(),
            plotx::script::api::UUIDDef_
        );
    }
};
static_assert(internal::IsTypeConverterAvailable_v<mce::UUID>);


template <>
struct TypeConverter<Vec3> {
    static Value toJs(Vec3 vec) {
        return JsScope::currentEngineChecked().newInstanceOfRaw(
            plotx::script::api::Vec3Def_,
            new Vec3(vec.x, vec.y, vec.z)
        );
    }
    static Vec3* toCpp(Value const& value) {
        if (!value.isObject()) {
            return nullptr;
        }
        return JsScope::currentEngineChecked().getNativeInstanceOf<Vec3>(
            value.asObject(),
            plotx::script::api::Vec3Def_
        );
    }
};

} // namespace qjspp