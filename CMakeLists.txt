cmake_minimum_required(VERSION 3.15)
project(CPP_Refresher VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)

FetchContent_declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.8
)
FetchContent_MakeAvailable(imgui)

# rlImGui herunterladen
FetchContent_Declare(
    rlImGui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
)
FetchContent_MakeAvailable(rlImGui)

add_library(rlImGui_custom STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)
target_include_directories(rlImGui_custom PUBLIC ${imgui_SOURCE_DIR} ${rlimgui_SOURCE_DIR})
target_link_libraries(rlImGui_custom PUBLIC raylib)

set(SOURCES
    src/main.cpp
    src/Ball2D.cpp
    src/BouncingBallsSimulation.cpp
    src/Application.cpp
    src/InputHandler.cpp
)


add_executable(2D_ParticleSimulation ${SOURCES})
target_include_directories(2D_ParticleSimulation PRIVATE include)
target_link_libraries(2D_ParticleSimulation PRIVATE raylib rlImGui_custom)