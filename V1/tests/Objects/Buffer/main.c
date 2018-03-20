
#include "Objects/Buffer.h"

#ifdef __cplusplus

using namespace					Objects;

#endif

int								main(void)
{
	Buffer						buf = Buffer_ctor(1024);
	Buffer						buf2 = Buffer_ctor(42);
	Buffer						buf3 = Buffer_ctor(0);
	Buffer						buf4 = Buffer_ctor(0);
	Buffer						*buf5 = Buffer_new(14);
	char const					hw[] = "Hello World !";

	Buffer_eq(&buf2, &buf);
	Buffer_write(&buf3, (uint8_t const *)&hw[0], sizeof(hw));
	Buffer_concat(&buf4, &buf3);
	Buffer_shift(&buf4, 6);
	Buffer_write(buf5, (uint8_t const *)&hw[0], 14);

	Buffer						*buf6 = Buffer_newCopy(buf5);
	bool						testEmpty = Buffer_empty(&buf4);

	Buffer_clear(&buf4);
	Buffer_shift(&buf3, Buffer_size(&buf3));
	testEmpty = Buffer_empty(&buf4);
	testEmpty = Buffer_empty(&buf3);

	Buffer_dtor(&buf);
	Buffer_dtor(&buf2);
	Buffer_dtor(&buf3);
	Buffer_dtor(&buf4);
	Buffer_delete(buf5);
	Buffer_delete(buf6);
	return 0;
}
