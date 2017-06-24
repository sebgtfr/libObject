/**
* \file					Buffer.cpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					24/06/2017
*/
#include <cstdlib>
#include "Buffer.hpp"

Buffer::Buffer(void) : m_length(0), m_capacity(0), m_datas(0)
{
}

Buffer::Buffer(Buffer const &copy) : m_length(copy.m_length), m_capacity(copy.m_capacity)
{

}

Buffer					&Buffer::operator=(Buffer const &other)
{
  if (&other != this)
    {
    }
  return (*this);
}

Buffer::~Buffer(void)
{
}
