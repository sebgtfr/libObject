/**
* \file				Exception.hpp
* \author			Sébastien Le Maire
* \version			1.0
* \date				23 Février 2018
*/

#ifndef OBJECTS_EXCEPTION_HPP_
# define OBJECTS_EXCEPTION_HPP_

# include <exception>

namespace								Objects
{
	class								Exception
		: public						std::exception
	{
	public:

		/* Sub Class */
		enum							CodeError
		{
										BAD_ALLOC,
										READ_NULLPTR,
										OUT_OF_RANGE,
										NO_ERROR
		};

	private:

		/* Static Private Attributs */
		static char const * const		MSGS_ERROR[Objects::Exception::NO_ERROR];

		/* Private Attributs */
		Objects::Exception::CodeError	_codeError;

	public:

		/* Ctor & Dtor */
		Exception(Objects::Exception::CodeError const codeError)
			: _codeError(codeError) {};
		virtual ~Exception(void) override {};

		/* Public Methods */
		virtual inline char const		*what(void) const noexcept override
			{
				return (this->_codeError < Objects::Exception::NO_ERROR) ?
					Objects::Exception::MSGS_ERROR[this->_codeError]
					: nullptr;
			}
	};
}

#endif /* !OBJECTS_EXCEPTION_HPP_ */
