
#include "Objects/Buffer.h"

int								main(void)
{
	Buffer						buf = Buffer_ctor(1024);
	Buffer						buf2 = Buffer_ctor(42);
	Buffer						buf3 = Buffer_ctor(0);
	Buffer						buf4 = Buffer_ctor(0);
	char const					hw[] = "Hello World !";

	Buffer_eq(&buf2, &buf);
	Buffer_write(&buf3, (uint8_t const *)&hw[0], sizeof(hw) + 1);
	Buffer_concat(&buf4, &buf3);
	Buffer_shift(&buf4, 6);

	bool						testEmpty = Buffer_empty(&buf4);

	Buffer_clear(&buf4);
	Buffer_shift(&buf3, Buffer_size(&buf3));
	testEmpty = Buffer_empty(&buf4);
	testEmpty = Buffer_empty(&buf3);

	Buffer_dtor(&buf);
	Buffer_dtor(&buf2);
	Buffer_dtor(&buf3);
	Buffer_dtor(&buf4);
	return 0;
}
