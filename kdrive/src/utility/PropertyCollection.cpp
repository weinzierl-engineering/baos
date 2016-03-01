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

#include "pch/kdrive_pch.h"
#include "kdrive/utility/PropertyCollection.h"
#include "kdrive/utility/Logger.h"
#include "kdrive/utility/LoggerFormatter.h"
#include <Poco/Exception.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Format.h>

using namespace kdrive::utility;
using Poco::Dynamic::Var;
using Poco::ScopedLock;
using Poco::FastMutex;
using Poco::Exception;
using Poco::NotFoundException;
using Poco::StringTokenizer;
using Poco::format;

CLASS_LOGGER("kdrive.utility.PropertyCollection")

/*******************************
** PropertyCollection
********************************/

PropertyCollection::PropertyCollection()
{
}

PropertyCollection::PropertyCollection(const PropertyCollection& propertyCollection)

	: map_(propertyCollection.map_)
	, mapMeta_(propertyCollection.mapMeta_)
{
}

PropertyCollection::~PropertyCollection()
{
}

PropertyCollection& PropertyCollection::operator=(const PropertyCollection& propertyCollection)
{
	if (this != &propertyCollection)
	{
		map_ = propertyCollection.map_;
		mapMeta_ = propertyCollection.mapMeta_;
	}
	return *this;
}

void PropertyCollection::setProperty(const std::string& key, const Var& value)
{
	ScopedLock<FastMutex> lock(mutex_);
	setPropertyUnsafe(key, value);
}

const Poco::Dynamic::Var& PropertyCollection::getProperty(const std::string& key) const
{
	ScopedLock<FastMutex> lock(mutex_);
	return getPropertyUnsafe(key);
}

const Poco::Dynamic::Var& PropertyCollection::getProperty(const std::string& key,
        const Poco::Dynamic::Var& defaultValue) const
{
	ScopedLock<FastMutex> lock(mutex_);
	return getPropertyUnsafe(key, defaultValue);
}

void PropertyCollection::removeProperty(const std::string& key)
{
	ScopedLock<FastMutex> lock(mutex_);
	Map::iterator iter = map_.find(key);
	if (iter != map_.end())
	{
		map_.erase(iter);
	}
}

bool PropertyCollection::isEmpty() const
{
	ScopedLock<FastMutex> lock(mutex_);
	return map_.empty();
}

bool PropertyCollection::isEmpty(const std::string& key) const
{
	ScopedLock<FastMutex> lock(mutex_);
	Map::const_iterator iter = map_.find(key);
	if (iter != map_.end())
	{
		const Var& value = iter->second;
		return value.isEmpty() ? true : false;
	}
	return true;
}

void PropertyCollection::clear()
{
	ScopedLock<FastMutex> lock(mutex_);
	map_.clear();
}

bool PropertyCollection::hasPropertyKey(const std::string& key) const
{
	ScopedLock<FastMutex> lock(mutex_);
	Map::const_iterator iter = map_.find(key);
	return iter != map_.end() ? true : false;
}

void PropertyCollection::keys(std::vector<std::string>& keys) const
{
	const std::string empty;
	PropertyCollection::keys(empty, keys);
}

void PropertyCollection::keys(const std::string& substr, std::vector<std::string>& keys) const
{
	ScopedLock<FastMutex> lock(mutex_);
	Map::const_iterator iter = map_.begin();
	Map::const_iterator end = map_.end();
	for (; iter != end; ++iter)
	{
		if ((substr.empty()) || (iter->first.find(substr) == 0))
		{
			keys.push_back(iter->first);
		}
	}
}

void PropertyCollection::filter(const std::string& substr, PropertyCollection& propertyCollection) const
{
	ScopedLock<FastMutex> lock(mutex_);

	Map::const_iterator iter = map_.begin();
	Map::const_iterator end = map_.end();
	for (; iter != end; ++iter)
	{
		if (substr.empty() || iter->first.find(substr) == 0)
		{
			propertyCollection.setProperty(iter->first, iter->second);
		}
	}
}

void PropertyCollection::join(const PropertyCollection& propertyCollection, bool overwrite)
{
	const std::string empty;
	join(empty, propertyCollection, overwrite);
}

void PropertyCollection::join(const std::string& substr, const PropertyCollection& propertyCollection, bool overwrite)
{
	const std::string empty;
	join(substr, empty, propertyCollection, overwrite);
}

void PropertyCollection::join(const std::string& substr, const std::string& key, const PropertyCollection& propertyCollection, bool overwrite)
{
	ScopedLock<FastMutex> lock(mutex_);

	PropertyCollection::Map::const_iterator iter = propertyCollection.map_.begin();
	PropertyCollection::Map::const_iterator end = propertyCollection.map_.end();
	for (; iter != end; ++iter)
	{
		if (substr.empty() || (iter->first.find(substr) == 0))
		{
			const std::string rootKey = !key.empty() ? format("%s.%s", key, iter->first) : iter->first;

			if (overwrite)
			{
				map_[rootKey] = iter->second;
			}
			else
			{
				map_.insert(PropertyCollection::Map::value_type(rootKey, iter->second));
			}
		}
	}
}

std::string PropertyCollection::toString() const
{
	ScopedLock<FastMutex> lock(mutex_);

	std::string s;

	Map::const_iterator iter = map_.begin();
	Map::const_iterator end = map_.end();
	for (; iter != end; ++iter)
	{
		s.append(iter->first);
		s.append("::");
		s.append(LoggerFormatter::toString(iter->second));
		s.append("\n");
	}

	return s;
}

PropertyCollection::ModifiedSignal& PropertyCollection::getModifiedSignal()
{
	return modifiedSignal_;
}

PropertyCollection::const_iterator PropertyCollection::begin() const
{
	return map_.begin();
}

PropertyCollection::const_iterator PropertyCollection::end() const
{
	return map_.end();
}

void PropertyCollection::lock()
{
	mutex_.lock();
}

void PropertyCollection::unlock()
{
	mutex_.unlock();
}

bool PropertyCollection::hasPropertyMetaKey(const std::string& key) const
{
	ScopedLock<FastMutex> lock(mutex_);
	Map::const_iterator iter = mapMeta_.find(key);
	return iter != mapMeta_.end() ? true : false;
}

void PropertyCollection::setPropertyMeta(const std::string& key, const Poco::Dynamic::Var& value)
{
	ScopedLock<FastMutex> lock(mutex_);

	Map::iterator iter = mapMeta_.find(key);

	if (iter == mapMeta_.end())
	{
		mapMeta_.insert(std::make_pair(key, value));
	}
	else
	{
		iter->second = value;
	}
}

const Var& PropertyCollection::getPropertyMeta(const std::string& key,
        const Poco::Dynamic::Var& defaultValue) const
{
	ScopedLock<FastMutex> lock(mutex_);

	Map::const_iterator iter = mapMeta_.find(key);
	if (iter == mapMeta_.end())
	{
		return defaultValue;
	}

	const Var& value = iter->second;
	return value;
}

void PropertyCollection::setPropertyUnsafe(const std::string& key, const Var& value)
{
	Map::iterator iter = map_.find(key);

	if (iter == map_.end())
	{
		map_.insert(std::make_pair(key, value));
	}
	else
	{
		iter->second = value;
	}

	modifiedSignal_(key, value);
}

const Var& PropertyCollection::getPropertyUnsafe(const std::string& key) const
{
	Map::const_iterator iter = map_.find(key);
	if (iter == map_.end())
	{
		throw NotFoundException(key);
	}
	const Var& value = iter->second;
	if (value.isEmpty())
	{
		poco_debug_f1(LOGGER(), "Key %s contains empty value", key);
	}
	return value;
}

const Var& PropertyCollection::getPropertyUnsafe(const std::string& key,
        const Poco::Dynamic::Var& defaultValue) const
{
	Map::const_iterator iter = map_.find(key);
	if (iter == map_.end())
	{
		return defaultValue;
	}

	const Var& value = iter->second;
	return value;
}

const PropertyCollection::Map& PropertyCollection::getMap() const
{
	return map_;
}

PropertyCollection::Map& PropertyCollection::getMap()
{
	return map_;
}

const PropertyCollection::Map& PropertyCollection::getMetaMap() const
{
	return mapMeta_;
}

PropertyCollection::Map& PropertyCollection::getMetaMap()
{
	return mapMeta_;
}

void PropertyCollection::setMetaMap(const PropertyCollection::Map& map)
{
	mapMeta_ = map;
}

/*********************************
** createPropertyCollection
**********************************/

PropertyCollection kdrive::utility::createPropertyCollection(const std::string& keyValues)
{
	PropertyCollection propertyCollection;
	StringTokenizer stringTokenizer(keyValues, ",");
	StringTokenizer::Iterator iter = stringTokenizer.begin();
	StringTokenizer::Iterator end = stringTokenizer.end();
	for (; iter != end; ++iter)
	{
		StringTokenizer stringTokenizerKeyValue(*iter, ":");
		if (stringTokenizerKeyValue.count() == 2)
		{
			propertyCollection.setProperty(stringTokenizerKeyValue[0], stringTokenizerKeyValue[1]);
		}
	}
	return propertyCollection;
}
