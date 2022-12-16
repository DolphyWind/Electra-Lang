#include <iostream>
#include <Electra.hpp>

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		std::cerr << "Error: No input file!";
		return 1;
	}
	Electra electra;
	electra.run();
	return 0;
}