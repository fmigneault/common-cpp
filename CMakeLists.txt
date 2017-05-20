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
else()
    set(CMAKE_CXX_COMPILER g++)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif()

# options
option(CommonCpp_BUILD_TESTS "Build tests" OFF)

# set projet paths/files
set(CommonCpp_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CommonCpp_INC_DIR  ${CommonCpp_ROOT_DIR}/inc)
set(CommonCpp_SRC_DIR  ${CommonCpp_ROOT_DIR}/src)
set(CommonCpp_IMG_DIR  ${CommonCpp_ROOT_DIR}/img)
set(CommonCpp_TEST_DIR ${CommonCpp_ROOT_DIR}/test)
set(CommonCpp_INCLUDE_DIRS ${CommonCpp_INC_DIR} CACHE PATH "Include directories of Common (C++)" FORCE)
set(CommonCpp_SOURCES_DIRS ${CommonCpp_SRC_DIR} CACHE PATH "Sources directories of Common (C++)" FORCE)
file(GLOB CommonCpp_HEADER_FILES "${CommonCpp_INC_DIR}/*.h" "${CommonCpp_INC_DIR}/*.hpp")
file(GLOB CommonCpp_SOURCE_FILES "${CommonCpp_SRC_DIR}/*.c" "${CommonCpp_SRC_DIR}/*.cpp")
file(GLOB CommonCpp_HEADER_TESTS "${CommonCpp_TEST_DIR}/*.h" "${CommonCpp_TEST_DIR}/*.hpp")
file(GLOB CommonCpp_SOURCE_TESTS "${CommonCpp_TEST_DIR}/*.c" "${CommonCpp_TEST_DIR}/*.cpp")

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INC_DIR inc CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/${CommonCpp_PROJECT})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed for config install)
foreach(p LIB BIN INC CMAKE)
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
if(${OpenCV_FOUND})
    set(CommonCpp_INCLUDE_DIRS ${CommonCpp_INCLUDE_DIRS}  ${OpenCV_INCLUDE_DIRS})
    set(CommonCpp_LIBRARIES    ${CommonCpp_LIBRARIES}     ${OpenCV_LIBRARIES})
    add_definitions(-DCOMMON_CPP_HAS_OPENCV)
endif()

# find Boost
option(Boost_USE_STATIC_LIBS    OFF)
option(Boost_USE_MULTITHREADED  ON)
option(Boost_USE_STATIC_RUNTIME OFF)
if(${CommonCpp_BUILD_TESTS})
    find_package(Boost REQUIRED COMPONENTS filesystem system unit_test_framework)
else()
    find_package(Boost REQUIRED COMPONENTS filesystem system)
endif()
if(${Boost_FOUND})    
    set(CommonCpp_INCLUDE_DIRS  ${CommonCpp_INCLUDE_DIRS}   ${Boost_INCLUDE_DIRS})
    set(CommonCpp_LIBRARIES     ${CommonCpp_LIBRARIES}      ${Boost_LIBRARIES})
    set(CommonCpp_LINK_DIRS     ${CommonCpp_LINK_DIRS}      ${Boost_LIBRARY_DIRS})
    if(WIN32)
        # disable auto linking 
        #add_definitions(-DBOOST_ALL_NO_LIB)
        #remove_definitions(-BOOST_NO_EXCEPTIONS)
    endif()
    # if(NOT ${Boost_USE_STATIC_LIBS})
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
link_directories(${CommonCpp_LINK_DIRS})
target_link_libraries(${CommonCpp_LIBRARY} ${CommonCpp_LIBRARIES})

if(${CommonCpp_BUILD_TESTS}) 
    set(CommonCpp_TEST ${CommonCpp_PROJECT}_Test)
    add_executable(${CommonCpp_TEST} ${CommonCpp_SOURCE_TESTS} ${CommonCpp_HEADER_TESTS})
    target_include_directories(${CommonCpp_TEST} PUBLIC ${CommonCpp_INCLUDE_DIRS})    
    target_link_libraries(${CommonCpp_TEST} ${CommonCpp_LIBRARIES} ${CommonCpp_PROJECT})
endif()

# fix config paths as required
string(REGEX REPLACE "\\\\" "/" INSTALL_INC_DIR ${INSTALL_INC_DIR}) 
string(REGEX REPLACE "\\\\" "/" INSTALL_LIB_DIR ${INSTALL_LIB_DIR}) 

# update config file
set(CommonCpp_CONFIG_INC   ${INSTALL_INC_DIR})
set(CommonCpp_CONFIG_LIB   ${INSTALL_LIB_DIR}/${CommonCpp_LIBRARY_EXT})
set(CommonCpp_CONFIG_FILE  ${CommonCpp_PROJECT}Config.cmake)
if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    set(CommonCpp_CONFIG_PATH ${CommonCpp_CONFIG_FILE})
else()
    set(CommonCpp_CONFIG_PATH ${CMAKE_BINARY_DIR}/${CommonCpp_CONFIG_FILE})
endif()
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INC_DIR}")
configure_file(cmake/${CommonCpp_CONFIG_FILE}.in ${CommonCpp_CONFIG_PATH})

# install
install(TARGETS ${CommonCpp_PROJECT}
        EXPORT  ${CommonCpp_TARGETS}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
install(FILES   ${CommonCpp_HEADER_FILES} DESTINATION ${INSTALL_INC_DIR})
install(FILES   ${CommonCpp_CONFIG_PATH}  DESTINATION ${INSTALL_CMAKE_DIR})

# if(${CommonCpp_BUILD_TESTS})
    # install(TARGETS ${CommonCpp_TEST_DIRS} RUNTIME  DESTINATION ${INSTALL_BIN_DIR})
    # file(GLOB CommonCpp_IMG_TESTS ${CommonCpp_IMG_DIR}/*)
    # install(FILES   ${CommonCpp_IMG_TESTS}  DESTINATION ${INSTALL_IMG_DIR})
# endif()

# extra definitions for msvc (avoid linking problems)
if(MSVC)
    target_compile_options(${CommonCpp_PROJECT}         PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_compile_definitions(${CommonCpp_PROJECT}     PRIVATE "-D_ITERATOR_DEBUG_LEVEL=$<$<CONFIG:Debug>:2;_DEBUG>$<$<NOT:$<CONFIG:Debug>>:0>")
    if(${CommonCpp_BUILD_TESTS})
        target_compile_options(${CommonCpp_TEST}        PRIVATE "/MD$<$<CONFIG:Debug>:d>")
        target_compile_definitions(${CommonCpp_TEST}    PRIVATE "-D_ITERATOR_DEBUG_LEVEL=$<$<CONFIG:Debug>:2;_DEBUG>$<$<NOT:$<CONFIG:Debug>>:0>")
    endif()    
endif()
