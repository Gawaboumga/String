#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <Character.hpp>

#include <atomic>

#include <utf8.h>

namespace U8
{

	class String
	{
		template <class InputIterator>
		using is_input_iterator = typename std::enable_if<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIterator>::iterator_category>::value, InputIterator>::type;

		public:

			typedef char value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef unsigned int size_type;
			typedef int difference_type;

			class StringIterator
			{
				public:

					typedef String::value_type value_type;
					typedef String::reference reference;
					typedef String::pointer pointer;
					typedef String::size_type size_type;
					typedef String::difference_type difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

					StringIterator(const String* string, size_type pos);
					~StringIterator();

					const int* base() const;

					Character operator*();
					const Character operator*() const;
					operator char*() const;

					bool operator==(const StringIterator& rhs) const;
					bool operator!=(const StringIterator& rhs) const;

					StringIterator operator++();
					StringIterator operator++(int);
					StringIterator operator--();
					StringIterator operator--(int);

				private:

					utf8::iterator<char*> m_ptr;
					size_type m_pos;
					const String* m_string;
			};

			// types:
			typedef StringIterator iterator;
			typedef const StringIterator const_iterator;
			typedef StringIterator reverse_iterator;
			typedef const StringIterator const_reverse_iterator;

			// iterators:
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			const_iterator cbegin() const;
			const_iterator cend() const;
			const_reverse_iterator crbegin() const;
			const_reverse_iterator crend() const;

			String();
			explicit String(char character);
			explicit String(const Character& character);
			String(size_type rep, char character);
			String(size_type rep, const Character& character);
			String(const std::string& string, size_type pos, size_type count);
			String(const String& string, size_type pos, size_type count);
			String(const char* string, size_type count);
			explicit String(const char* string);
			template <class InputIterator>
			String(is_input_iterator<InputIterator> first, InputIterator last);
			explicit String(const std::string& string);
			explicit String(const String& string);
			String(String&& string);
			String(std::initializer_list<Character> init);
			String(std::initializer_list<char> init);
			~String();

			void assign(size_type n, char character);
			void assign(size_type n, const Character& character);
			void assign(const std::string& string);
			void assign(const String& string);
			void assign(const std::string& string, size_type pos, size_type count = npos);
			void assign(const String& string, size_type pos, size_type count = npos);
			void assign(String&& string);
			void assign(const char* string, size_type count);
			void assign(const char* string);
			template <class InputIterator>
			void assign(is_input_iterator<InputIterator> first, InputIterator last);
			void assign(std::initializer_list<char> init);
			void assign(std::initializer_list<Character> init);

			Character at(size_type pos);
			const Character at(size_type pos) const;

			Character back();
			const Character back() const;

			size_type capacity() const;
			Character character_at(size_type pos) const;
			void clear(bool keepBuffer = true);
			uint32_t code_point(size_type pos) const;

			const char* data() const;

			bool empty() const;

			Character front();
			const Character front() const;

			size_type max_size() const;

			String& operator=(const std::string& other);
			String& operator=(const String& other);
			String& operator=(String&& other);
			String& operator=(const char* string);
			String& operator=(char character);
			String& operator=(const Character& character);
			String& operator=(std::initializer_list<char> init);
			String& operator=(std::initializer_list<Character> init);

			Character operator[](size_type pos);
			const Character operator[](size_type pos) const;

			bool operator==(const std::string& other) const;
			bool operator==(const String& other) const;
			bool operator==(const char* other) const;

			bool operator!=(const std::string& other) const;
			bool operator!=(const String& other) const;
			bool operator!=(const char* other) const;

			std::basic_string<char> raw_character(size_type pos) const;
			void reserve(size_type bufferSize = 0);
			void replace(size_type pos, size_type count, const Character& character);

			void shrink_to_fit();
			size_type size() const;
			void swap(String& other);

			static const size_type npos;

		private:

			struct SharedString
			{
				SharedString() :
				capacity(0),
				size(0),
				buffer(nullptr),
				refCount(1)
				{
				}

				SharedString(unsigned short referenceCount, size_type bufferSize, size_type stringSize, value_type* str) :
				capacity(bufferSize),
				size(stringSize),
				buffer(str),
				refCount(referenceCount)
				{
				}

				size_type capacity;
				size_type size;
				value_type* buffer;

				std::atomic_ushort refCount;
			};

			void ensure_ownership();
			char* raw_buffer();
			void release_string();

			SharedString* m_sharedString;

			static SharedString emptyString;
	};

	std::ostream& operator<<(std::ostream& os, const String& str);

} // U8

namespace std
{

	void swap(U8::String& lhs, U8::String& rhs);

} // std

#include <String.inl>

#endif // __STRING_HPP__
