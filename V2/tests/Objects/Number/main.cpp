
#include <iostream>
#include "Objects/Number.hpp"

int								main(void)
{
    Objects::Number             i;
    Objects::Number             answer = 42;
    Objects::Number             oppAnswer = -42;
    Objects::Number             maxChar = 127;
    Objects::Number             minChar = -128;
    Objects::Number             maxUChar = 255;
    Objects::Number             minUChar = -255;

    i = (unsigned)65365;
    if (i == (unsigned)65365)
        i = -42;
    if (i == -42)
        return 0;
	return 1;
}
