/**
* \file					Singleton.hpp
* \author				Sébastien Le Maire
* \version				1.0
* \date					24/06/2017
*/

#ifndef SINGLETON_HPP_
# define SINGLETON_HPP_

template <class T>
class					Singleton
{
protected: /* Attributs */
  static T     				ms_instance;

protected: /* ctor & dtor */
  Singleton() {};
  virtual ~Singleton(void) {};

private:
  T					&operator=(T const &);

public: /* Static public's methods */
  static T     				&getInstance(void)
  {
    return (Singleton<T>::ms_instance);
  };
};

template <class T>
T					Singleton<T>::ms_instance = T();

#endif /* !SINGLETON_HPP_ */
