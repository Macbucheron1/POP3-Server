# TP2_CPP_CS_3A

## Development Setup

You can first enter a nix shell to obtain the same dev environment as the one used for the project
```bash
nix develop
```

Then you need to create the _C++ build files_ 
```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

Finally to build the project, go to the root of the project:
```bash
cmake --build build
```