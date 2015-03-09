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
    bool sflg = false;

    std::string filename;
    std::string tracefile;
    std::string sstring;
    Pdp8::Simulator sim;

    // Process input arguments
    opterr = 0; // Turn off option error messages
    while ((c = getopt(argc, argv, "v:o:t:s:dp")) != -1)
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
        case 's': // Set switches
            sflg = true;
            sstring = optarg;
        case 'd': // Debug
            sim.set_debug(true);
            break;
        case 'p':
            sim.set_pause(true);
            break;
        case '?': // Invalid argument
            switch (optopt)
            {    
            case 'o':
            case 'v':
            case 't':
            case 's':
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
                printHelp(argv[0]);
                return 0;
            }
        }
        catch (...)
        {
            std::cerr << "Unable to load \"" << filename << "\": invald file format" << std::endl;
            printHelp(argv[0]);
            return 0;
        }
    }
    else
    {
        std::cerr << "Either option -o or -v must be present" << std::endl;
        printHelp(argv[0]);
        return 0;
    }

    // Handle -t flag
    if (tflg)
    {
        sim.set_tracefile(tracefile);
    }

    if (sflg)
    {
        Pdp8::reg12 sw;
        try
        {
           sw = std::stoul(sstring, NULL, 8);
        }
        catch (...)
        {
            std::cerr << "Switch value is invalid" << std::endl;
            printHelp(argv[0]);
            return 0;
        }
        sim.set_switches(sw);
    }

    sim.start();
    std::cout << std::endl << "Final memory contents:" << std::endl;
    sim.dump_memory();
    std::cout << std::endl;
    sim.print_stats();

    return 0;
}

void printHelp(std::string filename)
{
    std::cerr << "Usage: " << filename << " [options]" << std::endl;
    std::cerr << "  options:" << std::endl;
    std::cerr << "-v <filename>     Loads a hex formated memory file" << std::endl;
    std::cerr << "-o <filename>     Loads an octal formated memory file" << std::endl;
    std::cerr << "-t <filename>     Specifies the filename for the tracefile output" << std::endl;
    std::cerr << "-s <oct number>   Sets the switches to the value in number" << std::endl;
    std::cerr << "-d                Print debug messages" << std::endl;
    std::cerr << "-p                Pause between debug messages" << std::endl;
}
