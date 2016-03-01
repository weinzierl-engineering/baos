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

#
# Toolchain file for building for Raspberry Pi
#
# Download cross compiler
# -----------------------
# https://github.com/raspberrypi/tools
#
# Install it
# ----------
# unpack it to /opt/toolchains/raspberrypi
# When you use an other path then set toolchain_dir
#
# Usage
# -----
# cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/raspbian-toolchain.cmake ..
#

set(toolchain_dir /opt/toolchains/raspberrypi/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian)

set(toolchain_bin_dir ${toolchain_dir}/bin)
set(toolchain_libc_dir ${toolchain_dir}/arm-linux-gnueabihf)
set(toolchain_inc_dir ${toolchain_libc_dir}/include)
set(toolchain_lib_dir ${toolchain_libc_dir}/lib)

set(CMAKE_SYSTEM_NAME Linux CACHE INTERNAL "system name")
set(CMAKE_SYSTEM_PROCESSOR arm CACHE INTERNAL "processor")
set(CMAKE_C_COMPILER ${toolchain_bin_dir}/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${toolchain_bin_dir}/arm-linux-gnueabihf-g++)
set(CMAKE_AR ${toolchain_bin_dir}/arm-linux-gnueabihf-ar CACHE FILEPATH "archiver")
set(CMAKE_LINKER ${toolchain_bin_dir}/arm-linux-gnueabihf-ld CACHE FILEPATH "linker")
set(CMAKE_NM ${toolchain_bin_dir}/arm-linux-gnueabihf-nm CACHE FILEPATH "nm")
set(CMAKE_OBJCOPY ${toolchain_bin_dir}/arm-linux-gnueabihf-objcopy CACHE FILEPATH "objcopy")
set(CMAKE_OBJDUMP ${toolchain_bin_dir}/arm-linux-gnueabihf-objdump CACHE FILEPATH "objdump")
set(CMAKE_STRIP ${toolchain_bin_dir}/arm-linux-gnueabihf-strip CACHE FILEPATH "strip")
set(CMAKE_RANLIB ${toolchain_bin_dir}/arm-linux-gnueabihf-ranlib CACHE FILEPATH "ranlib")
set(CMAKE_C_FLAGS "-isystem ${toolchain_inc_dir} -fPIC" CACHE INTERNAL "c compiler flags")
set(CMAKE_CXX_FLAGS "-isystem ${toolchain_inc_dir} -fPIC" CACHE INTERNAL "cxx compiler flags")

set(link_flags -L${toolchain_lib_dir})
set(CMAKE_EXE_LINKER_FLAGS ${link_flags} CACHE INTERNAL "exe link flags")
set(CMAKE_MODULE_LINKER_FLAGS ${link_flags} CACHE INTERNAL "module link flags")
set(CMAKE_SHARED_LINKER_FLAGS ${link_flags} CACHE INTERNAL "shared lnk flags")

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH ${toolchain_libc_dir} CACHE INTERNAL "cross root directory")

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, 
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER CACHE INTERNAL "")
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY CACHE INTERNAL "")
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY CACHE INTERNAL "")
