#
# Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
# All rights reserved.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
# WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
#

project(BAOS_SDK)
cmake_minimum_required(VERSION 3.0.0)

#  Libraries linked via full path no longer produce linker search paths. (since version 2.6)
cmake_policy(SET CMP0003 NEW)

# Automatically link Qt executables to qtmain target on Windows. (since version 2.8.11)
if(("${CMAKE_VERSION}" VERSION_GREATER 2.8.11) OR ("${CMAKE_VERSION}" VERSION_EQUAL 2.8.11))
  cmake_policy(SET CMP0020 NEW)
endif ()

######################################################################
# General
######################################################################

# ---------- ROOT PATH

set(BAOS_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# ---------- ADDITIONAL CMAKE FILES

include(${BAOS_SDK_DIR}/cmake/log.cmake)
include(${BAOS_SDK_DIR}/cmake/precompiled_headers.cmake)
include(${BAOS_SDK_DIR}/cmake/warning.cmake)
include(${BAOS_SDK_DIR}/cmake/set-options.cmake)

# ---------- USER OPTIONS 

# Provide user options to customise the build process

sdk_set_option(WZSDK_STATIC "Static build" TRUE)
sdk_set_option(WZSDK_SAMPLES "Build Samples" TRUE)
sdk_set_option(WZSDK_SAMPLES_QT "Build Qt Samples" FALSE)
sdk_set_option(WZSDK_BINDINGS "Build Bindings" TRUE)

# ---------- ENVIRONMENT

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

if (MSVC AND NOT WIN32_WINNT)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif ()

if (NOT APPLE)
  # Create debug libraries with d postfix
  set(CMAKE_DEBUG_POSTFIX "d")
endif ()

if (CMAKE_SYSTEM_NAME MATCHES Linux)
  # add _DEBUG to the debug flags, this is auto set in windows but not linux
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
endif ()

# Set compiler specific build flags
if (CMAKE_COMPILER_IS_GNUCXX)

  if ((NOT ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm.*")) AND
      (NOT ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "mipsel")))
    add_definitions(-msse)
  endif ()

  if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
    add_definitions(-fPIC)
  endif()

endif ()

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# We don't want to install in default system location, install is really for the SDK, so call it that
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)  
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/sdk" CACHE PATH "SDK install path" FORCE)
endif ()

# ---------- STATIC / SHARED BUILD DEFINITIONS

if (WZSDK_STATIC)
  set(WZSDK_LINKMODE STATIC)    
  add_definitions(-DKDRIVE_STATIC)
else ()
  set(WZSDK_LINKMODE SHARED)  
endif ()

MESSAGE( STATUS "Build libraries as ${WZSDK_LINKMODE}" )

######################################################################
# Third Party Source Libraries
######################################################################

# ---------- BOOST

# try and find boost
find_package(Boost)

# Add boost include path
if (Boost_INCLUDE_DIR)
  include_directories(SYSTEM "${Boost_INCLUDE_DIR}")
endif ()

# Add boost link path
if (Boost_LIBRARY_DIRS)
  link_directories("${Boost_LIBRARY_DIRS}")
endif ()

# ---------- QT

if (WZSDK_SAMPLES_QT)
  # qt 4/5 support
  # we have to set the version, either "4" or "5"
  set(WZSDK_MAJOR_QT_VERSION "5")
  include(${BAOS_SDK_DIR}/cmake/qt.cmake)
endif ()

######################################################################
# System Libraries
######################################################################

if (CMAKE_SYSTEM_NAME MATCHES Linux)
  SET(SYSTEM_LIBS pthread dl rt)
endif ()

if (WIN32)
   SET(SYSTEM_LIBS setupapi)
endif ()

######################################################################
# poco
######################################################################

# NOTE: We copy here some configuration stuff from poco/CMakeLists.txt.
# We want integrate it here in our sdk and we could not easy use the 
# CMakeLists.txt file from Poco

# ---------- POCO definitions

# root location of poco
set(POCO_DIR "${BAOS_SDK_DIR}/thirdparty/poco")

# poco version

file(STRINGS "${POCO_DIR}/libversion" SHARED_LIBRARY_VERSION)

# NOTE: We do here not read the version information from the VERSION file (as in poco sdk)
# because we have problems to compile it shared under linux.
# The content of Version is 1.6.0 (2014-12-22). And we get problems with (2014-12-22)
# So we hardcoded it here to 1.6.0 without 2014-12-22 suffix
set(PROJECT_VERSION "1.6.0")

include(${POCO_DIR}/cmake/PocoMacros.cmake)

# poco compiler flags

set(POCO_STATIC ${WZSDK_STATIC})

if (POCO_STATIC)
    add_definitions( -DPOCO_STATIC -DPOCO_NO_AUTOMATIC_LIBS)
    set( LIB_MODE STATIC )
else ()
    set( LIB_MODE SHARED )
endif(POCO_STATIC)

# poco system libraries
if (CMAKE_SYSTEM_NAME MATCHES Linux)
  SET(SYSLIBS pthread dl rt)
endif ()

# Foundation
include_directories("${POCO_DIR}/Foundation/include")
add_subdirectory(${POCO_DIR}/Foundation)

# Net
SET(ENABLE_NET ON)
include_directories("${POCO_DIR}/Net/include")
add_subdirectory(${POCO_DIR}/Net)

######################################################################
# kdrive (kdriveBAOS library)
######################################################################

set(KDRIVE_LIBRARY_NAME "kdriveBAOS")

# ---------- APPEND KDRIVE TARGET

include_directories("${BAOS_SDK_DIR}/kdrive/include")
add_subdirectory("${BAOS_SDK_DIR}/kdrive")

######################################################################
# dotnet bindings
######################################################################

if (WZSDK_BINDINGS AND MSVC)
  add_subdirectory(dotnet)
endif ()

######################################################################
# samples
######################################################################

if (WZSDK_SAMPLES)
  add_subdirectory(samples)
endif ()
