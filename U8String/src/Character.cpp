#include <Character.hpp>

namespace U8
{

	Character::Character() :
		m_string(nullptr)
	{
		byte[0] = '\0';
	}

	Character::Character(char character) :
		m_string(nullptr)
	{
		assign(character);
	}

	Character::Character(const char* character) :
		m_string(nullptr)
	{
		assign(character);
	}

	Character::Character(const Character& character) :
		m_string(nullptr)
	{
		assign(character);
	}

	Character::~Character()
	{
	}

	void Character::assign(char character)
	{
		byte[0] = character;
		byte[1] = '\0';

		replace();
	}

	void Character::assign(const char* character)
	{
		if (utf8::distance(character, character + strlen(character)) > 1)
			throw std::invalid_argument("Character class contains only one character.");

		unsigned int i = 0;
		while (i < 4 && character[i])
		{
			byte[i] = character[i];
			++i;
		}

		if (i < 4)
			byte[i] = '\0';

		replace();
	}

	void Character::assign(const Character& character)
	{
		for (unsigned int i = 0; i < 4; ++i)
			byte[i] = character.byte[i];

		replace();
	}

	UnicodeData::GeneralCategory Character::category() const
	{
		return UnicodeData::general_category(code_point());
	}

	uint32_t Character::code_point() const
	{
		return *utf8::iterator<const char*>(&byte[0], &byte[0], &byte[4]);
	}

	unsigned char Character::combining_class() const
	{
		return UnicodeData::canonical_combining_classes(code_point());
	}

	int Character::compare(const Character& other, const std::locale& locale) const
	{
		auto& f = std::use_facet<std::collate<char>>(locale);
		return f.compare(byte, byte + number_byte(),
			other.byte, other.byte + other.number_byte());
	}

	UnicodeData::BidirectionalCategory Character::direction() const
	{
		return UnicodeData::bidirectional_category(code_point());
	}

	bool Character::has_mirrored() const
	{
		return UnicodeData::mirrored(code_point());
	}

	bool Character::isalnum(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::alnum;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isalpha(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::alpha;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	/*bool Character::isblank(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::blank;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}*/

	bool Character::iscntrl(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::cntrl;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isdigit(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::digit;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isgraph(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::graph;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::islower(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::lower;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isprint(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::print;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::ispunct(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::punct;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isspace(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::space;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isupper(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::upper;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	bool Character::isxdigit(const std::locale& locale) const
	{
		auto tmp = std::ctype_base::xdigit;
		return std::use_facet<std::ctype<char>>(locale).is(byte, byte + number_byte(), &tmp);
	}

	Character::size_type Character::number_byte() const
	{
		auto i = 0U;
		while (i < 4 && byte[i])
			++i;
		return i;
	}

	Character& Character::operator=(char character)
	{
		assign(character);

		return *this;
	}

	Character& Character::operator=(const char* character)
	{
		assign(character);

		return *this;
	}

	Character& Character::operator=(const Character& character)
	{
		assign(character);

		return *this;
	}

	Character& Character::operator=(Character&& character)
	{
		std::move(character.byte, character.byte + 4, byte);

		replace();

		return *this;
	}

	Character::operator std::basic_string<char> () const
	{
		char byteArray[5] = { '\0', '\0', '\0', '\0', '\0' };
		unsigned int i = 0;
		while (i < 4U && byte[i])
		{
			byteArray[i] = byte[i];
			++i;
		}

		return std::basic_string<char>(byteArray);
	}

	std::vector<Character> Character::tomultilower(const std::locale& locale) const
	{
		auto codepoint = code_point();

		std::array<UnicodeData::Unicode, 3> unicodes;
		if (codepoint == 0x49 && locale.name() != "lt_LT.utf8")
			unicodes = { '\0' };
		else
			unicodes = UnicodeData::special_lowercase_mapping(codepoint);

		if (unicodes[0] == '\0')
			return { tolower(locale) };

		return convert_multi_unicodes(unicodes);
	}

	std::vector<Character> Character::tomultititlecase(const std::locale& locale) const
	{
		auto codepoint = code_point();

		std::array<UnicodeData::Unicode, 3> unicodes = { { '\0' } };
		if (codepoint != 0x69)
			unicodes = UnicodeData::special_titlecase_mapping(codepoint);

		if (unicodes[0] == '\0')
			return { totitlecase(locale) };

		return convert_multi_unicodes(unicodes);
	}

	std::vector<Character> Character::tomultiupper(const std::locale& locale) const
	{
		auto codepoint = code_point();

		std::array<UnicodeData::Unicode, 3> unicodes = { { '\0' } };
		if (codepoint != 0x69)
			unicodes = UnicodeData::special_uppercase_mapping(codepoint);

		if (unicodes[0] == '\0')
			return { toupper(locale) };

		return convert_multi_unicodes(unicodes);
	}

	Character Character::tolower(const std::locale& locale) const
	{
		auto codePoint = code_point();

		Character tmp;

		if (locale.name() == "tr_TR.utf8" || locale.name() == "az_AZ.utf8")
			if (codePoint == 0x49)
			{
				tmp.fromCodePoint(0x131);
				return tmp;
			}

		UnicodeData::Unicode unicode = UnicodeData::lowercase_mapping(codePoint);

		tmp.fromCodePoint(unicode);
		return tmp;
	}

	Character Character::totitlecase(const std::locale& locale) const
	{
		auto codePoint = code_point();

		Character tmp;

		if (locale.name() == "tr_TR.utf8" || locale.name() == "az_AZ.utf8")
			if (codePoint == 0x69)
			{
				tmp.fromCodePoint(0x130);
				return tmp;
			}

		UnicodeData::Unicode unicode = UnicodeData::titlecase_mapping(codePoint);

		tmp.fromCodePoint(unicode);
		return tmp;
	}

	Character Character::toupper(const std::locale& locale) const
	{
		auto codePoint = code_point();

		Character tmp;

		if (locale.name() == "tr_TR.utf8" || locale.name() == "az_AZ.utf8")
			if (codePoint == 0x69)
			{
				tmp.fromCodePoint(0x130);
				return tmp;
			}

		UnicodeData::Unicode unicode = UnicodeData::uppercase_mapping(codePoint);

		tmp.fromCodePoint(unicode);

		return tmp;
	}

	Character Character::fromUTF16(const char16_t character[3])
	{
		Character tmp;
		char* end = utf8::utf16to8(character, character + (character[1] ? 2 : 1), tmp.byte);
		if (end != tmp.byte + 4)
			*end = '\0';

		return tmp;
	}

	Character Character::fromUTF32(const char32_t character[2])
	{
		Character tmp;
		char* end = utf8::utf32to8(character, character + 1, tmp.byte);
		if (end != tmp.byte + 4)
			*end = '\0';

		return tmp;
	}

	Character Character::fromWide(const wchar_t* /*character*/, const std::locale& /*locale*/)
	{
		/*typedef std::codecvt_utf8<wchar_t> convert_wide_to_utf8;
		std::wstring_convert<convert_wide_to_utf8, wchar_t> converterWUTF8;

		return converterWUTF8.to_bytes(character);*/

		assert(false);
		return "";
	}

	Character::Character(const_pointer* offset, uint32_t code_point, const Basic_String* string) :
		m_isPointer(true), m_string(const_cast<Basic_String*>(string))
	{
		m_offset.m_offsetPointer = offset;
		fromCodePoint(code_point);
	}

	Character::Character(const_pointer offset, uint32_t code_point, const Basic_String* string) :
		m_isPointer(false), m_string(const_cast<Basic_String*>(string))
	{
		m_offset.m_offset = offset;
		fromCodePoint(code_point);
	}

	std::vector<Character> Character::convert_multi_unicodes(const std::array<UnicodeData::Unicode, 3>& unicodes) const
	{
		auto it = unicodes.begin();
		std::vector<Character> tmpReturn;
		while (it != unicodes.end() && *it != '\0')
		{
			Character tmp;
			tmp.fromCodePoint(*it);
			tmpReturn.push_back(tmp);

			++it;
		}

		return tmpReturn;
	}

	void Character::replace()
	{
		if (m_string)
		{
			if (m_isPointer)
				m_string->replace(*m_offset.m_offsetPointer, *this);
			else
			{
				m_string->replace(m_offset.m_offset, *this);
			}
		}
	}

	void Character::fromCodePoint(UnicodeData::Unicode codePoint)
	{
		char* end = utf8::append(codePoint, byte);
		if (end != byte + 4)
			*end = '\0';
	}

	bool operator==(const Character& lhs, const Character& rhs)
	{
		return lhs.code_point() == rhs.code_point();
	}

	bool operator!=(const Character& lhs, const Character& rhs)
	{
		return !operator==(lhs, rhs);
	}

	bool operator<(const Character& lhs, const Character& rhs)
	{
		return lhs.compare(rhs) == -1;
	}

	bool operator<=(const Character& lhs, const Character& rhs)
	{
		auto tmp = lhs.compare(rhs);
		return tmp == -1 || tmp == 0;
	}

	bool operator>(const Character& lhs, const Character& rhs)
	{
		return !operator<=(lhs, rhs);
	}

	bool operator>=(const Character& lhs, const Character& rhs)
	{
		return !operator<(lhs, rhs);
	}

	std::ostream& operator<<(std::ostream& os, const Character& character)
	{
		return os << std::string(character);
	}

	std::istream& operator>>(std::istream& is, Character& character)
	{
		char c = '\0';
		int i = 0;

		while (i < 4)
		{
			is.get(c);
			character.byte[i] = c;
			if (c == '\0')
				i = 4;
			++i;
		}

		return is;
	}

} // U8
