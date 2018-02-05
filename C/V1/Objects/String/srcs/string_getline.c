/**
* \file			        string_getline.c
* \author			Sébastien Le Maire
* \version			1.0
* \date				22 Décembre 2016
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"

/**
* \brief		        Taille lecture/écriture d'un flux
* \details		        Macro Déterminant la taille de lecture/ecriture d'un flux.
*				L'utilisateur peut déterminer cette en définisant cette macro
*				avant d'inclure le fichier header mystring.h.
* \return		        Taille de lecture/ecriture d'un flux.
*/
uint64_t const                  l_stringBufferSize = 1024;

/**
 * \brief		        Charactère '\n' pour la fin d'une ligne dans un fichier.
 * \return		        '\n'
 */
static char const               l_newline = '\n';

static void			string_change_save(char **save, char *value)
{
    free(*save);
    *save = value;
}

static t_bool			string_getline_getsave(t_string *this,
                                               char **save,
                                               t_bool *end)
{
    uint64_t			size = 0;
    char				*tmp = NULL;

    while (((*save)[size]) && ((*save)[size] != l_newline))
        ++size;
    if (size)
        {
            if (!string_change(this, *save, size))
                return (false);
        }
    else
        string_reset(this);
    if ((*save)[size])
        {
            *end = true;
            if ((*save)[size + 1])
                if (!(tmp = strdup((*save) + (size + 1))))
                    return (false);
        }
    string_change_save(save, tmp);
    return (true);
}

static t_bool			string_getline_concat(t_string *this,
                                              char **save,
                                              char *buffer,
                                              t_bool *end)
{
    uint64_t			size = 0;

    while ((buffer[size]) && (buffer[size] != l_newline))
        ++size;
    if (size)
        {
            if (!string_concat(this, buffer, size))
                return (false);
        }
    else
        string_reset(this);
    if (buffer[size] == l_newline)
        {
            *end = true;
            if (buffer[size + 1])
                if (!(*save = strdup(buffer + (size + 1))))
                    return (false);
        }
    return (true);
}

/**
* \brief		        Lit un ligne dans le flux.
* \details		        Lit une ligne dans le flux fd jusqu'au '\n' ou '\0'
*				ou EOF. Dans le cas du '\n', celui-ci ne sera pas
*				retranscrit.
* \param this			Référence sur l'objet de chaîne de caractère.
* \param fd			File descriptor du flux auquel on ecrit les données.
* \return false			Echec de la lecture du flux ou de l'allocation mémoire.
* \return true		        Lecture du flux et allocation mémoire réussit avec succès.
*
*/
t_bool				string_getline(t_string *this, int const fd)
{
    static char		*save = NULL;
    int				ret = 1;
    char			buffer[l_stringBufferSize + 1];
    t_bool			end = false;

    if (save)
        {
            if (!string_getline_getsave(this, &save, &end))
                return (false);
        }
    else
        string_reset(this);
    while ((!end) && ((ret = read(fd, (void *)buffer, l_stringBufferSize)) > 0))
        {
            buffer[ret] = g_nullchar;
            if (!string_getline_concat(this, &save, buffer, &end))
                return (false);
        }
    return (!((ret <= 0) && (!end)));
}
