#include <iostream>
#include <unistd.h>
#include <cctype>
#include <cstdlib>
#include "pdp8-memory.h"

int main (int argc, char **argv)
{
    int c;
    bool vflg = false;
    bool oflg = false;
    int ferr;
    std::string filename;
    Pdp8::Memory mm;

    // Process input arguments
    opterr = 0; // Turn off option error messages
    while ((c = getopt(argc, argv, "v:o:")) != -1)
    {
        switch(c)
        {
        case 'v': // Load from hex file
            vflg = true;
            filename = optarg;
            break;
        case 'o': // Load from oct file
            oflg = true;
            filename = optarg;
            break;
        case '?': // Invalid argument
            if (optopt == 'o')
                std::cerr << "Option -o requires an argument" << std::endl;
            else if (optopt == 'v')
                std::cerr << "Option -v reuires an argument" << std::endl;
            else if (std::isprint(optopt))
                std::cerr << "Unknown option: " << (char) optopt << std::endl;
            else
                std::cerr << "Unknown option: 0x" << std::hex << optopt << std::endl;
        default:
            return 0;
        }
    }

    // Handle -o and -v flags
    if (oflg && vflg)
    {
        std::cerr << "Options -o and -v are mutually exclusive" << std::endl;
    }
    else
    {
        try
        {
            if (oflg)
            {
                ferr = mm.load_from_oct(filename);
            }
            else if (vflg)
            {
                ferr = mm.load_from_hex(filename);
            }

            if (ferr == 0)
            {
                std::cerr << "File \"" << filename << "\" does not exist or contains no data" << std::endl;
            }
        }
        catch (...)
        {
            std::cerr << "Unable to load \"" << optarg << "\": invald file format" << std::endl;
            return 0;
        }
    }

    mm.dump_memory(std::cout);
    
    return 0;
}
