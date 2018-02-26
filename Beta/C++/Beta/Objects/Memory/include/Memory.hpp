/**
* \file					Memory.hpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					24/06/2017
*/

#ifndef MEMORY_HPP_
# define MEMORY_HPP_

# include <cstdlib>
# include <vector>
# include "Singleton.hpp"

class					Memory : public Singleton<Memory>
{
  friend class Singleton<Memory>;

private: /* Private's attributs */
  std::vector<void *>			m_instancePtr;

public: /* Public's attributs */
  unsigned short int			m_maxDiffSizeCapacity;

private: /* ctor & dtor */
  Memory(void);
  virtual ~Memory(void);
  void					operator()(void *vPtr) const;

public: /* Public's methods */
  void					*allocate(size_t const size);
  void				        deallocate(void *ptr);
  void					*reallocate(void *ptr, size_t const size);

public: /* Public template's methods */
  template<typename T>
  T					*allocate(size_t const size = 1)
  {
    return (static_cast<T *>(this->allocate(size * sizeof(T))));
  };

  template<typename T>
  void				        deallocate(T *ptr)
  {
    this->deallocate(static_cast<void *>(ptr));
  };
  template<typename T>
  T					*reallocate(T *ptr, size_t const size)
  {
    return (static_cast<T *>(this->reallocate(static_cast<void *>(ptr), size * sizeof(T))));
  }

public: /* Public static's methods */
  static void		       		copy(void *dest, void const *src,
					     size_t const size);
  static void  				move(void *dest, void const *src,
					     size_t const size);
  static void				changeMaxDiffSizeCapacity(unsigned short int const max,
								  Memory &mem = Memory::getInstance());

public: /* Public static template's methods */
  template <typename T>
  static void	       			copy(T *dest, T const *src,
					     size_t const size = sizeof(T))
  {
    Memory::copy(static_cast<void *>(dest), static_cast<void const *>(src), size);
  }

  template <typename T>
  static void	       			move(T *dest, T const *src,
					     size_t const size = sizeof(T))
  {
    Memory::move(static_cast<void *>(dest), static_cast<void const *>(src), size);
  }

};

#endif /* !MEMORY_HPP_ */
