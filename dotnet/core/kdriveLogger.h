//
// Copyright (c) 2002-2015 WEINZIERL ENGINEERING GmbH
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
#include "kdriveManagedConfig.h"
#include <kdrive/utility/LoggerFormatter.h>
#include <Poco/Logger.h>
#include <Poco/Channel.h>
#include <Poco/Message.h>
#include <Poco/Mutex.h>
#include <Poco/AutoPtr.h>
#using <mscorlib.dll>

namespace unmanaged
{

/// <summary>
/// Maps the Poco::Logger to the System::Console
/// </summary>
struct ConsoleChannel : public Poco::Channel
{
	virtual void log(const Poco::Message& msg);
	static Poco::FastMutex mutex_;
};

} // end namespace unmanaged

namespace kdrive
{

/// <summary>
/// Start/Stop the logging system
/// </summary>
/// <para>
/// If you start the logger you must stop it (i.e. on close, or app end)
///	to release the logging resources. If you don't stop the logger your
///	application may crash on exit
/// </para>
/// <para>
/// If you start the logger the output will appear on the console.
///	For non-console (i.e. gui) applications this is the output window of the
///	visual studio debugger
/// </para>
public ref class Logger
{
public:
	enum class Level
	{
		None = 0,
		Fatal,
		Critical,
		Error,
		Warning,
		Notice,
		Information,
		Debug,
		Trace
	};

	static void SetConsoleChannel()
	{
		try
		{
			kdrive::utility::LoggerFormatter loggerFormatter;
			Poco::AutoPtr<unmanaged::ConsoleChannel> channel = new unmanaged::ConsoleChannel;
			loggerFormatter.initLogger(channel);
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	static void SetFileChannel()
	{
		try
		{
			INIT_ROOT_FILE_LOGGER();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	static void SetFileChannel(System::String^ fileName)
	{
		try
		{
			std::string s = interop::StringConvA(fileName);
			kdrive::utility::LoggerFormatter loggerFormatter;
			loggerFormatter.initRootFileLogger(s);
			poco_information(Poco::Logger::root(), "File Logger Started");
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	static void Log(Level level, System::String^ message)		
	{
		try
		{
			std::string s = interop::StringConvA(message);

			switch (level)
			{
			case Level::None:
				break;

			case Level::Fatal:
				poco_fatal(logger(), s);
				break;

			case Level::Critical:
				poco_critical(logger(), s);
				break;

			case Level::Error:
				poco_error(logger(), s);
				break;

			case Level::Warning:
				poco_warning(logger(), s);
				break;

			case Level::Notice:
				poco_notice(logger(), s);
				break;

			case Level::Information:
				poco_information(logger(), s);
				break;

			case Level::Debug:
				poco_debug(logger(), s);
				break;

			case Level::Trace:
				poco_trace(logger(), s);
				break;

			default:
				poco_information(logger(), s);
				break;
			}
		} 
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	static void Dump(Level level, System::String^ message, array<unsigned char>^ data)
	{
		try
		{
			std::string s = interop::StringConvA(message);
			if (data->Length)
			{
				pin_ptr<unsigned char> pp = &data[0];
				const unsigned char* begin = pp;
				std::vector<unsigned char> v(begin, begin + data->Length);
				logger().dump(s, &v.at(0), v.size(), static_cast<Poco::Message::Priority>((int)level));
			}
			else
			{
				logger().dump(s, 0, 0, static_cast<Poco::Message::Priority>((int)level));
			}
		} 
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	static void Shutdown()
	{
		try
		{
			Poco::Logger::shutdown();
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

	static void SetLevels(Level level)
	{
		try
		{
			Poco::Logger::setLevel("", (int)level);
			Poco::Logger::root().setLevel((int)level);			
		}
		WZ_KDRIVE_CLR_DEFAULT_CATCH
	}

private:
	/*
		make the constructor private, because it's not needed. It's an static holder typ
	*/
	Logger::Logger()
	{
	}

	static Poco::Logger& logger()
	{
		return Poco::Logger::get("kdrive.dotnet");
	}
};

} // end namespace kdrive

