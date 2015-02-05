#include <iostream>
#include <unistd.h>
#include <cctype>
#include <cstdlib>
#include "pdp8-memory.h"

int main (int argc, char **argv)
{
    int c;
    Pdp8::Memory mm;

    // Process input arguments
    opterr = 0; // Turn of option error messages
    while ((c = getopt(argc, argv, "")) != -1)
    {
        switch(c)
        {
        case '?': // Invalid argument
            if (std::isprint(optopt))
                std::cout << "Unknown option: " << (char) optopt << std::endl;
            else
                std::cout << "Unknown option: 0x" << std::hex << optopt << std::endl;
            break;
        default:
            abort();
        }
    }

    mm.load_from_file("add01.mem");
    mm.store(0, 100);
    mm.dump_memory(std::cout);
}
