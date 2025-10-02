# TP2_CPP_CS_3A

## Development Setup

### Option 1: Using Nix

You can first enter a nix shell to obtain the same dev environment as the one used for the project
```bash
nix develop
```

Then you need to create the _C++ build files_ 
```bash
cmake -S . -B build
```

Finally to build the project, go to the root of the project:
```bash
cmake --build build
```

### Option 2: Manual Installation (Without Nix)

> [!CAUTION]
> We give the used version of each external dependency as an indication
> The project can be build using other version but may not work.
> For the **ASIO** library, the code was also tested with the version given for the lab (_1.30.2_).

**Prerequisites**:
- **ASIO**: The networking library _1.24.0_
- **CMake**: To build the project _3.31.7_
- **GNU Make**: To compile the project _4.4.1_
- **GCC**: To compile _14.3.0_

If you don't use Nix, you'll need to add the ASIO library.
Download ASIO from https://think-async.com/Asio/Download.html and extract it at the root of the project.
You should have a structure like this:

```
.
├── asio/
│   └── (ASIO library files)
├── asio.hpp
├── CMakeLists.txt
├── flake.lock
├── flake.nix
├── include/
│   ├── RequestFactory.h
│   ├── Request.h
│   ├── Response.h
│   └── Server.h
├── INSTALL.md
├── README.md
└── src/
    ├── main.cpp
    ├── Request.cpp
    ├── RequestFactory.cpp
    ├── Response.cpp
    └── Server.cpp
```

Then build the project:
```bash
cmake -S . -B build
cmake --build build
```

## Running the Server

Once built, you can run the server:
```bash
./bin/serveur-echo
```