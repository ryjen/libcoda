project "arg3log"
    kind "StaticLib"
    files {
        "log.h",
        "log.cpp"
    }
    excludes {
        "*.test.cpp"
    }