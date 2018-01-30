/**
* \file					Buffer.hpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					24/06/2017
*/

#ifndef BUFFER_HPP_
# define BUFFER_HPP_

class					Buffer
{
private: /* Private's attributs */
  size_t				m_size;
  size_t				m_capacity;
  void					*m_data;

public: /* ctor & dtor on canonics form */
  Buffer(size_t const size = 0);
  Buffer(Buffer const &copy);
  Buffer				&operator=(Buffer const &other);
  ~Buffer(void);

private: /* Private's methods */
  void					resize(size_t const capacity);

public: /* Public's methods */
  void					reset(void);
  void				        clear(void);
  size_t				size(void) const;
  void					*getData(size_t const shift = 0) const;
  void					assign(void const *data,
					       size_t const size);
  void				        change(void const *data,
					       size_t const size);
  void				        concat(void const *data,
					       size_t const size);
  void				        shift(size_t const shift);

public: /* Public template's methods */
  template<typename T>
  T					*getData(size_t const shift = 0) const
  {
    return static_cast<T *>(this->getData(shift));
  }

  template<typename T>
  inline void				assign(T const *data,
					       size_t const size = sizeof(T))
  {
    this->assign(static_cast<void const *>(data), size);
  };

  template<typename T>
  inline void				assign(T const &data,
					       size_t const size = sizeof(T))
  {
    this->assign(static_cast<void const *>(&data), size);
  };

  template<typename T>
  inline void				change(T const *data,
					       size_t const size = sizeof(T))
  {
    this->change(static_cast<void const *>(data), size);
  }

  template<typename T>
  inline void				change(T const &data,
					       size_t const size = sizeof(T))
  {
    this->change(static_cast<void const *>(&data), size);
  }

  template<typename T>
  inline void				concat(T const *data,
					       size_t const size = sizeof(T))
  {
    this->concat(static_cast<void const *>(data), size);
  }

  template<typename T>
  inline void				concat(T const &data,
					       size_t const size = sizeof(T))
  {
    this->concat(static_cast<void const *>(&data), size);
  }

};

#endif /* !BUFFER_HPP_ */
