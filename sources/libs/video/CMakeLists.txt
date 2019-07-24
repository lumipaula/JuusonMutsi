project(Video LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2TTF)
include_directories(${SDL_INCLUDE_DIRS})

set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/src")


file(GLOB SOURCES "${source_path}/*.cpp")

add_library(Video SHARED ${SOURCES})

target_include_directories(Video PUBLIC ${include_path})

target_link_libraries(Video ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY})

if(UNIX)
install(TARGETS Video LIBRARY DESTINATION bin/ COMPONENT Runtime)
else()
install(TARGETS Video RUNTIME DESTINATION bin/ COMPONENT Runtime)
endif()