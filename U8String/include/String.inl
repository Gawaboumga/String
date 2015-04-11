#include <utf8.h>
#include <iostream>

namespace U8
{

	template <class InputIterator>
	String::String(is_input_iterator<InputIterator> first, InputIterator last) :
	m_sharedString(&emptyString)
	{
		size_type distance = static_cast<size_type>(std::distance(first, last));

		if (distance > 0)
			assign(first, last);
	}

	template <class InputIterator>
	void String::assign(is_input_iterator<InputIterator> first, InputIterator last)
	{
		ensure_ownership();

		size_type distance = static_cast<size_type>(std::distance(first, last));

		if (distance > capacity())
			reserve(distance + 1);

		std::copy(first, last, raw_buffer());

		m_sharedString->buffer[distance] = '\0'; // String is terminated by a '\0'.
		m_sharedString->size = utf8::distance(first, last);
	}

	template <class InputIterator>
	String::iterator String::insert(const_iterator pos, is_input_iterator<InputIterator> first, InputIterator last)
	{
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
