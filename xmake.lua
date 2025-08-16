add_rules("mode.debug", "mode.release")

add_repositories("liteldev-repo https://github.com/LiteLDev/xmake-repo.git")
add_repositories("engsr6982-repo https://github.com/engsr6982/xmake-repo.git")

add_requires("levilamina 1.4.1", {configs = {target_type = "server"}})
add_requires("levibuildscript")

-- engsr6982
add_requires("qjspp 0.1.0");

if not has_config("vs_runtime") then
    set_runtimes("MD")
end


target("PlotX") -- Change this to your mod name.
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    add_rules("plugin.compile_commands.autoupdate")
    add_cxflags("/EHa", "/utf-8", "/W4", "/w44265", "/w44289", "/w44296", "/w45263", "/w44738", "/w45204")
    add_defines("NOMINMAX", "UNICODE")
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")
    add_headerfiles("src/(plotx/**.h)")
    add_files("src/**.cpp")
    add_includedirs("src")
    add_packages("levilamina", "qjspp")