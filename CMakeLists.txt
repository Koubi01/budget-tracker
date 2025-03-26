cmake_minimum_required(VERSION 3.8)
project(Budget_tracker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_compile_options(-Wall -Wextra -pedantic)

include(C:/Users/koubi/Documents/GitHub/vcpkg/scripts/buildsystems/vcpkg.cmake)

add_executable(Budget_tracker main2.cpp lib.cpp Huff.cpp)


find_package(Crow CONFIG REQUIRED)
target_link_libraries(Budget_tracker PRIVATE Crow::Crow asio::asio)


add_custom_target(run
    COMMAND Budget_tracker
    DEPENDS Budget_tracker
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    )
