{
  description = "Flake pour mon TP C++";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";       
      pkgs = import nixpkgs { inherit system; };
    in {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gcc
          cmake
          clang-tools
          pkg-config
          asio
        ];

        shellHook = ''
          export PS1="\n\[\033[1;35m\][nix-shell TP2-CPP]\[\033[0m\]$ "
          if [ ! -d build ]; then
            cmake -S . -B build
          fi
        '';
      };
    };
}
