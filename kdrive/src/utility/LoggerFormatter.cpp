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

#include "pch/kdrive_pch.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Logger.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FileChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/Format.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Process.h>
#include <Poco/NumberFormatter.h>
#include <Poco/NumberParser.h>
#include <Poco/StringTokenizer.h>
#include <typeinfo>
#if KDRIVE_REMOTE_SYSLOG_LOGGER_ENABLED == 1
#include <Poco/Net/RemoteSyslogChannel.h>
#endif

using namespace kdrive::utility;
using Poco::AutoPtr;
using Poco::Channel;
using Poco::ConsoleChannel;
using Poco::Dynamic::Var;
using Poco::FileChannel;
using Poco::FormattingChannel;
using Poco::Logger;
using Poco::Path;
using Poco::File;
using Poco::PatternFormatter;
using Poco::Process;
using Poco::format;
using Poco::NumberFormatter;
using Poco::NumberParser;
using Poco::StringTokenizer;
#if KDRIVE_REMOTE_SYSLOG_LOGGER_ENABLED == 1
using Poco::Net::RemoteSyslogChannel;
#endif

LoggerFormatter::LoggerFormatter()

	: format_("%H:%M:%S:%i [%s] %t")
{
}

LoggerFormatter::LoggerFormatter(const std::string& format)

	: format_(format)
{
}

LoggerFormatter::~LoggerFormatter()
{
}

/*
	\note "" for channel name means all channels. When you use only the root logger
	then only the root and the new children use the new (currently configured) channel.
	Already existing logger are unchanged. Because we want that all use now the new channel
	we set it also for all with "" for channel name.
*/
void LoggerFormatter::initLogger(Channel* channel)
{
	AutoPtr<Poco::PatternFormatter> patternFormatter = new PatternFormatter(format_);
	patternFormatter->setProperty(PatternFormatter::PROP_TIMES, "local");
	AutoPtr<FormattingChannel> formattingChannel = new FormattingChannel(patternFormatter, channel);
	Logger::root().setChannel(formattingChannel);
	Logger::setChannel("", formattingChannel);
}

void LoggerFormatter::initRootConsoleLogger()
{
	AutoPtr<ConsoleChannel> channel = new ConsoleChannel;
	initLogger(channel);
}

void LoggerFormatter::initRootFileLogger()
{
	const int pid = static_cast<int>(Process::id());
	const std::string filename = format("logfile_%d.txt", pid);
	const Path path(Path::current(), filename);
	initRootFileLogger(path.toString());
}

void LoggerFormatter::initRootFileLogger(const std::string& filename)
{
	try
	{
		Path path(filename);
		File f1(path.parent());
		f1.createDirectories();
		File f2(filename);
		f2.createFile();
	}
	catch (...)
	{
	}

	AutoPtr<FileChannel> channel = new Poco::FileChannel(filename);
	initLogger(channel);
}

#if KDRIVE_REMOTE_SYSLOG_LOGGER_ENABLED == 1

void LoggerFormatter::initRootRemoteLogger(const std::string& address, const std::string& name)
{
	AutoPtr<RemoteSyslogChannel> channel = new RemoteSyslogChannel(address, name);
	initLogger(channel);
}

#endif

void LoggerFormatter::setFormat(const std::string& format)
{
	format_ = format;
}

const std::string& LoggerFormatter::getFormat() const
{
	return format_;
}

std::string LoggerFormatter::toHex(const std::vector<unsigned char>& v)
{
	return v.empty() ? "" : toHex(&v.at(0), v.size());
}

std::string LoggerFormatter::toHex(const unsigned char* buffer, std::size_t bufferSize)
{
	std::string s;

	for (std::size_t index = 0; index < bufferSize; ++index)
	{
		if (index)
		{
			s.append(" ");
		}
		s.append(NumberFormatter::formatHex(buffer[index], 2));
	}

	return s;
}

std::string LoggerFormatter::toHex(const std::vector<unsigned short>& v)
{
	return v.empty() ? "" : toHex(&v.at(0), v.size());
}

std::string LoggerFormatter::toHex(const unsigned short* buffer, std::size_t bufferSize)
{
	std::string s;

	for (std::size_t index = 0; index < bufferSize; ++index)
	{
		if (index)
		{
			s.append(" ");
		}
		s.append(NumberFormatter::formatHex(buffer[index], 4));
	}

	return s;
}

std::string LoggerFormatter::toHex(const std::vector<std::vector<unsigned char> >& values)
{
	std::string s;

	std::vector<std::vector<unsigned char> >::const_iterator iter = values.begin();
	for ( ; iter != values.end(); ++iter)
	{
		if (iter != values.begin())
		{
			s += ", ";
		}
		s += toHex(*iter);
	}

	return s;
}

std::string LoggerFormatter::toString(const std::vector<int>& v)
{
	return v.empty() ? "" : toString(&v.at(0), v.size());
}

std::string LoggerFormatter::toString(const int* buffer, std::size_t bufferSize)
{
	std::string s;

	for (std::size_t index = 0; index < bufferSize; ++index)
	{
		if (index)
		{
			s.append(" ");
		}
		s.append(NumberFormatter::format(buffer[index]));
	}

	return s;
}

std::string LoggerFormatter::toString(const Var& var, bool showHex, bool showDec)
{
	std::string s;

	try
	{
		if (var.isEmpty())
		{
			s = "is empty";
		}
		else if (var.type() == typeid(bool))
		{
			s = var.convert<std::string>();
		}
		else if (var.type() == typeid(unsigned char))
		{
			const unsigned int data = var.extract<unsigned char>();
			s = showDec ? NumberFormatter::format(data) : "";
			s += showDec && showHex ? " = " : "";
			s += showHex ? format("0x%02X", data) : "";
		}
		else if (var.type() == typeid(unsigned short))
		{
			const unsigned int data = var.extract<unsigned short>();
			s = showDec ? NumberFormatter::format(data) : "";
			s += showDec && showHex ? " = " : "";
			s += showHex ? format("0x%04X", data) : "";
		}
		else if (var.type() == typeid(unsigned int))
		{
			const unsigned int data = var.extract<unsigned int>();
			s = showDec ? NumberFormatter::format(data) : "";
			s += showDec && showHex ? " = " : "";
			s += showHex ? format("0x%08X", data) : "";
		}
		else if (var.type() == typeid(std::vector<unsigned char>))
		{
			const std::vector<unsigned char>& data = var.extract<std::vector<unsigned char> >();
			s = toHex(data);
		}
		else if (var.type() == typeid(std::vector<unsigned short>))
		{
			const std::vector<unsigned short>& values = var.extract<std::vector<unsigned short> >();
			s = toHex(values);
		}
		else if (var.type() == typeid(std::vector<int>))
		{
			const std::vector<int>& values = var.extract<std::vector<int> >();
			s = toString(values);
		}
		else if (var.type() == typeid(std::vector<std::vector<unsigned char> >))
		{
			const std::vector<std::vector<unsigned char> >& values = var.extract<std::vector<std::vector<unsigned char> > >();
			s = toHex(values);
		}
		else
		{
			s = var.convert<std::string>();
		}
	}
	catch (...)
	{
		s = "?";
	}

	return s;
}

std::vector<unsigned char> LoggerFormatter::parseHex(const std::string& hexString)
{
	std::vector<unsigned char> v;
	StringTokenizer stringTokenizer(hexString, " ", StringTokenizer::TOK_TRIM);
	StringTokenizer::Iterator iter = stringTokenizer.begin();
	StringTokenizer::Iterator end = stringTokenizer.end();
	for (; iter != end; ++iter)
	{
		unsigned char value = NumberParser::parseHex(*iter);
		v.push_back(value);
	}
	return v;
}
