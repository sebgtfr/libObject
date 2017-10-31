/**
* \file				vector_foreach.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				09 Décembre 2016
*/

#include <stdarg.h>
#include "vector.h"

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments du tableau.
* \details		        Parse l'intégralité des cases du tableau en éxécutant le callback {foreach} pour chaques objets.
* \param this			Référence sur le tableau.
* \param foreach		Callback appelé pour chaques cases du tableau afin d'éxécuté
*				une fonctionnalité sur chacun des objets contenu.
* \return			none
*
*/
void				vector_foreach(t_vector const *this,
					       t_fct_foreach foreach)
{
  if (foreach)
    {
      void			*iterator = this->_data;
      uint64_t			i = 0;

      while (i < this->_length)
	{
	  foreach(iterator);
	  iterator += this->_size_item;
	  ++i;
	}
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments du tableau
* \details		        Parse l'intégralité des cases du tableau en éxécutant le callback {foreach} pour chaques objets
*				en ajoutant en second paramètre du callback, la référence {data} fourni en paramètre.
* \param this			Référence sur le tableau.
* \param foreach		Callback appelé pour chaques cases du tableau afin d'éxécuté
* \param data			Référence vers un objet
*				une fonctionnalité sur chaques objets du  tableau.
* \return			none
*
*/
void				vector_foreach_data(t_vector const *this,
						    t_fct_foreach_data foreach,
						    void *data)
{
  if (foreach)
    {
      void			*iterator = this->_data;
      uint64_t			i = 0;

      while (i < this->_length)
	{
	  foreach(iterator, data);
	  iterator += this->_size_item;
	  ++i;
	}
    }
}

/**
* \brief		        Applique une fonctionnalité sur l'ensemble des éléments du tableau.
* \details		        Parse l'intégralité des cases du tableau en éxécutant le callback {foreach} pour chaques objets
*				en ajoutant en second paramètre du callback, un tableau de taille {argc} dont chaques case correspond
*				à une référence vers un objets fourni en paramètre via les varargs.
* \param this			Référence sur la liste.
* \param foreach		Callback appelé pour chaques cases du tableau afin d'éxécuté
*				une fonctionnalité sur chaques objets du tableau.
* \param argc			Nombre de référence à récupérer via les varargs.
* \param ...		        Varargs: attend {argc} référence(s).
* \return			none
*
*/
void				vector_foreach_ap(t_vector const *this,
						  t_fct_foreach_ap foreach,
						  uint64_t const argc, ...)
{
  if (foreach)
    {
      void			**argv = NULL;
      void			*iterator = this->_data;
      uint64_t			i = 0;

      if (argc && (argv = malloc(sizeof(*argv) * argc)))
	{
	  va_list		ap;

	  va_start(ap, argc);
	  while (i < argc)
	    {
	      argv[i] = va_arg(ap, void *);
	      ++i;
	    }
	  va_end(ap);
	}
      for (i = 0; i < this->_length; ++i)
	{
	  foreach(iterator, argv);
	  iterator += this->_size_item;
	}
      if (argv)
	free(argv);
    }
}
