#include "ll/api/form/ModalForm.h"
#include "plotx/script/api/Helper.hpp"
#include "plotx/script/api/levilamina/defs.hpp"


namespace plotx::script::api::inline levilamina {

using namespace ll::form;

qjspp::ClassDefine const ModalFormDef_ = qjspp::defineClass<ModalForm>("ModalForm")
                                             .constructor<>()
                                             .instanceMethod("setTitle", &ModalForm::setTitle)
                                             .instanceMethod("setContent", &ModalForm::setContent)
                                             .instanceMethod("setUpperButton", &ModalForm::setUpperButton)
                                             .instanceMethod("setLowerButton", &ModalForm::setLowerButton)
                                             .instanceMethod("sendTo", &ModalForm::sendTo)
                                             .instanceMethod("sendUpdate", &ModalForm::sendUpdate)
                                             .build();

} // namespace plotx::script::api::inline levilamina