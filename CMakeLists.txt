#========================================
# Common (C++) 
#========================================

cmake_minimum_required(VERSION 2.8)

# project
set(CommonCpp_PROJECT "CommonCpp")
project(${CommonCpp_PROJECT})

if(MSVC)
    set(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)    
    add_definitions("/EHsc")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-D_ITERATOR_DEBUG_LEVEL=2 -D_DEBUG)
    else()
        add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    endif()
else()
    set(CMAKE_CXX_COMPILER g++)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif()

# set projet paths/files
set(CommonCpp_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(CommonCpp_INC  ${CommonCpp_ROOT}/inc)
set(CommonCpp_SRC  ${CommonCpp_ROOT}/src)
set(CommonCpp_INCLUDE_DIRS ${CommonCpp_INC} CACHE PATH "Include directories of Common (C++)" FORCE)
set(CommonCpp_SOURCES_DIRS ${CommonCpp_SRC} CACHE PATH "Sources directories of Common (C++)" FORCE)
file(GLOB CommonCpp_HEADER_FILES "${CommonCpp_INC}/*.h" "${CommonCpp_INC}/*.hpp")
file(GLOB CommonCpp_SOURCE_FILES "${CommonCpp_SRC}/*.c" "${CommonCpp_SRC}/*.cpp")

### ==== NO TESTS FOR NOW ==== HEADERS/SOURCES INCLUDED AS IS
### COULD USE FIND CTEST + AUTO RUN TEST ON BUILD

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR     lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR     bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR inc CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/${CommonCpp_PROJECT})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# drop down list of library type
set(CommonCpp_LIBRARY_STATIC "STATIC")
set(CommonCpp_LIBRARY_SHARED "SHARED")
set(CommonCpp_LIBRARY_TYPE ${CommonCpp_LIBRARY_STATIC} CACHE STRING "Library type to generate")
set_property(CACHE CommonCpp_LIBRARY_TYPE PROPERTY STRINGS ${CommonCpp_LIBRARY_STATIC} ${CommonCpp_LIBRARY_SHARED}) 
set(CommonCpp_LIBRARY_EXT ${CommonCpp_PROJECT}${CMAKE_${CommonCpp_LIBRARY_TYPE}_LIBRARY_SUFFIX})

# find OpenCV
find_package(OpenCV 3)
if (${OpenCV_FOUND})
    set(CommonCpp_INCLUDE_DIRS ${CommonCpp_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS})
    set(CommonCpp_LIBRARIES    ${CommonCpp_LIBRARIES}     ${OpenCV_LIBRARIES})
    add_definitions(-DCOMMON_CPP_HAS_OPENCV)
endif()

# find Boost
option(Boost_USE_STATIC_LIBS    OFF)
option(Boost_USE_MULTITHREADED  ON)
option(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS filesystem system)
if (${Boost_FOUND})    
    set(CommonCpp_INCLUDE_DIRS ${CommonCpp_INCLUDE_DIRS}  ${Boost_INCLUDE_DIRS})
    set(CommonCpp_LIBRARIES    ${CommonCpp_LIBRARIES}     ${Boost_LIBRARIES})
    if (WIN32)
        # disable auto linking 
        #add_definitions(-DBOOST_ALL_NO_LIB)
        #remove_definitions(-BOOST_NO_EXCEPTIONS)
    endif()
    # if (NOT ${Boost_USE_STATIC_LIBS})
        # # avoid invalid linking error when using shared libs
        # add_definitions(-DBOOST_ALL_DYN_LINK)
    # endif()
endif()

# include/linking
set(CommonCpp_LIBRARY ${CommonCpp_PROJECT})
add_library(${CommonCpp_LIBRARY} ${CommonCpp_LIBRARY_TYPE} ${CommonCpp_SOURCE_FILES} ${CommonCpp_HEADER_FILES})
if(MSVC)
    set_target_properties(${CommonCpp_LIBRARY} PROPERTIES LINKER_LANGUAGE C++)
endif()
include_directories(${CommonCpp_INCLUDE_DIRS})
target_link_libraries(${CommonCpp_LIBRARY} ${CommonCpp_LIBRARIES})

# if (${CommonCpp_BUILD_TESTS}) 
    # set(CommonCpp_TESTS ${CommonCpp_PROJECT}_Test)
    # add_executable(${CommonCpp_TESTS} ${CommonCpp_SOURCE_TESTS} ${CommonCpp_HEADER_TESTS} ${CommonCpp_SOURCE_FILES} ${CommonCpp_HEADER_FILES})
    # target_link_libraries(${CommonCpp_TESTS} ${CommonCpp_LIBRARIES})
# endif()

# fix config paths as required
string(REGEX REPLACE "\\\\" "/" INSTALL_INCLUDE_DIR ${INSTALL_INCLUDE_DIR}) 
string(REGEX REPLACE "\\\\" "/" INSTALL_LIB_DIR     ${INSTALL_LIB_DIR}) 

# update config file
set(CommonCpp_CONFIG_INC   ${INSTALL_INCLUDE_DIR})
set(CommonCpp_CONFIG_LIB   ${INSTALL_LIB_DIR}/${CommonCpp_LIBRARY_EXT})
set(CommonCpp_CONFIG_FILE  ${CommonCpp_PROJECT}Config.cmake)
if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(CommonCpp_CONFIG_PATH ${CommonCpp_CONFIG_FILE})
else()
    set(CommonCpp_CONFIG_PATH ${CMAKE_BINARY_DIR}/${CommonCpp_CONFIG_FILE})
endif()
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
configure_file(cmake/${CommonCpp_CONFIG_FILE}.in ${CommonCpp_CONFIG_PATH})

# install
install(TARGETS ${CommonCpp_PROJECT}
        EXPORT  ${CommonCpp_TARGETS}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
install(FILES   ${CommonCpp_HEADER_FILES} DESTINATION ${INSTALL_INCLUDE_DIR})
install(FILES   ${CommonCpp_CONFIG_PATH}  DESTINATION ${INSTALL_CMAKE_DIR})

# if (${CommonCpp_BUILD_TESTS})
    # install(TARGETS ${CommonCpp_TESTS} RUNTIME     DESTINATION ${INSTALL_BIN_DIR})
    # file(GLOB CommonCpp_IMGTEST_FILES ${CommonCpp_IMGTEST_DIR}/*)
    # install(FILES    ${CommonCpp_IMGTEST_FILES}    DESTINATION ${INSTALL_IMGTEST_DIR})
# endif()
