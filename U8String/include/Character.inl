#include <utf8.h>

namespace U8
{

	template <class OutputIterator>
	void Character::toUTF16(OutputIterator result) const
	{
		utf8::utf8to16(byte, byte + number_byte(), result);
	}

	template <class OutputIterator>
	void Character::toUTF32(OutputIterator result) const
	{
		utf8::utf8to32(byte, byte + number_byte(), result);
	}

	template <class OutputIterator>
	void Character::toWide(OutputIterator result, const std::locale& locale) const
	{
		/*std::mbstate_t mb = std::mbstate_t();
		std::wstring_convert<std::codecvt<char, wchar_t, std::mbstate_t>(locale)> wideConv;
		std::wstring tmp = wideConv.from_bytes(byte);
		for (auto c : tmp)
		{
			*result = c;
			++result;
		}*/
	}

} // U8
