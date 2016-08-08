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

set(samples_TARGETS 
  BaosDatapointDescription
  BaosEnumerator
  BaosEventListener
  BaosLightSwitcher
  BaosMultiConnector
  BaosMultiThreaded
  BaosSerial
  BaosSerialLightSwitcher
  BaosServerItem
)

set(LIBS ${KDRIVE_LIBRARY_NAME} Net Foundation ${SYSTEM_LIBS})

foreach(sample ${samples_TARGETS})
  set(target_APP "sample_${sample}")
  add_executable(${target_APP} ${sample}.cpp)
  add_dependencies(${target_APP} ${KDRIVE_LIBRARY_NAME})
  target_link_libraries(${target_APP} ${LIBS})
endforeach(sample)

if (WZSDK_SAMPLES_QT)
  add_subdirectory(PushButtonDemo)
endif ()