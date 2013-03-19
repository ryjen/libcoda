project "arg3variant"
    kind "StaticLib"
    files {
        "variant.h",
        "variant.cpp",
        "variant_alt.h"
    }
    excludes {
        "variant.test.cpp"
    }