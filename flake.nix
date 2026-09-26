{
  description = "Seamwork modern C++23 development shell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
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
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        packages = with pkgs; [
          boost
          cmake
          curl
          doxygen
          gcc14
          gdb
          git
          gnumake
          json_c
          lcov
          mariadb
          mariadb-connector-c
          ninja
          openssl
          pgConfig
          pkg-config
          postgresql
          postgresql.dev
          postgresql.lib
          sqlite
          uriparser
          valgrind
        ];

        shellHook = ''
          export CC=gcc
          export CXX=g++
          echo "Seamwork C++23 dev shell"
          echo "Compiler: $($CXX --version | head -n 1)"
          echo "Configure with: cmake --preset dev"
        '';
      };
    };
}
