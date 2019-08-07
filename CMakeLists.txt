cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

SET(CMAKE_INSTALL_PREFIX "JMutsi" CACHE PATH "Root folder for Juuson Mutsi" FORCE)


project(JuusonMutsi)

enable_language(CXX)
enable_language(C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sources/src/loader)


file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/sources/src/loader/*.cpp"
)

add_subdirectory(sources/libs/video)
add_subdirectory(sources/libs/game)
add_subdirectory(sources/libs/core)



add_executable(JuusonMutsi ${SOURCES})



target_link_libraries(JuusonMutsi PUBLIC Game Core)

install(TARGETS JuusonMutsi RUNTIME DESTINATION bin/)