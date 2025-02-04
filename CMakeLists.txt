cmake_minimum_required(VERSION 3.15)
project(tinygl VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(fmt REQUIRED)

include_directories(
    ${Stb_INCLUDE_DIRS}
)

set(SOURCES
    src/camera_plugin.cpp
    src/camera.cpp
    src/shader.cpp
    src/timer.cpp
    src/texture.cpp
)

set(HEADERS
    src/builder.hpp
    src/camera_plugin.hpp
    src/renderer_plugin.hpp
    src/camera.hpp
    src/window.hpp
    src/texture.hpp

    src/utils.hpp
    src/model.hpp
    src/config.hpp
    src/object.hpp
    src/pipeline.hpp
    src/plugin.hpp
    src/res.hpp
    src/shader.hpp
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
    fmt::fmt
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
