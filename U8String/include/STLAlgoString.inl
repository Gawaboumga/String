namespace std
{
	template<typename T>
	struct dummy : std::false_type
	{ };

	using U8IT = typename U8::U8String<>::iterator;
	template <class T>
	U8IT remove(U8IT first, U8IT last, const T& value)
	{
		static_assert(dummy<T>::value, "U8::remove should be used and remove should not be called at the same time with erase");
		return nullptr;
	}

	template <class UnaryPredicate>
	U8IT remove_if(U8IT first, U8IT last, UnaryPredicate p)
	{
		static_assert(dummy<UnaryPredicate>::value, "U8::remove_if should be used and remove_if should not be called at the same time with erase");
		return nullptr;
	}

	//! You should do something like this:
	//! auto it = U8::remove[_if](string.itBegin, string.itEnd, parameter);
	//! string.erase(it, string.itEnd);

}

namespace U8
{

	using U8IT = typename U8::U8String<>::iterator;

	template <class T, typename = typename std::enable_if<std::is_convertible<T, Character>::value>::type>
	U8IT remove(U8IT first, U8IT last, const T& value)
	{
		const U8String<>* realString = static_cast<const U8String<>*>(last.string());

		first = std::find(first, last, value);
		const char* realFirst = first.base();

		typename U8String<>::size_type offsetRealFirst = std::distance(realString->data(), realFirst);
		typename U8String<>::size_type offsetI = 0;

		if (first != last)
		{
			const char* rawEnd = realString->data() + realString->raw_size();
			for(const char* i = realFirst; i != rawEnd; utf8::next(i, rawEnd))
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

					rawEnd = realString->data() + realString->raw_size();
					utf8::next(realFirst, rawEnd);
				}
			}
		}

		offsetRealFirst = std::distance(realString->data(), realFirst);

		return U8IT(realString, realString->data() + offsetRealFirst);
	}

	template <class UnaryPredicate, typename = typename std::enable_if<!std::is_convertible<UnaryPredicate, Character>::value>::type>
	U8IT remove_if(U8IT first, U8IT last, UnaryPredicate p)
	{
		/*const U8String<>* realString = static_cast<const U8String<>*>(last.string());
		first = std::find_if(first, last, p);

		auto indexFirst = utf8::distance(realString->begin().base(), first.base());
		auto indexLast = indexFirst + utf8::distance(first.base(), last.base());

		if (indexFirst != indexLast)
		{
			for (auto indexForward = indexFirst; ++indexForward != indexLast; )
			{
				auto itRight = realString->begin();
				std::advance(itRight, indexForward);
				if (!p(*itRight))
				{
					auto itLeft = realString->begin();
					auto itRight = realString->begin();

					std::advance(itLeft, indexFirst);

					*itLeft = *itRight;
					indexFirst++;
				}
			}
		}

		auto itBegin = realString->begin();
		std::advance(itBegin, indexFirst);
		return itBegin;*/


		const U8String<>* realString = last.string();

		first = std::find_if(first, last, p);
		const char* realFirst = first.base();

		typename U8String<>::size_type offsetRealFirst = std::distance(realString->data(), realFirst);
		typename U8String<>::size_type offsetI = 0;

		if (first != last)
		{
			const char* rawEnd = realString->data() + realString->raw_size();
			for(const char* i = realFirst; i != rawEnd; utf8::next(i, rawEnd))
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

					rawEnd = realString->data() + realString->raw_size();
					utf8::next(realFirst, rawEnd);
				}
			}
		}

		offsetRealFirst = std::distance(realString->data(), realFirst);

		return U8IT(realString, realString->data() + offsetRealFirst);
	}

}
