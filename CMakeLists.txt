cmake_minimum_required(VERSION 3.15)
project(tinygl VERSION 0.1)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
