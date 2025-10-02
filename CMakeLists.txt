cmake_minimum_required(VERSION 3.15) # (REQUIS)

# Définition du projet (REQUIS)
project(serveur-echo 
    VERSION 1.0.0
    DESCRIPTION "Implémentation de POP3 en C++"
    LANGUAGES CXX
)

# Export compile commands pour clangd  (OPTIONNEL pour intellisense)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configuration C++ (REQUIS)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Définir le répertoire de sortie des exécutables (OPTIONNEL va par défaut dans build/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Définition des sources (REQUIS)
set(SOURCES
    src/main.cpp
    src/Server.cpp
    src/Request.cpp
    src/Response.cpp
    src/RequestFactory.cpp
    src/RequestQuit.cpp
    src/Message.cpp
    src/RequestUnknown.cpp
)

# Création de l'exécutable (REQUIS)
add_executable(${PROJECT_NAME} ${SOURCES})

# Configuration des includes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Configuration pour les threads (REQUIS pour asio)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Affichage des informations de compilation (OPTIONNEL)
message(STATUS "Projet: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Compilateur: ${CMAKE_CXX_COMPILER}")
message(STATUS "Standard C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Type de build: ${CMAKE_BUILD_TYPE}")
