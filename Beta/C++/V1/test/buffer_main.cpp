

#include <iostream>

#include "Buffer.hpp"

int								main(void)
{
	Object::Static::Buffer		buffer(sizeof(size_t));

	buffer.write<size_t>(42);
	buffer.seek(0);
	std::cout << "Content should be 42 and content is "
			  << buffer.read<size_t>() << std::endl;
	buffer.write<size_t>(84);
	std::cout << "Content should be 0 and content is "
			  << buffer.read<size_t>() << std::endl;
	buffer.seek(0);
	std::cout << "Content should be 42 and content is "
			  << buffer.read<size_t>() << std::endl;
	buffer.seek(0);
	buffer.write<size_t>(84);
	buffer.seek(0);
	std::cout << "Content should be 84 and content is "
			  << buffer.read<size_t>() << std::endl;

	Object::Static::Buffer		buffer2(buffer);

	buffer.seek(0);
	std::cout << "Content should be 84 and content is "
			  << buffer.read<size_t>() << std::endl;

	Object::Dynamic::Buffer		dynBuf;
	Object::Dynamic::Buffer		dynBuf2(sizeof(int));
	Object::Dynamic::Buffer		dynBuf3(buffer);

	dynBuf.write<int>(42);
	dynBuf2.write<int>(42);

	dynBuf.seek(0);
	std::cout << "Content should be 42 and content is "
			  << dynBuf.read<int>() << std::endl;
	dynBuf2.seek(0);
	std::cout << "Content should be 42 and content is "
			  << dynBuf2.read<int>() << std::endl;
	dynBuf3.seek(0);
	std::cout << "Content should be 84 and content is "
			  << dynBuf3.read<size_t>() << std::endl;

	dynBuf2.seek(0);

	return 0;
}
