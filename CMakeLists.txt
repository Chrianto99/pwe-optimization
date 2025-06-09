cmake_minimum_required(VERSION 3.27)
project(pweOptimization)

set(CMAKE_CXX_STANDARD 20)

add_executable(pweOptimization main.cpp
        GraphDirectory/Graph.cpp
        GraphDirectory/Graph.h
        GraphDirectory/Edge.cpp
        GraphDirectory/Edge.h
        GraphDirectory/Node.cpp
        GraphDirectory/Node.h
        PropagationDirectory/Ray.cpp
        PropagationDirectory/Ray.h
        PropagationDirectory/ModeHandler.cpp
        PropagationDirectory/ModeHandler.h
        GraphDirectory/TxConfig.cpp
        GraphDirectory/TxConfig.h
        GraphDirectory/TileConfig.cpp
        GraphDirectory/TileConfig.h
        GraphDirectory/Room.cpp
        GraphDirectory/Room.h
        PropagationDirectory/RayHandler.h
        PropagationDirectory/RayHandler.cpp
        PropagationDirectory/RayHandler.h
        PropagationDirectory/SystemState.cpp
        PropagationDirectory/SystemState.h)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

# Disable tests
set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(json)

target_link_libraries(pweOptimization PRIVATE nlohmann_json::nlohmann_json)
