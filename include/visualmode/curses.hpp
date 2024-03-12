#pragma once

#ifdef HAS_PDCURSES
#include <thirdparty/pdcurses/curses.h>
#elif defined(HAS_NCURSES)
#include <ncurses.h>
#endif // HAS_PDCURSES
