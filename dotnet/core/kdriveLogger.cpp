//
// Copyright (c) 2002-2016 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#include "kdriveLogger.h"

namespace unmanaged
{

Poco::FastMutex ConsoleChannel::mutex_;

void ConsoleChannel::log(const Poco::Message& msg)
{
	Poco::FastMutex::ScopedLock lock(mutex_);
	System::String^ s = gcnew System::String(msg.getText().c_str());
	System::Console::WriteLine(s);
}

} // end namespace unmanaged
