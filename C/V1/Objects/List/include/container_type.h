/**
* \file			        container_type.h
* \author			Sébastien Le Maire
* \version			1.0
* \date				04 Décembre 2016
*/

#ifndef CONTAINER_TYPE_H_
# define CONTAINER_TYPE_H_

/*
** All typedef functions
*/
/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement clear. Il s'agit de la destruction de l'objet.
*				Le prototype du callback est :  void clear(void *content);
* \param content       	        Référence vers l'objet détruit.
*/
typedef void		(*t_fct_clear)(void *content);

/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement foreach. Il s'agit du parsing d'un conteneur.
*				Le prototype du callback est :  void foreach(void *content);
* \param content       	        Référence vers l'objet courrant du parsing.
*/
typedef void		(*t_fct_foreach)(void *content);

/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement foreach avec donnée unique. Il s'agit du parsing d'un conteneur.
*				Le prototype du callback est :  void foreach(void *content, void *data);
* \param content       	        Référence vers l'objet courrant du parsing.
* \param data			Référence vers un objet quelconque.
*/
typedef void		(*t_fct_foreach_data)(void *content, void *data);

/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement foreach avec données variatiques. Il s'agit du parsing d'un conteneur.
*				Le prototype du callback est :  void foreach(void *content, void **datas);
* \param content       	        Référence vers l'objet courrant du parsing.
* \param datas			Tableau de références vers des objets quelconques.
*/
typedef void		(*t_fct_foreach_ap)(void *content, void **datas);

/**
* \brief		        Callback sur un évènement.
* \details		        Callback sur un évènement compare. Il s'agit du parsing d'un conteneur avec une méthodes de comparaison des objets.
*				Le prototype du callback est :  void foreach(void *content, void const *data);
* \param content       	        Référence vers l'objet courrant du parsing.
* \param data			Référence vers un objet quelconque pour la comparaison.
* \return			true en cas de succès.
* \return			false en cas d'echec.
*/
typedef t_bool		(*t_fct_compare)(void *content, void const *data);

/**
* \brief		        Récupère le contenu d'un tableau de références..
* \details		        Récupère le contenu du tableau datas dans l'évènement foreach avec données variatiques.
* \param d       	        Tableau de données variatiques (cf #t_fct_foreach_ap).
* \param i		        Index dans le tableau.
* \param t			Type de l'objet référencé.
*/
# define AP_DATA(d,i,t)	(*((t *)d[i]))

#endif /* !CONTAINER_TYPE_H_ */
