#========================================
# Common (C++) 
#========================================

cmake_minimum_required(VERSION 2.8)

# project
set(COMMON-CPP_PROJECT "CommonCpp")
project(${COMMON-CPP_PROJECT})

if(MSVC)
    set(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    add_definitions("/EHsc")
endif()

# set projet paths/files
set(COMMON-CPP_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(COMMON-CPP_INC  ${COMMON-CPP_ROOT}/inc)
set(COMMON-CPP_SRC  ${COMMON-CPP_ROOT}/src)
set(COMMON-CPP_INCLUDE_DIRS ${COMMON-CPP_INC} CACHE PATH "Include directories of Common (C++)" FORCE)
set(COMMON-CPP_SOURCES_DIRS ${COMMON-CPP_SRC} CACHE PATH "Sources directories of Common (C++)" FORCE)
file(GLOB COMMON-CPP_HEADER_FILES "${COMMON-CPP_INC}/*.h" "${COMMON-CPP_INC}/*.hpp")
file(GLOB COMMON-CPP_SOURCE_FILES "${COMMON-CPP_SRC}/*.c" "${COMMON-CPP_SRC}/*.cpp")

### ==== NO TESTS FOR NOW ==== HEADERS/SOURCES INCLUDED AS IS
### COULD USE FIND CTEST + AUTO RUN TEST ON BUILD

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR     lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR     bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR inc CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/${COMMON-CPP_PROJECT})
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
set(COMMON-CPP_LIBRARY_STATIC "STATIC")
set(COMMON-CPP_LIBRARY_SHARED "SHARED")
set(COMMON-CPP_LIBRARY_TYPE ${COMMON-CPP_LIBRARY_STATIC} CACHE STRING "Library type to generate")
set_property(CACHE COMMON-CPP_LIBRARY_TYPE PROPERTY STRINGS ${COMMON-CPP_LIBRARY_STATIC} ${COMMON-CPP_LIBRARY_SHARED}) 
set(COMMON-CPP_LIBRARY_EXT ${COMMON-CPP_PROJECT}${CMAKE_${COMMON-CPP_LIBRARY_TYPE}_LIBRARY_SUFFIX})

# find OpenCV
find_package(OpenCV 3)
if (${OpenCV_FOUND})
    set(COMMON-CPP_INCLUDE_DIRS ${COMMON-CPP_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS})
    set(COMMON-CPP_LIBRARIES    ${COMMON-CPP_LIBRARIES}     ${OpenCV_LIBRARIES})
    add_definitions(-DCOMMON_CPP_HAS_OPENCV)
endif()

# find Boost
option(Boost_USE_STATIC_LIBS    ON)
option(Boost_USE_MULTITHREADED  ON)
option(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS filesystem system)
if (${Boost_FOUND})    
    set(COMMON-CPP_INCLUDE_DIRS ${COMMON-CPP_INCLUDE_DIRS}  ${Boost_INCLUDE_DIRS})
    set(COMMON-CPP_LIBRARIES    ${COMMON-CPP_LIBRARIES}     ${Boost_LIBRARIES})
    if (WIN32)
        # disable auto linking 
        #add_definitions(-DBOOST_ALL_NO_LIB)
        remove_definitions(-BOOST_NO_EXCEPTIONS)
    endif()
    if (NOT ${Boost_USE_STATIC_LIBS})
        # avoid invalid linking error when using shared libs
        add_definitions(-DBOOST_ALL_DYN_LINK)
    endif()
endif()

# include/linking
set(COMMON-CPP_LIBRARY ${COMMON-CPP_PROJECT})
add_library(${COMMON-CPP_LIBRARY} ${COMMON-CPP_LIBRARY_TYPE} ${COMMON-CPP_SOURCE_FILES} ${COMMON-CPP_HEADER_FILES})
set_target_properties(${COMMON-CPP_LIBRARY} PROPERTIES LINKER_LANGUAGE C++)
include_directories(${COMMON-CPP_INCLUDE_DIRS})
target_link_libraries(${COMMON-CPP_LIBRARY} ${COMMON-CPP_LIBRARIES})

# if (${COMMON-CPP_BUILD_TESTS}) 
    # set(COMMON-CPP_TESTS ${COMMON-CPP_PROJECT}_Test)
    # add_executable(${COMMON-CPP_TESTS} ${COMMON-CPP_SOURCE_TESTS} ${COMMON-CPP_HEADER_TESTS} ${COMMON-CPP_SOURCE_FILES} ${COMMON-CPP_HEADER_FILES})
    # target_link_libraries(${COMMON-CPP_TESTS} ${COMMON-CPP_LIBRARIES})
# endif()

# fix config paths as required
string(REGEX REPLACE "\\\\" "/" INSTALL_INCLUDE_DIR ${INSTALL_INCLUDE_DIR}) 
string(REGEX REPLACE "\\\\" "/" INSTALL_LIB_DIR     ${INSTALL_LIB_DIR}) 

# update config file
set(COMMON-CPP_CONFIG_INC   ${INSTALL_INCLUDE_DIR})
set(COMMON-CPP_CONFIG_LIB   ${INSTALL_LIB_DIR}/${COMMON-CPP_LIBRARY_EXT})
set(COMMON-CPP_CONFIG_FILE  ${COMMON-CPP_PROJECT}Config.cmake)
if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(COMMON-CPP_CONFIG_PATH ${COMMON-CPP_CONFIG_FILE})
else()
    set(COMMON-CPP_CONFIG_PATH ${CMAKE_BINARY_DIR}/${COMMON-CPP_CONFIG_FILE})
endif()
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")
configure_file(cmake/${COMMON-CPP_CONFIG_FILE}.in ${COMMON-CPP_CONFIG_PATH})

# install
install(TARGETS ${COMMON-CPP_PROJECT}
        EXPORT  ${COMMON-CPP_TARGETS}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
install(FILES   ${COMMON-CPP_HEADER_FILES} DESTINATION ${INSTALL_INCLUDE_DIR})
install(FILES   ${COMMON-CPP_CONFIG_PATH}  DESTINATION ${INSTALL_CMAKE_DIR})

# if (${COMMON-CPP_BUILD_TESTS})
    # install(TARGETS ${COMMON-CPP_TESTS} RUNTIME     DESTINATION ${INSTALL_BIN_DIR})
    # file(GLOB COMMON-CPP_IMGTEST_FILES ${COMMON-CPP_IMGTEST_DIR}/*)
    # install(FILES    ${COMMON-CPP_IMGTEST_FILES}    DESTINATION ${INSTALL_IMGTEST_DIR})
# endif()