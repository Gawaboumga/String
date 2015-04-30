#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <cstdint>
#include <locale>
#include <string>

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
			Character(Character&& character) = default;
			~Character();

			void assign(char character);
			void assign(const char* character);
			void assign(const Character& character);

			uint32_t code_point() const;
			int compare(const Character& character, const std::locale& locale = std::locale()) const;

			size_type number_byte() const;

			Character& operator=(char character);
			Character& operator=(const char* character);
			Character& operator=(const Character& character);
			Character& operator=(Character&& character) = default;

			operator std::basic_string<char> () const;

		private:

			Character(size_type position, const String* string);

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

} // U8

#endif // __CHARACTER_HPP__
