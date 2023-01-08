cmake_minimum_required(VERSION 3.8)

project(zia)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CORE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

include_directories(${CONAN_INCLUDE_DIRS})
conan_basic_setup()
enable_testing()
if(UNIX)
    add_definitions("-fPIC -ggdb")
#    add_definitions("-W -Wall -Wextra -Weffc++")
elseif(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
endif()

set(CORE_SOURCES
    ${CORE_PATH}/main.cpp
    ${CORE_PATH}/ConfigLoader.cpp
    ${CORE_PATH}/ModuleLoader.cpp
    ${CORE_PATH}/Core.cpp
    ${CORE_PATH}/NetworkQueue.cpp
    ${CORE_PATH}/queues/RequestQueue.cpp src/queues/ResponseQueue.cpp include/queues/ResponseQueue.hpp src/ShellInterpreter.cpp include/ShellInterpreter.hpp src/Application.cpp include/Application.hpp)

set(TEST_SOURCES

)
include(ExternalProject)

ExternalProject_Add(ziapi
    GIT_REPOSITORY  https://github.com/martin-olivier/ZiAPI.git
    GIT_TAG         v3.0.0
    INSTALL_COMMAND ""
    TEST_COMMAND    ""
)
ExternalProject_Get_Property(ziapi SOURCE_DIR)
include_directories(${SOURCE_DIR}/include)
include_directories(${SOURCE_DIR}/include/queues)

add_executable(zia ${CORE_SOURCES})
add_dependencies(zia ziapi)
add_subdirectory(lib/)

if(MSVC)
    set_target_properties(zia PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
endif()

if(UNIX)
    target_link_libraries(zia PRIVATE dl pthread ssl crypto)
endif()

target_include_directories(zia PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)