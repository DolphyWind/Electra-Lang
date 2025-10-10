/**
MIT License

Copyright (c) 2023 Yunus Emre Aydın

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <Electra.hpp>

// #define __EMSCRIPTEN__
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>

Electra interpreter;
std::ostringstream oss;
std::istringstream iss;

void init(std::string input)
{
    if(!input.ends_with('\n'))
    {
        input = input + '\n';
    }

    interpreter = Electra();
    oss = std::ostringstream();
    iss = std::istringstream(input);

    interpreter.m_out = &oss;
    interpreter.m_in = &iss;
}

void set_source_code(const std::string& code)
{
    interpreter.setSourceCode(code);
}

std::string get_output()
{
    return oss.str();
}

void step()
{
    interpreter.step();
}

bool has_currents()
{
    return interpreter.has_currents();
}

void generate()
{
    interpreter.generateFromGenerators();
}

EMSCRIPTEN_BINDINGS(electra) {
    emscripten::function("init", &init);
    emscripten::function("set_source_code", set_source_code);
    emscripten::function("get_output", &get_output);
    emscripten::function("step", step);
    emscripten::function("has_currents", has_currents);
    emscripten::function("generate", generate);
}

#else

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    setvbuf(stdin, nullptr, _IOFBF, 1024 * 1024);

	std::cout << std::setprecision(15);
    std::vector<std::string> args;
    args.reserve(argc);
    for(int i = 0; i < argc; ++i)
    {
        args.emplace_back(argv[i]);
    }

	Electra electraInterpreter(args);
	electraInterpreter.mainLoop();
	return 0;
}

#endif
