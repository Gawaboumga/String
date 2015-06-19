#include <Character.hpp>

#include <String.hpp>

#include <utf8.h>

#include <cassert>
#include <cstring>

namespace U8
{

	Character::Character() :
		m_position(0), m_string(nullptr)
	{
		byte[0] = '\0';
	}

	Character::Character(char character) :
		m_position(0), m_string(nullptr)
	{
		assign(character);
	}

	Character::Character(const char* character) :
		m_position(0), m_string(nullptr)
	{
		assign(character);
	}

	Character::Character(const Character& character) :
		m_position(0), m_string(nullptr)
	{
		assign(character.byte);
	}

	Character::~Character()
	{
	}

	void Character::assign(char character)
	{
		byte[0] = character;
		byte[1] = '\0';
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
		{
			byte[i] = '\0';
		}
	}

	void Character::assign(const Character& character)
	{
		size_type i = 0;
		while (i < character.number_byte())
		{
			byte[i] = character[i];
			++i;
		}
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

		if (m_string)
			m_string->replace(m_position, 1, *this);

		return *this;
	}

	Character& Character::operator=(const char* character)
	{
		assign(character);

		if (m_string)
			m_string->replace(m_position, 1, *this);

		return *this;
	}

	Character& Character::operator=(const Character& character)
	{
		assign(character);

		if (m_string)
			m_string->replace(m_position, 1, *this);

		return *this;
	}

	Character& Character::operator=(Character&& character)
	{
		if (m_string)
			m_string->replace(m_position, 1, character);

		std::copy(character.byte, character.byte + 4, byte);
		m_position = character.m_position;
		m_string = character.m_string;
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

	Character Character::tolower(const std::locale& /*locale*/) const
	{
		//! Todo use locale for azeri and so on http://unicode.org/faq/casemap_charprop.html
		UnicodeData::Unicode unicode = UnicodeData::lowercase_mapping(code_point());

		Character tmp;
		tmp.fromCodePoint(unicode);

		return tmp;
	}

	Character Character::totitlecase(const std::locale& /*locale*/) const
	{
		UnicodeData::Unicode unicode = UnicodeData::titlecase_mapping(code_point());

		Character tmp;
		tmp.fromCodePoint(unicode);

		return tmp;
	}

	Character Character::toupper(const std::locale& /*locale*/) const
	{
		UnicodeData::Unicode unicode = UnicodeData::uppercase_mapping(code_point());

		Character tmp;
		tmp.fromCodePoint(unicode);

		return tmp;
	}

	Character Character::fromUTF16(const char16_t character[2])
	{
		Character tmp;
		char* end = utf8::utf16to8(character, character + (character[1] ? 2 : 1), tmp.byte);
		if (end != tmp.byte + 4)
			*end = '\0';

		return tmp;
	}

	Character Character::fromUTF32(const char32_t character[1])
	{
		Character tmp;
		char* end = utf8::utf32to8(character, character + 1, tmp.byte);
		if (end != tmp.byte + 4)
			*end = '\0';

		return tmp;
	}

	Character Character::fromWide(const wchar_t* character, const std::locale& locale)
	{
		/*typedef std::codecvt_utf8<wchar_t> convert_wide_to_utf8;
		std::wstring_convert<convert_wide_to_utf8, wchar_t> converterWUTF8;

		return converterWUTF8.to_bytes(character);*/

		std::mbstate_t mb = std::mbstate_t();
		auto& f = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(locale);
		const wchar_t* from_next;
		char* to_next;
		Character tmp;
		f.out(mb, character, &character[2], from_next,
				  tmp.byte, &tmp.byte[4], to_next);

		return tmp;
	}

	Character::Character(size_type position, const String* string) :
		m_position(position), m_string(const_cast<String*>(string))
	{
		std::basic_string<char> tmp = string->raw_character(position);
		unsigned int i = 0;
		while (i < tmp.size())
		{
			byte[i] = tmp[i];
			++i;
		}

		if (i < 4U)
		{
			byte[i] = '\0';
		}
	}

	void Character::fromCodePoint(UnicodeData::Unicode codePoint)
	{
		char* end = utf8::append(codePoint, byte);
		if (end != byte + 4)
			*end = '\0';
	}

	char Character::operator[](unsigned char pos) const
	{
		assert(pos < 4);

		return byte[pos];
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
