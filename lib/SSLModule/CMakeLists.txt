project(SSLModule)
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(SOURCES_PATH
    ${SOURCES_PATH}/SSLModule.cpp
        src/SSLServer.cpp include/SSLServer.hpp src/Session.cpp include/Session.hpp)

if(UNIX)
    add_definitions("-fPIC")
#    add_definitions("-W -Wall -Wextra -Weffc++")
endif()
add_library(SSLModule SHARED ${SOURCES_PATH})
add_dependencies(SSLModule ziapi)
set_target_properties(SSLModule PROPERTIES PREFIX "")
target_include_directories(SSLModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
if(UNIX)
    target_link_libraries(SSLModule PRIVATE dl pthread ssl crypto)
endif()