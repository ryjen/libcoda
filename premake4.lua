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

      if not os.isdir("bin/release") then
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

      if _ARGS[2] then
        if not os.isdir(_ARGS[2]) then
          error("That is not a valid package name")
        end
        package = _ARGS[2]
        libraries = { "libarg3#{package}.a" }
        folders = { package }
      else
        libraries = { "libarg3.dylib", "libarg3db.a", "libarg3dice.a", "libarg3.log.a", "libarg3net.a", "libarg3format.a", "libarg3json.a", "libarg3math.a", "libarg3string.a"}
        folders = {"collections", "db", "dice", "format", "net", "log", "json", "math", "string"}
      end

      for l=1, #libraries do
        if os.isfile("bin/release/"..libraries[l]) then
            os.copyfile("bin/release/"..libraries[l], bindir)
        end
      end

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
newaction {
    trigger   = "release",
    description = "builds a release",
    execute = function()
       if( os.isdir("bin")) then
          error("You must run clean first")
       end

       if _ARGS[1] then
         version = _ARGS[1]
       else
         version = "1.0"
       end
       os.execute("tar --exclude=libarg3_"..version..".tar.gz -czf libarg3_"..version..".tar.gz .");
    end
}
newoption {
   trigger     = "static",
   description = "Build static libraries"
}

newoption {
  trigger      = "no-curl",
  description  = "don't include libcurl in library"
}

if _ACTION == "clean" then
    matches = os.matchfiles("**.orig")
    for i=1, #matches do
        os.remove(matches[i])
    end
    matches = os.matchfiles("**.a")
    for i=1, #matches do
        os.remove(matches[i])
    end
    os.rmdir("bin")
    os.rmdir("obj")
end

if _ACTION == "gmake" then
  if not os.isdir('db') then
    os.execute('git clone git@github.com:c0der78/arg3db.git db');
  end

  if not os.isdir('dice') then
    os.execute('git clone git@github.com:c0der78/arg3dice.git dice');
  end
end

solution "arg3"
    configurations { "debug", "release" }
    language "C++"

    buildoptions { "-std=c++11", "-stdlib=libc++", "-Wall", "-Werror", "-Ivendor"}

    linkoptions { "-stdlib=libc++" }

    if _OPTIONS["no-curl"] then
      buildoptions { "-DARG3_NO_CURL" }
    end

    configuration "Debug"
        flags "Symbols"
        targetdir "bin/debug"
        buildoptions { "-g -D_DEBUG" }
    configuration "release"
        targetdir "bin/release"
        buildoptions { "-O" }

    if _OPTIONS["static"] then
        include "db"

        include "dice"

        include "format"

        include "log"

        include "net"

        include "json"

        include "math"

        include "string"
    else
        project "arg3"
            kind "SharedLib"
            files {
                "**.cpp",
                "**.h"
            }
            excludes {
                "**.test.cpp"
            }
            if _OPTIONS["no-curl"] then
              links { "json", "sqlite3" }
            else
              links { "json", "sqlite3", "curl" }
            end
    end

    project "arg3test"
        kind "ConsoleApp"
        excludes {
            "**/arg3.test.cpp"
        }
        files {
            "**.test.cpp"
        }
        includedirs { "vendor" }
        if not _OPTIONS["static"] then
            links { "arg3", "sqlite3" }
        else
            links {
                "sqlite3",
                "json",
                "curl",
                "arg3log",
                "arg3db",
                "arg3dice",
                "arg3format",
                "arg3net",
                "arg3json",
                "arg3math",
                "arg3string"
            }
        end
        configuration "Debug"
        postbuildcommands {
          "bin/debug/arg3test"
        }
        configuration "Release"
        postbuildcommands {
          "bin/release/arg3test"
        }


