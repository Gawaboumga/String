#include <utf8.h>

#include <algorithm>
#include <cassert>
//#include <codecvt>
#include <cstring>
#include <sstream>
#include <iostream>

namespace U8
{

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8StringIterator::U8StringIterator(const Basic_String* string, const_pointer it) :
		m_it(it), m_string(string)
	{
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8StringIterator::~U8StringIterator()
	{
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_pointer U8String<Traits, Allocator>::U8StringIterator::base() const
	{
		return m_it;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::U8StringIterator& U8String<Traits, Allocator>::U8StringIterator::operator++()
	{
		utf8::next(m_it, m_string->end_string());

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::U8StringIterator U8String<Traits, Allocator>::U8StringIterator::operator++(int /*junk*/)
	{
		U8StringIterator tmp(*this);
		operator++();
		return tmp;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::U8StringIterator& U8String<Traits, Allocator>::U8StringIterator::operator--()
	{
		utf8::prior(m_it, m_string->data());

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::U8StringIterator U8String<Traits, Allocator>::U8StringIterator::operator--(int /*junk*/)
	{
		U8StringIterator tmp(*this);
		operator--();
		return tmp;
	}

	template <typename Traits, class Allocator>
	const Basic_String* U8String<Traits, Allocator>::U8StringIterator::string() const
	{
		return m_string;
	}

	template <typename Traits, class Allocator>
	Character U8String<Traits, Allocator>::U8StringIterator::operator*()
	{
		return { &m_it, utf8::peek_next(m_it, m_it + 4), m_string };
	}

	template <typename Traits, class Allocator>
	const Character U8String<Traits, Allocator>::U8StringIterator::operator*() const
	{
		return { &m_it, utf8::peek_next(m_it, m_it + 4), m_string };
	}

	template <typename Traits, class Allocator>
	bool U8String<Traits, Allocator>::U8StringIterator::operator==(const U8StringIterator& rhs) const
	{
		return m_it == rhs.m_it;
	}

	template <typename Traits, class Allocator>
	bool U8String<Traits, Allocator>::U8StringIterator::operator!=(const U8StringIterator& rhs) const
	{
		return !operator==(rhs);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::ReverseU8StringIterator& U8String<Traits, Allocator>::ReverseU8StringIterator::operator++()
	{
		utf8::prior(m_it, m_string->data() - 1);

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::ReverseU8StringIterator U8String<Traits, Allocator>::ReverseU8StringIterator::operator++(int /*junk*/)
	{
		ReverseU8StringIterator tmp(*this);
		operator++();
		return tmp;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::ReverseU8StringIterator& U8String<Traits, Allocator>::ReverseU8StringIterator::operator--()
	{
		utf8::next(m_it, m_string->end_string());

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::ReverseU8StringIterator U8String<Traits, Allocator>::ReverseU8StringIterator::operator--(int /*junk*/)
	{
		ReverseU8StringIterator tmp(*this);
		operator--();
		return tmp;

	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::begin()
	{
		return U8StringIterator(this, data());
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_iterator U8String<Traits, Allocator>::begin() const
	{
		return U8StringIterator(this, data());
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::end()
	{
		return U8StringIterator(this, end_string());
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_iterator U8String<Traits, Allocator>::end() const
	{
		return U8StringIterator(this, end_string());
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::reverse_iterator U8String<Traits, Allocator>::rbegin()
	{
		auto it = end_string();
		utf8::prior(it, data());
		return ReverseU8StringIterator(this, it);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_reverse_iterator U8String<Traits, Allocator>::rbegin() const
	{
		auto it = end_string();
		utf8::prior(it, data());
		return ReverseU8StringIterator(this, it);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::reverse_iterator U8String<Traits, Allocator>::rend()
	{
		return ReverseU8StringIterator(this, data() - 1);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_reverse_iterator U8String<Traits, Allocator>::rend() const
	{
		return ReverseU8StringIterator(this, data() - 1);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_iterator U8String<Traits, Allocator>::cbegin() const
	{
		return begin();
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_iterator U8String<Traits, Allocator>::cend() const
	{
		return end();
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_reverse_iterator U8String<Traits, Allocator>::crbegin() const
	{
		return rbegin();
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_reverse_iterator U8String<Traits, Allocator>::crend() const
	{
		return rend();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String() :
		U8String(Allocator())
	{
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const Allocator& alloc) :
		U8String("", 0U, alloc)
	{
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(char character, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(1, character);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const Character& character, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(1, character);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const std::vector<Character>& characters, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(characters);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(size_type rep, char character, const Allocator& alloc) :
		U8String(rep, Character(character), alloc)
	{
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(size_type rep, const Character& character, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(rep, character);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const U8String& string, size_type pos, size_type count, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(string, pos, count);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const char* string, size_type count, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(string, string + count);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const char* string, const Allocator& alloc) :
		U8String(string, std::strlen(string), alloc)
	{
	}

	template <typename Traits, class Allocator>
	template <typename InputIter, typename>
	U8String<Traits, Allocator>::U8String(InputIter first, InputIter last, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(first, last);
		invariant();
	}


	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const std::string& string, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(string.begin(), string.end());
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(const U8String& string, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(string);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(U8String&& string, const Allocator& alloc) :
		Allocator(alloc)
	{
		assign(std::move(string));
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(std::initializer_list<const char*> init, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(init);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(std::initializer_list<Character> init, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(init);
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::U8String(std::initializer_list<char> init, const Allocator& alloc) :
		Allocator(alloc)
	{
		initialize(0, 0);
		m_data.non_sso.capacity = 0;
		assign(init.begin(), init.end());
		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::~U8String()
	{
		if (!is_sso())
			this->deallocate(m_data.non_sso.ptr, capacity());
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::append(char character)
	{
		return insert(size(), 1, character);
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::append(const Character& character)
	{
		return insert(size(), 1, character);
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::append(const char* string)
	{
		return insert(size(), string);
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::append(const U8String& string)
	{
		return insert(size(), string.data());
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(const std::vector<Character>& characters)
	{
		clear(true);

		for (auto character : characters)
			push_back(character);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(size_type n, char character)
	{
		if (n > capacity())
			reserve(n + 1);

		if (n > sso_capacity)
		{
			m_data.non_sso.capacity = n;
			initialize_non_sso(n, n);
		}
		else
		{
			if (!is_sso())
				this->deallocate(m_data.non_sso.ptr, capacity());

			initialize_sso(n, n);
		}

		Traits::assign(raw_buffer(), n, character);
		Traits::assign(raw_buffer()[n], '\0'); // U8String is terminated by a '\0'.
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(size_type n, const Character& character)
	{
		if (n > capacity())
			reserve(n * character.number_byte() + 1);

		if (n > sso_capacity)
		{
			m_data.non_sso.capacity = n * character.number_byte();
			initialize_non_sso(n, n * character.number_byte());
		}
		else
		{
			if (!is_sso())
				this->deallocate(m_data.non_sso.ptr, capacity());

			initialize_sso(n, n * character.number_byte());
		}

		auto tmp = std::basic_string<char>(character);
		for (auto i = 0U; i != n * character.number_byte(); ++i)
			raw_buffer()[i] = tmp[i % character.number_byte()];

		Traits::assign(raw_buffer()[n * character.number_byte()], '\0'); // U8String is terminated by a '\0'.
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(const U8String& string)
	{
		if (this != &string)
		{
			if (!is_sso())
				this->deallocate(m_data.non_sso.ptr, capacity());

			if (string.is_sso())
				 m_data = string.m_data;
			else
			{
				pointer newBuffer = this->allocate(string.capacity() + 1);
				Traits::move(newBuffer, string.data(), string.raw_size());
				Traits::assign(newBuffer[string.raw_size()], '\0');

				m_data.non_sso.ptr = newBuffer;
				m_data.non_sso.capacity = string.capacity();
				m_data.non_sso.end_string = string.raw_size();
				m_data.non_sso.size = string.size();

				assert(capacity() == string.capacity());
				assert(raw_size() == string.raw_size());
				assert(size() == string.size());
			}

			invariant();
		}
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(const U8String& string, size_type pos, size_type count)
	{
		if (pos > string.size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(string.size()) + ')');

		if (count == npos)
			assign(string.get_pointer_character(pos), string.get_pointer_character(string.size()));
		else
			assign(string.get_pointer_character(pos), string.get_pointer_character(std::min(string.size(), pos + count)));
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(U8String&& string)
	{
		m_data = string.m_data;
		string.m_data.non_sso.capacity = 0;
		string.m_data.sso.end_string = 30;
		string.m_data.sso.size = static_cast<char>(1 << 7);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(const char* string, size_type count)
	{
		assign(string, string + count);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(const char* string)
	{
		size_type sizeU8String = std::strlen(string);

		assign(string, string + sizeU8String);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(const_iterator first, const_iterator last)
	{
		assign(first.base(), last.base());
	}

	template <typename Traits, class Allocator>
	template <typename InputIter, typename>
	void U8String<Traits, Allocator>::assign(InputIter first, InputIter last)
	{
		return assign(first, last, typename std::iterator_traits<InputIter>::iterator_category());
	}

	template <typename Traits, class Allocator>
	template <typename InputIter>
	void U8String<Traits, Allocator>::assign(InputIter first, InputIter last, std::input_iterator_tag)
	{
		clear(true);

		for (; first != last; ++first)
			push_back(*first);
	}

	template <typename Traits, class Allocator>
	template <typename RandomIter>
	void U8String<Traits, Allocator>::assign(RandomIter first, RandomIter last, std::random_access_iterator_tag)
	{
		assert(first <= last);

		size_type distance = std::distance(first, last);
		auto newSize = utf8::distance(first, last);

		if (distance > sso_capacity)
			reserve(distance);

		Traits::move(raw_buffer(), &*first, distance);
		Traits::assign(raw_buffer()[distance], '\0'); // U8String is terminated by a '\0'.

		initialize(newSize, distance);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(std::initializer_list<const char*> init)
	{
		clear(true);

		for (auto i : init)
			push_back(Character(i));
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(std::initializer_list<Character> init)
	{
		clear(true);

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

		Traits::assign(raw_buffer()[sum], '\0'); // U8String is terminated by a '\0'.
		initialize(std::distance(init.begin(), init.end()), sum);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::assign(std::initializer_list<char> init)
	{
		assign(init.begin(), init.end());
	}

	template <typename Traits, class Allocator>
	Character U8String<Traits, Allocator>::at(size_type pos)
	{
		if (pos >= size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		auto tmp = get_pointer_character(pos);

		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	const Character U8String<Traits, Allocator>::at(size_type pos) const
	{
		if (pos >= size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		auto tmp = get_pointer_character(pos);

		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	Character U8String<Traits, Allocator>::back()
	{
		auto tmp = get_pointer_character(size() - 1);

		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	const Character U8String<Traits, Allocator>::back() const
	{
		auto tmp = get_pointer_character(size() - 1);

		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::capacity() const
	{
		return is_sso() ? sso_capacity : m_data.non_sso.capacity;
	}

	template <typename Traits, class Allocator>
	uint32_t U8String<Traits, Allocator>::code_point(size_type pos) const
	{
		pointer it = get_pointer_character(pos);

		return utf8::peek_next(it, it + 4);
	}

	template <typename Traits, class Allocator>
	int U8String<Traits, Allocator>::compare(const char* other, const std::locale& locale) const
	{
		auto& f = std::use_facet<std::collate<char>>(locale);
		std::basic_string<char> s1(data()), s2(other);
		return f.compare(s1.data(), s1.data() + s1.size(),
			s2.data(), s2.data() + s2.size());
	}

	template <typename Traits, class Allocator>
	int U8String<Traits, Allocator>::compare(const U8String& other, const std::locale& locale) const
	{
		auto& f = std::use_facet<std::collate<char>>(locale);
		std::basic_string<char> s1(data()), s2(other.data());
		return f.compare(s1.data(), s1.data() + s1.size(),
			s2.data(), s2.data() + s2.size());
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::copy(char* dest, size_type count, size_type pos) const
	{
		if (pos >= size())
			throw std::out_of_range("Index out of range (" + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		auto it = iterator( this, get_pointer_character(pos) );

		iterator endIt;
		if (count < size())
			endIt = iterator( this, get_pointer_character(size()) );
		else
			endIt = end();

		Traits::copy(dest, it.base(), std::distance(it.base(), endIt.base()));

		return std::min(count, size());
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::clear(bool keepBuffer)
	{
		if (!keepBuffer && !is_sso())
			this->deallocate(m_data.non_sso.ptr, capacity());

		if (is_sso())
			initialize_sso(0, 0);
		else
			initialize_non_sso(0, 0);

		invariant();
	}

	template <typename Traits, class Allocator>
	const char* U8String<Traits, Allocator>::data() const
	{
		return is_sso() ? m_data.sso.string : m_data.non_sso.ptr;
	}

	template <typename Traits, class Allocator>
	bool U8String<Traits, Allocator>::empty() const
	{
		return size() == 0;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::erase(size_type index, size_type count)
	{
		erase(iterator(this, get_pointer_character(index)), iterator(this, get_pointer_character(index + std::min(count, size() - index))));

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::erase(const_iterator position)
	{
		auto tmp = position;
		return erase(position, ++tmp);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::erase(const_iterator first, const_iterator lastIt)
	{
		assert(first.string() == lastIt.string());
		assert(first.base() >= data() && first.base() <= end_string());

		iterator last = lastIt;

		auto lengthBeginning = std::distance(begin().base(), first.base());
		auto length = std::distance(first.base(), last.base());

		pointer firstTmp = const_cast<pointer>(first.base());
		pointer lastTmp = const_cast<pointer>(last.base());

		auto nbCharacters = utf8::distance(firstTmp, lastTmp);

		std::rotate(firstTmp, lastTmp, const_cast<pointer>(end_string()));
		Traits::assign(raw_buffer()[raw_size() - length], '\0');

		if (is_sso())
			initialize_sso(size() - nbCharacters, raw_size() - length);
		else
			initialize_non_sso(size() - nbCharacters, raw_size() - length);

		invariant();

		return iterator(this, data() + lengthBeginning);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find(const U8String& str, size_type pos) const
	{
		return find(str.data(), pos);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find(const char* string, size_type pos) const
	{
		if (pos >= size() || string[0] == '\0')
			return npos;

		auto itBegin = iterator(this, get_pointer_character(pos));

		auto tmp = std::search(itBegin.base(), end().base(), string, string + std::strlen(string));

		if (tmp == end_string())
			return npos;
		else
			return utf8::distance(data(), tmp);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find(const Character& character, size_type pos) const
	{
		auto itBegin = iterator(this, get_pointer_character(pos));
		auto it = std::find(itBegin, end(), character);
		return std::distance(begin(), it);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_first_of(const U8String& str, size_type pos) const
	{
		return find_first_of(str.data(), pos);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_first_of(const char* string, size_type pos) const
	{
		if (pos >= size() || string[0] == '\0')
			return npos;

		auto itBegin = iterator(this, get_pointer_character(pos));

		auto tmp = std::find_first_of(itBegin.base(), end().base(), string, string + std::strlen(string));

		if (tmp == end().base())
			return npos;
		else
			return utf8::distance(begin().base(), tmp);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_first_not_of(const U8String& str, size_type pos) const
	{
		if (str.empty() || pos > size())
			return npos;

		auto it = iterator( this, get_pointer_character(pos) );

		for (; it != end(); ++it, ++pos)
		{
			bool found = false;
			for (auto itStr = str.begin(); itStr != str.end(); ++itStr)
			{
				if (*it == *itStr)
				{
					found = true;
					break;
				}
			}

			if (found == false)
				return pos;
		}

		return npos;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_first_not_of(const char* string, size_type pos) const
	{
		if (string[0] == '\0')
			return npos;

		return find_first_not_of(U8String(string), pos);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_last_of(const U8String& str, size_type pos) const
	{
		return find_last_of(str.data(), pos);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_last_of(const char* string, size_type pos) const
	{
		if (string[0] == '\0')
			return npos;

		auto itBegin = rbegin();

		if (pos != npos)
		{
			if (pos >= size())
				return npos;

			std::advance(itBegin, size() - pos - 1);
		}

		auto tmp = std::find_first_of(itBegin, rend(), string, string + std::strlen(string));

		if (tmp == rend())
			return npos;
		else
			return std::distance(tmp, rend()) - 1;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_last_not_of(const U8String& str, size_type pos) const
	{
		if (pos != npos && pos >= size())
			return npos;

		if (pos == npos)
			pos = size() - 1;

		auto it = reverse_iterator( this, get_pointer_character(pos) );

		for (; it != rend(); ++it, --pos)
		{
			bool found = false;
			for (auto itStr = str.begin(); itStr != str.end(); ++itStr)
			{
				if (*it == *itStr)
				{
					found = true;
					break;
				}
			}

			if (found == false)
				return pos;
		}

		return npos;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::find_last_not_of(const char* string, size_type pos) const
	{
		if (string[0] == '\0')
			return npos;

		return find_last_not_of(U8String(string), pos);
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::fromUTF16(const char16_t* character)
	{
		auto size = std::char_traits<char16_t>::length(character);
		U8String tmp;
		tmp.reserve(size * 4 + 1);
		auto end = utf8::utf16to8(character, character + size, tmp.raw_buffer());
		*end = '\0';
		size = std::distance(tmp.raw_buffer(), end);
		auto p = utf8::distance(tmp.data(), tmp.data() + std::distance(tmp.raw_buffer(), end));
		tmp.initialize(p, size);

		return tmp;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::fromUTF32(const char32_t* character)
	{
		auto size = std::char_traits<char32_t>::length(character);
		U8String tmp;
		tmp.reserve(size * 4 + 1);
		auto end = utf8::utf32to8(character, character + size, tmp.raw_buffer());
		*end = '\0';
		size = std::distance(tmp.raw_buffer(), end);
		auto p = utf8::distance(tmp.data(), tmp.data() + std::distance(tmp.raw_buffer(), end));
		tmp.initialize(p, size);

		return tmp;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::fromWide(const wchar_t* character)
	{
		/*typedef std::codecvt_utf8<wchar_t> convert_wide_to_utf8;
		std::wstring_convert<convert_wide_to_utf8, wchar_t> converterWUTF8;

		return converterWUTF8.to_bytes(character);*/
		return {};
	}

	template <typename Traits, class Allocator>
	Character U8String<Traits, Allocator>::front()
	{
		const_pointer tmp = data();
		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	const Character U8String<Traits, Allocator>::front() const
	{
		const_pointer tmp = data();
		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::allocator_type U8String<Traits, Allocator>::get_allocator() const
	{
		return allocator_type();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::insert(size_type index, size_type count, char character)
	{
		insert(iterator(this, get_pointer_character(index)), count, Character(character));

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::insert(size_type index, size_type count, const Character& character)
	{
		insert(iterator(this, get_pointer_character(index)), count, character);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::insert(size_type index, const U8String& string, size_type subpos, size_type sublen)
	{
		return insert(index, string.substr(subpos, sublen));
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::insert(size_type index, const U8String& string)
	{
		return insert(index, string.data());
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::insert(size_type index, const char* string)
	{
		insert(iterator(this, get_pointer_character(index)), string, string + std::strlen(string));

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::insert(const_iterator pos, const Character& character)
	{
		return insert(pos, 1, character);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::insert(const_iterator pos, size_type count, const Character& character)
	{
		auto offset = std::distance(data(), pos.base());
		auto distance = count * character.number_byte();
		auto endSize = raw_size() + distance;

		if (empty())
			reserve(raw_size() + distance + 1);
		else
			reserve(raw_size() + distance);

		std::move_backward(data() + offset, end_string(), const_cast<pointer>(end_string() + distance));

		auto tmp = std::basic_string<char>(character);
		for (auto i = 0U; i != count * character.number_byte(); ++i)
			raw_buffer()[offset + i] = tmp[i % character.number_byte()];

		Traits::assign(raw_buffer()[raw_size() + distance], '\0'); // U8String is terminated by a '\0'.

		if (is_sso())
			initialize_sso(size() + count, raw_size() + distance);
		else
			initialize_non_sso(size() + count, raw_size() + distance);

		invariant();

		return pos;
	}

	template <typename Traits, class Allocator>
	template <typename InputIter, typename>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::insert(const_iterator pos, InputIter first, InputIter last)
	{
		return insert(pos, first, last, typename std::iterator_traits<InputIter>::iterator_category());
	}

	template <typename Traits, class Allocator>
	template <typename InputIter>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::insert(const_iterator pos, InputIter first, InputIter last, std::input_iterator_tag)
	{
		auto returnIt = pos;

		for (; first != last; ++first, returnIt++)
			returnIt = insert(returnIt, Character(*first));

		invariant();

		return returnIt;
	}

	template <typename Traits, class Allocator>
	template <typename RandomIter>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::insert(const_iterator pos, RandomIter first, RandomIter last, std::random_access_iterator_tag)
	{
		assert(first < last);

		size_type distance = std::distance(first, last);
		size_type offset = std::distance(data(), pos.base());
		auto tmp = raw_size() + distance;

		if (empty())
			reserve(raw_size() + distance + 1);
		else
			reserve(raw_size() + distance);

		std::move_backward(pos.base(), end_string(), const_cast<pointer>(end_string() + distance));

		Traits::move(raw_buffer() + offset, first, distance);

		if (is_sso())
			initialize_sso(size() + utf8::distance(first, last), tmp);
		else
			initialize_non_sso(size() + utf8::distance(first, last), tmp);

		Traits::assign(raw_buffer()[tmp], '\0'); // U8String is terminated by a '\0'.

		invariant();

        return { this, data() + offset };
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::iterator U8String<Traits, Allocator>::insert(const_iterator pos, std::initializer_list<Character> ilist)
	{
		auto offset = std::distance(data(), pos.base());
		size_type sum = 0U;
		for (const auto& ch : ilist)
			sum += ch.number_byte();

		if (empty())
			reserve(raw_size() + sum + 1); // U8String is terminated by a '\0'.
		else
			reserve(raw_size() + sum);

		std::move_backward(pos.base(), end_string(), const_cast<pointer>(end_string() + sum));

		auto position = 0;
		for (auto& character : ilist)
		{
			auto tmp = std::basic_string<char>(character);
			for (auto i = 0U; i != character.number_byte(); ++i, ++position)
				raw_buffer()[offset + position] = tmp[i];
		}

		auto tmp = raw_size() + sum;

		if (is_sso())
			initialize_sso(size() + ilist.size(), tmp);
		else
			initialize_non_sso(size() + ilist.size(), tmp);

		Traits::assign(raw_buffer()[tmp], '\0'); // U8String is terminated by a '\0'.

		invariant();

		return pos;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::max_size() const
	{
		return npos;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>::operator const char*() const
	{
		return data();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(const std::vector<Character>& characters)
	{
		assign(characters);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(const U8String& other)
	{
		if (this != &other)
			assign(other);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(U8String&& other) noexcept
	{
		U8String(std::move(other)).swap(*this);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(const char* string)
	{
		assign(string);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(char character)
	{
		assign(1, character);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(const Character& character)
	{
		assign(1, character);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(std::initializer_list<const char*> init)
	{
		assign(init);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(std::initializer_list<Character> init)
	{
		assign(init);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator=(std::initializer_list<char> init)
	{
		assign(init);

		return *this;
	}

	template <typename Traits, class Allocator>
	Character U8String<Traits, Allocator>::operator[](size_type pos)
	{
		const_pointer tmp = get_pointer_character(pos);
		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	const Character U8String<Traits, Allocator>::operator[](size_type pos) const
	{
		const_pointer tmp = get_pointer_character(pos);
		return { tmp, utf8::peek_next(tmp, tmp + 4), this };
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator+=(const U8String& other)
	{
		append(other);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator+=(const char* other)
	{
		append(other);

		return *this;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::operator+=(const Character& other)
	{
		append(other);

		return *this;
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::pop_back()
	{
		erase(size() - 1, 1);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::push_back(const Character& character)
	{
		insert(end(), character);
	}

	template <typename Traits, class Allocator>
	template <class OutputIterator>
	void U8String<Traits, Allocator>::raw_character(size_type pos, OutputIterator result) const
	{
		auto it = iterator( this, get_pointer_character(pos) );

		auto tmp = it;
		++it;

		for (const char* iter = tmp.base(); iter != it.base(); ++iter)
			*result++ = *iter;
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::reserve(size_type bufferSize)
	{
		size_type oldSize = size();

		// We already have enough space
		if (bufferSize <= capacity())
			return;

		pointer newBuffer = this->allocate(bufferSize + 1);

		auto rawSize = raw_size();
		Traits::move(newBuffer, data(), rawSize);
		Traits::assign(newBuffer[rawSize], '\0');

		if (!is_sso())
			this->deallocate(m_data.non_sso.ptr, capacity());

		m_data.non_sso.ptr = newBuffer;
		m_data.non_sso.capacity = bufferSize;
		initialize_non_sso(oldSize, rawSize);

		invariant();
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::resize(size_type count, const Character& character)
	{
		if (size() < count)
			insert(size(), count - size(), character);
		else
		{
			auto tmp = std::distance(get_pointer_character(count), end_string());
			if (is_sso())
				initialize_sso(count, raw_size() - tmp);
			else
				initialize_non_sso(count, raw_size() - tmp);
			Traits::assign(raw_buffer()[raw_size()], '\0');
		}

		invariant();
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::replace(size_type pos, size_type count, const U8String& string)
	{
		return replace(iterator(this, get_pointer_character(pos)), iterator(this, get_pointer_character(pos + count)), string);
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::replace(const_iterator first, const_iterator last, const U8String& string)
	{
		erase(first, last);
		insert(first, string.begin().base(), string.end().base());

		invariant();

		return *this;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::rfind(const U8String& string, size_type pos) const
	{
		return rfind(string.data(), pos);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::rfind(const char* string, size_type pos) const
	{
		if (pos != npos && pos >= size())
			return npos;

		auto itEnd = end();
		if (pos != npos)
		{
			itEnd = begin();
			std::advance(itEnd, pos);
		}

		auto tmp = std::find_end(begin().base(), itEnd.base(), string, string + std::strlen(string));

		if (tmp == itEnd.base())
			return npos;
		else
			return utf8::distance(begin().base(), tmp);
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::rfind(const Character& character, size_type pos) const
	{
		auto itBegin = rbegin();
		if (pos != npos)
			std::advance(itBegin, size() - pos);

		auto it = std::find(itBegin, rend(), character);

		if (it == rend())
			return npos;
		else
			return utf8::distance(data(), it.base());
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::shrink_to_fit()
	{
		if (is_sso())
			return;

		auto oldSize = size();
		auto bufferSize = raw_size();

		pointer newBuffer = this->allocate(bufferSize + 1);

		Traits::move(newBuffer, data(), bufferSize);
		Traits::assign(newBuffer[bufferSize], '\0');

		this->deallocate(m_data.non_sso.ptr, capacity());

		m_data.non_sso.ptr = newBuffer;
		m_data.non_sso.capacity = bufferSize;
		m_data.non_sso.size = oldSize;

		invariant();
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::size() const
	{
		return is_sso() ? m_data.sso.size & ((1 << 7) - 1) : m_data.non_sso.size;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::substr(size_type pos, size_type count) const
	{
		if (pos > size())
			throw std::out_of_range("Index out of range " + std::to_string(pos) + " >= " + std::to_string(size()) + ')');

		return U8String(*this, pos, count);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::swap(U8String& other)
	{
		std::swap(m_data, other.m_data);
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::tolower(const std::locale& locale) const
	{
		U8String tmp;
		tmp.reserve(raw_size() + 1);

		for (auto it = begin(); it != end(); ++it)
		{
			std::vector<Character> tmpLower = (*it).tomultilower(locale);
			for (auto character : tmpLower)
				tmp.push_back(character);
		}

		return tmp;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::totitlecase(const std::locale& locale) const
	{
		U8String tmp;
		tmp.reserve(raw_size() + 1);

		for (auto it = begin(); it != end(); ++it)
		{
			if (locale.name() == "lt_LT.utf8" && *it == u8"\u0307")
				continue;

			std::vector<Character> tmpLower = (*it).tomultititlecase(locale);
			for (auto character : tmpLower)
				tmp.push_back(character);
		}

		return tmp;
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> U8String<Traits, Allocator>::toupper(const std::locale& locale) const
	{
		U8String tmp;
		tmp.reserve(raw_size() + 1);

		for (auto it = begin(); it != end(); ++it)
		{
			if (locale.name() == "lt_LT.utf8" && *it == u8"\u0307")
				continue;

			std::vector<Character> tmpLower = (*it).tomultiupper(locale);
			for (auto character : tmpLower)
				tmp.push_back(character);
		}

		return tmp;
	}

	template <typename Traits, class Allocator>
	template <class OutputIterator>
	void U8String<Traits, Allocator>::toUTF16(OutputIterator result) const
	{
		utf8::utf8to16(data(), data() + raw_size(), result);
	}

	template <typename Traits, class Allocator>
	template <class OutputIterator>
	void U8String<Traits, Allocator>::toUTF32(OutputIterator result) const
	{
		utf8::utf8to32(data(), data() + raw_size(), result);
	}

	template <typename Traits, class Allocator>
	template <class OutputIterator>
	void U8String<Traits, Allocator>::toWide(OutputIterator result) const
	{
		/*typedef std::codecvt_utf8<wchar_t> convert_wide_to_utf8;
		std::wstring_convert<convert_wide_to_utf8, wchar_t> converterWUTF8;

		std::wstring tmp = converterWUTF8.from_bytes(data());

		for (auto c : tmp)
			*result++ = c;*/
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_pointer U8String<Traits, Allocator>::end_string() const
	{
		return is_sso() ? data() + (30 - m_data.sso.end_string) : data() + m_data.non_sso.end_string;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::const_pointer U8String<Traits, Allocator>::get_pointer_character(size_type pos) const
	{
		assert(pos <= size());

		const_pointer raw;

		if (pos > size() / 2)
		{
			raw = end_string();

			auto it = size();
			while (it-- != pos)
				utf8::prior(raw, data());
		}
		else
		{
			raw = const_cast<pointer>(data());
			auto it = 0U;
			while (it++ != pos)
				utf8::next(raw, end_string());
		}

		return raw;
	}

	template <typename Traits, class Allocator>
	bool U8String<Traits, Allocator>::is_sso() const
	{
		if (m_data.non_sso.size & MASK())
			return true;
		else
			return false;
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::initialize(size_type newSize, size_type endString)
	{
		if (endString <= sso_capacity)
			initialize_sso(newSize, endString);
		else
			initialize_non_sso(newSize, endString);
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::initialize_sso(size_type newSize, size_type endString)
	{
		assert(newSize <= 30);
		assert(endString <= 30);

		m_data.sso.end_string = 30 - endString;
		m_data.sso.size = newSize + (1 << 7);

		assert(is_sso());
	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::initialize_non_sso(size_type newSize, size_type endString)
	{
		m_data.non_sso.end_string = endString;
		m_data.non_sso.size = newSize;

		assert(!is_sso());
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::MASK() const
	{
		size_type tmp = 1;
		return tmp << 63;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::pointer U8String<Traits, Allocator>::raw_buffer()
	{
		return is_sso() ? m_data.sso.string : m_data.non_sso.ptr;
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type U8String<Traits, Allocator>::raw_size() const
	{
		return std::distance(data(), end_string());
	}

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator>& U8String<Traits, Allocator>::replace(const_pointer& offsetPointer, const Character& character)
	{
		const char* t = offsetPointer;
		size_type offset = std::distance(data(), t);
		assert(offset >= 0 && offset <= raw_size());

		char* beginPtr = raw_buffer() + offset;
		char* endPtr = beginPtr;
		utf8::next(endPtr, raw_buffer() + raw_size());

		size_type distance = std::distance(beginPtr, endPtr);
		auto sizeChar = character.number_byte();

		if (distance == sizeChar)
			Traits::copy(raw_buffer() + offset, character.byte, sizeChar);
		else if (distance < sizeChar) // We must make it bigger.
		{
			auto lengthToGet = raw_size() + sizeChar - distance;
			reserve(lengthToGet);

			auto endBuffer = raw_buffer() + raw_size();
			beginPtr = raw_buffer() + offset;

			std::move_backward(beginPtr, endBuffer, endBuffer + sizeChar - distance);

			Traits::copy(raw_buffer() + offset, character.byte, sizeChar);

			if (is_sso())
				initialize_sso(size(), raw_size() - distance + sizeChar);
			else
				initialize_non_sso(size(), raw_size() - distance + sizeChar);

			Traits::assign(raw_buffer()[raw_size()], '\0');

			offsetPointer = data() + offset;
		}
		else  // We can left shift.
		{
			std::rotate(beginPtr, beginPtr - sizeChar + distance, const_cast<pointer>(end_string()));

			Traits::copy(raw_buffer() + offset, character.byte, sizeChar);
			Traits::assign(raw_buffer()[raw_size() - distance + sizeChar], '\0');

			if (is_sso())
				initialize_sso(size(), raw_size() - distance + sizeChar);
			else
				initialize_non_sso(size(), raw_size() - distance + sizeChar);
		}

		invariant();

		return *this;

	}

	template <typename Traits, class Allocator>
	void U8String<Traits, Allocator>::invariant() const
	{
		assert(size() <= raw_size());
		assert(raw_size() <= capacity());
		if (!empty())
			assert(*(data() + raw_size()) == '\0');
	}

	template <typename Traits, class Allocator>
	typename U8String<Traits, Allocator>::size_type const U8String<Traits, Allocator>::npos(std::numeric_limits<U8String<Traits, Allocator>::size_type>::max());

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> operator+(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		U8String<Traits, Allocator> tmp;

		auto firstSize = lhs.raw_size();
		auto secondSize = rhs.raw_size();

		if ((firstSize + secondSize) <= U8String<Traits, Allocator>::sso_capacity)
		{
			Traits::copy(tmp.raw_buffer(), lhs.data(), firstSize);
			Traits::copy(tmp.raw_buffer() + firstSize, rhs.data(), secondSize);
			Traits::assign(tmp.raw_buffer()[firstSize + secondSize], '\0');

			tmp.initialize(lhs.size() + rhs.size(), firstSize + secondSize);
		}
		else
		{
			typename U8String<Traits, Allocator>::pointer newBuffer = lhs.get_allocator().allocate(firstSize + secondSize + 1);
			Traits::copy(newBuffer, lhs.data(), firstSize);
			Traits::copy(newBuffer + firstSize, rhs.data(), secondSize);
			Traits::assign(newBuffer[firstSize + secondSize], '\0');

			tmp.m_data.non_sso.ptr = newBuffer;
			tmp.initialize(lhs.size() + rhs.size(), firstSize + secondSize);
		}

		return tmp;
	}

	template <typename Traits, class Allocator>
	bool operator==(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		// std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); c++14
		/*auto first1 = lhs.begin();
		auto last1 = lhs.end();
		auto first2 = rhs.begin();
		auto last2 = rhs.end();

		for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return first1 == last1 && first2 == last2;*/

		if (rhs.empty() && lhs.empty())
			return true;

		if (rhs.empty() && !lhs.empty())
			return false;

		if (lhs.empty() && !rhs.empty())
			return false;

		assert(*(lhs.data() + lhs.raw_size()) == '\0');
		assert(*(rhs.data() + rhs.raw_size()) == '\0');

		return std::strcmp(lhs.data(), rhs.data()) == 0;
	}

	template <typename Traits, class Allocator>
	bool operator==(const char* lhs, const U8String<Traits, Allocator>& rhs)
	{
		if (rhs.empty() && (*lhs == '\0'))
			return true;

		if (!rhs.empty() && (*lhs == '\0'))
			return false;

		if (rhs.empty() && (*lhs != '\0'))
			return false;

		assert(*(rhs.data() + rhs.raw_size()) == '\0');

		return std::strcmp(lhs, rhs.data()) == 0;
	}

	template <typename Traits, class Allocator>
	bool operator==(const U8String<Traits, Allocator>& lhs, const char* rhs)
	{
		if (lhs.empty() && (*rhs == '\0'))
			return true;

		if (!lhs.empty() && (*rhs == '\0'))
			return false;

		if (lhs.empty() && (*rhs != '\0'))
			return false;

		assert(*(lhs.data() + lhs.raw_size()) == '\0');

		return std::strcmp(lhs.data(), rhs) == 0;
	}

	template <typename Traits, class Allocator>
	bool operator!=(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		return !operator==(lhs, rhs);
	}

	template <typename Traits, class Allocator>
	bool operator!=(const char* lhs, const U8String<Traits, Allocator>& rhs)
	{
		return std::strcmp(lhs, rhs.data()) != 0;
	}

	template <typename Traits, class Allocator>
	bool operator!=(const U8String<Traits, Allocator>& lhs, const char* rhs)
	{
		return std::strcmp(lhs.data(), rhs) != 0;
	}

	template <typename Traits, class Allocator>
	bool operator<(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		return lhs.compare(rhs) == -1;
	}

	template <typename Traits, class Allocator>
	bool operator<=(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		auto tmp = lhs.compare(rhs);
		return tmp == -1 || tmp == 0;
	}

	template <typename Traits, class Allocator>
	bool operator>(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		return !operator<=(lhs, rhs);
	}

	template <typename Traits, class Allocator>
	bool operator>=(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs)
	{
		return !operator<(lhs, rhs);
	}

	template <typename Traits, class Allocator>
	std::istream& operator>>(std::istream& is, U8String<Traits, Allocator>& str)
	{
		str.clear();

		std::string tmp;
		is >> tmp;

		str.assign(tmp);

		return is;

	}

	template <typename Traits, class Allocator>
	std::ostream& operator<<(std::ostream& os, const U8String<Traits, Allocator>& str)
	{
		if (str.empty())
			return os;

		return operator<<(os, str.data());
	}

} // U8

namespace std
{

	template <typename Traits, class Allocator>
	void swap(U8::U8String<Traits, Allocator>& lhs, U8::U8String<Traits, Allocator>& rhs)
	{
		lhs.swap(rhs);
	}

} // std
