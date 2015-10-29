#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <Character.hpp>

#include <atomic>
#include <locale>

#include <utf8.h>

namespace U8
{

	template <typename Traits, class Allocator>
	U8String<Traits, Allocator> operator+(const U8String<Traits, Allocator> & lhs, const U8String<Traits, Allocator>& rhs);

	template <typename Traits = std::char_traits<char>, class Allocator = std::allocator<char>>
	class U8String final : public Basic_String, private Traits, Allocator
	{
		template <class RandomIter>
		using RequireRandomIter = typename std::enable_if<std::is_convertible<typename std::iterator_traits<RandomIter>::iterator_category, std::random_access_iterator_tag>::value>::type;
		template <class InputIter>
		using RequireInputIter = typename std::enable_if<std::is_convertible<typename std::iterator_traits<InputIter>::iterator_category, std::input_iterator_tag>::value>::type;

		public:

			using traits_type = Traits;
			using value_type = typename Traits::char_type;
			using allocator_type = Allocator;
			using size_type = typename std::allocator_traits<Allocator>::size_type;
			using difference_type = typename std::allocator_traits<Allocator>::difference_type;
			using reference = value_type&;
			using const_reference = const value_type&;
			using pointer = typename std::allocator_traits<Allocator>::pointer;
			using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

			class U8StringIterator
			{
				public:

					typedef U8String::value_type value_type;
					typedef U8String::reference reference;
					typedef U8String::pointer pointer;
					typedef U8String::size_type size_type;
					typedef U8String::difference_type difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

					U8StringIterator() = default;
					U8StringIterator(const U8StringIterator& other) = default;
					U8StringIterator(const U8String* string, const_pointer it);
					~U8StringIterator();

					const_pointer base() const;

					Character operator*();
					const Character operator*() const;
					U8StringIterator& operator=(const U8StringIterator& other) = default;

					bool operator==(const U8StringIterator& rhs) const;
					bool operator!=(const U8StringIterator& rhs) const;

					U8StringIterator& operator++();
					U8StringIterator operator++(int);
					U8StringIterator& operator--();
					U8StringIterator operator--(int);

					const U8String* string() const;

				protected:

					const_pointer m_it;
					const U8String* m_string;
			};

			class ReverseU8StringIterator : public U8StringIterator
			{
				public:
					using U8StringIterator::U8StringIterator;

					ReverseU8StringIterator& operator++();
					ReverseU8StringIterator operator++(int);
					ReverseU8StringIterator& operator--();
					ReverseU8StringIterator operator--(int);

				private:

					using U8StringIterator::m_it;
					using U8StringIterator::m_string;
			};

			// types:
			using iterator = U8StringIterator;
			using const_iterator = const U8StringIterator;
			using reverse_iterator = ReverseU8StringIterator;
			using const_reverse_iterator = const ReverseU8StringIterator;

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

			U8String();
			explicit U8String(const Allocator& alloc);
			U8String(char character, const Allocator& alloc = Allocator());
			U8String(const Character& character, const Allocator& alloc = Allocator());
			U8String(const std::vector<Character>& characters, const Allocator& alloc = Allocator());
			U8String(size_type rep, char character, const Allocator& alloc = Allocator());
			U8String(size_type rep, const Character& character, const Allocator& alloc = Allocator());
			U8String(const U8String& string, size_type pos, size_type count = npos, const Allocator& alloc = Allocator());
			U8String(const char* string, size_type count, const Allocator& alloc = Allocator());
			U8String(const char* string, const Allocator& alloc = Allocator());
			template <typename InputIter, typename = RequireInputIter<InputIter>>
			U8String(InputIter first, InputIter last, const Allocator& alloc = Allocator());
			U8String(const std::string& string, const Allocator& alloc = Allocator());
			U8String(const U8String& string, const Allocator& alloc = Allocator());
			U8String(U8String&& string, const Allocator& alloc = Allocator());
			U8String(std::initializer_list<const char*> init, const Allocator& alloc = Allocator());
			U8String(std::initializer_list<Character> init, const Allocator& alloc = Allocator());
			U8String(std::initializer_list<char> init, const Allocator& alloc = Allocator());
			~U8String();

			U8String& append(const char character);
			U8String& append(const Character& character);
			U8String& append(const char* string);
			U8String& append(const U8String& string);

			void assign(const std::vector<Character>& characters);
			void assign(size_type n, char character);
			void assign(size_type n, const Character& character);
			void assign(const U8String& string);
			void assign(const U8String& string, size_type pos, size_type count = npos);
			void assign(U8String&& string);
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
			void clear(bool keepBuffer = true);
			uint32_t code_point(size_type pos) const;
			int compare(const U8String& other, const std::locale& locale = std::locale()) const;
			int compare(const char* other, const std::locale& locale = std::locale()) const;
			size_type copy(char* dest, size_type count, size_type pos = 0) const;

			const char* data() const;

			bool empty() const;
			U8String& erase(size_type index = 0, size_type count = npos);
			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);

			size_type find(const U8String& str, size_type pos = 0) const;
			size_type find(const char* string, size_type pos = 0) const;
			size_type find(const Character& character, size_type pos = 0) const;
			size_type find_first_of(const U8String& str, size_type pos = 0) const;
			size_type find_first_of(const char* string, size_type pos = 0) const;
			size_type find_first_not_of(const U8String& str, size_type pos = 0) const;
			size_type find_first_not_of(const char* string, size_type pos = 0) const;
			size_type find_last_of(const U8String& str, size_type pos = npos) const;
			size_type find_last_of(const char* string, size_type pos = npos) const;
			size_type find_last_not_of(const U8String& str, size_type pos = npos) const;
			size_type find_last_not_of(const char* string, size_type pos = npos) const;
			static U8String fromUTF16(const char16_t* character);
			static U8String fromUTF32(const char32_t* character);
			static U8String fromWide(const wchar_t* character);
			Character front();
			const Character front() const;

			allocator_type get_allocator() const;

			U8String& insert(size_type index, size_type count, char character);
			U8String& insert(size_type index, size_type count, const Character& character);
			U8String& insert(size_type index, const U8String& string, size_type subpos, size_type sublen = npos);
			U8String& insert(size_type index, const U8String& string);
			U8String& insert(size_type index, const char* string);
			iterator insert(const_iterator pos, const Character& character);
			iterator insert(const_iterator pos, size_type count, const Character& character);
			template <typename InputIter, typename = RequireInputIter<InputIter>>
			iterator insert(const_iterator pos, InputIter first, InputIter last);
			iterator insert(const_iterator pos, std::initializer_list<Character> ilist);

			size_type max_size() const;

			operator const char*() const;

			U8String& operator=(const std::vector<Character>& characters);
			U8String& operator=(const U8String& other);
			U8String& operator=(U8String&& other) noexcept;
			U8String& operator=(const char* string);
			U8String& operator=(char character);
			U8String& operator=(const Character& character);
			U8String& operator=(std::initializer_list<const char*> init);
			U8String& operator=(std::initializer_list<Character> init);
			U8String& operator=(std::initializer_list<char> init);

			Character operator[](size_type pos);
			const Character operator[](size_type pos) const;

			friend U8String operator+<>(const U8String& lhs, const U8String& rhs);

			U8String& operator+=(const U8String& other);
			U8String& operator+=(const char* string);
			U8String& operator+=(const Character& other);

			void pop_back();
			void push_back(const Character& character);

			template <class OutputIterator>
			void raw_character(size_type pos, OutputIterator result) const;
			void reserve(size_type bufferSize = 0);
			void resize(size_type count, const Character& character = Character());
			U8String& replace(size_type pos, size_type count, const U8String& string);
			U8String& replace(const_iterator first, const_iterator last, const U8String& string);
			size_type rfind(const U8String& string, size_type pos = npos) const;
			size_type rfind(const char* string, size_type pos = npos) const;
			size_type rfind(const Character& character, size_type pos = npos) const;

			void shrink_to_fit();
			size_type size() const;
			U8String substr(size_type pos = 0, size_type count = npos) const;
			void swap(U8String& other);

			U8String tolower(const std::locale& locale = std::locale()) const;
			U8String totitlecase(const std::locale& locale = std::locale()) const;
			U8String toupper(const std::locale& locale = std::locale()) const;
			template <class OutputIterator>
			void toUTF16(OutputIterator result) const;
			template <class OutputIterator>
			void toUTF32(OutputIterator result) const;
			template <class OutputIterator>
			void toWide(OutputIterator result) const;

			static const size_type npos;

			size_type raw_size() const;

		private:

			template <typename InputIter>
			void assign(InputIter first, InputIter last, std::input_iterator_tag);
			template <typename RandomIter>
			void assign(RandomIter first, RandomIter last, std::random_access_iterator_tag);

			const_pointer end_string() const;

			const_pointer get_pointer_character(size_type pos) const;

			void initialize(size_type newSize, size_type endString);
			void initialize_sso(size_type newSize, size_type endString);
			void initialize_non_sso(size_type newSize, size_type endString);
			template <typename InputIter>
			iterator insert(const_iterator pos, InputIter first, InputIter last, std::input_iterator_tag);
			template <typename RandomIter>
			iterator insert(const_iterator pos, RandomIter first, RandomIter last, std::random_access_iterator_tag);
			void invariant() const;
			bool is_sso() const;

			size_type MASK() const;

			pointer raw_buffer();
			U8String& replace(const_pointer& offsetPointer, const Character& character);

			union Data
			{
				struct NonSSO
				{
					char* ptr;
					std::size_t capacity;
					std::size_t end_string;
					std::size_t size;
				} non_sso;
				struct SSO
				{
					char string[sizeof(NonSSO) / sizeof(char) - 2];
					char end_string;
					char size;
				} sso;
			} m_data;

			static std::size_t const sso_capacity = sizeof(typename Data::NonSSO) / sizeof(char) - 2;

	};

	template <typename Traits, class Allocator>
	bool operator==(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator==(const char* lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator==(const U8String<Traits, Allocator>& lhs, const char* rhs);
	template <typename Traits, class Allocator>
	bool operator!=(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator!=(const char* lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator!=(const U8String<Traits, Allocator>& lhs, const char* rhs);

	template <typename Traits, class Allocator>
	bool operator<(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator<=(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator>(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs);
	template <typename Traits, class Allocator>
	bool operator>=(const U8String<Traits, Allocator>& lhs, const U8String<Traits, Allocator>& rhs);

	template <typename Traits, class Allocator>
	std::istream& operator>>(std::istream& is, U8String<Traits, Allocator>& str);
	template <typename Traits, class Allocator>
	std::ostream& operator<<(std::ostream& os, const U8String<Traits, Allocator>& str);

	typedef U8String<> String;

} // U8

namespace std
{

	template <typename Traits, class Allocator>
	void swap(U8::U8String<Traits, Allocator>& lhs, U8::U8String<Traits, Allocator>& rhs);

} // std

#include <String.inl>
#include <STLAlgoString.inl>

#endif // __STRING_HPP__
