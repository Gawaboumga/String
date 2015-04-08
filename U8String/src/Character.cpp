#include <Character.hpp>

#include <String.hpp>

#include <utf8.h>

#include <cassert>
#include <cstring>

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
	}

	void Character::assign(const char* character)
	{
		unsigned int i = 0;
		while (character[i] && i < 4)
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
		unsigned int i = 0;
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

	Character::size_type Character::number_byte() const
	{
		return std::strlen(byte);
	}

	bool Character::operator==(char character) const
	{
		return byte[0] == character && byte[1] == '\0';
	}

	bool Character::operator==(const char* character) const
	{
		return code_point() == *utf8::iterator<const char*>(character, character, character + 4);
	}

	bool Character::operator==(const Character& character) const
	{
		return code_point() == character.code_point();
	}

	bool Character::operator!=(char character) const
	{
		return !operator==(character);
	}

	bool Character::operator!=(const char* character) const
	{
		return !operator==(character);
	}

	bool Character::operator!=(const Character& character) const
	{
		return !operator==(character);
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
		while (byte[i] && i < 4U)
		{
			byteArray[i] = byte[i];
			++i;
		}

		return std::basic_string<char>(byteArray);
	}

	Character::Character(uint32_t position, const String* string)
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


		m_position = position;
		m_string = const_cast<String*>(string);
	}

	char Character::operator[](unsigned char pos) const
	{
		assert(pos < 4);

		return byte[pos];
	}

	std::ostream& operator<<(std::ostream& os, const Character& character)
	{
		return os << std::string(character);
	}

} // U8
