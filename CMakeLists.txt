cmake_minimum_required(VERSION 3.15)
project(tinygl VERSION 0.1)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(stb REQUIRED)

include_directories(
    ${glm_INCLUDE_DIRS}
    ${stb_INCLUDE_DIRS}
)

file(GLOB SHADERS
    shaders/*.vert
    shaders/*.frag
)

file(GLOB SOURCES
    src/*.cpp
    src/*.hpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${SOURCES}
    ${SHADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
