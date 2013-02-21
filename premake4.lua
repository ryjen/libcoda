--_ACTION = _ACTION or "arg3"
newaction {
   trigger     = "indent",
   description = "Format source files",
   execute = function ()
      os.execute("astyle -N -A1 -R '*.cpp' '*.h'");
   end
}
newaction {
    trigger     = "install",
    description = "Install headers and lib",
    execute = function() 

      if not _ARGS[1] or not os.isdir(_ARGS[1]) then
        error("You must specify an install location")
      end

      if not os.isdir("bin/Release") then
        error("You must make a release build first")
      end

      bindir = _ARGS[1].."/lib"
      headerdir = _ARGS[1].."/include/arg3"

      if not os.isdir(bindir) then
        os.mkdir(bindir)
      end

      if not os.isdir(headerdir) then
        os.mkdir(headerdir)
      end

      libraries = { "libarg3.a", "libarg3db.a", "libarg3dice.a", "libarg3format.a", "libarg3strings.a"}
      for l=1, #libraries do
        if os.isfile("bin/Release/"..libraries[l]) then
            os.copyfile("bin/Release/"..libraries[l], bindir)
        end
      end

      folders = {"collections", "db", "dice", "format", "strings", "variant"}
      for f=1, #folders do 
          headers = os.matchfiles(folders[f].."/**.h")
          tempdir = headerdir.."/"..folders[f]
          os.mkdir(tempdir)
          for i=1, #headers do
            os.copyfile(headers[i], tempdir)
          end
      end
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
    os.rmdir("bin")
    os.rmdir("obj")
end

solution "arg3"
    configurations { "Debug", "Release" }
    kind "StaticLib"
    language "C++"

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
    
    configuration "Debug"
        flags "Symbols"
        targetdir "bin/Debug"
    configuration "Release"
        targetdir "bin/Release"
    
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


