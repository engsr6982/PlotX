#include "PlotXDef.hpp"
#include "ll/api/io/Logger.h"
#include "plotx/PlotX.hpp"
#include "qjspp/Values.hpp"


namespace plotx::script {


std::string formatArgs(qjspp::Arguments const& args) {
    static constexpr std::string_view prefix = "[Scripting] ";

    size_t argc = args.length();
    if (argc == 0) {
        return std::string{prefix};
    }

    std::ostringstream oss;
    oss << prefix;
    for (size_t i = 0; i < argc; ++i) {
        auto arg = args[i];
        if (arg.isString()) oss << arg.toString().value();
        else oss << args[i].toString();

        if (i < argc - 1) {
            oss << " ";
        }
    }
    return oss.str();
}
qjspp::Value logImpl(qjspp::Arguments const& args, ll::io::LogLevel level) {
    PlotX::getInstance().getSelf().getLogger().log(level, formatArgs(args));
    return {};
}


qjspp::ClassDefine const LoggerDef_ =
    qjspp::defineClass<void>("logger")
        .function(
            "trace",
            [](qjspp::Arguments const& args) -> qjspp::Value { return logImpl(args, ll::io::LogLevel::Trace); }
        )
        .function(
            "debug",
            [](qjspp::Arguments const& args) -> qjspp::Value { return logImpl(args, ll::io::LogLevel::Debug); }
        )
        .function(
            "info",
            [](qjspp::Arguments const& args) -> qjspp::Value { return logImpl(args, ll::io::LogLevel::Info); }
        )
        .function(
            "warn",
            [](qjspp::Arguments const& args) -> qjspp::Value { return logImpl(args, ll::io::LogLevel::Warn); }
        )
        .function(
            "error",
            [](qjspp::Arguments const& args) -> qjspp::Value { return logImpl(args, ll::io::LogLevel::Error); }
        )
        .function(
            "fatal",
            [](qjspp::Arguments const& args) -> qjspp::Value { return logImpl(args, ll::io::LogLevel::Fatal); }
        )
        .build();


} // namespace plotx::script