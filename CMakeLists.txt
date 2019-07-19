cmake_minimum_required(VERSION 3.10)

set(CMAKE_INSTALL_PREFIX "JuusonMutsi")

project(JuusonMutsi)

enable_language(CXX)
enable_language(C)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/platform/win)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/win/*.cpp"
)

add_executable(JuusonMutsi ${SOURCES})

install(TARGETS JuusonMutsi RUNTIME DESTINATION bin/)