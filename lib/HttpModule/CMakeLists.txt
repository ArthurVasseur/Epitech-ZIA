project(httpModule)
set(SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(SOURCES_PATH
        ${SOURCES_PATH}/HttpModule.cpp
        )

#add_definitions("-fPIC")
#add_definitions("-W -Wall -Wextra -Weffc++")
add_library(HttpModule SHARED ${SOURCES_PATH})
add_dependencies(HttpModule ziapi)
set_target_properties(HttpModule PROPERTIES PREFIX "")
target_include_directories(HttpModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)