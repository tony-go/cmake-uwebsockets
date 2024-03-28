cmake_minimum_required(VERSION 3.24)

project(use_usocket LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
  uSockets_content
  GIT_REPOSITORY https://github.com/uNetworking/uSockets
  GIT_TAG v0.8.5
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(uSockets_content)
file(GLOB_RECURSE SOURCES ${usockets_content_SOURCE_DIR}/src/*.c)
add_library(uSockets ${SOURCES})
target_include_directories(uSockets PUBLIC ${usockets_content_SOURCE_DIR}/src)
target_compile_definitions(uSockets PRIVATE LIBUS_NO_SSL)

FetchContent_Declare(
  uWebSockets_content
  GIT_REPOSITORY https://github.com/uNetworking/uWebSockets
  GIT_TAG v20.37.0
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
)
FetchContent_MakeAvailable(uWebSockets_content)
find_package(ZLIB REQUIRED)
add_library(uWebSockets INTERFACE)
target_include_directories(uWebSockets INTERFACE ${uwebsockets_content_SOURCE_DIR}/src/)
target_link_libraries(uWebSockets INTERFACE uSockets ${ZLIB_LIBRARIES})
target_compile_options(uWebSockets INTERFACE -Wno-deprecated-declarations)

# Client exec
add_executable(client client_ws.cc)
target_link_libraries(client uWebSockets)

# Server exec
add_executable(server server_ws.cc)
target_link_libraries(server uWebSockets)
