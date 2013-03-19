project "arg3strings"
    kind "StaticLib"
    files {
        "strings.h",
        "strings.cpp"
    }
    excludes {
        "strings.test.cpp"
    }