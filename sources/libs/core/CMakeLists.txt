project(Core LANGUAGES C CXX)

set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/src")


find_package (Threads)

file(GLOB SOURCES 
    "${source_path}/compute/*.cpp"
    "${source_path}/util/*.cpp"

)

add_library(Core SHARED ${SOURCES})

target_include_directories(Core PUBLIC 
    "${source_path}/compute/"
    "${source_path}/util/"


)

target_link_libraries(Core PUBLIC ${CMAKE_THREAD_LIBS_INIT})

if(UNIX)
install(TARGETS Core LIBRARY DESTINATION bin/ COMPONENT Runtime)
else()
install(TARGETS Core RUNTIME DESTINATION bin/ COMPONENT Runtime)
endif()