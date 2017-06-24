#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "number.h"

int				main(int ac, char **av)
{
  if (ac == 3)
    {
      t_number			a;
      t_number			b;
      t_number			res;

      number_ctor(&a, NUMBER_STRING, (uint64_t)av[1]);
      number_ctor(&b, NUMBER_STRING, (uint64_t)av[2]);
      number_ctor(&res, NUMBER_UNDEFINED, (uint64_t)NULL);
      if (number_multiplication(&a, &b, &res))
	(void)printf("\n%s * %s = %s\n\n", NUMBER_DATA(&a), NUMBER_DATA(&b),
		     NUMBER_DATA(&res));


      int64_t			numA = number_integer(&a);
      int64_t			numB = number_integer(&b);

      (void)printf("\n%ld * %ld = %ld\n\n", numA, numB, numA * numB);
      number_dtor(&a);
      number_dtor(&b);
      number_dtor(&res);
      return (EXIT_SUCCESS);
    }
  else
    (void)printf("%s [a] [b]\n", av[0]);
  return (EXIT_FAILURE);
}
