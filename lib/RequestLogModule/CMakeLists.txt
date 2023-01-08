project(request_log)
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(SOURCES_PATH
    ${SOURCES_PATH}/RequestLogModule.cpp
)

if(UNIX)
    add_definitions("-fPIC")
#    add_definitions("-W -Wall -Wextra -Weffc++")
endif()
add_library(request_log SHARED ${SOURCES_PATH})
set_target_properties(request_log PROPERTIES PREFIX "")
target_include_directories(request_log PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)