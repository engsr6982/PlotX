#include "ModuleDef.hpp"
#include "qjspp/Module.hpp"

#include "plotx/script/api/levilamina/defs.hpp"

#include "plotx/script/api/minecraft/defs.hpp"

#include "plotx/script/api/plotx/defs.hpp"

namespace plotx::script {


qjspp::ModuleDefine const& GetLeviLaminaModuleDef() {
    using namespace api::levilamina;
    static auto def = qjspp::defineModule("levilamina")
                          .exportClass(SimpleFormDef_)
                          .exportClass(CustomFormDef_)
                          .exportClass(ModalFormDef_)
                          .exportClass(EventBusDef_)
                          .exportClass(EventDef_)
                          .exportClass(CancellableEventDef_)
                          .exportClass(PlayerJoinEventDef_)
                          .build();
    return def;
}

qjspp::ModuleDefine const& GetMinecraftModuleDef() {
    using namespace api::minecraft;
    static auto def = qjspp::defineModule("minecraft").exportClass(PlayerDef_).exportClass(UUIDDef_).build();
    return def;
}

qjspp::ModuleDefine const& GetPlotXModuleDef() {
    using namespace api::plotx;
    static auto def = qjspp::defineModule("plotx").exportClass(LoggerDef_).build();
    return def;
}


} // namespace plotx::script