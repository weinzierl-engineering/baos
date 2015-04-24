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

#ifndef __WZF_UTILITY_PROPERTY_COLLECTION_PROPERTY_COLLECTION_H__
#define __WZF_UTILITY_PROPERTY_COLLECTION_PROPERTY_COLLECTION_H__

#include "kdrive/utility/Config.h"
#include <Poco/Dynamic/Var.h>
#include <Poco/Mutex.h>
#include <boost/signals2.hpp>
#include <string>
#include <map>

namespace kdrive
{
namespace utility
{

/*******************************
** PropertyCollection
********************************/

/*!
	Implements a Var collection based on a std::map
*/
class wzfUtility_API PropertyCollection
{
public:
	typedef std::map<std::string, Poco::Dynamic::Var> Map;
	typedef Map::const_iterator const_iterator;

	/*!
		Default Constructor
	*/
	PropertyCollection();

	/*!
		Copy Constructor
	*/
	PropertyCollection(const PropertyCollection& propertyCollection);

	/*!
		Destroys the DynamicPropertyCollection.
	*/
	virtual ~PropertyCollection();

	/*!
		Assignment operator
	*/
	PropertyCollection& operator=(const PropertyCollection& propertyCollection);

	/*!
		Sets the property value
	*/
	void setProperty(const std::string& key, const Poco::Dynamic::Var& value);

	/*!
		Gets the property value
		If the key is not in the property collection an exception will be thrown
	*/
	const Poco::Dynamic::Var& getProperty(const std::string& key) const;

	/*!
		Gets the property value
		If the key is not found then returns the default value
	*/
	const Poco::Dynamic::Var& getProperty(const std::string& key,
	                                      const Poco::Dynamic::Var& defaultValue) const;

	/*!
		Removes the property
	*/
	void removeProperty(const std::string& key);

	/*!
		returns false if the key exists and the associated value is not empty
		returns true if the key doesn't exist
		returns true if the key exists and the associate value is empty
	*/
	bool isEmpty(const std::string& key) const;

	/*!
		Removes all properties
	*/
	void clear();

	/*!
		\return true if the property key is supported
	*/
	bool hasPropertyKey(const std::string& key) const;

	/*!
		enumerates the keys
	*/
	void keys(std::vector<std::string>& keys) const;

	/*!
		enumerates the keys based on a filter (substr)
		we currently use std::string::find
		this may be replaced with a regex in the future
		If substr is empty all keys are copied
	*/
	void keys(const std::string& substr, std::vector<std::string>& keys) const;

	/*!
		Copies filtered properties to a new property collection type
		Note PropertyCollectionType doesn't have to use the same Policy
		as our class. If substr is empty all keys are copied
	*/
	void filter(const std::string& substr, PropertyCollection& propertyCollection) const;

	/*!
		Copies all the key,value pairs that have not already been inserted into the map
		from properties. If overwrite is true copies all properties from propertyCollection
		regardless of whether they are already in the map or not.
	*/
	void join(const PropertyCollection& propertyCollection, bool overwrite = false);

	/*!
		Copies all the key,value pairs that have not already been inserted into the map
		from properties. Filters on substr.	If overwrite is true copies all properties from
		propertyCollection regardless of whether they are already in the map or not.
	*/
	void join(const std::string& substr, const PropertyCollection& propertyCollection, bool overwrite = false);

	/*!
		Copies all the key,value pairs that have not already been inserted into the map
		from properties. Filters on substr.	If overwrite is true copies all properties from
		propertyCollection regardless of whether they are already in the map or not.
		All keys will be appended to key (key is the new root).
	*/
	void join(const std::string& substr, const std::string& key, const PropertyCollection& propertyCollection, bool overwrite = false);

	/*!
		Writes out to contents of the Property Collection to a string
	*/
	std::string toString() const;

	/*!
		Returns the modified signal
		Called when a property is set
	*/
	typedef boost::signals2::signal<void (const std::string& key, const Poco::Dynamic::Var& value)> ModifiedSignal;
	ModifiedSignal& getModifiedSignal();

	/*!
		gets the property value
		Performs a type conversion
		If the Var can't safely convert to a T
		an exception will be thrown
	*/
	template <typename T>
	T getProperty(const std::string& key) const
	{
		return getProperty(key).convert<T>();
	}

	/*!
		gets the property value
		extracts it from the dynamic value
		i.e. used for std::vector types
	*/
	template <typename T>
	const T& extract(const std::string& key) const
	{
		return getProperty(key).extract<T>();
	}

	/*!
		gets the property value
		by converting it to a T
		i.e. to a std::string
	*/
	template <typename T>
	T convert(const std::string& key) const
	{
		return getProperty(key).convert<T>();
	}

	/*!
		Returns the map begin iterator
	*/
	const_iterator begin() const;

	/*!
		Returns the map end iterator
	*/
	const_iterator end() const;

	/*!
		Locks the collection
	*/
	void lock();

	/*!
		Unlocks the collection
	*/
	void unlock();

	/*!
		\return true if the property meta key is supported
	*/
	bool hasPropertyMetaKey(const std::string& key) const;

	/*!
		Sets the meta property value
	*/
	void setPropertyMeta(const std::string& key, const Poco::Dynamic::Var& value);

	/*!
		Gets the meta property value
		If the key is not found then returns the default value
	*/
	const Poco::Dynamic::Var& getPropertyMeta(const std::string& key,
	        const Poco::Dynamic::Var& defaultValue) const;

	/*!
		Returns the meta map
	*/
	const Map& getMetaMap() const;

	/*!
		Returns the meta map
	*/
	Map& getMetaMap();

	/*!
		Sets the Meta map
	*/
	void setMetaMap(const Map&);

protected:
	/*!
		Sets the property and calls the property modified signal
		Unsafe in that it doesn't use the mutex
	*/
	virtual void setPropertyUnsafe(const std::string& key, const Poco::Dynamic::Var& value);

	/*!
		Gets the property value
		If the key is not supported an exception will be thrown
		Unsafe in that it doesn't use the mutex
	*/
	virtual const Poco::Dynamic::Var& getPropertyUnsafe(const std::string& key) const;

	/*!
		Gets the property value
		If the key is not found returns the deafult value
		Unsafe in that it doesn't use the mutex
	*/
	virtual const Poco::Dynamic::Var& getPropertyUnsafe(const std::string& key,
	        const Poco::Dynamic::Var& defaultValue) const;

	/*!
		Returns the map
	*/
	const Map& getMap() const;

	/*!
		Returns the map
	*/
	Map& getMap();

protected:
	mutable Poco::FastMutex mutex_;
	Map map_;
	Map mapMeta_; /*!< Meta information about properties */
	ModifiedSignal modifiedSignal_;
};

/*!
	A very basic function to create a PropertyCollection from a string
	which has the following format:
	key1:value,key2:value,key3:value
	Assumes there are no : or , in the keys or values
	And can only create simple value types (int, string etc)
	However the value type will always be string
	Will not handle arrays (std::vector)

	For example:
	PropertyCollection propertyCollection(createPropertyCollection("SeqNo:1,Source:1001,Destination:1002");
	is equivalent to:
	PropertyCollection propertyCollection;
	propertyCollection.setProperty("SeqNo", "1");
	propertyCollection.setProperty("Source", "1001");
	propertyCollection.setProperty("Destination", "1002");
*/
wzfUtility_API PropertyCollection createPropertyCollection(const std::string& keyValues);

}
} // end namespace kdrive::utility

#endif // __WZF_UTILITY_PROPERTY_COLLECTION_PROPERTY_COLLECTION_H__
