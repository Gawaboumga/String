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

	uint32_t Character::code_point() const
	{
		return *utf8::iterator<const char*>(&byte[0], &byte[0], &byte[4]);
	}

	int Character::compare(const Character& other, const std::locale& locale) const
	{
		auto& f = std::use_facet<std::collate<char>>(locale);
		return f.compare(byte, byte + number_byte(),
			other.byte, other.byte + other.number_byte());
	}

	Character::size_type Character::number_byte() const
	{
		return std::strlen(byte);
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

} // U8
