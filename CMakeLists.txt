cmake_minimum_required(VERSION 3.20)
project(QtHomework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        Test
        REQUIRED)

enable_testing(true)

add_executable(QtHomework main.cpp read_file.h read_file.cpp combination_counter.h combination_counter.cpp)

target_link_libraries(QtHomework
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts)

add_executable(tests Tests.h Tests.cpp combination_counter.h combination_counter.cpp)
add_test(test tests)
target_link_libraries(tests PRIVATE Qt5::Test)



