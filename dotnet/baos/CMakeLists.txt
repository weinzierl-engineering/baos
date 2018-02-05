#
# Copyright (c) 2002-2018 WEINZIERL ENGINEERING GmbH
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
# .net bindings for kdriveBAOS
######################################################################

if (NOT MSVC)
  message (FATAL_ERROR "You need a MSVC compiler to build this library.")
endif ()

# ---------- SOURCE AND HEADER FILES

set (HEADER_FILES
	../core/kdriveManagedConfig.h		
	../core/kdriveManagedInterop.h	
	../core/kdriveLogger.h
	BaosConnection.h
	BaosDatapoint.h
	BaosDatapointDescriptions.h
	BaosEvent.h
	BaosHeartbeat.h
	BaosParameter.h
	BaosServerItems.h
	Connector.h
	StreamConnection.h
	README.h
)

set (SOURCE_FILES
	../core/kdriveLogger.cpp
	AssemblyInfo.cpp
	BaosConnection.cpp
	BaosDatapoint.cpp
	BaosDatapointDescriptions.cpp
	BaosEvent.cpp
	BaosHeartbeat.cpp
	BaosParameter.cpp
	BaosServerItems.cpp
	Connector.cpp
	StreamConnection.cpp
	kdriveBAOS_dotnet.rc
)

# ---------- TARGET

set(target_APP kdriveBAOS_dotnet)

# add clr compile flags
string(REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /clr")

add_library(${target_APP} SHARED ${HEADER_FILES} ${SOURCE_FILES})

# sets the "keyword" attribute in the project file (otherwise default value is "Win32Proj")
# needed when you want changed some .net specific properties e.g. target framework version 
set_target_properties(${target_APP} PROPERTIES VS_GLOBAL_KEYWORD "ManagedCProj") 

# it need kdrive, Poco Foundation, Poco Net (and some system libraries)
add_dependencies(${target_APP} ${KDRIVE_LIBRARY_NAME})
target_link_libraries(${target_APP} ${KDRIVE_LIBRARY_NAME} Net Foundation ${SYSTEM_LIBS})
