# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( cgal_ )

cmake_minimum_required(VERSION 2.8.10)

find_package(CGAL QUIET COMPONENTS Core )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if ( CGAL_FOUND )

  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

  create_single_source_cgal_program( "cgal_graham_andrew.cc" )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

