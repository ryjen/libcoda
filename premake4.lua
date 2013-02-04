--_ACTION = _ACTION or "arg3"

solution "arg3"
    configurations { "Debug", "Release" }
    kind "StaticLib"
    language "C++"
    configuration "Debug"
        flags "Symbols"
    
    buildoptions { "-std=c++11", "-stdlib=libc++"}

    include "collections"

    include "db"

    include "dice-engine"

    include "format"

    include "strings"

    include "variant"