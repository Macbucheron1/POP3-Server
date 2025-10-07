{
  description = "Flake pour mon TP C++";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";       
      pkgs = import nixpkgs { inherit system; };
      
      commonDeps = with pkgs; {
        buildTools = [ cmake gcc ];
        libraries = [ asio ];
        devTools = [ clang-tools pkg-config ];
      };

      pname = "pop3-server";
      version = "1.0.0";
      
    in {
      packages.${system} = {
        default = pkgs.stdenv.mkDerivation {
          inherit pname version;        
          src = ./.;
          nativeBuildInputs = commonDeps.buildTools;
          buildInputs = commonDeps.libraries;

          configurePhase = ''
            cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
          '';

          buildPhase = ''
            cmake --build build
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp bin/${pname} $out/bin/
          '';
        };
      };

      devShells.${system}.default = pkgs.mkShell {
        buildInputs = commonDeps.buildTools 
                   ++ commonDeps.libraries 
                   ++ commonDeps.devTools;

        shellHook = ''
          export PS1="\n\[\033[1;35m\][nix-shell TP2-CPP]\[\033[0m\]$ "
          if [ ! -d build ]; then
            cmake -S . -B build
          fi
        '';
      };
    };
}
