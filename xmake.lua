set_project("seewo-obstructor")
set_policy("compatibility.version", "3.0")

set_languages("c++2b")
set_warnings("all") 
add_rules("plugin.compile_commands.autoupdate", {outputdir = "build"})
add_rules("mode.releasedbg")

includes("dependencies/blook.lua")
add_requires("wintoast", "blook", "nlohmann_json")

target("obstructor")
    set_kind("shared")
    add_files("src/*.cc", "src/**/*.cc")
    add_syslinks("gdi32", "user32")
    add_packages("wintoast", "blook", "nlohmann_json")
    set_encodings("utf8")