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
    switches = 0;
    ac = 0;
    l = 0;
    debug = false;
    pause = false;
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
    out << std::dec;
    out << "Clocks   : " << stats.clocks << std::endl;
    out << "AND Ops  : " << stats.ops[Pdp8::Sim::AND] << std::endl;
    out << "TAD Ops  : " << stats.ops[Pdp8::Sim::TAD] << std::endl;
    out << "ISZ Op   : " << stats.ops[Pdp8::Sim::ISZ] << std::endl;
    out << "DCA Ops  : " << stats.ops[Pdp8::Sim::DCA] << std::endl;
    out << "JMS Ops  : " << stats.ops[Pdp8::Sim::JMS] << std::endl;
    out << "JMP Ops  : " << stats.ops[Pdp8::Sim::JMP] << std::endl;
    out << "I/O Ops  : " << stats.ops[Pdp8::Sim::IOT] << std::endl;
    out << "Micro Ops: " << stats.ops[Pdp8::Sim::OPR] << std::endl;
    out << "Total    : " << insts  << std::endl;
}

// Start Simulation
// INPUT: Address to start at
// OUTPUT: None
void Pdp8::Simulator::start(unsigned short pc_start)
{
    bool halt;
    pc = pc_start;

    do
    {   
        print_debug();
        halt = process_instruction();
    } while (!halt);
    print_debug();
}

// Sets debug mode
// INPUT: True for on, false for off
// OUTPUT: None
void Pdp8::Simulator::set_debug(bool value)
{
    debug = value;
}

// Sets pause mode
// INPUT: True for on, false for off
// OUTPUT: None
void Pdp8::Simulator::set_pause(bool value)
{
    pause = value;
}

// Sets switches
// INPUT: value of switches
// OUTPUT: None
void Pdp8::Simulator::set_switches(Pdp8::reg12 sw)
{
    switches = sw;
}

//
// Private functions


// Decode instruction
// INPUT: 12 bit instruction to decode
// OUPTUP: instruction decoded in struct
Pdp8::Sim::Inst Pdp8::Simulator::decode(Pdp8::reg12 inst, unsigned short pc)
{
    Pdp8::Sim::Inst rv;

    rv.op = static_cast<Pdp8::Sim::Ops>(inst.to_ulong() >> 9);
    rv.ind = inst[8];
    rv.zero = inst[7];
    rv.offset = inst.to_ulong() & 0x7Fu;
    rv.micro = inst.to_ulong() & 0x1FF;
    rv.page = pc >> 7;

    return rv;
}

// Proccess instruction
// INPUT: None
// OUTPUT: True if not halted, false if halted
bool Pdp8::Simulator::process_instruction()
{
    Pdp8::Sim::Inst inst = decode(memory->fetch(pc.to_ulong()), pc.to_ulong());
    unsigned short  mar;
    Pdp8::reg12     mbr;
    std::bitset<13> iac;
    bool            halt = false;

    stats.ops[inst.op] += 1;
    pc = pc.to_ulong() + 1;

    switch (inst.op)
    {
    case (Pdp8::Sim::AND):
        mar = get_address(inst);
        mbr = memory->load(mar);
        ac &= mbr;
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::TAD):
        mar = get_address(inst);
        mbr = memory->load(mar);
        iac = ac.to_ulong();
        iac[12] = static_cast<unsigned int>(l);
        iac = iac.to_ulong() + mbr.to_ulong();
        ac = iac.to_ulong() & 0xFFF;
        l = iac[12];
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::ISZ):
        mar = get_address(inst);
        mbr = memory->load(mar);
        mbr = mbr.to_ulong() + 1;
        memory->store(mar, mbr);
        if (mbr.to_ulong() == 0)
        {
            pc = pc.to_ulong() + 1;
        }
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::DCA):
        mar = get_address(inst);
        memory->store(mar, ac);
        ac = 0;
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::JMS):
        mar = get_address(inst);
        memory->store(mar, pc);
        pc = mar + 1;
        stats.clocks += 2; 
        break;
    case (Pdp8::Sim::JMP):
        mar = get_address(inst);
        pc = mar;
        stats.clocks += 1;
        break;
    case (Pdp8::Sim::IOT):
        break;
    case (Pdp8::Sim::OPR):
        halt = process_micro(inst.micro);
        stats.clocks += 1;
        break;
    default:
        break;    
    }
    

    return halt;
}

// Process a micro op
// INPUT: Micro op to be prossessed
// OUTPUT: True if halt, false otherwise
bool Pdp8::Simulator::process_micro(Pdp8::reg9 micro)
{
    bool halt = false;

    if (micro[8] == 0)
    {
        // Group 1
        bool iac = micro[0];
        bool bsw = micro[1];
        bool ral = micro[2];
        bool rar = micro[3];
        bool cml = micro[4];
        bool cma = micro[5];
        bool cll = micro[6];
        bool cla = micro[7];

        // Clear accumulator if cla bit set
        if (cla)
            ac = 0;

        // Clear link if cll bit set
        if (cll)
            l = 0;

        // Complement accumulator if cma bit set
        if (cma)
            ac = ~ac;

        // Complement link if cml bit set
        if (cml)
            l = ~l;

        // Increment l/ac if iac bit set
        if (iac)
        {
            std::bitset<13> lac = ac.to_ulong();
            if (l)
                lac[12] = 1;
            else
                lac[12] = 0;

            lac = lac.to_ulong() + 1;

            l = lac[12];
            ac = lac.to_ulong() & 0xFFFu;
        }

        std::bitset<13> lac = ac.to_ulong();
        lac = ac.to_ulong();
        if (l)
            lac[12] = 1;
        else
            lac[12] = 0;

        if (bsw)
        {
            if (ral && !rar)
            {
                std::bitset<13> nlac = lac << 2;
                nlac[1] = lac[12];
                nlac[0] = lac[11];
                
                l = nlac[12];
                ac = nlac.to_ulong() & 0xFFFu; 
            }
            else if (rar && !ral)
            {
                std::bitset<13> nlac = lac >> 2;
                nlac[12] = lac[1];
                nlac[11] = lac[0];
                
                l = nlac[12];
                ac = nlac.to_ulong() & 0xFFFu;
            }
        }
        else
        {
            if (ral && !rar)
            {
                std::bitset<13> nlac = lac << 1;
                nlac[0] = lac[12];
                
                l = nlac[12];
                ac = nlac.to_ulong() & 0xFFFu; 
            }
            else if (rar && !ral)
            {
                std::bitset<13> nlac = lac >> 1;
                nlac[12] = lac[0];
                
                l = nlac[12];
                ac = nlac.to_ulong() & 0xFFFu;
            }
        } 
    }
    else if (micro[0] == 0)
    {
        // Group 2
        bool hlt = micro[1];
        bool osr = micro[2];
        bool rev = micro[3];
        bool snl = micro[4];
        bool sza = micro[5];
        bool sma = micro[6];
        bool cla = micro[7];
        bool skip = false;

        // Skip if bit 8 is true and all conditions in first block  are true
        // Or, skip if any of the other conditions is true
        if (rev)
        {
            if ((!sma || (sma && ac[11] == 0)) &&
                (!sza || (sza && ac != 0))     &&
                (!snl || (snl && l == 0)))
            {
                skip = true;
            }
        }
        else if (sma && ac[11] != 0)
        {
            skip = true;
        }
        else if (sza && ac == 0)
        {
            skip = true;
        }
        else if (snl && l != 0)
        {
            skip = true;
        }

        // skip next instruction if skip is true
        if (skip)
            pc = pc.to_ulong()  +  1;
        
        // Clear accumulator if cla bit is set
        if (cla)
            ac = 0;
        
        // OR accumulator with switches if osr bit is set
        if (osr)
            ac |= switches;

        // Return true if halt bit is set
        if (hlt)
            halt = true;
        
    }
    else
    {
        // Group 3
    }

    return halt;
}

// Get effective address
// INPUT: Instruction to get address from
// OUTPUT: Address
unsigned short Pdp8::Simulator::get_address(Pdp8::Sim::Inst inst)
{
    unsigned short page;
    unsigned short addr;

    // Set page
    if (inst.zero)
        page = inst.page;
    else
        page = 0;

    addr = (page << 7) | inst.offset;

    // Get indirect address
    if(inst.ind)
    {
        if (addr >= 010 && addr <= 017)
        {
            Pdp8::reg12 ival = memory->load(addr);
            ival = ival.to_ulong() + 1;
            memory->store(addr, ival);
            stats.clocks += 2;
            addr = ival.to_ulong();
        }
        else
        {
            addr = memory->load(addr).to_ulong();
        }
    stats.clocks += 1;
    }

    // Get data from memory
    return addr;
}

// Print debug information
// INPUT: None
// OUTPUT: Debug information
void Pdp8::Simulator::print_debug(void)
{
    // Do nothing if debug not set
    if (!debug)
        return;
    std::cerr << std::setfill('0');
    std::cerr << "PC: " << pc << " (0" << std::setw(4) << std::oct << pc.to_ulong() << ") ";
    std::cerr << "AC: " << ac << " (0" << std::setw(4) << std::oct << ac.to_ulong() << ") ";
    std::cerr << "L: ";
    if (l)
        std::cerr << "1";
    else
        std::cerr << "0";
    std::cerr << std::dec << " Clock: " << stats.clocks;

    if (pause)
        std::cin.get();
    else
        std::cerr << std::endl;
}
