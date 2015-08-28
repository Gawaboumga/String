namespace U8
{

}

namespace U8
{

	using U8IT = typename U8::U8String<>::iterator;

	template <class T>
	U8IT remove(U8IT first, U8IT last, const T& value)
	{
		const U8String<>* realString = static_cast<const U8String<>*>(last.string());

		first = std::find(first, last, value);
		const char* realFirst = first.base();

		typename U8String<>::size_type offsetRealFirst = std::distance(realString->data(), realFirst);
		typename U8String<>::size_type offsetI = 0;

		if (first != last)
		{
			for(const char* i = realFirst; i != (realString->data() + realString->raw_size()); utf8::next(i, realString->data() + realString->raw_size()))
			{
				if (!(*U8IT(realString, i) == value))
				{
					auto firstChar = (*U8IT(realString, realFirst)).number_byte();
					auto lastChar = (*U8IT(realString, i)).number_byte();
					const char* oldData = realString->data();
					*U8IT(realString, realFirst) = std::move(*U8IT(realString, i));
					offsetRealFirst = std::distance(oldData, realFirst);
					offsetI = std::distance(oldData, i);

					realFirst = realString->data() + offsetRealFirst;
					i = realString->data() + offsetI;

					i += lastChar - firstChar;

					utf8::next(realFirst, realString->data() + realString->raw_size());
				}
			}
		}

		offsetRealFirst = std::distance(realString->data(), realFirst);

		return U8IT(realString, realString->data() + offsetRealFirst);
	}

	template <class UnaryPredicate>
	U8IT remove_if(U8IT first, U8IT last, UnaryPredicate p)
	{
		const U8String<>* realString = static_cast<const U8String<>*>(last.string());

		first = std::find_if(first, last, p);
		const char* realFirst = first.base();

		typename U8String<>::size_type offsetRealFirst = std::distance(realString->data(), realFirst);
		typename U8String<>::size_type offsetI = 0;

		if (first != last)
		{
			for(const char* i = realFirst; i != (realString->data() + realString->raw_size()); utf8::next(i, realString->data() + realString->raw_size()))
			{
				if (!p(*U8IT(realString, i)))
				{
					auto firstChar = (*U8IT(realString, realFirst)).number_byte();
					auto lastChar = (*U8IT(realString, i)).number_byte();
					const char* oldData = realString->data();
					*U8IT(realString, realFirst) = std::move(*U8IT(realString, i));
					offsetRealFirst = std::distance(oldData, realFirst);
					offsetI = std::distance(oldData, i);

					realFirst = realString->data() + offsetRealFirst;
					i = realString->data() + offsetI;

					i += lastChar - firstChar;

					utf8::next(realFirst, realString->data() + realString->raw_size());
				}
			}
		}

		offsetRealFirst = std::distance(realString->data(), realFirst);

		return U8IT(realString, realString->data() + offsetRealFirst);
	}

}
