#include <iostream>
#include <locale>
#include <Electra.hpp>

int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);
	std::wcout.imbue(std::locale("en_US.UTF-8"));
	std::wcin.imbue(std::locale("en_US.UTF-8"));
	Electra electra(argc, argv);
	electra.run();
	return 0;
}