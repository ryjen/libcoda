project "arg3string"
    kind "StaticLib"
    files {
        "*.h",
        "*.cpp"
    }
    excludes {
        "*.test.cpp"
    }