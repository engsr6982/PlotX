#include "ModuleDef.hpp"
#include "plotx/script/api/MinecraftDef.hpp"
#include "plotx/script/api/PlotXDef.hpp"
#include "qjspp/Module.hpp"

#include "LeviLaminaDef.hpp"

namespace plotx::script {


qjspp::ModuleDefine const& GetLeviLaminaModuleDef() {
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
    static auto def = qjspp::defineModule("minecraft")
                          .exportClass(PlayerDef_)
                          .exportClass(UUIDDef_)
                          .build();
    return def;
}

qjspp::ModuleDefine const& GetPlotXModuleDef() {
    static auto def = qjspp::defineModule("plotx").exportClass(LoggerDef_).build();
    return def;
}


} // namespace plotx::script