cmake_minimum_required(VERSION 3.15)
project(tinygl VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

include_directories(
    ${Stb_INCLUDE_DIRS}
)

set(SOURCES
    src/app.cpp
    src/camera.cpp
    src/config.cpp
    src/shader.cpp
)

set(HEADERS
    src/const.hpp
    src/app.hpp
    src/camera.hpp
    src/config.hpp
    src/shader.hpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm-header-only
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
