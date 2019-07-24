//
// Copyright (c) 2002-2019 WEINZIERL ENGINEERING GmbH
// All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,
// WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
//

#pragma once

#include <windows.h>
#include <Poco/Exception.h>

namespace unmanaged
{

struct null_deleter
{
	void operator()(void const*) const
	{
	}
};

} // end namespace unmanaged

namespace kdrive
{
namespace interop
{

/*********************************
** String Conversions
**********************************/

class StringConvA
{
public:

	StringConvA(System::String^ s)
		: szAnsi_(static_cast<char*>(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s).ToPointer()))
	{
	}

	~StringConvA()
	{
		System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(szAnsi_));
	}

	operator LPCSTR() const
	{
		return szAnsi_;
	}

private:
	char* szAnsi_;
};

class StringConvW
{
public:

	StringConvW(System::String^ s)
		: szUnicode_(static_cast<wchar_t*>(System::Runtime::InteropServices::Marshal::StringToHGlobalUni(s).ToPointer()))
	{
	}

	~StringConvW()
	{
		System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr(szUnicode_));
	}

	operator LPCWSTR() const
	{
		return szUnicode_;
	}

private:
	wchar_t* szUnicode_;
};

#ifdef _UNICODE
#define StringConvT StringConvW
#else
#define StringConvT StringConvA
#endif

/*********************************
** Buffer Conversions
**********************************/

struct ArrayCreator
{
	static array<unsigned char>^ Copy(const unsigned char* buffer, int bufferSize)
	{
		array<unsigned char>^ a = gcnew array<unsigned char>(bufferSize);
		for (int i = 0; i < bufferSize; ++i)
		{
			a[i] = buffer[i];
		}
		return a;
	}
};

} // end namespace interop

/*********************************
** Exception Conversions
**********************************/

public ref class KdriveException : public System::ApplicationException
{
public:
	KdriveException()

		: ApplicationException()
	{
	}

	KdriveException(System::String^ message)

		: ApplicationException(message)
	{
	}


	KdriveException(System::String^ message, System::Exception^ innerException)

		: ApplicationException(message, innerException)
	{
	}

protected:
	KdriveException(System::Runtime::Serialization::SerializationInfo^ info, System::Runtime::Serialization::StreamingContext context)

		: ApplicationException(info, context)
	{
	}

};

struct ExceptionHandler
{
	static void Rethrow(std::exception& exception)
	{
		Poco::Exception* e = dynamic_cast<Poco::Exception*>(&exception);
		const std::string strError = e ? e->displayText() : exception.what();
		const std::wstring wstrError(strError.begin(), strError.end());
		System::String^ string = gcnew System::String(wstrError.c_str());
		throw gcnew KdriveException(string);
	}
};

} // end namespace kdrive

// The default exception handler to convert a std::exception / Poco::Exception
// into a managed C++ kdrive::rpc::netnnode::bindings::Exception
#define WZ_KDRIVE_CLR_DEFAULT_CATCH \
	catch (std::exception& exception) { kdrive::ExceptionHandler::Rethrow(exception); } \
	catch (...) { throw; }

// use this macro if you are returning a value from the function
// i.e. once this handler is invoked you never come out again as
// it throws an exception regardless
// this is to get rid of the compiler warning that not all return paths are covered
// i.e. either the return is successful, or we catch the exception and rethrow
#define WZ_KDRIVE_CLR_CATCH_BLACK_HOLE \
	catch (std::exception& exception) { kdrive::ExceptionHandler::Rethrow(exception); } \
	catch (...) { throw; } \
	throw gcnew kdrive::KdriveException("Should Never Reach This Exception!");
