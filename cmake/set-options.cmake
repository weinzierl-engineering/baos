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

MACRO(sdk_set_default_string c desc value)
  if (NOT DEFINED ${c})
    set(${c} ${value} CACHE STRING ${desc}) 
  endif ()
   
endmacro() 

MACRO(sdk_set_component c value)
  if (NOT DEFINED ${c})
    set(${c} ${value}) 
    MESSAGE(STATUS "Build ${c} ${value}")
  else ()
    MESSAGE(STATUS "Build ${c} (user defined value)")
  endif ()
  
  if (${c})
	add_definitions(-D${c}_ENABLED)
  endif ()
    
endmacro() 

MACRO(sdk_set_option c desc value)
  if (NOT DEFINED ${c})
    option(${c} ${desc} ${value})
    MESSAGE(STATUS "Option ${c} ${value}")
  else ()
    MESSAGE(STATUS "Option ${c} (user defined value)")
  endif ()
  
  if (${c})
	add_definitions(-D${c}_ENABLED)
  endif ()
  
endmacro() 
