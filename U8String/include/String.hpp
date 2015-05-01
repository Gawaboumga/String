#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <Character.hpp>

#include <atomic>
#include <locale>

#include <utf8.h>

namespace U8
{

	class String
	{
		template <class RandomIter>
		using RequireRandomIter = typename std::enable_if<std::is_convertible<typename std::iterator_traits<RandomIter>::iterator_category, std::random_access_iterator_tag>::value>::type;

		public:

			typedef char value_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;

			class StringIterator
			{
				public:

					typedef String::value_type value_type;
					typedef String::reference reference;
					typedef String::pointer pointer;
					typedef String::size_type size_type;
					typedef String::difference_type difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

					StringIterator(const StringIterator& other) = default;
					StringIterator(const String* string, size_type pos);
					~StringIterator();

					const int* base() const;

					difference_type number_character(const StringIterator& rhs) const;

					Character operator*();
					const Character operator*() const;
					operator char*() const;
					StringIterator& operator=(const StringIterator& other) = default;

					bool operator==(const StringIterator& rhs) const;
					bool operator!=(const StringIterator& rhs) const;

					StringIterator& operator++();
					StringIterator operator++(int);
					StringIterator& operator--();
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
			String(char character);
			String(const Character& character);
			String(size_type rep, char character);
			String(size_type rep, const Character& character);
			String(const String& string, size_type pos, size_type count);
			String(const char* string, size_type count);
			String(const char* string);
			template <typename RandomIter, typename = RequireRandomIter<RandomIter>>
			String(RandomIter first, RandomIter last);
			String(const std::string& string);
			String(const String& string);
			String(String&& string);
			String(std::initializer_list<const char*> init);
			String(std::initializer_list<Character> init);
			String(std::initializer_list<char> init);
			~String();

			String& append(const Character& character);
			String& append(const char* string);
			String& append(const String& string);

			void assign(size_type n, char character);
			void assign(size_type n, const Character& character);
			void assign(const String& string);
			void assign(const String& string, size_type pos, size_type count = npos);
			void assign(String&& string);
			void assign(const char* string, size_type count);
			void assign(const char* string);
			template <typename RandomIter, typename = RequireRandomIter<RandomIter>>
			void assign(RandomIter first, RandomIter last);
			void assign(std::initializer_list<const char*> init);
			void assign(std::initializer_list<Character> init);
			void assign(std::initializer_list<char> init);

			Character at(size_type pos);
			const Character at(size_type pos) const;

			Character back();
			const Character back() const;

			size_type capacity() const;
			Character character_at(size_type pos) const;
			void clear(bool keepBuffer = true);
			uint32_t code_point(size_type pos) const;
			int compare(const String& other, const std::locale& locale = std::locale()) const;

			const char* data() const;

			bool empty() const;
			String& erase(size_type index = 0, size_type count = npos);
			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);

			size_type find(const String& str, size_type pos = 0) const;
			size_type find(const char* string, size_type start = 0) const;
			size_type find(const Character& character, size_type pos = 0) const;
			Character front();
			const Character front() const;

			String& insert(size_type index, size_type count, const Character& character);
			String& insert(size_type index, const char* string);
			iterator insert(const_iterator pos, const Character& character);
			iterator insert(const_iterator pos, size_type count, const Character& character);
			template <typename RandomIter, typename = RequireRandomIter<RandomIter>>
			iterator insert(const_iterator pos, RandomIter first, RandomIter last);
			iterator insert(const_iterator pos, std::initializer_list<Character> ilist);

			size_type max_size() const;

			String& operator=(const String& other);
			String& operator=(String&& other);
			String& operator=(const char* string);
			String& operator=(char character);
			String& operator=(const Character& character);
			String& operator=(std::initializer_list<const char*> init);
			String& operator=(std::initializer_list<Character> init);
			String& operator=(std::initializer_list<char> init);

			Character operator[](size_type pos);
			const Character operator[](size_type pos) const;

			friend String operator+(const String& lhs, const String& rhs);

			String& operator+=(const char* string);
			String& operator+=(const String& other);
			String& operator+=(const Character& other);

			void pop_back();
			void push_back(const Character& character);

			std::basic_string<char> raw_character(size_type pos) const;
			void reserve(size_type bufferSize = 0);
			void replace(size_type pos, size_type count, const Character& character);

			void shrink_to_fit();
			size_type size() const;
			String substr(size_type pos = 0, size_type count = npos) const;
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
			char* get_index(size_type pos);
			char* raw_buffer();
			void release_string();
			void right_shift(size_type pos, size_type length, size_type end);

			SharedString* m_sharedString;

			static SharedString emptyString;
	};

	bool operator==(const String& lhs, const String& rhs);
	bool operator!=(const String& lhs, const String& rhs);

	bool operator<(const String& lhs, const String& rhs);
	bool operator<=(const String& lhs, const String& rhs);
	bool operator>(const String& lhs, const String& rhs);
	bool operator>=(const String& lhs, const String& rhs);

	std::istream& operator>>(std::istream& is, String& str);
	std::ostream& operator<<(std::ostream& os, const String& str);

} // U8

namespace std
{

	void swap(U8::String& lhs, U8::String& rhs);

} // std

#include <String.inl>

#endif // __STRING_HPP__
