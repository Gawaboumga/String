#include <utf8.h>
#include <cassert>
#include <iostream>

namespace U8
{
	template <typename RandomIter, typename>
	String::String(RandomIter first, RandomIter last) :
	m_sharedString(&emptyString)
	{
		if (first != last)
			assign(first, last);
	}

	template <typename RandomIter, typename>
	void String::assign(RandomIter first, RandomIter last)
	{
		assert(first < last);

		ensure_ownership();

		size_type distance = static_cast<size_type>(std::distance(first, last));

		if (distance > capacity())
			reserve(distance + 1);

		std::copy(first, last, raw_buffer());

		m_sharedString->buffer[distance] = '\0'; // String is terminated by a '\0'.
		m_sharedString->size = utf8::distance(first, last);
	}

	template <typename RandomIter, typename>
	String::iterator String::insert(const_iterator pos, RandomIter first, RandomIter last)
	{
		assert(first < last);

		ensure_ownership();

		size_type distance = static_cast<size_type>(std::distance(first, last));

		auto offset = pos - data();

		if (first >= data() && last <= data() + capacity())
		{
			auto offsetBegin = first - data();
			auto offsetEnd = last - data();

			if (empty())
				reserve(capacity() + distance + 1); // For the '\0'
			else
				reserve(capacity() + distance);

			if (!empty())
				right_shift(offset, distance, capacity() - 1);

			std::copy(data() + offsetBegin, data() + offsetEnd, raw_buffer() + offset);

			m_sharedString->buffer[capacity() - 1] = '\0'; // String is terminated by a '\0'.
			m_sharedString->size += utf8::distance(data() + offsetBegin, data() + offsetEnd);

			return StringIterator(this, utf8::distance(raw_buffer(), raw_buffer() + offset));
		}
		else
		{
			if (empty())
				reserve(capacity() + distance + 1); // For the '\0'
			else
				reserve(capacity() + distance);

			if (!empty())
				right_shift(offset, distance, capacity() - 1);

			std::copy(first, last, raw_buffer() + offset);

			m_sharedString->buffer[capacity() - 1] = '\0'; // String is terminated by a '\0'.
			m_sharedString->size += utf8::distance(first, last);

			return StringIterator(this, utf8::distance(raw_buffer(), raw_buffer() + offset));
		}
	}

} // U8
