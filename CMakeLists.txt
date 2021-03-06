#==--- flame/CMakeLists.txt -------------------------------------------------==#
#
#                      Copyright (c) 2020 Rob Clucas
#
#  This file is distributed under the MIT License. See LICENSE for details.
#
#==--------------------------------------------------------------------------==#

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(flame)

# Allow clang-format to configure from the build.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#===== [packages] =============================================================#

# Change to path to pytorch install
set(CMAKE_PREFIX_PATH "~/opt/libtorch;~/opt/opencv/build")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

find_package(OpenCV REQUIRED)

#===== [subdirs] ==============================================================#

add_subdirectory(docs)
add_subdirectory(examples)

#==============================================================================#