#ifndef CUSTOM_MAP_H
#define CUSTOM_MAP_H

#include <map>
#include <vector>

template <typename Key, typename Value>
class CustomMap
{
public:
	~CustomMap ();
	CustomMap ();

	bool HasElements () const;
	bool Exists (Key key) const;
	void Insert (Key key, Value& value);
	bool Update (Key key, Value& value);
	bool Remove (Key key, Value& value);
	void RemoveAll ();
	bool Get (Key key, Value& value) const;

	void GatherAll (std::vector<Value>& vVao) const;

protected:
	std::map<Key, Value> m_Map;

};

template <typename Key, typename Value>
CustomMap<Key, Value>::~CustomMap ()
{
}

template <typename Key, typename Value>
CustomMap<Key, Value>::CustomMap ()
{
}

template <typename Key, typename Value>
bool CustomMap<Key, Value>::HasElements () const
{
	bool hasElements;

	hasElements = (m_Map.size() > 0);

	return hasElements;
}

template <typename Key, typename Value>
bool CustomMap<Key, Value>::Exists (Key key) const
{
	bool exists;

	exists = (m_Map.find (key) != m_Map.end ());
	
	return exists;
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::Insert (Key key, Value& value)
{
	m_Map[key] = value;
}

template <typename Key, typename Value>
bool CustomMap<Key, Value>::Update (Key key, Value& value)
{
	auto iter = m_Map.find (key);

	if (iter != m_Map.end ())
	{
		iter->second = value;
		return true;
	}

	return false;
}

template <typename Key, typename Value>
bool CustomMap<Key, Value>::Remove (Key key, Value& value)
{
	bool exists;

	auto iter = m_Map.find (key);

	if (iter != m_Map.end ())
	{
		value = iter->second;
		m_Map.erase (iter);
		exists = true;
	}
	else
	{
		exists = false;
	}

	return exists;
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::RemoveAll ()
{
	m_Map.clear ();
}


template <typename Key, typename Value>
bool CustomMap<Key, Value>::Get (Key key, Value& value) const
{
	bool exists;

	auto iter = m_Map.find (key);

	if (iter != m_Map.end ())
	{
		value = iter->second;
		exists = true;
	}
	else
	{
		exists = false;
	}

	return exists;
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::GatherAll (std::vector<Value>& vVao) const
{
	if (m_Map.size () > 0)
	{
		vVao.resize (m_Map.size ());
		std::vector<Value>::iterator viter = vVao.begin ();
		for (auto iter = m_Map.begin (); iter!= m_Map.end (); iter++)
		{
			*viter++ = iter->second;
		}
	}
	else
	{
		vVao.clear ();
	}
}
#endif