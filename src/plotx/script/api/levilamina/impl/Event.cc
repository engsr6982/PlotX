#include "ll/api/event/Event.h"
#include "ll/api/event/Cancellable.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/EventId.h"
#include "ll/api/event/ListenerBase.h"
#include "ll/api/event/player/PlayerJoinEvent.h"
#include "plotx/PlotX.hpp"
#include "plotx/script/api/Helper.hpp"
#include "plotx/script/api/levilamina/defs.hpp"
#include "qjspp/Definitions.hpp"
#include "qjspp/JsScope.hpp"
#include "qjspp/Values.hpp"
#include <string>


namespace plotx::script::api::inline levilamina {


qjspp::EnumDefine const EventPriorityDef_ = qjspp::defineEnum<ll::event::EventPriority>("EventPriority")
                                                .value("Highest", ll::event::EventPriority::Highest)
                                                .value("High", ll::event::EventPriority::High)
                                                .value("Normal", ll::event::EventPriority::Normal)
                                                .value("Low", ll::event::EventPriority::Low)
                                                .value("Lowest", ll::event::EventPriority::Lowest)
                                                .build();

qjspp::ClassDefine const EventDef_ =
    qjspp::defineClass<ll::event::Event>("Event")
        .disableConstructor()
        .instanceMethod(
            "getId",
            [](void* inst, qjspp::Arguments const&) -> qjspp::Value {
                return qjspp::String{static_cast<ll::event::Event*>(inst)->getId().name};
            }
        )
        .build();


using CancellableEventCRTP                    = ll::event::Cancellable<ll::event::Event>; // CRTP
qjspp::ClassDefine const CancellableEventDef_ = qjspp::defineClass<CancellableEventCRTP>("CancellableEvent")
                                                    .disableConstructor()
                                                    .extends(EventDef_)
                                                    .instanceMethod("isCancelled", &CancellableEventCRTP::isCancelled)
                                                    .instanceMethod("setCancelled", &CancellableEventCRTP::setCancelled)
                                                    .instanceMethod("cancel", &CancellableEventCRTP::cancel)
                                                    .build();

qjspp::ClassDefine const PlayerJoinEventDef_ = qjspp::defineClass<ll::event::PlayerJoinEvent>("PlayerJoinEvent")
                                                   .disableConstructor()
                                                   .extends(CancellableEventDef_)
                                                   .instanceMethod("self", &ll::event::PlayerJoinEvent::self)
                                                   .build();


#define GET_EVENT_BUS() ll::event::EventBus::getInstance()
qjspp::ClassDefine const EventBusDef_ =
    qjspp::defineClass<void>("EventBus")
        .function(
            "emplaceListener",
            [](qjspp::Arguments const& args) -> qjspp::Value {
                auto argc = args.length();
                if (argc < 2 || argc > 3) {
                    throw qjspp::JsException{qjspp::JsException::Type::SyntaxError, "Invalid number of arguments"};
                }
                if (!args[0].isString()) {
                    throw qjspp::JsException{qjspp::JsException::Type::TypeError, "Invalid event name"};
                }
                if (!args[1].isFunction()) {
                    throw qjspp::JsException{qjspp::JsException::Type::TypeError, "Invalid callback function"};
                }
                if (argc == 3 && !args[2].isNumber()) {
                    throw qjspp::JsException{qjspp::JsException::Type::TypeError, "Invalid listener priority"};
                }

                auto listener = ll::event::ListenerPtr{nullptr};
                auto scoped   = qjspp::ScopedValue{args.engine(), args[1]};
                auto name     = args[0].asString().value();

                if (name == "PlayerJoinEvent") {
                    listener = GET_EVENT_BUS().emplaceListener<ll::event::PlayerJoinEvent>(
                        [sc = std::move(scoped)](ll::event::PlayerJoinEvent& ev) {
                            auto           engine = sc.engine();
                            qjspp::JsScope lock{engine};

                            auto cb = sc.value().asFunction();
                            try {
                                cb.call({}, {engine->newInstanceOfView(PlayerJoinEventDef_, &ev)});
                            } catch (qjspp::JsException const& e) {
                                PlotX::getInstance().getSelf().getLogger().error(
                                    "[Scripting] Error while handling PlayerJoinEvent: {}\n{}",
                                    e.what(),
                                    e.stacktrace()
                                );
                            }
                        },
                        argc == 3 ? static_cast<ll::event::EventPriority>(args[2].asNumber().getInt32())
                                  : ll::event::EventPriority::Normal
                    );
                } else if (name == "PlayerLeaveEvent") {
                }

                return qjspp::Number{static_cast<int>(listener->getId())};
            }
        )
        .function(
            "removeListener",
            [](qjspp::Arguments const& args) -> qjspp::Value {
                auto argc = args.length();
                if (argc != 1) {
                    throw qjspp::JsException{qjspp::JsException::Type::SyntaxError, "Invalid number of arguments"};
                }
                if (!args[0].isNumber()) {
                    throw qjspp::JsException{qjspp::JsException::Type::TypeError, "Invalid listener id"};
                }
                auto ret = GET_EVENT_BUS().removeListener(args[0].asNumber().getInt32());
                return qjspp::Boolean{ret};
            }
        )
        .function("publish", [](qjspp::Arguments const& args) -> qjspp::Value { return {}; })
        .build();


} // namespace plotx::script::api::inline levilamina