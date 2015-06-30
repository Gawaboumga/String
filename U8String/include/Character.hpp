#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <UnicodeData.hpp>

#include <cstdint>
#include <locale>
#include <string>
#include <vector>

namespace U8
{

	class String;

	class Character
	{
		friend class String;

		typedef char value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		public:

			Character();
			Character(char character);
			Character(const char* character);
			Character(const Character& character);
			Character(const std::vector<Character>& character);
			Character(Character&& character) = default;
			~Character();

			void assign(char character);
			void assign(const char* character);
			void assign(const Character& character);

			UnicodeData::GeneralCategory category() const;
			uint32_t code_point() const;
			unsigned char combining_class() const;
			int compare(const Character& character, const std::locale& locale = std::locale()) const;

			UnicodeData::BidirectionalCategory direction() const;

			bool has_mirrored() const;

			bool isalnum(const std::locale& locale = std::locale()) const;
			bool isalpha(const std::locale& locale = std::locale()) const;
			bool isblank(const std::locale& locale = std::locale()) const;
			bool iscntrl(const std::locale& locale = std::locale()) const;
			bool isdigit(const std::locale& locale = std::locale()) const;
			bool isgraph(const std::locale& locale = std::locale()) const;
			bool islower(const std::locale& locale = std::locale()) const;
			bool isprint(const std::locale& locale = std::locale()) const;
			bool ispunct(const std::locale& locale = std::locale()) const;
			bool isspace(const std::locale& locale = std::locale()) const;
			bool isupper(const std::locale& locale = std::locale()) const;
			bool isxdigit(const std::locale& locale = std::locale()) const;

			size_type number_byte() const;

			Character& operator=(char character);
			Character& operator=(const char* character);
			Character& operator=(const Character& character);
			Character& operator=(Character&& character);

			operator std::basic_string<char> () const;

			std::vector<Character> tolower(const std::locale& locale = std::locale()) const;
			std::vector<Character> totitlecase(const std::locale& locale = std::locale()) const;
			std::vector<Character> toupper(const std::locale& locale = std::locale()) const;

			friend std::istream& operator>>(std::istream& is, Character& character);

			static Character fromUTF16(const char16_t character[3]);
			static Character fromUTF32(const char32_t character[2]);
			static Character fromWide(const wchar_t* character, const std::locale& locale = std::locale());

		private:

			Character(size_type position, const String* string);

			std::vector<Character> convert_multi_unicodes(const std::array<UnicodeData::Unicode, 3>& unicodes) const;

			void fromCodePoint(UnicodeData::Unicode codePoint);

			char operator[](unsigned char pos) const;

			char byte[4];
			size_type m_position;
			String* m_string;
	};


	bool operator==(const Character& lhs, const Character& rhs);
	bool operator!=(const Character& lhs, const Character& rhs);

	bool operator<(const Character& lhs, const Character& rhs);
	bool operator<=(const Character& lhs, const Character& rhs);
	bool operator>(const Character& lhs, const Character& rhs);
	bool operator>=(const Character& lhs, const Character& rhs);

	std::ostream& operator<<(std::ostream& os, const Character& character);
	std::istream& operator>>(std::istream& is, Character& character);

} // U8

#endif // __CHARACTER_HPP__
