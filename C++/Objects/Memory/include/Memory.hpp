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
# include <algorithm>
# include <new>
# include "Singleton.hpp"

class					Memory : public Singleton<Memory>
{
  friend class Singleton<Memory>;

private: /* Private's attributs */
  std::vector<void *>			m_instancePtr;

private: /* ctor & dtor */
  Memory(void) {};
  virtual ~Memory(void)
  {
    for (std::vector<void *>::iterator it = this->m_instancePtr.begin();
	 it != this->m_instancePtr.end(); ++it)
      {
	::free(*it);
      }
  };
  void					operator()(void *vPtr) const
  {
    ::free(vPtr);
  };

public: /* Template public's methods */
  template<typename T>
  T					*allocate(size_t const size)
  {
    void			       	*newBlock = ::malloc(sizeof(T) * size);

    if (!newBlock)
      {
	std::bad_alloc			ex;
	throw ex;
      }
    this->m_instancePtr.push_back(newBlock);
    return static_cast<T *>(newBlock);
  };

  template<typename T>
  void				        deallocate(T *ptr)
  {
    if (ptr && !this->m_instancePtr.empty())
      {
	void				*vPtr = static_cast<void *>(ptr);
	std::vector<void *>::iterator	it = std::find(this->m_instancePtr.begin(),
						       this->m_instancePtr.end(),
						       vPtr);

	if (vPtr && *it == vPtr)
	  {
	    this->m_instancePtr.erase(it);
	    ::free(vPtr);
	  }
      }
  };
  template<typename T>
  T					*reallocate(T *ptr, size_t const size)
  {
    if (ptr && !this->m_instancePtr.empty())
      {
	void				*vPtr = static_cast<void *>(ptr);
	std::vector<void *>::iterator	it = std::find(this->m_instancePtr.begin(),
						       this->m_instancePtr.end(),
						       vPtr);
	if (vPtr && *it == vPtr)
	  {
	    if ((*it = ::realloc(vPtr, sizeof(T) * size)))
	      return static_cast<T *>(*it);
	    else
	      {
		std::bad_alloc		ex;
		throw ex;
	      }
	  }
      }
    return this->allocate<T>(size);
  }

  void					*allocate(size_t const size)
  {
    void       				*newBlock = ::malloc(size);

    if (!newBlock)
      {
	std::bad_alloc			ex;
	throw ex;
      }
    this->m_instancePtr.push_back(newBlock);
    return newBlock;
  };

  void				        deallocate(void *ptr)
  {
    if (ptr && !this->m_instancePtr.empty())
      {
	std::vector<void *>::iterator	it = std::find(this->m_instancePtr.begin(),
						       this->m_instancePtr.end(),
						       ptr);

	if (ptr && *it == ptr)
	  {
	    this->m_instancePtr.erase(it);
	    ::free(ptr);
	  }
      }
  };

  void					*reallocate(void *ptr, size_t const size)
  {
    if (ptr && !this->m_instancePtr.empty())
      {
	std::vector<void *>::iterator	it = std::find(this->m_instancePtr.begin(),
						       this->m_instancePtr.end(),
						       ptr);
	if (ptr && *it == ptr)
	  {
	    if ((*it = ::realloc(ptr, size)))
	      return (*it);
	    else
	      {
		std::bad_alloc		ex;
		throw ex;
	      }
	  }
      }
    return this->allocate(size);
  }
};

#endif /* !MEMORY_HPP_ */
