/**
* \file				        Memory.cpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					29/06/2017
*/
#include <cstring>
#include <algorithm>
#include <new>
#include "Memory.hpp"

Memory::Memory(void) : m_maxDiffSizeCapacity(128)
{
}

Memory::~Memory(void)
{
  for (std::vector<void *>::iterator it = this->m_instancePtr.begin();
       it != this->m_instancePtr.end(); ++it)
    {
      ::free(*it);
    }
}

void					Memory::operator()(void *vPtr) const
{
  ::free(vPtr);
}

/*
** Public's methods
*/

void					*Memory::allocate(size_t const size)
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

void				        Memory::deallocate(void *ptr)
{
  if (ptr && !this->m_instancePtr.empty())
    {
      std::vector<void *>::iterator	it = std::find(this->m_instancePtr.begin(),
						       this->m_instancePtr.end(),
						       ptr);

      if (ptr && *it == ptr)
	{
	  this->m_instancePtr.erase(it);
	  if ((this->m_instancePtr.capacity() - this->m_instancePtr.size()) > this->m_maxDiffSizeCapacity)
	    {
	      std::vector<void *>    	tmp(this->m_instancePtr.begin(), this->m_instancePtr.end());

	      this->m_instancePtr.swap(tmp);
	    }
	  ::free(ptr);
	}
    }
};

void					*Memory::reallocate(void *ptr,
							    size_t const size)
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

/*
** Public static's methods
*/

void			       		Memory::copy(void *dest, void const *src,
						     size_t const size)
{
  (void)::memcpy(dest, src, size);
}

void					Memory::move(void *dest, void const *src,
						     size_t const size)
{
  (void)::memmove(dest, src, size);
}

void					Memory::changeMaxDiffSizeCapacity(unsigned short int const max,
									  Memory &mem)
{
  mem.m_maxDiffSizeCapacity = max;
}
