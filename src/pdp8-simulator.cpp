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
    stats.clocks = 0;
    for (int i = 0; i < Sim::num_ops; ++i)
    {
        stats.ops[i] = 0;
    }
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

// Print statistics
// INPUT: Stream to use (cout default)
// OUTPUT: None
void Pdp8::Simulator::print_stats(std::ostream& out) const
{
    int insts = 0;

    for (int i = 0; i < Pdp8::Sim::num_ops; ++i)
        insts += stats.ops[i];

    out << "Instructions: " << insts  << std::endl;
    out << "Clocks      : " << stats.clocks << std::endl;
    out << "AND Sim     : " << stats.ops[Pdp8::Sim::AND] << std::endl;
    out << "TAD Sim     : " << stats.ops[Pdp8::Sim::TAD] << std::endl;
    out << "ISZ Sim     : " << stats.ops[Pdp8::Sim::ISZ] << std::endl;
    out << "DCA Sim     : " << stats.ops[Pdp8::Sim::DCA] << std::endl;
    out << "JMS Sim     : " << stats.ops[Pdp8::Sim::JMS] << std::endl;
    out << "I/O Sim     : " << stats.ops[Pdp8::Sim::JMP] << std::endl;
    out << "Micro Sim   : " << stats.ops[Pdp8::Sim::OPR] << std::endl;
}

// Start Simulation
// INPUT: Address to start at
// OUTPUT: None
void Pdp8::Simulator::start(unsigned short pc_start)
{
    pc = pc_start;

    while (process_instruction())
        continue;
}



//
// Private functions


// Decode instruction
// INPUT: 12 bit instruction to decode
// OUPTUP: instruction decoded in struct
Pdp8::Sim::Inst Pdp8::Simulator::decode(Pdp8::reg12 inst)
{
    Pdp8::Sim::Inst rv;

    rv.op = static_cast<Pdp8::Sim::Ops>(inst.to_ulong() >> 9);
    rv.ind = inst[8];
    rv.zero = inst[7];
    rv.offset = inst.to_ulong() & 0x7Fu;
    rv.micro = inst.to_ulong() >> 3;

    return rv;
}

// Proccess instruction
// INPUT: None
// OUTPUT: True if not halted, false if halted
bool Pdp8::Simulator::process_instruction()
{
    Pdp8::Sim::Inst instruction = decode(memory->fetch(pc.to_ulong()));
    bool halt = false;
    stats.ops[instruction.op] += 1;

    
    switch (instruction.op)
    {
    case (Pdp8::Sim::AND):
        break;
    case (Pdp8::Sim::TAD):
        break;
    case (Pdp8::Sim::ISZ):
        break;
    case (Pdp8::Sim::DCA):
        break;
    case (Pdp8::Sim::JMS):
        break;
    case (Pdp8::Sim::JMP):
        break;
    case (Pdp8::Sim::IOT):
        break;
    case (Pdp8::Sim::OPR):
        break;
    default:
        break;    
    }


    return halt;
}
