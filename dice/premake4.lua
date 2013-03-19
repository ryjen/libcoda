project "arg3dice"
    kind "StaticLib"
    files {
        "**.h",
        "**.cpp"
    }
    excludes {
        "**.test.cpp"
    }
