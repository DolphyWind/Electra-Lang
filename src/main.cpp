#include <iostream>
#include <locale>
#include <Electra.hpp>
#include <codecvt>

#ifdef _WIN32
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#endif

int main(int argc, char *argv[])
{
	#ifdef _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	#else
	std::ios_base::sync_with_stdio(false);
	std::wcout.imbue(std::locale(std::wcout.getloc(), new std::codecvt_utf8<char_t>));
	std::wcerr.imbue(std::locale(std::wcerr.getloc(), new std::codecvt_utf8<char_t>));
	std::wcin.imbue(std::locale(std::wcin.getloc(), new std::codecvt_utf8<char_t>));
	#endif
	Electra electra(argc, argv);
	electra.run();
	return 0;
}