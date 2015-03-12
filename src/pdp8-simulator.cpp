// pdp8-simulator.cpp
// Edward Sayers
// ECE 486: PDP-8 Instruction Set Simulator

#include "pdp8-simulator.h"

//
// Public Functions
//


// Constructor for Simulator
Pdp8::Simulator::Simulator()
{
    // Create memory
    memory = new Memory;

    // Zero out stats
    stats.clocks = 0;       
    for (int i = 0; i < Sim::num_ops; ++i)
    {
        stats.ops[i] = 0;
    }

    // Switchs, ac and l initialized to 0
    switches = 0;
    ac = 0;
    l = 0;

    // Debug and pause off by default
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
    int insts = 0; // Instruction total

    // Total instructions from each mnemonic
    for (int i = 0; i < Pdp8::Sim::num_ops; ++i)
        insts += stats.ops[i];

    // Print statistics
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
    bool halt;      // halt condition
    pc = pc_start;  // set pc to starting addess

    // Process instructions until halt is encountered
    // If debug is true, print before and after every instruction
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
    Pdp8::Sim::Inst rv; // return value

    // Seperate instruction into parts
    rv.op       = static_cast<Pdp8::Sim::Ops>(inst.to_ulong() >> 9); // Op code
    rv.ind      = inst[8];                  // indirect flag
    rv.zero     = inst[7];                  // zero flag
    rv.offset   = inst.to_ulong() & 0x7Fu;  // page offset
    rv.micro    = inst.to_ulong() & 0x1FF;  // micro instructions
    rv.page     = pc >> 7;                  // page

    return rv;
}

// Proccess instruction
// INPUT: None
// OUTPUT: True if not halted, false if halted
bool Pdp8::Simulator::process_instruction()
{
    Pdp8::Sim::Inst inst;           // decoded instruction
    unsigned short  mar;            // address buffer
    Pdp8::reg12     mbr;            // data buffer
    std::bitset<13> lac;            // l+ac for ac arithmetic
    bool            halt = false;   // halt flag, defaults to start

    // Fetch and decode instruction
    inst = decode(memory->fetch(pc.to_ulong()), pc.to_ulong());

    stats.ops[inst.op] += 1;    // add to appropriate instruction count
    pc = pc.to_ulong() + 1;     // increment pc

    // Switch on op code
    switch (inst.op)
    {
    case (Pdp8::Sim::AND):
        // calculate address and load value
        mar = get_address(inst);
        mbr = memory->load(mar);

        // and ac with value from memory
        ac &= mbr;

        // update stats
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::TAD):
        // calculate address and load value
        mar = get_address(inst);
        mbr = memory->load(mar);

        // Combine l and ac
        lac = ac.to_ulong();
        lac[12] = static_cast<unsigned int>(l);

        // add value from memory to lac
        lac = lac.to_ulong() + mbr.to_ulong();

        // update ac and l to reflect new value
        ac = lac.to_ulong() & 0xFFF;
        l = lac[12];

        // update stats
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::ISZ):
        // calculate address and load value
        mar = get_address(inst);
        mbr = memory->load(mar);

        // increment and store
        mbr = mbr.to_ulong() + 1;
        memory->store(mar, mbr);

        // increment pc if result was 0
        if (mbr.to_ulong() == 0)
        {
            pc = pc.to_ulong() + 1;
        }

        // update stats
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::DCA):
        // calculate address and store ac there
        mar = get_address(inst);
        memory->store(mar, ac);
        
        // clear ac
        ac = 0;

        // update statse
        stats.clocks += 2;
        break;
    case (Pdp8::Sim::JMS):
        // calculate address and store return value there
        mar = get_address(inst);
        memory->store(mar, pc);

        // set pc to instruction after address
        pc = mar + 1;

        // update statistics
        stats.clocks += 2; 
        break;
    case (Pdp8::Sim::JMP):
        // calculate address
        mar = get_address(inst);

        // set pc to jump target
        pc = mar;

        // update stats
        stats.clocks += 1;
        break;
    case (Pdp8::Sim::IOT):
        // Print message if IOT instruction is encountered
        std::cerr << std::setfill('0') << "0" << std::oct;
        std::cerr << std::setw(4) << std::oct << pc.to_ulong() - 1;
        std::cerr << ": IOT Instructions are not supported";
        std::cerr << std::endl << std::dec;
        break;
    case (Pdp8::Sim::OPR):
        // handle micro opts in fuction
        halt = process_micro(inst.micro);

        // update stats
        stats.clocks += 1;
        break;
    default:
        break;    
    }
    
    // return halt value
    return halt;
}

// Process a micro op
// INPUT: Micro op to be prossessed
// OUTPUT: True if halt, false otherwise
bool Pdp8::Simulator::process_micro(Pdp8::reg9 micro)
{
    bool halt = false; // halt value defaults to false

    if (micro[8] == 0) // Group 1
    {
        // set flags from instruction
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


        // combine l and ac 
        std::bitset<13> lac = ac.to_ulong();
        lac[12] = static_cast<unsigned int>(l);

        // Increment l/ac if iac bit set
        if (iac)
        {
            // increment combined register
            lac = lac.to_ulong() + 1;

        }


        // handle rotations
        if (bsw)
        {
            if (ral && !rar)
            {
                // rotate left 2
                std::bitset<13> nlac = lac << 2;
                nlac[1] = lac[12];
                nlac[0] = lac[11];
                
                lac = nlac;
            }
            else if (rar && !ral)
            {
                // rotate right 2
                std::bitset<13> nlac = lac >> 2;
                nlac[12] = lac[1];
                nlac[11] = lac[0];

                lac = nlac;
            }
        }
        else
        {
            
            if (ral && !rar)
            {
                // rotate left
                std::bitset<13> nlac = lac << 1;
                nlac[0] = lac[12];
                
                lac = nlac;
            }
            else if (rar && !ral)
            {
                // rotate right
                std::bitset<13> nlac = lac >> 1;
                nlac[12] = lac[0];
                
                lac = nlac;    
            }
        } 
        // set l and ac from result
        l = lac[12];
        ac = lac.to_ulong() & 0xFFFu;
    }
    else if (micro[0] == 0) // Group 2
    {
        // set flags from instruction
        bool hlt = micro[1];
        bool osr = micro[2];
        bool rev = micro[3];
        bool snl = micro[4];
        bool sza = micro[5];
        bool sma = micro[6];
        bool cla = micro[7];

        bool skip = false;  // skip flag

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
    else // Group 3
    {
        // print message if a group 3 micro opt is encountered
        std::cerr << std::setfill('0') << "0" << std::oct;
        std::cerr << std::setw(4) << pc.to_ulong() - 1;
        std::cerr << ": Group 3 micro ops are not supported";
        std::cerr << std::endl << std::dec;
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
    std::cerr << "PC: " << pc << " (0";
    std::cerr << std::setw(4) << std::oct << pc.to_ulong() << ") ";
    std::cerr << "AC: " << ac << " (0";
    std::cerr << std::setw(4) << std::oct << ac.to_ulong() << ") ";
    std::cerr << "L: ";

    if (l)
        std::cerr << "1";
    else
        std::cerr << "0";

    std::cerr << std::dec << " Clock: " << stats.clocks;

    // Handle pause
    if (pause)
        std::cin.get();
    else
        std::cerr << std::endl;
}
