/**
* \file			        string_split.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <stdlib.h>
#include "vector.h"
#include "mystring.h"

static uint64_t       		string_split_count_elem(t_string *this,
                                                    char const lim)
{
    uint64_t     			size = 0;
    uint64_t     		    i = 0;

    while ((this->_data[i]))
        {
            if (this->_data[i] == lim)
                ++size;
            ++i;
        }
    return (size);
}

static t_bool	       		string_split_fill_string(t_string *this,
                                                     char const lim,
                                                     t_string *str,
                                                     uint64_t *accu)
{
    uint64_t			i = *accu;
    uint64_t			j = 0;

    *str = g_defaultString;
    while ((this->_data[*accu]) && (this->_data[*accu] != lim))
        ++(*accu);
    str->_length = (*accu - i);
    str->_capacity = str->_length;
    if (!(str->_data = malloc(sizeof(char) * (str->_capacity + 1))))
        return (false);
    while (i < (*accu))
        str->_data[j++] = this->_data[i++];
    str->_data[str->_capacity] = g_nullchar;
    if (this->_data[*accu])
        ++(*accu);
    return (true);
}


/**
* \brief		        Découpe une chaîne de caractère dans un tableau.
* \details		        Découpe la chaîne de caractère contenu dans {this}
*				par rapport au caractère {lim}.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param lim			Caractère limitant les morceaux de chaîne à couper..
* \return NULL			Echec de l'allocation mémoire.
* \return t_vector*		Création du tableau de string avec succès.
*
*/
t_vector			*string_split(t_string *this,
                                  char const lim)
{
    t_vector			*array = NULL;

    if (lim)
        {
            uint64_t			accu = 0;
            uint64_t     		size = string_split_count_elem(this, lim);

            if ((array = malloc(sizeof(*array))) &&
                (vector_ctor(array, sizeof(t_string), size)))
                {
                    while (array->_length < size)
                        {
                            if (!(string_split_fill_string(this, lim,
                                                           ((t_string *)array->_data) +
                                                           array->_length,
                                                           &accu)))
                                {
                                    free(array);
                                    return (NULL);
                                }
                            ++array->_length;
                        }
                }
        }
    return (array);
}
