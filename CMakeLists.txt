cmake_minimum_required(VERSION 3.15)
project(tinygl VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

include_directories(
    ${Stb_INCLUDE_DIRS}
)

set(SOURCES
   src/camera_plugin.cpp
   src/camera.cpp
   src/mesh.cpp
   src/model.cpp
   src/shader.cpp
   src/texture.cpp
   src/timer.cpp
)

set(HEADERS
    src/camera_plugin.hpp
    src/camera.hpp
    src/mesh.hpp
    src/model.hpp
    src/shader.hpp
    src/texture.hpp
    src/timer.hpp

    src/builder.hpp
    src/config.hpp
    src/pipeline.hpp
    src/plugin.hpp
    src/renderer_plugin.hpp
    src/utils.hpp
    src/window.hpp
    
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm-header-only
    fmt::fmt-header-only
    assimp::assimp
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
