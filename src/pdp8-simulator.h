// pdp8-simulator.h
// Edward Sayers
// ECE 486: PDP-8 Instruction Set Simulator


#ifndef PDP8_SIMULATOR_H
#define PDP8_SIMULATOR_H

#include "pdp8-memory.h"

namespace Pdp8
{  
    namespace Sim
    {
        const int num_ops = 8;
        
        // Data structure to store statistics 
        struct Stats
        {
            int clocks;
            int ops[num_ops];
        };


        // Enumeration of op codes
        enum Ops
        {
            AND = 0,
            TAD = 1,
            ISZ = 2,
            DCA = 3,
            JMS = 4,
            JMP = 5,
            IOT = 6,
            OPR = 7,
        };
        
        // Data structure for decoded instructions
        struct Inst
        {       
           Pdp8::Sim::Ops   op;     // Op code
           bool             ind;    // Indirect flag
           bool             zero;   // Zero flag
           unsigned short   offset; // Page offset
           reg9             micro;  // Micro coded instructions
           unsigned short   page;   // Page
        };

    };
    class Simulator
    {
    public:
        Simulator();
        ~Simulator();
        
        // Wrappers for memory functions
        int load_from_hex(std::string);
        int load_from_oct(std::string);
        void set_tracefile(std::string); 
        int dump_memory(std::ostream& = std::cout) const;

        // Print statistics
        void print_stats(std::ostream& = std::cout) const;

        // Start simulation
        void start(unsigned short = 0200);

        // Functions to change parameters
        void set_debug(bool);
        void set_pause(bool);
        void set_switches(Pdp8::reg12);

    private:
        // State
        Memory *  memory;   // Pointer to memory class
        Sim::Stats stats;   // Statistic struct
        reg12 ac;           // Accumulator
        reg12 pc;           // Program Counter
        bool  l;            // Link Register
        reg12 switches;     // State of front panel switches
        bool debug;         // Debug flag
        bool pause;         // Pause flag

        // private functions
        Sim::Inst decode(reg12, unsigned short);
        bool process_instruction();
        bool process_micro(Pdp8::reg9);
        unsigned short get_address(Pdp8::Sim::Inst);
        void print_debug(void);
    };
};
#endif
