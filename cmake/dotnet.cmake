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

# set the target framework (.net) version
# the VS specific default frameworks are:
# VS 2008: 3.5; VS 2010: 4.0; VS 2012: 4.5
# NOTE: Currently implemented for VS 2008
# FRAMEWORK_VERSION: e.g. "2.0", "3.5", ...
function(set_dotnet_target_framework_version TARGET_PROJECT FRAMEWORK_VERSION)
  if(MSVC)
  
    # Visual Studio 2008
	# It used a decimal value e.g. "131072" for .net 2.0
	# It is not possibile to use .net version > 3.5
	# See: http://social.msdn.microsoft.com/Forums/vstudio/en-US/09a309a0-a8fc-407d-9fb5-7e1c1a26d397/net-framework-4-with-visual-studio-2008-and-use-it-in-vs-2008?forum=netfxsetup
	if(MSVC90)
	
	  # .net 2.0
	  if(FRAMEWORK_VERSION STREQUAL "2.0")
	    set(VERSION_STR "131072")
	  # .net 3.0
	  elseif(FRAMEWORK_VERSION STREQUAL "3.0")
	    set(VERSION_STR "196608")
	  # .net 3.5
	  elseif(FRAMEWORK_VERSION STREQUAL "3.5")
	    set(VERSION_STR "196613")
	  else()
        message (FATAL_ERROR "Visual Studio 2008 do not support .net framework: ${FRAMEWORK_VERSION}")	  
	  endif()
	 
	else()
	  message (FATAL_ERROR "set_dotnet_target_framework_version is not implemented for current compiler")	
	endif(MSVC90)
	
    # set the target framework (.net) version
	message (STATUS "Use .net target framework version: ${FRAMEWORK_VERSION}")	
    set_target_properties(${TARGET_PROJECT} PROPERTIES VS_DOTNET_TARGET_FRAMEWORK_VERSION ${VERSION_STR}) 

  endif(MSVC)
endfunction(set_dotnet_target_framework_version)
