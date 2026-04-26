cmake_minimum_required(VERSION 3.17)
project(dhbw-advanced-software-engineering VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_APP "Baut die Hauptapplikation" ON)
option(BUILD_TESTS "Baut die Unit-Tests" ON)

# Sammle Quelldateien
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(logic_core STATIC ${LIB_SOURCES})
target_include_directories(logic_core PUBLIC include external/json)

if(BUILD_APP)
    # Erzeuge das Executable
    add_executable(${PROJECT_NAME} src/main.cpp)
    target_link_libraries(${PROJECT_NAME} logic_core)
endif()

if(BUILD_TESTS)
    enable_testing()

    file(GLOB TEST_FILES CONFIGURE_DEPENDS "tests/*_test.cpp")

    foreach(test_src ${TEST_FILES})
        get_filename_component(test_name ${test_src} NAME_WE)
        
        add_executable(${test_name} ${test_src})
        target_link_libraries(${test_name} PRIVATE logic_core)
        
        add_test(NAME ${test_name} COMMAND ${test_name})
    endforeach()
endif()