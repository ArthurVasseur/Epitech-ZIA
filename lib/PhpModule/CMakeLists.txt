project(phpCgi)
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(SOURCES
    ${SOURCES_PATH}/PhpCgi.cpp
)
include_directories(src/subprocess)
if(UNIX)
    add_definitions("-fPIC")
#    add_definitions("-W -Wall -Wextra -Weffc++")
endif()

add_library(phpCgi SHARED ${SOURCES})
file(DOWNLOAD
        https://raw.githubusercontent.com/arun11299/cpp-subprocess/master/subprocess.hpp
        ${CMAKE_SOURCE_DIR}/build/subprocess-prefix/subprocess.hpp)

add_dependencies(phpCgi ziapi)
set_target_properties(phpCgi PROPERTIES PREFIX "")

target_include_directories(phpCgi PUBLIC ${CMAKE_SOURCE_DIR}/build/subprocess-prefix/)
target_include_directories(phpCgi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
if(UNIX)
    target_link_libraries(phpCgi PRIVATE dl)
endif()