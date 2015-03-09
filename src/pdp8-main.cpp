#include <iostream>
#include <unistd.h>
#include <cctype>
#include <cstdlib>
#include "pdp8-simulator.h"

void printHelp(std::string);

int main (int argc, char **argv)
{
    int c;

    // Input flags
    bool vflg = false;
    bool oflg = false;
    bool tflg = false;

    std::string filename;
    std::string tracefile;
    Pdp8::Simulator sim;

    // Process input arguments
    opterr = 0; // Turn off option error messages
    while ((c = getopt(argc, argv, "v:o:t:")) != -1)
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
        case 't': // Tracefile name
            tflg = true;
            tracefile = optarg;
            break;
        case '?': // Invalid argument
            switch (optopt)
            {    
            case 'o':
            case 'v':
            case 't':
                std::cerr << "Option -" << (char) optopt << " requires an argument" << std::endl;
                break;
            default:
                if (std::isprint(optopt))
                    std::cerr << "Unknown option: " << (char) optopt << std::endl;
                else
                    std::cerr << "Unknown option: 0x" << std::hex << optopt << std::endl;
                printHelp(argv[0]);
                break;
            }
        default:
            printHelp(argv[0]);
            return 0;
        }
    }

    // Handle -o and -v flags
    if (oflg && vflg)
    {
        std::cerr << "Options -o and -v are mutually exclusive" << std::endl;
    }
    else if (oflg | vflg)
    {
        try
        {
            int ferr = 0; // To store number of times memory is touched
            if (oflg)
            {
                ferr = sim.load_from_oct(filename);
            }
            else if (vflg)
            {
                ferr = sim.load_from_hex(filename);
            }

            if (ferr == 0)
            {
                std::cerr << "File \"" << filename << "\" does not exist or contains no data" << std::endl;
            }
        }
        catch (...)
        {
            std::cerr << "Unable to load \"" << filename << "\": invald file format" << std::endl;
            return 0;
        }
    }
    else
    {
        std::cerr << "Either option -o or -v must be present" << std::endl;;
        printHelp(argv[0]);
    }

    // Handle -t flag
    if (tflg)
    {
        sim.set_tracefile(tracefile);
    }

    sim.dump_memory();

    return 0;
}

void printHelp(std::string filename)
{
    std::cerr << "Usage: " << filename << " [options]" << std::endl;
    std::cerr << "  options:" << std::endl;
    std::cerr << "-v <filename>     Loads a hex formated memory file" << std::endl;
    std::cerr << "-o <filename>     Loads an octal formated memory file" << std::endl;
    std::cerr << "-t <filename>     Specifies the filename for the tracefile output" << std::endl;
}
