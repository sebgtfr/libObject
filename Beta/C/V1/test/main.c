#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "list.h"
#include "mystring.h"

int				main(void)
{
	t_string	str;
	int			answer = 42;
	t_vector	arrayint;
	t_list		listInt;

	string_ctor(&str, "Hello");
	vector_ctor(&arrayint, sizeof(int), 0);
	vector_ctor(&arrayint, sizeof(int), 0);
	list_ctor(&listInt, sizeof(int));

	string_concat(&str, " World ", 0);
	string_push_back(&str, '!');
	string_print(&str, 1);

	vector_push_back(&arrayint, &answer);
	list_push_back(&listInt, &answer);

	t_vector	*split = string_split(&str, ' ');

	string_dtor(&str);
	vector_dtor(&arrayint, NULL);
	vector_dtor(split, NULL);
	free(split);
	list_dtor(&listInt, NULL);
    return (EXIT_SUCCESS);
}
