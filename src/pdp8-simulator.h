/*  pdp8-simulator.h
 *  Edward Sayers
 *  ECE 486 Project
 */


#ifndef PDP8_SIMULATOR_H
#define PDP8_SIMULATOR_H

#include "pdp8-memory.h"

namespace Pdp8
{  
    namespace Sim
    {
        const int num_ops = 8;
         
        struct Stats
        {
            int clocks;
            int ops[num_ops];
        };


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

        struct Inst
        {
           Pdp8::Sim::Ops   op;
           bool             ind;
           bool             zero;
           unsigned short   offset;
           reg9             micro;
        };
    };
    class Simulator
    {
    public:
        Simulator();
        ~Simulator();

        int load_from_hex(std::string);
        int load_from_oct(std::string);
        void set_tracefile(std::string); 
        int dump_memory(std::ostream& = std::cout) const;
        void print_stats(std::ostream& = std::cout) const;
        void start(unsigned short = 0200);

    private:
        Memory *  memory;
        Sim::Stats stats;
        reg12 ac;
        reg12 pc;
        bool  l;

        Sim::Inst decode(reg12);
        bool process_instruction();
    };
};
#endif
