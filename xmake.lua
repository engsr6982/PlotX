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

option("overworld")
    set_default(true)
    set_showmenu(true)
option_end()


target("PlotX") -- Change this to your mod name.
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    add_rules("plugin.compile_commands.autoupdate")
    add_cxflags("/EHa", "/utf-8", "/W4", "/w44265", "/w44289", "/w44296", "/w45263", "/w44738", "/w45204")
    add_defines("NOMINMAX", "UNICODE", "PLOTX_EXPORT")
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")
    add_headerfiles(
        "src/(PlotX/**.hpp)"
    )
    add_files(
        "src/**.cpp",
        "src/**.cc"
    )
    add_includedirs("src", "patches")
    add_packages("levilamina", "qjspp")

    if has_config("overworld") then
        add_defines("PLOTX_OVERWORLD")
    end