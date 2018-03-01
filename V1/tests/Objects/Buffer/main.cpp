
#include "Objects/Buffer.hpp"

int								main(void)
{
	Objects::Buffer				buf(1024);
	Objects::Buffer				buf2(42);
	Objects::Buffer				buf3;
	Objects::Buffer				buf4;
	char const					hw[] = "Hello World !";

	buf2 = buf;
	buf3.write((uint8_t const *)&hw[0], sizeof(hw) + 1);
	buf4.write(buf3);
	buf4.shift(6);

	bool						testEmpty = buf4.empty();

	buf4.clear();
	buf3.shift(buf3.size());
	testEmpty = buf4.empty();
	testEmpty = buf3.empty();

	return 0;
}
