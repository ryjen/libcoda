--_ACTION = _ACTION or "arg3"
newaction {
   trigger     = "indent",
   description = "Format source files",
   execute = function ()
      os.execute("astyle -N -A1 -R *.cpp *.h");
   end
}

newoption {
   trigger     = "monolithic",
   description = "Build one giant library instead of smaller component libraries"
}

if _ACTION == "clean" then
    matches = os.matchfiles("**.orig")
    for i=1, #matches do
        os.remove(matches[i])
    end
end

solution "arg3"
    configurations { "Debug", "Release" }
    kind "StaticLib"
    language "C++"
    configuration "Debug"
        flags "Symbols"
    
    buildoptions { "-std=c++11", "-stdlib=libc++", "-Wall", "-Werror"}

    linkoptions { "-stdlib=libc++" }

    if not _OPTIONS["monolithic"] then
        include "db"

        include "dice"

        include "format"

        include "strings"
    else
        project "arg3"
            kind "StaticLib"
            files {
                "**.cpp",
                "**.h"
            }
            excludes {
                "**.test.cpp"
            }
    end
    
    project "arg3test"
        kind "ConsoleApp"
        files {
            "**.test.cpp",
            "arg3.test.cpp"
        }
        if _OPTIONS["monolithic"] then
            links { "sqlite3", "arg3" }
        else
            links { 
                "sqlite3",
                "arg3db", 
                "arg3dice", 
                "arg3format", 
                "arg3strings"
            }
        end
        postbuildcommands {
            "./arg3test"
        }


