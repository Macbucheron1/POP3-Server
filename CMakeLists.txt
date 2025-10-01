cmake_minimum_required(VERSION 3.15)

# Définition du projet
project(serveur-echo 
    VERSION 1.0.0
    DESCRIPTION "Serveur echo en C++ avec ASIO"
    LANGUAGES CXX)

# Configuration C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options de compilation pour le debug et la performance
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -Wextra")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -DNDEBUG")
endif()

# Recherche du package ASIO
find_package(PkgConfig REQUIRED)
pkg_check_modules(ASIO REQUIRED asio)

# Définition des sources
set(SOURCES
    main.cpp
    Server.cpp
)

set(HEADERS
    Server.h
)

# Création de l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Configuration des includes et libraries pour ASIO
target_include_directories(${PROJECT_NAME} PRIVATE ${ASIO_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${ASIO_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${ASIO_CFLAGS_OTHER})

# Si ASIO n'est pas trouvé via pkg-config, utiliser les headers locaux
if(NOT ASIO_FOUND)
    message(STATUS "ASIO non trouvé via pkg-config, utilisation des headers locaux")
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

# Configuration pour les threads (requis par ASIO)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Installation
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Option pour créer un package
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Affichage des informations de compilation
message(STATUS "Projet: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Compilateur: ${CMAKE_CXX_COMPILER}")
message(STATUS "Standard C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Type de build: ${CMAKE_BUILD_TYPE}")
