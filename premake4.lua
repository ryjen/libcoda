--_ACTION = _ACTION or "arg3"

solution "arg3"
    configurations { "Debug", "Release" }
    kind "StaticLib"
    language "C++"
    configuration "Debug"
        flags "Symbols"
    
    buildoptions { "-std=c++11", "-stdlib=libc++", "-Wall", "-Werror"}

    linkoptions { "-stdlib=libc++" }

    include "db"

    include "dice-engine"

    include "format"

    include "strings"

    include "variant"

    project "arg3test"
        kind "ConsoleApp"
        language "C++"
        files {
            "**.test.cpp",
            "arg3.test.cpp"
        }
        links { 
            "sqlite3",
            "arg3db", 
            "arg3dice", 
            "arg3format", 
            "arg3strings", 
            "arg3variant" 
        }
