#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <cstdint>
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
		typedef unsigned int size_type;
		typedef int difference_type;

		public:

			Character();
			Character(char character);
			Character(const char* character);
			Character(const Character& character);
			~Character();

			void assign(char character);
			void assign(const char* character);
			void assign(const Character& character);

			uint32_t code_point() const;

			size_type number_byte() const;

			bool operator==(char character) const;
			bool operator==(const char* character) const;
			bool operator==(const Character& character) const;
			bool operator!=(char character) const;
			bool operator!=(const char* character) const;
			bool operator!=(const Character& character) const;

			Character& operator=(char character);
			Character& operator=(const char* character);
			Character& operator=(const Character& character);

			operator std::basic_string<char> () const;

		private:

			Character(uint32_t position, const String* string);

			char operator[](unsigned char pos) const;

			char byte[4];
			size_type m_position;
			String* m_string;
	};

	std::ostream& operator<<(std::ostream& os, const Character& character);

} // U8

#endif // __CHARACTER_HPP__
