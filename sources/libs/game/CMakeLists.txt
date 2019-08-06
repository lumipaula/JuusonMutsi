project(Game LANGUAGES C CXX)

set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/src")


file(GLOB SOURCES 
    "${source_path}/classes/*.cpp"
    "${source_path}/effects/*.cpp"
    "${source_path}/entities/*.cpp"
    "${source_path}/environment/*.cpp"
    "${source_path}/items/*.cpp"
)

add_library(Game SHARED ${SOURCES})

target_include_directories(Game PUBLIC 
    "${source_path}/classes/"
    "${source_path}/effects/"
    "${source_path}/entities/"
    "${source_path}/environment/"
    "${source_path}/items/"

)

target_link_libraries(Game PUBLIC Core)

if(UNIX)
install(TARGETS Game LIBRARY DESTINATION bin/ COMPONENT Runtime)
else()
install(TARGETS Game RUNTIME DESTINATION bin/ COMPONENT Runtime)
endif()