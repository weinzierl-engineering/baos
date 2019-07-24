#
# Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
# All rights reserved.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
# WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
#
#
# This module can be used to init the Qt settings.
# Typical usage could be something like:
#
#   In the root CMake file:
#   include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/qt.cmake)
#
#   Per project:
#   # ...
#   sdk_qt_wrap_ui(HEADER_FILES_UI ${UI_FILES})
#   sdk_qt_wrap_cpp(SOURCE_FILES_MOC ${HEADER_FILES_MOC})
#   # add qrc resources
#   sdk_qt_add_resources(SOURCE_FILES_QRC ${QRC_FILES})
#   # ...
#   # Use the Qt module (e.g. Widget) from Qt 5.
#   # (only needed for qt-5.0.x and qt-5.1.x; do nothings for other qt versions)
#   sdk_qt_use_modules(helloworld)
#   # ...
#   # Use the Qt module (e.g. Widget) from Qt 5.
#   target_link_libraries(helloworld ${LIBS} ${WZSDK_QT_LIBRARIES})
#
#
# Note: If Qt 5 is used than CMake > 2.8.11 is required.
# If you use a other CMake version, you need implement the older handling (e.g with qt5_use_modules)
#
#
# See also:
# http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html (Qt-5.0)
# http://qt-project.org/doc/qt-5/cmake-manual.html (Qt-5.2)


######################################################################
# used qt version
######################################################################

# set WZSDK_MAJOR_QT_VERSION if not exist; default is 4
# sdk_set_default_string(WZSDK_MAJOR_QT_VERSION "Major Qt version (4 or 5). Default value is Qt 4." "4")

# set list of possible values for the WZSDK_MAJOR_QT_VERSION cache variable
# set_property(CACHE WZSDK_MAJOR_QT_VERSION PROPERTY STRINGS "4;5")

message(STATUS "WZSDK_MAJOR_QT_VERSION='${WZSDK_MAJOR_QT_VERSION}'")

######################################################################
# init
######################################################################

# Qt 4.x
if(WZSDK_MAJOR_QT_VERSION STREQUAL "4")

  find_package(Qt4 REQUIRED)

  # add some useful macros and variables
  # (QT_USE_FILE is a variable defined by find_package(Qt4))
  include(${QT_USE_FILE})

  if (QT_LIBRARY_DIR AND MSYS)
    if (NOT EXISTS ${QT_LIBRARY_DIR}/libqtmain.a)
      message (FATAL_ERROR "It appears you're trying to use MSYS with Qt built by msvc")
    endif (NOT EXISTS ${QT_LIBRARY_DIR}/libqtmain.a)
  endif (QT_LIBRARY_DIR AND MSYS)

  LIST(APPEND WZSDK_QT_LIBRARIES ${QT_QTMAIN_LIBRARY})
  LIST(APPEND WZSDK_QT_LIBRARIES ${QT_LIBRARIES})

# Qt 5.x
elseif(WZSDK_MAJOR_QT_VERSION STREQUAL "5")

  if("${CMAKE_VERSION}" VERSION_LESS 2.8.11)
    message(ERROR "For Qt 5 is cmake >= 2.8.11 required")
  endif ()

  find_package(Qt5Widgets REQUIRED)
  find_package(Qt5Concurrent REQUIRED) # since qt 5.x is it split
  find_package(Qt5PrintSupport REQUIRED) # since qt 5.x is it split (need for QsciScintilla)
  find_package(Qt5Sql REQUIRED)

  if("${Qt5Widgets_VERSION}" VERSION_LESS 5.2.0)
    message (STATUS "Info: WZSDK_QT_LIBRARIES is empty because Qt-5.0.x or Qt-5.1.x is used")
  else()
    LIST(APPEND WZSDK_QT_LIBRARIES Qt5::Concurrent Qt5::Widgets Qt5::PrintSupport Qt5::Sql)
  endif()


# unsupported Qt version
else()
  message (FATAL_ERROR "Not support Qt major version: ${WZSDK_MAJOR_QT_VERSION}")

endif()

######################################################################
# config project
######################################################################

# sdk_qt_wrap_ui(outfiles inputfile)
# Note: inputfile is ARGN
macro(sdk_qt_wrap_ui outfiles)

	# Qt 4.x
	if(WZSDK_MAJOR_QT_VERSION STREQUAL "4")
	  qt4_wrap_ui(${outfiles} ${ARGN})

	# Qt 5.x
	elseif(WZSDK_MAJOR_QT_VERSION STREQUAL "5")
	  qt5_wrap_ui(${outfiles} ${ARGN})

	# unsupported Qt version
	else()
	  message (FATAL_ERROR "Not support Qt major version: ${WZSDK_MAJOR_QT_VERSION}")
	endif()

endmacro(sdk_qt_wrap_ui)

# sdk_qt_wrap_cpp(outfiles inputfile)
# Note: inputfile is ARGN
macro(sdk_qt_wrap_cpp outfiles)

	# Qt 4.x
	if(WZSDK_MAJOR_QT_VERSION STREQUAL "4")
	  qt4_wrap_cpp(${outfiles} ${ARGN})

	# Qt 5.x
	elseif(WZSDK_MAJOR_QT_VERSION STREQUAL "5")
	  qt5_wrap_cpp(${outfiles} ${ARGN})

	# unsupported Qt version
	else()
	  message (FATAL_ERROR "Not support Qt major version: ${WZSDK_MAJOR_QT_VERSION}")
	endif()

endmacro(sdk_qt_wrap_cpp)

# sdk_qt_add_resources(outfiles inputfile)
# Note: inputfile is ARGN
macro(sdk_qt_add_resources outfiles)

	# Qt 4.x
	if(WZSDK_MAJOR_QT_VERSION STREQUAL "4")
	  qt4_add_resources(${outfiles} ${ARGN})

	# Qt 5.x
	elseif(WZSDK_MAJOR_QT_VERSION STREQUAL "5")
	  qt5_add_resources(${outfiles} ${ARGN})

	# unsupported Qt version
	else()
	  message (FATAL_ERROR "Not support Qt major version: ${WZSDK_MAJOR_QT_VERSION}")
	endif()

endmacro(sdk_qt_add_resources)


# Workaround for  Qt 5.0.x or 5.1.x
# If you use Qt 5.0.x or 5.1.x then it is needed to call this function for each target.
# Nothing happen if you use an other Qt version.
#
# Indicates that the target uses the named Qt 5 modules. The target will be
# linked to the specified modules, use the include directories installed by
# those modules, use the COMPILE_DEFINITIONS set by those modules, and use
# the COMPILE_FLAGS set by the modules.
#
# Sample
# sdk_qt_use_modules(helloworld)
#
# This is the same (but it do it for all qt version) as you call:
# qt5_use_modules(helloworld Concurrent Widgets)
#
macro(sdk_qt_use_modules target_project)

	# Qt 5.x
	if(WZSDK_MAJOR_QT_VERSION STREQUAL "5")
		if("${Qt5Widgets_VERSION}" VERSION_LESS 5.2.0)
			LIST(APPEND WZSDK_QT_Modules Concurrent Widgets PrintSupport)
			if (Qt5Network_FOUND)
				LIST(APPEND WZSDK_QT_Modules Network)
			endif()
			if (Qt5Sql_FOUND)
				LIST(APPEND WZSDK_QT_Modules Sql)
			endif()

			qt5_use_modules(${target_project} ${WZSDK_QT_Modules})
		endif()
	endif()

endmacro(sdk_qt_use_modules)
