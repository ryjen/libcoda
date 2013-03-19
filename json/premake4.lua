project "arg3json"
    kind "StaticLib"
    files {
        "*.h",
        "*.cpp",
    }
    excludes {
        "*.test.cpp"
    }