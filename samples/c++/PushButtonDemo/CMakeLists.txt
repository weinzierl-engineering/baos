#
# Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
# All rights reserved.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
# WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
#

######################################################################
# BAOS sample PushButtonDemo
######################################################################

# ---------- SOURCE AND HEADER FILES

set (HEADER_FILES
)

set (HEADER_FILES_MOC
    mainwindow.h
)

set (SOURCE_FILES
    main.cpp
    mainwindow.cpp
)

set (UI_FILES
    mainwindow.ui
)

set (QRC_FILES
    PushButtonDemo.qrc
)

# ---------- TARGET

set(target_APP sample_PushButtonDemo)

sdk_qt_wrap_ui(HEADER_FILES_UI ${UI_FILES})
sdk_qt_wrap_cpp(SOURCE_FILES_MOC ${HEADER_FILES_MOC})

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add qrc resources
sdk_qt_add_resources(SOURCE_FILES_QRC ${QRC_FILES})

# create an executable file named "sample_PushButtonDemo" from the source files in the variable "qtproject_SRCS".
add_executable(${target_APP} WIN32 
	${HEADER_FILES} 
	${HEADER_FILES_MOC} 
	${HEADER_FILES_UI} 
	${SOURCE_FILES} 
	${SOURCE_FILES_MOC}
	${SOURCE_FILES_QRC}
)

# link the "sample_PushButtonDemo" target against the Qt libraries. 
sdk_qt_use_modules(${target_APP}) # workaround for Qt-5.0.x and Qt-5.1.x

# the sample need kdrive, Poco Foundation, Poco Net and Qt (and some system libraries)
add_dependencies(${target_APP} ${KDRIVE_LIBRARY_NAME})
target_link_libraries(${target_APP} ${KDRIVE_LIBRARY_NAME} Net Foundation ${WZSDK_QT_LIBRARIES} ${SYSTEM_LIBS})

