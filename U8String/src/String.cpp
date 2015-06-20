#include <String.hpp>

#include <algorithm>
#include <cstring>
#include <sstream>
#include <iostream>

namespace U8
{

	String::StringIterator::StringIterator(const String* string, size_type pos) :
		m_pos(pos), m_string(string)
	{
	}

	String::StringIterator::~StringIterator()
	{
	}

	String::StringIterator::difference_type String::StringIterator::number_character(const StringIterator& rhs) const
	{
		if (m_string != rhs.m_string)
			throw std::logic_error("Iterators are not associated with the same string !");

		return rhs.m_pos - m_pos;
	}

	String::StringIterator& String::StringIterator::operator++()
	{
		++m_pos;

		return *this;
	}

	String::StringIterator String::StringIterator::operator++(int /*junk*/)
	{
		StringIterator tmp(*this);
		operator++();
		return tmp;
	}

	String::StringIterator& String::StringIterator::operator--()
	{
		--m_pos;

		return *this;
	}

	String::StringIterator String::StringIterator::operator--(int /*junk*/)
	{
		StringIterator tmp(*this);
		operator--();
		return tmp;
	}

	Character String::StringIterator::operator*()
	{
		return { m_pos, m_string };
	}

	const Character String::StringIterator::operator*() const
	{
		return { m_pos, m_string };
	}

	String::StringIterator::operator const char* () const
	{
		const_pointer ptr = m_string->data();
		utf8::advance(ptr, m_pos, m_string->data() + m_string->capacity());
		return ptr;
	}

	bool String::StringIterator::operator==(const StringIterator& rhs) const
	{
		return m_pos == rhs.m_pos && m_string == rhs.m_string;
	}

	bool String::StringIterator::operator!=(const StringIterator& rhs) const
	{
		return !operator==(rhs);
	}

	String::iterator String::begin()
	{
		return StringIterator(this, 0);
	}
	String::const_iterator String::begin() const
	{
		return StringIterator(this, 0);
	}
	String::iterator String::end()
	{
		return StringIterator(this, size());
	}
	String::const_iterator String::end() const
	{
		return StringIterator(this, size());
	}
	String::reverse_iterator String::rbegin()
	{
		return StringIterator(this, size() - 1);
	}
	String::const_reverse_iterator String::rbegin() const
	{
		return StringIterator(this, size() - 1);
	}
	String::reverse_iterator String::rend()
	{
		return StringIterator(this, -1);
	}
	String::const_reverse_iterator String::rend() const
	{
		return StringIterator(this, -1);
	}
	String::const_iterator String::cbegin() const
	{
		return begin();
	}
	String::const_iterator String::cend() const
	{
		return end();
	}
	String::const_reverse_iterator String::crbegin() const
	{
		return rbegin();
	}
	String::const_reverse_iterator String::crend() const
	{
		return rend();
	}

	String::String() :
	m_sharedString(&emptyString)
	{
		//ctor
	}

	String::String(char character) :
	m_sharedString(&emptyString)
	{
		if (character != '\0')
			assign(1, character);
	}

	String::String(const Character& character) :
	m_sharedString(&emptyString)
	{
		if (character != '\0')
			assign(1, character);
	}

	String::String(size_type rep, char character) :
	m_sharedString(&emptyString)
	{
		if (rep > 0 && character != '\0')
			assign(rep, character);
	}

	String::String(size_type rep, const Character& character) :
	m_sharedString(&emptyString)
	{
		if (rep > 0 && character != '\0')
			assign(rep, character);
	}

	String::String(const String& string, size_type pos, size_type count) :
	m_sharedString(&emptyString)
	{
		if (count > 0)
			assign(string, pos, count);
	}

	String::String(const char* string, size_type count) :
	m_sharedString(&emptyString)
	{
		if (count > 0)
			assign(string, string + count);
	}

	String::String(const char* string) :
	m_sharedString(&emptyString)
	{
		if (string)
			assign(string);
	}

	String::String(const std::string& string) :
	m_sharedString(&emptyString)
	{
		if (!string.empty())
			assign(string.begin(), string.end());
	}

	String::String(const String& string) :
	m_sharedString(string.m_sharedString)
	{
		if (m_sharedString != &emptyString)
			m_sharedString->refCount++;
	}

	String::String(String&& string) noexcept :
	m_sharedString(string.m_sharedString)
	{
		string.m_sharedString = &emptyString;
	}

	String::String(std::initializer_list<const char*> init) :
	m_sharedString(&emptyString)
	{
		if (init.size() != 0)
			assign(init);
	}

	String::String(std::initializer_list<Character> init) :
	m_sharedString(&emptyString)
	{
		if (init.size() != 0)
			assign(init);
	}

	String::String(std::initializer_list<char> init) :
	m_sharedString(&emptyString)
	{
		if (init.size() != 0)
			assign(init.begin(), init.end());
	}

	String::~String()
	{
		release_string();
	}

	String& String::append(const Character& character)
	{
		return insert(size(), 1, character);
	}

	String& String::append(const char* string)
	{
		return insert(size(), string);
	}

	String& String::append(const String& string)
	{
		return insert(size(), string.data());
	}

	void String::assign(size_type n, char character)
	{
		if (n > 0U)
		{
			ensure_ownership();

			if (n > capacity())
				reserve(n + 1);

			m_sharedString->size = n;

			std::fill(raw_buffer(), raw_buffer() + n, character);
			m_sharedString->buffer[n] = 0; // String is terminated by a '\0'.
		}
		else
			release_string();
	}

	void String::assign(size_type n, const Character& character)
	{
		if (n > 0)
		{
			ensure_ownership();

			if (n > capacity())
				reserve(n * character.number_byte() + 1);

			m_sharedString->size = n;

			auto tmp = std::basic_string<char>(character);
			for (auto i = 0U; i != n * character.number_byte(); ++i)
				raw_buffer()[i] = tmp[i % character.number_byte()];
			//std::fill(raw_buffer(), raw_buffer() + n * character.number_byte(), character);
			m_sharedString->buffer[n * character.number_byte()] = 0; // String is terminated by a '\0'.
		}
		else
			release_string();
	}

	void String::assign(const String& string)
	{
		release_string();

		m_sharedString = string.m_sharedString;
		if (m_sharedString != &emptyString)
			m_sharedString->refCount++;
	}

	void String::assign(const String& string, size_type pos, size_type count)
	{
		if (count > 0)
		{
			if (count == npos)
				assign(StringIterator(&string, pos), StringIterator(&string, string.size()));
			else
				assign(StringIterator(&string, pos), StringIterator(&string, pos + count));
		}
		else
			release_string();
	}

	void String::assign(String&& string)
	{
		release_string();

		std::swap(m_sharedString, string.m_sharedString);
	}

	void String::assign(const char* string, size_type count)
	{
		if (count != 0)
			assign(string, string + count);
		else
			release_string();
	}

	void String::assign(const char* string)
	{
		size_type sizeString = std::strlen(string);

		if (sizeString > 0)
			assign(string, string + sizeString);
		else
			release_string();
	}

	void String::assign(const_iterator first, const_iterator last)
	{
		assign(static_cast<const_pointer>(first), static_cast<const_pointer>(last));
	}

	void String::assign(std::initializer_list<const char*> init)
	{
		if (init.size() != 0)
		{
			clear();

			for (auto i : init)
			{
				append(String(i));
			}
		}
		else
			release_string();
	}

	void String::assign(std::initializer_list<Character> init)
	{
		if (init.size() != 0)
		{
			ensure_ownership();

			size_type sum = 0U;
			for (const auto& character : init)
				sum += character.number_byte();

			if (sum > capacity())
				reserve(sum + 1);

			for (auto character : init)
			{
				auto tmp = std::basic_string<char>(character);
				for (auto i = 0U; i != character.number_byte(); ++i)
					raw_buffer()[i] = tmp[i % character.number_byte()];
			}

			m_sharedString->buffer[sum] = '\0'; // String is terminated by a '\0'.
			m_sharedString->size = std::distance(init.begin(), init.end());
		}
		else
			release_string();
	}

	void String::assign(std::initializer_list<char> init)
	{
		if (init.size() != 0)
			assign(init.begin(), init.end());
		else
			release_string();
	}

	Character String::at(size_type pos)
	{
		if (pos >= size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		ensure_ownership();

		return { pos, this };
	}

	const Character String::at(size_type pos) const
	{
		if (pos >= size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		return { pos, this };
	}

	Character String::back()
	{
		return { size() - 1, this };
	}

	const Character String::back() const
	{
		return { size() - 1, this };
	}

	String::size_type String::capacity() const
	{
		return m_sharedString->capacity;
	}

	Character String::character_at(size_type pos) const
	{
		return { pos, this };
	}

	uint32_t String::code_point(size_type pos) const
	{
		utf8::iterator<const char*> it(data(), data(), data() + capacity());

		std::advance(it, pos);

		return *it;
	}

	int String::compare(const String& other, const std::locale& locale) const
	{
		auto& f = std::use_facet<std::collate<char>>(locale);
		std::basic_string<char> s1(data()), s2(other.data());
		return f.compare(s1.data(), s1.data() + s1.size(),
			s2.data(), s2.data() + s2.size());
	}

	void String::clear(bool keepBuffer)
	{
		if (keepBuffer)
		{
			ensure_ownership();
			m_sharedString->size = 0;
		}
		else
			release_string();
	}

	const char* String::data() const
	{
		return m_sharedString->buffer;
	}

	bool String::empty() const
	{
		return m_sharedString->size == 0;
	}

	String& String::erase(size_type index, size_type count)
	{
		erase(StringIterator(this, index), StringIterator(this, std::min(index + std::min(count, size()), size())));

		return *this;
	}

	String::iterator String::erase(const_iterator position)
	{
		auto tmp = position;
		return erase(position, ++tmp);
	}

	String::iterator String::erase(const_iterator first, const_iterator last)
	{
		auto lengthBeginning = begin().number_character(first);
		auto length = first.number_character(last);

		pointer firstTmp = const_cast<pointer>(static_cast<const_pointer>(first));
		pointer lastTmp = const_cast<pointer>(static_cast<const_pointer>(last));
		std::rotate(firstTmp, lastTmp, &raw_buffer()[capacity()]);

		m_sharedString->buffer[capacity() - 1] = '\0';
		m_sharedString->size -= length;

		return StringIterator(this, lengthBeginning);
	}

	String::size_type String::find(const String& str, size_type pos) const
	{
		return find(str.data(), pos);
	}

	String::size_type String::find(const char* string, size_type pos) const
	{
		auto stringSize = strlen(string);
		if (stringSize == 0)
			return empty() == true;

		auto it = begin();
		std::advance(it, pos);

		auto offset = it - begin();

		for (auto i = offset; data()[i]; ++i)
		{
			if (data()[i] == string[0])
			{
				auto beginning = i;

				++i;
				bool canContinue = true;
				for (auto j = 1U; j < stringSize && canContinue; ++i, ++j)
					if (data()[i] != string[j])
						canContinue = false;

				if (canContinue)
					return utf8::distance(data(), data() + beginning);

				--i;
			}
		}

		return npos;
	}

	String::size_type String::find(const Character& character, size_type pos) const
	{
		auto itBegin = begin();
		std::advance(itBegin, pos);
		auto it = std::find(itBegin, end(), character);
		return itBegin.number_character(it);
	}

	Character String::front()
	{
		return { 0, this };
	}

	const Character String::front() const
	{
		return { 0, this };
	}

	String& String::insert(size_type index, size_type count, const Character& character)
	{
		insert(StringIterator(this, index), count, character);

		return *this;
	}

	String& String::insert(size_type index, const char* string)
	{
		insert(StringIterator(this, index), string, string + std::strlen(string));

		return *this;
	}

	String::iterator String::insert(const_iterator pos, const Character& character)
	{
		return insert(pos, 1, character);
	}

	String::iterator String::insert(const_iterator pos, size_type count, const Character& character)
	{
		auto offset = pos - data();
		auto distance = count * character.number_byte();

		if (empty())
			reserve(capacity() + distance + 1); // String is terminated by a '\0'.
		else
			reserve(capacity() + distance);

		if (!empty())
			right_shift(offset, distance, capacity() - 1);

		auto tmp = std::basic_string<char>(character);
		for (auto i = 0U; i != count * character.number_byte(); ++i)
			raw_buffer()[offset + i] = tmp[i % character.number_byte()];

		m_sharedString->buffer[capacity() - 1] = '\0'; // String is terminated by a '\0'.
		m_sharedString->size += count;

		return StringIterator(this, utf8::distance(raw_buffer(), raw_buffer() + offset));
	}

	String::iterator String::insert(const_iterator pos, std::initializer_list<Character> ilist)
	{
		auto offset = pos - data();
		size_type sum = 0U;
		for (const auto& ch : ilist)
			sum += ch.number_byte();

		if (empty())
			reserve(capacity() + sum + 1); // String is terminated by a '\0'.
		else
			reserve(capacity() + sum);

		if (!empty())
			right_shift(offset, sum, capacity() - 1);

		auto position = 0;
		for (auto& character : ilist)
		{
			auto tmp = std::basic_string<char>(character);
			for (auto i = 0U; i != character.number_byte(); ++i, ++position)
				raw_buffer()[offset + position] = tmp[i];
		}

		m_sharedString->buffer[capacity() - 1] = '\0'; // String is terminated by a '\0'.
		m_sharedString->size += ilist.size();

		return StringIterator(this, utf8::distance(raw_buffer(), raw_buffer() + offset));
	}

	String::size_type String::max_size() const
	{
		return npos;
	}

	String& String::operator=(const String& other)
	{
		if (this != &other)
			assign(other);

		return *this;
	}

	String& String::operator=(String&& other) noexcept
	{
		String(std::move(other)).swap(*this);

		return *this;
	}

	String& String::operator=(const char* string)
	{
		assign(string);

		return *this;
	}

	String& String::operator=(char character)
	{
		assign(1, character);

		return *this;
	}

	String& String::operator=(const Character& character)
	{
		assign(1, character);

		return *this;
	}

	String& String::operator=(std::initializer_list<const char*> init)
	{
		assign(init);

		return *this;
	}

	String& String::operator=(std::initializer_list<Character> init)
	{
		assign(init);

		return *this;
	}

	String& String::operator=(std::initializer_list<char> init)
	{
		assign(init);

		return *this;
	}

	Character String::operator[](size_type pos)
	{
		ensure_ownership();

		return { pos, this };
	}

	const Character String::operator[](size_type pos) const
	{
		return { pos, this };
	}

	String& String::operator+=(const char* other)
	{
		append(other);
		return *this;
	}

	String& String::operator+=(const String& other)
	{
		append(other);
		return *this;
	}

	String& String::operator+=(const Character& other)
	{
		append(other);
		return *this;
	}

	void String::pop_back()
	{
		erase(size() - 1, 1);
	}

	void String::push_back(const Character& character)
	{
		insert(end(), character);
	}

	std::basic_string<char> String::raw_character(size_type pos) const
	{
		utf8::iterator<const char*> it(data(), data(), data() + capacity());

		std::advance(it, pos);

		auto tmp = it;
		++it;

		std::basic_string<char> st;
		for (const char* iter = tmp.base(); iter != it.base(); ++iter)
		{
			st.push_back(*iter);
		}

		return st;
	}

	void String::reserve(size_type bufferSize)
	{
		size_type oldSize = size();

		// Nous avons déjà la place requise
		if (bufferSize <= capacity())
			return;

		pointer newBuffer = new value_type[bufferSize];

		std::copy(data(), data() + capacity(), newBuffer);
		release_string();

		m_sharedString = new SharedString;
		m_sharedString->buffer = newBuffer;
		m_sharedString->capacity = bufferSize;
		m_sharedString->size = oldSize;
	}

	void String::replace(size_type pos, size_type count, const Character& character)
	{
		if (pos >= size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		auto it = begin();
		std::advance(it, pos);

		pointer tmp = const_cast<pointer>(static_cast<const_pointer>(it));
		++it;

		size_type diff = it - tmp;
		if (diff == count * character.number_byte())
		{
			for (auto i = 0U; i < diff; ++i)
				tmp[i] = character.byte[i % character.number_byte()];

			m_sharedString->size += count - 1;
		}
		else if (diff < count * character.number_byte()) // We must make it bigger.
		{
			auto offset = tmp - data();

			reserve(capacity() + count * character.number_byte() - diff); // New buffer allowed => iterators invalidate.
			m_sharedString->buffer[capacity() - 1] = '\0';

			pointer newTmp = raw_buffer() + offset;

			// We make a right shift !
			pointer beginBuffer = newTmp + (count * character.number_byte() - diff);
			pointer endBuffer = &m_sharedString->buffer[capacity() - 2];

			for (pointer i = endBuffer; i != beginBuffer; --i)
				*i = *(i - count * character.number_byte() + diff);

			for (auto i = 0U; i < count * character.number_byte(); ++i)
				newTmp[i] = character.byte[i % character.number_byte()];

			m_sharedString->size += count - 1;
		}
		else  // We can left shift.
		{
			std::rotate(tmp + count * character.number_byte(), tmp + diff, raw_buffer() + capacity());

			for (auto i = 0U; i < count * character.number_byte(); ++i)
				tmp[i] = character.byte[i % character.number_byte()];

			m_sharedString->size += count - 1;
		}
	}

	void String::shrink_to_fit()
	{
		if (m_sharedString == &emptyString)
			return;

		auto it = data();
		while (*it)
			++it;

		auto bufferSize = std::distance(data(), it);
		auto oldSize = size();

		pointer newBuffer = new value_type[bufferSize + 1];
		newBuffer[bufferSize] = '\0';

		std::copy(data(), it, newBuffer);
		release_string();

		m_sharedString = new SharedString;
		m_sharedString->buffer = newBuffer;
		m_sharedString->capacity = bufferSize + 1;
		m_sharedString->size = oldSize;
	}

	String::size_type String::size() const
	{
		return m_sharedString->size;
	}

	String String::substr(size_type pos, size_type count) const
	{
		if (pos > size())
			throw std::out_of_range("Index out of range " + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		return String(*this, pos, count);
	}

	void String::swap(String& other)
	{
		std::swap(m_sharedString, other.m_sharedString);
	}

	void String::ensure_ownership()
	{
		if (m_sharedString == &emptyString)
			return;

		if (m_sharedString->refCount > 1)
		{
			m_sharedString->refCount--;

			pointer newBuffer = new value_type[capacity()];
			std::copy(static_cast<const_pointer>(begin()), static_cast<const_pointer>(end()), newBuffer);

			m_sharedString = new SharedString(1, capacity(), size(), newBuffer);
		}
	}

	String::pointer String::raw_buffer()
	{
		return m_sharedString->buffer;
	}

	void String::release_string()
	{
		if (m_sharedString == &emptyString)
			return;

		if (--m_sharedString->refCount == 0)
		{
			delete[] data();
			delete m_sharedString;
		}

		m_sharedString = &emptyString;
	}

	void String::right_shift(size_type pos, size_type length, size_type endBuf)
	{
		pointer beginBuffer = raw_buffer() + pos + length - 1;
		pointer endBuffer = raw_buffer() + endBuf - 1;

		for (pointer i = endBuffer; i != beginBuffer; --i)
			*i = *(i - length);
	}

	String::SharedString String::emptyString(0, 0, 0, nullptr);
	String::size_type const String::npos(std::numeric_limits<String::size_type>::max());

	String operator+(const String& lhs, const String& rhs)
	{
		auto firstSize = std::strlen(lhs.data());
		auto secondSize = std::strlen(rhs.data());
		String::pointer newBuffer = new String::value_type[firstSize + secondSize + 1];
		std::copy(lhs.data(), lhs.data() + firstSize, newBuffer);
		std::copy(rhs.data(), rhs.data() + secondSize, newBuffer + firstSize);
		newBuffer[firstSize + secondSize] = '\0';

		String tmp;
		tmp.m_sharedString = new String::SharedString(1, firstSize + secondSize + 1, lhs.size() + rhs.size(), newBuffer);
		return tmp;
	}

	bool operator==(const String& lhs, const String& rhs)
	{
		// std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); c++14
		auto first1 = lhs.begin();
		auto last1 = lhs.end();
		auto first2 = rhs.begin();
		auto last2 = rhs.end();

		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return first1 == last1 && first2 == last2;
	}

	bool operator!=(const String& lhs, const String& rhs)
	{
		return !operator==(lhs, rhs);
	}

	bool operator<(const String& lhs, const String& rhs)
	{
		return lhs.compare(rhs) == -1;
	}

	bool operator<=(const String& lhs, const String& rhs)
	{
		auto tmp = lhs.compare(rhs);
		return tmp == -1 || tmp == 0;
	}

	bool operator>(const String& lhs, const String& rhs)
	{
		return !operator<=(lhs, rhs);
	}

	bool operator>=(const String& lhs, const String& rhs)
	{
		return !operator<(lhs, rhs);
	}

	std::istream& operator>>(std::istream& is, String& str)
	{
		str.clear();

		std::string tmp;
		is >> tmp;

		str.assign(tmp);

		return is;

	}

	std::ostream& operator<<(std::ostream& os, const String& str)
	{
		if (str.empty())
			return os;

		return operator<<(os, str.data());
	}

} // U8

namespace std
{

	void swap(U8::String& lhs, U8::String& rhs)
	{
		lhs.swap(rhs);
	}

} // std
