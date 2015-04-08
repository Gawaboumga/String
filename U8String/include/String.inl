#include <utf8.h>

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
		size_type distance = static_cast<size_type>(std::distance(first, last));

		if (distance > capacity())
			reserve(distance + 1);

		std::copy(first, last, m_sharedString->buffer);

		m_sharedString->buffer[distance] = '\0'; // String is terminated by a '\0'.
		m_sharedString->size = utf8::distance(first, last);
	}

} // U8
