cmake_minimum_required(VERSION 3.27)
project(pweOptimization)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(pweOptimization
        main.cpp
        src/Graph/Graph.cpp
        src/Graph/Edge.cpp
        src/Graph/Node.cpp
        src/Graph/TxConfig.cpp
        src/Graph/TileConfig.cpp
        src/Propagation/Ray.cpp
        src/Propagation/ModeHandler.cpp
        src/Propagation/Room.cpp
        src/Propagation/RayHandler.cpp
        src/Propagation/SystemState.cpp
)

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
