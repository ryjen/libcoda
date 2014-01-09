project "arg3math"
    kind "StaticLib"
    files {
        "*.h",
        "*.cpp",
    }
    excludes {
        "*.test.cpp"
    }