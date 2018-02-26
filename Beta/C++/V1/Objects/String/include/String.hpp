
#ifndef OBJECTS_STRING_HPP_
# define OBJECTS_STRING_HPP_

# include "Objects/System.hpp"
# include "Objects/Char.hpp"

namespace								Objects
{
	namespace							Unicode
	{
		namespace						String
		{
			uint8						sizeUnicodeChar(char const c);

			class						Iterator
			{
			private:
				/* Private Attributes */
				char					*_current;

			public:
				/* ctor */
				Iterator(char *begin) : _current(begin) {};
				Iterator(Objects::Unicode::String::Iterator const &it)
					: _current(it._current) {};
				~Iterator(void) {};

				/* Public Methods */
				inline Objects::Unicode::Char				operator*(void)
					{
						return Objects::Unicode::Char(this->_current);
					}
				inline Objects::Unicode::String::Iterator	&operator++(void)
					{
						this->_current += Objects::Unicode::String::sizeUnicodeChar(*this->_current);
						return *this;
					}
				Objects::Unicode::String::Iterator	operator++(int)
					{
						Objects::Unicode::String::Iterator	it(*this);

						this->_current += Objects::Unicode::String::sizeUnicodeChar(*this->_current);
						return it;
					}
				inline bool					operator==(Objects::Unicode::String::Iterator const &it)
					{
						return this->_current == it._current;
					}
				inline bool					operator!=(Objects::Unicode::String::Iterator const &it)
					{
						return this->_current != it._current;
					}
			};
		}
	}

	class								String
	{
	public:
		/* Sub Class */
		class							Iterator
		{
		private:
			/* Private Attributes */
			char						*_current;

		public:
			/* ctor */
			Iterator(char *begin) : _current(begin) {};
			Iterator(Objects::String::Iterator const &it)
				: _current(it._current) {};
			~Iterator(void) {};

			/* Public Methods */
			inline char							&operator*(void)
				{
					return *this->_current;
				}
			Objects::String::Iterator			&operator++(void)
				{
					++this->_current;
					return *this;
				}
			Objects::String::Iterator			operator++(int)
				{
					Objects::String::Iterator	it(*this);

					++this->_current;
					return it;
				}
			inline bool					operator==(Objects::String::Iterator const &it)
				{
					return this->_current == it._current;
				}
			inline bool					operator!=(Objects::String::Iterator const &it)
				{
					return this->_current == it._current;
				}
		};


	private:
		/* Private Attributes */
		wordsize						_capacity;
		wordsize						_size;
		wordsize						_unicodeSize;
		char							*_data;

	public:
		/* ctor & dtor on canonics form */
		String(char const *str = nullptr);
		String(String const &copy);
		Objects::String					&operator=(Objects::String const &other);
		~String(void);

		/* Accessor */
		inline wordsize					capacity(void) const
			{
				return this->_capacity;
			}
		inline wordsize					size(void) const
			{
				return this->_size;
			}
		inline wordsize					unicodeSize(void) const
			{
				return this->_unicodeSize;
			}
		inline char const				*getRawData(void) const
			{
				return static_cast<char const *>(this->_data);
			}
		void							resize(wordsize const size);
		void							capacity(wordsize const capacity);
		char							&operator[](wordsize const idx);
		char							operator[](wordsize const idx) const;

		/* Static Public Methods */


	private:
		/* Private Methods */
		void							copy(char const *copy);
		void							copy(Objects::String const &copy);
		void							copy(Objects::String const &copy,
											 wordsize begin);

		/* Static Private Methods */
		static wordsize					strUnicodeLen(char const *str);
		static wordsize					strlen(char const *str);
	};
}

#endif /* !OBJECTS_STRING_HPP_ */
