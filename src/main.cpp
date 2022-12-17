#include <iostream>
#include <Electra.hpp>

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		std::cerr << "Error: No input file!" << std::endl;
		return 1;
	}
	Electra electra(argv[1]);
	electra.run();
	return 0;
}