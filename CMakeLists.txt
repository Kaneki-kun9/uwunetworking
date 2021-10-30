cmake_minimum_required(VERSION 3.15)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Fix stuff that's broken by default
include(ForbidInSource)
include(SetBuildType)

project(
  uwunetworking 
  VERSION 0.1
  DESCRIPTION
    "Reimplementing a Networkstack"
  LANGUAGES C)
add_executable(${PROJECT_NAME} "src/main.c" "src/tap.c" "src/eth.c" "src/common.c")

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)
# TODO: Fix for clang/MSVC
list(
  APPEND
  DEBUG_FLAGS
  -Wall
  -Wextra
  -Wpedantic
  -Wcast-align
  -Wcast-qual
  -Wformat=2
  -Winit-self
  -Wlogical-op
  -Wredundant-decls
  -Wshadow
  -Wsign-conversion
  -Wstrict-overflow=5
  -Wswitch-default
  -Wundef
  -Wunreachable-code
  -Wwrite-strings
  -fno-stack-protector
  -g
  -O0
  -fdiagnostics-color=always
  -fno-omit-frame-pointer)
list(APPEND DEBUG_LD_OPTS -fno-omit-frame-pointer)

target_compile_options(${PROJECT_NAME} PRIVATE ${DEBUG_FLAGS})

install(
  TARGETS ${PROJECT_NAME}
  CONFIGURATIONS Release
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Hack to force cmake to add system (libc) header path to compile_commands.json.
# This also adds a lot of junk, but as long as it doesn't slow clangd too much
# I'll deal.
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
      ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

# Define DEBUG macro in debug builds
target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")