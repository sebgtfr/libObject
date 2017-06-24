/**
* \file					Buffer.hpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					24/06/2017
*/

#ifndef BUFFER_HPP_
# define BUFFER_HPP_

# include <cstdint>

class					Buffer
{
private:
  uint64_t				m_length;
  uint64_t				m_capacity;
  void					*m_datas;

public: /* ctor & dtor on canonics form */
  Buffer(void);
  Buffer(Buffer const &copy);
  Buffer				&operator=(Buffer const &other);
  ~Buffer(void);
};

#endif /* !BUFFER_HPP_ */
