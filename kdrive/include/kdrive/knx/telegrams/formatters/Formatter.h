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

#ifndef __KDRIVE_KNX_TELEGRAMS_FORMATTERS_FORMATTER_H__
#define __KDRIVE_KNX_TELEGRAMS_FORMATTERS_FORMATTER_H__

#include "kdrive/knx/Config.h"
#include "kdrive/knx/core/Buffer.h"
#include <vector>

namespace kdrive
{
namespace knx
{

/**************************************
** AbstractFormatter
***************************************/

struct kdriveKnx_API AbstractFormatter
{
	AbstractFormatter();
	virtual ~AbstractFormatter();

	/*
		Returns the formatter size
	*/
	virtual std::size_t size() const = 0;

	/*!
		Reads from the buffer into local storage
	*/
	std::size_t read(std::vector<unsigned char>& buffer);

	/*!
		Reads from the buffer into local storage
	*/
	std::size_t read(const Buffer& buffer);

	/*!
		Writes to the buffer from local storage
		Resizes the buffer to the formatter size.
		(i.e. the buffer can be empty)
	*/
	std::size_t write(std::vector<unsigned char>& buffer);

	/*!
		Writes to the buffer from local storage
		\exception(Poco::Exception) If buffer is too small.
	*/
	std::size_t write(Buffer& buffer);

	/*
		Returns true if the formatter is valid
	*/
	virtual bool isValid() const = 0;

	/*!
		Sets the formatter default values (if any)
	*/
	virtual void setDefaults();

protected:
	virtual void prepareRead();
	virtual void postRead();
	virtual void prepareWrite();
	virtual void postWrite();

private:
	/*!
		Reads from the buffer into local storage
	*/
	virtual std::size_t readImpl(const Buffer& buffer) = 0;

	/*!
		Writes to the buffer from local storage
	*/
	virtual std::size_t writeImpl(Buffer& buffer) = 0;
};

/*********************************
** FormatterReader
**********************************/

template <class T>
struct FormatterReader : public T
{
	FormatterReader(unsigned char* buffer, std::size_t bufferSize)
	{
		Buffer b;
		b.setBuffer(buffer, bufferSize);
		T::read(b);
	}

	FormatterReader(const unsigned char* buffer, std::size_t bufferSize)
	{
		Buffer b;
		b.setBuffer(const_cast<unsigned char*>(buffer), bufferSize);
		T::read(b);
	}

	FormatterReader(std::vector<unsigned char>& buffer)
	{
		T::read(buffer);
	}
};

/**************************************
** Null Formatter
***************************************/

class kdriveKnx_API NullFormatter : public AbstractFormatter
{
public:
	NullFormatter();
	NullFormatter(unsigned char value);
	virtual ~NullFormatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

	void set(unsigned char value);
	unsigned char get() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);
};

/**************************************
** ByteFormatter
***************************************/

class kdriveKnx_API ByteFormatter : public AbstractFormatter
{
public:
	ByteFormatter();
	ByteFormatter(unsigned char value);
	virtual ~ByteFormatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

	void set(unsigned char value);
	unsigned char get() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);

private:
	unsigned char value_;
};

/**************************************
** WordFormatter
***************************************/

class kdriveKnx_API WordFormatter : public AbstractFormatter
{
public:
	WordFormatter();
	WordFormatter(unsigned short value);
	virtual ~WordFormatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

	void set(unsigned short value);
	unsigned short get() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);

private:
	unsigned short value_;
};

/**************************************
** UIntFormatter
***************************************/

class kdriveKnx_API UIntFormatter : public AbstractFormatter
{
public:
	UIntFormatter();
	UIntFormatter(unsigned int value);
	virtual ~UIntFormatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

	void set(unsigned int value);
	unsigned int get() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);

private:
	unsigned int value_;
};

/**************************************
** Formatter
***************************************/

class kdriveKnx_API Formatter : public AbstractFormatter
{
public:
	Formatter();
	virtual ~Formatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

protected:
	typedef std::vector<AbstractFormatter*> Formatters;

protected:
	std::size_t readFromBuffer(const Buffer& buffer);
	std::size_t writeToBuffer(Buffer& buffer);
	void addFormatter(AbstractFormatter* formatter);
	void insertFormatter(AbstractFormatter* formatter, int index);
	void removeFormatter(AbstractFormatter* formatter);
	const Formatters& getFormatters() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);

private:
	Formatters formatters_;
};

/**************************************
** GreedyFormatter
***************************************/

/*!
	By default there is no limit. (limit_ = -1)
*/
class kdriveKnx_API GreedyFormatter : public AbstractFormatter
{
public:
	GreedyFormatter();
	virtual ~GreedyFormatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

	void setBuffer(const std::vector<unsigned char>& buffer);
	const std::vector<unsigned char>& getBuffer() const;
	std::vector<unsigned char>& getBuffer();

	/*!
		Set the limit.
		If limit < 0 the formatter is not limited.
	*/
	void setLimit(int limit);

	/*!
		Gets the limit.
	*/
	int getLimit() const;

	/*!
		Returns true, if the formatter is limited.
	*/
	bool isLimited() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);

private:
	std::vector<unsigned char> buffer_;
	int limit_;
};

/**************************************
** DelimitedGreedyFormatter
***************************************/

template <int limit>
struct kdriveKnx_API DelimitedGreedyFormatter : public GreedyFormatter
{
	DelimitedGreedyFormatter()
	{
		setLimit(limit);
	}

	virtual ~DelimitedGreedyFormatter()
	{
	}

	virtual void setDefaults()
	{
		setLimit(limit);
	}
};

/**************************************
** WordListFormatter
***************************************/

/*!
	This formatter is similarly to the GreedyFormatter.
	It reads/writes a list of unsigned short values from a buffer
*/
class kdriveKnx_API WordListFormatter : public AbstractFormatter
{
public:
	WordListFormatter();
	virtual ~WordListFormatter();

	virtual std::size_t size() const;
	virtual bool isValid() const;

	void set(const std::vector<unsigned short>& values);
	const std::vector<unsigned short>& get() const;

private:
	virtual std::size_t readImpl(const Buffer& buffer);
	virtual std::size_t writeImpl(Buffer& buffer);

private:
	std::vector<unsigned short> values_;
};

}
} // end namespace kdrive::knx

#endif // __KDRIVE_KNX_TELEGRAMS_FORMATTERS_FORMATTER_H__
