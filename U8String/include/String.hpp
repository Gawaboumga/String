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
		template <class InputIter>
		using RequireInputIter = typename std::enable_if<std::is_convertible<typename std::iterator_traits<InputIter>::iterator_category, std::input_iterator_tag>::value>::type;

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

					difference_type number_character(const StringIterator& rhs) const;

					Character operator*();
					const Character operator*() const;
					operator const char* () const;
					StringIterator& operator=(const StringIterator& other) = default;

					bool operator==(const StringIterator& rhs) const;
					bool operator!=(const StringIterator& rhs) const;

					StringIterator& operator++();
					StringIterator operator++(int);
					StringIterator& operator--();
					StringIterator operator--(int);

				protected:

					size_type m_pos;
					const String* m_string;
			};

			class ReverseStringIterator : public StringIterator
			{
				public:
					using StringIterator::StringIterator;

					ReverseStringIterator& operator++();
					ReverseStringIterator operator++(int);
					ReverseStringIterator& operator--();
					ReverseStringIterator operator--(int);
			};

			// types:
			typedef StringIterator iterator;
			typedef const StringIterator const_iterator;
			typedef ReverseStringIterator reverse_iterator;
			typedef const ReverseStringIterator const_reverse_iterator;

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
			String(const std::vector<Character>& characters);
			String(size_type rep, char character);
			String(size_type rep, const Character& character);
			String(const String& string, size_type pos, size_type count);
			String(const char* string, size_type count);
			String(const char* string);
			template <typename InputIter, typename = RequireInputIter<InputIter>>
			String(InputIter first, InputIter last);
			String(const std::string& string);
			String(const String& string);
			String(String&& string) noexcept;
			String(std::initializer_list<const char*> init);
			String(std::initializer_list<Character> init);
			String(std::initializer_list<char> init);
			~String();

			String& append(const Character& character);
			String& append(const char* string);
			String& append(const String& string);

			void assign(const std::vector<Character>& characters);
			void assign(size_type n, char character);
			void assign(size_type n, const Character& character);
			void assign(const String& string);
			void assign(const String& string, size_type pos, size_type count = npos);
			void assign(String&& string);
			void assign(const char* string, size_type count);
			void assign(const char* string);
			void assign(const_iterator first, const_iterator last);
			template <typename InputIter, typename = RequireInputIter<InputIter>>
			void assign(InputIter first, InputIter last);
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
			size_type copy(char* dest, size_type count, size_type pos = 0) const;

			const char* data() const;

			bool empty() const;
			String& erase(size_type index = 0, size_type count = npos);
			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);

			size_type find(const String& str, size_type pos = 0) const;
			size_type find(const char* string, size_type pos = 0) const;
			size_type find(const Character& character, size_type pos = 0) const;
			size_type find_first_of(const String& str, size_type pos = 0) const;
			size_type find_first_of(const char* string, size_type pos = 0) const;
			size_type find_first_not_of(const String& str, size_type pos = 0) const;
			size_type find_first_not_of(const char* string, size_type pos = 0) const;
			size_type find_last_of(const String& str, size_type pos = npos) const;
			size_type find_last_of(const char* string, size_type pos = npos) const;
			size_type find_last_not_of(const String& str, size_type pos = npos) const;
			size_type find_last_not_of(const char* string, size_type pos = npos) const;
			Character front();
			const Character front() const;

			String& insert(size_type index, size_type count, char character);
			String& insert(size_type index, size_type count, const Character& character);
			String& insert(size_type index, const String& string, size_type subpos, size_type sublen = npos);
			String& insert(size_type index, const String& string);
			String& insert(size_type index, const char* string);
			iterator insert(const_iterator pos, const Character& character);
			iterator insert(const_iterator pos, size_type count, const Character& character);
			template <typename InputIter, typename = RequireInputIter<InputIter>>
			iterator insert(const_iterator pos, InputIter first, InputIter last);
			iterator insert(const_iterator pos, std::initializer_list<Character> ilist);

			size_type max_size() const;

			String& operator=(const std::vector<Character>& characters);
			String& operator=(const String& other);
			String& operator=(String&& other) noexcept;
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
			void resize(size_type count, const Character& character = Character());
			void replace(size_type pos, size_type count, const Character& character);
			size_type rfind(const String& string, size_type pos = npos) const;
			size_type rfind(const char* string, size_type pos = npos) const;
			size_type rfind(const Character& character, size_type pos = npos) const;

			void shrink_to_fit();
			size_type size() const;
			String substr(size_type pos = 0, size_type count = npos) const;
			void swap(String& other);

			String tolower(const std::locale& locale = std::locale()) const;
			String totitlecase(const std::locale& locale = std::locale()) const;
			String toupper(const std::locale& locale = std::locale()) const;

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

			template <typename InputIter>
			void assign(InputIter first, InputIter last, std::input_iterator_tag);
			template <typename RandomIter>
			void assign(RandomIter first, RandomIter last, std::random_access_iterator_tag);

			void ensure_ownership();

			template <typename InputIter>
			iterator insert(const_iterator pos, InputIter first, InputIter last, std::input_iterator_tag);
			template <typename RandomIter>
			iterator insert(const_iterator pos, RandomIter first, RandomIter last, std::random_access_iterator_tag);

			pointer raw_buffer();
			size_type raw_size() const;
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
