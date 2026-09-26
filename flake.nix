{
  description = "Seamwork modern C++23 development and CI environments";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };

      seamworkPackages = with pkgs; [
        clang
        cmake
        gcc14
        ninja
      ];

      postgresqlDev = pkgs.postgresql.dev;
      postgresqlLib = pkgs.postgresql.lib;
      pgConfig = pkgs.writeShellScriptBin "pg_config" ''
        case "$1" in
          --includedir)
            echo "${postgresqlDev}/include"
            ;;
          --includedir-server)
            echo "${postgresqlDev}/include/server"
            ;;
          --libdir)
            echo "${postgresqlLib}/lib"
            ;;
          --pkglibdir)
            echo "${pkgs.postgresql}/lib"
            ;;
          --version)
            echo "PostgreSQL ${pkgs.postgresql.version}"
            ;;
          *)
            echo "unsupported pg_config option: $1" >&2
            exit 1
            ;;
        esac
      '';

      legacyPackages = seamworkPackages ++ (with pkgs; [
        boost
        curl
        doxygen
        gdb
        git
        gnumake
        json_c
        lcov
        mariadb
        mariadb-connector-c
        openssl
        pgConfig
        pkg-config
        postgresql
        postgresql.dev
        postgresql.lib
        sqlite
        uriparser
        valgrind
      ]);

      compilerHook = ''
        if [ -z "$CC" ]; then export CC=gcc; fi
        if [ -z "$CXX" ]; then export CXX=g++; fi
        echo "Seamwork C++23 environment"
        echo "Compiler: $($CXX --version | head -n 1)"
      '';
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = seamworkPackages;

        shellHook = compilerHook + ''
          echo "Configure with: cmake --preset dev"
        '';
      };

      devShells.${system}.legacy = pkgs.mkShell {
        packages = legacyPackages;

        shellHook = compilerHook + ''
          echo "Legacy compatibility configure: cmake --preset legacy-dev"
        '';
      };
    };
}
