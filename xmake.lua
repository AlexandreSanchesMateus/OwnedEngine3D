add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

add_requires("fmt", "libsdl3", "libsdl3_image", "libsdl3_ttf", "entt", "glm", "rapidjson", "lua")
add_requires("openal-soft", { configs = { shared = true }})
add_requires("imgui", {configs = {sdl3 = true, sdl3_renderer = true }})

add_requireconfs("libsdl", "**.libsdl", {configs = { sdlmain = is_mode("distrib") or false }})

set_project("OwnedEngine3D")

set_allowedmodes("debug", "release", "distrib")

set_languages("cxx20")
set_exceptions("cxx")
set_encodings("utf-8")
set_rundir(".")
set_warnings("allextra")
add_includedirs("include")
add_installfiles("(assets/**)", { prefixdir = "bin" })

add_cxflags("/wd4251")

if is_mode("distrib") then
    set_optimize("fastest")
    set_symbols("none")
else
    add_defines("WITH_EDITOR")
    if is_mode("debug") then
        set_suffixname("-debug")
    end
end

target("OwnedEngine3D")
    if is_mode("distrib") then
        set_kind("static")
        add_defines("OWNED_ENGINE_STATIC", { public = true })
    else
        set_kind("shared")
    end

    add_headerfiles("include/OwnedEngine3D/**.h")
    add_files("src/OwnedEngine3D/**.cpp")
    add_packages("fmt", "libsdl3", "libsdl3_image", "libsdl3_ttf", "imgui", "entt", "glm", "rapidjson", "openal-soft","lua", { public = true })
    add_defines("OWNED_ENGINE_BUILD")

    if is_mode("distrib") then
        remove_files("src/OwnedEngine3D/Editor/**.cpp")
    end

target("EngineCoreFeature")
    set_kind("binary")
    add_deps("OwnedEngine3D")
    add_files("src/EngineCoreFeature/main.cpp")
