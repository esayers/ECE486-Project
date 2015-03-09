/* pdp8-simulator.cpp
 * Edward Sayers
 * ECE 486 Project
 */

#include "pdp8-simulator.h"

//
// Public Functions
//


// Constructor for Simulator
Pdp8::Simulator::Simulator()
{
    memory = new Memory;
    pc = 0200;              // Default to start at address 0200
}

// Destructor for simulator
Pdp8::Simulator::~Simulator()
{
    delete memory;
}

// Load simulator memory from hex file
// INPUT: filename to load
// OUTPUT: Number of memory locations loaded
int Pdp8::Simulator::load_from_hex(std::string filename)
{
    return memory->load_from_hex(filename);
}

// Load simulator memory from oct file
// INPUT: filename to load
// OUTPUT: Number of memory locations loaded
int Pdp8::Simulator::load_from_oct(std::string filename)
{
    return memory->load_from_oct(filename);
}

// Set name of tracefile output
// INPUT: filename
// OUTPUT: None
void Pdp8::Simulator::set_tracefile(std::string filename)
{
    memory->set_tracefile(filename);
}

// Dump memory contents to a stream
// INPUT: Stream to use (cout default)
// OUTPUT: Number of memory locations printed
int Pdp8::Simulator::dump_memory(std::ostream& out) const
{
    return memory->dump_memory(out);
}
