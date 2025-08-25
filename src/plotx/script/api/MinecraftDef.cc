#include "MinecraftDef.hpp"
#include "ll/api/service/Bedrock.h"
#include "mc/platform/UUID.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/level/Level.h"
#include "plotx/script/api/Helper.hpp"
#include "qjspp/Binding.hpp"
#include <string>


#include "Helper.hpp"

namespace plotx::script {


qjspp::ClassDefine const PlayerDef_ =
    qjspp::defineClass<Player>("Player")
        .disableConstructor()
        .instanceProperty(
            "uuid",
            [](void* inst, qjspp::Arguments const& args) {
                return args.engine()->newInstanceOfView(
                    UUIDDef_,
                    const_cast<mce::UUID*>(&static_cast<Player*>(inst)->getUuid()),
                    args.thiz() // 关联生命周期
                );
            }
        )
        .instanceProperty(
            "realName",
            [](void* inst, qjspp::Arguments const&) { return qjspp::String{static_cast<Player*>(inst)->getRealName()}; }
        )
        .instanceMethod("sendMessage", &Player::sendMessage)
        .instanceMethod("isOperator", &Player::isOperator)
        .instanceMethod("getLocaleCode", &Player::getLocaleCode)
        .build();


qjspp::ClassDefine const UUIDDef_ = qjspp::defineClass<mce::UUID>("UUID")
                                        .constructor<std::string const&>()
                                        .instanceMethod("asString", &mce::UUID::asString)
                                        .function("canParse", &mce::UUID::canParse)
                                        .function("fromString", &mce::UUID::fromString)
                                        .build();


} // namespace plotx::script