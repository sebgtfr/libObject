
#include "Objects/Buffer.hpp"

int								main(void)
{
	Objects::Buffer				buf(1024);
	Objects::Buffer				buf2(42);
	Objects::Buffer				buf3;
	Objects::Buffer				buf4;
	Objects::Buffer				*buf5 = new Objects::Buffer(14);
	char const					hw[] = "Hello World !";

	buf2 = buf;
	buf3.write((uint8_t const *)&hw[0], sizeof(hw));
	buf4.write(buf3);
	buf4.shift(6);
	buf5->write((uint8_t const *)&hw[0], 14);

	Objects::Buffer				*buf6 = new Objects::Buffer(*buf5);
	bool						testEmpty = buf4.empty();

	buf4.clear();
	buf3.shift(buf3.size());
	testEmpty = buf4.empty();
	testEmpty = buf3.empty();

	delete buf5;
	delete buf6;
	return 0;
}
