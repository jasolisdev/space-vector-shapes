workspace "sfml_project"
  architecture "x86"
  configurations { "Debug", "Release" }
  defines {"SFML_STATIC"}
  cppdialect "C++17"
  location "build"

newoption {
  trigger     = "sfmlpath",
  value       = "path",
  description = "Path to the SFML root directory (must be relative to this file's location)"
 }

outputdir = "%{cfg.system}_%{cfg.buildcfg}-%{cfg.architecture}"

if os.host() == "windows" then

    if not _OPTIONS["sfmlpath"] then
         _OPTIONS["sfmlpath"] = "vendor/%{cfg.system}/SFML-2.5.1"
    end

  includedirs (_OPTIONS["sfmlpath"].."/include")
  libdirs (_OPTIONS["sfmlpath"].."/lib")

  debugSFMLlibs = {
        "sfml-graphics-s-d",
        "sfml-window-s-d",
        "sfml-audio-s-d",
        "sfml-system-s-d"
    }

    releaseSFMLlibs = {
        "sfml-graphics-s",
        "sfml-window-s",
        "sfml-audio-s",
        "sfml-system-s"
    }
end

if os.host() == "linux" then
    architecture "x86_64"

    includedirs { "/usr/include/SFML" }
    libdirs { "/usr/lib" }

    debugSFMLlibs = {
        "lsfml-graphics",
        "lsfml-window",
        "lsfml-audio",
        "lsfml-system"
    }
    releaseSFMLlibs = debugSFMLlibs
end

project "sfml_project"
  kind "ConsoleApp"
  language "C++"
  targetdir "bin/%{cfg.system}/%{cfg.buildcfg}"

  files { "include/**.h", "src/**.cpp" }

  if os.host() == "windows" then
    includedirs (_OPTIONS["sfmlpath"].."/include")
    libdirs (_OPTIONS["sfmlpath"].."/lib")

  filter {"configurations:*", "system:windows"}
    links {
        "opengl32",
        "freetype",
        "winmm",
        "gdi32",
        "flac",
        "vorbisenc",
        "vorbisfile",
        "vorbis",
        "ogg",
        "ws2_32",
        "openal32"
    }

  filter {"configurations:Release", "system:windows"}
    defines { "NDEBUG" }
    optimize "On"
    links
    {
        releaseSFMLlibs
    }

  filter {"configurations:Debug", "system:windows"}
    defines {"DEBUG"}
    symbols "On"
    links
    {
        debugSFMLlibs
    }

  filter {}   --reset filters
end

if os.host() == "linux" then
    includedirs { "/usr/include/SFML" }
    libdirs { "/usr/lib" }

  filter {"configurations:Release", "system:linux"}
    defines { "NDEBUG" }
    optimize "On"
    links
    {	
        "sfml-graphics",
        "sfml-window",
        "sfml-system",
        "sfml-audio",
        "sfml-network"
    }

  filter {"configurations:Debug", "system:linux"}
    defines {"DEBUG"}
    symbols "On"
    links
    {	
        "sfml-graphics",
        "sfml-window",
        "sfml-system",
        "sfml-audio",
        "sfml-network"
    }
end
