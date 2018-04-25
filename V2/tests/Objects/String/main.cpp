
#include <iostream>
#include "Objects/String.hpp"

int								main(void)
{
	int							vAnswer = 42;
	float						vPi = 3.1415f;
	float						vTestFloat = 0.015f;
	double						vTestDouble = 0.0016f;
	Objects::String const		name = "Sébastien";

	Objects::String				answer = "La réponse à la question est ";
	Objects::String				pi = "PI = ";
	Objects::String				testFloat = "0.015 = ";
	Objects::String				testDouble = "1.0016 = ";

	std::cout << answer + vAnswer << std::endl;
	std::cout << pi + vPi << std::endl;
	std::cout << testFloat + vTestFloat << std::endl;
	std::cout << testDouble + vTestDouble << std::endl;

	answer += vAnswer;
	pi += vPi;
	testFloat += vTestFloat;
	testDouble += vTestDouble;

	std::cout << answer << std::endl;
	std::cout << pi << std::endl;
	std::cout << testFloat << std::endl;
	std::cout << testDouble << std::endl;

	Objects::String				str;

	str = "Salut, je m'appelle " + name + " et j'ai " + 18 + " ans !";
	std::cout << str << std::endl;

	str = Objects::String::format("Pi = %2.2f", vPi);
	std::cout << str << std::endl;

	return 0;
}
