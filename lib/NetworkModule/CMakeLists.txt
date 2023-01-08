project(NetworkModule)
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(SOURCES_PATH
    ${SOURCES_PATH}/NetworkModule.cpp
    ${SOURCES_PATH}/TCPServer.cpp
    ${SOURCES_PATH}/Session.cpp)

if(UNIX)
    add_definitions("-fPIC")
#    add_definitions("-W -Wall -Wextra -Weffc++")
endif()
add_library(NetworkModule SHARED ${SOURCES_PATH})
add_dependencies(NetworkModule ziapi)
set_target_properties(NetworkModule PROPERTIES PREFIX "")
target_include_directories(NetworkModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
if(UNIX)
    target_link_libraries(NetworkModule PRIVATE dl pthread)
endif()