#==--- flame/docs/CMakeLists.txt --------------------------------------------==#
#
#                      Copyright (c) 2020 Rob Clucas
#
#  This file is distributed under the MIT License. See LICENSE for details.
#
#==--------------------------------------------------------------------------==#

#==--- [doxygen] ------------------------------------------------------------==#

find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR   ${PROJECT_SOURCE_DIR}/include)
set(DOXYGEN_OUTPUT_DIR  ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
set(DOXYGEN_INDEX_FILE  ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN         ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

#This will be the main output of our command
#
set(DOXYGEN_INDEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)
file(MAKE_DIRECTORY    ${DOXYGEN_OUTPUT_DIR})
add_custom_command(
  OUTPUT          ${DOXYGEN_INDEX_FILE}
  COMMAND         ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
  MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
  COMMENT         "Generating docs")

add_custom_target(doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

#==--- [sphinx] -------------------------------------------------------------==#

find_package(Sphinx REQUIRED)

set(SPHINX_SOURCE     ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD      ${CMAKE_CURRENT_BINARY_DIR}/docs/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_custom_command(
  OUTPUT            ${SPHINX_INDEX_FILE}
  COMMAND           ${SPHINX_EXECUTABLE} 
                    -b html 
                    -Dbreathe_projects.Flame=${DOXYGEN_OUTPUT_DIR}/xml
                    ${SPHINX_SOURCE} 
                    ${SPHINX_BUILD}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS           ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
                    ${DOXYGEN_INDEX_FILE}
  MAIN_DEPENDENCY   ${CMAKE_CURRENT_SOURCE_DIR}/conf.py
  COMMENT           "Generating documentation with Sphinx")

add_custom_target(sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})