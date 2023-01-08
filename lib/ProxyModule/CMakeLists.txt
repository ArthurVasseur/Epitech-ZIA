project(proxy)
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(SOURCES
    ${SOURCES_PATH}/Proxy.cpp
        src/HttpRequest.cpp)
if(UNIX)
    add_definitions("-fPIC")
#    add_definitions("-W -Wall -Wextra -Weffc++")
endif()

add_library(proxy SHARED ${SOURCES})

add_dependencies(proxy ziapi)
set_target_properties(proxy PROPERTIES PREFIX "")

target_include_directories(proxy PUBLIC ${CMAKE_SOURCE_DIR}/build/subprocess-prefix/)
target_include_directories(proxy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
if(UNIX)
    target_link_libraries(proxy PRIVATE dl)
endif()