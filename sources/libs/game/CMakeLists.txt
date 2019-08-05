project(Game LANGUAGES C CXX)

set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SOURCES "${source_path}/*.cpp")

add_library(Game SHARED ${SOURCES})

target_include_directories(Video PUBLIC ${include_path})

if(UNIX)
install(TARGETS Game LIBRARY DESTINATION bin/ COMPONENT Runtime)
else()
install(TARGETS Game RUNTIME DESTINATION bin/ COMPONENT Runtime)
endif()