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
           unsigned short   page;
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
        void set_debug(bool);
        void set_pause(bool);
        void set_switches(Pdp8::reg12);

    private:
        Memory *  memory;
        Sim::Stats stats;
        reg12 ac;
        reg12 pc;
        bool  l;
        reg12 switches;
        bool debug;
        bool pause;

        Sim::Inst decode(reg12, unsigned short);
        bool process_instruction();
        bool process_micro(Pdp8::reg9);
        unsigned short get_address(Pdp8::Sim::Inst);
        void print_debug(void);
    };
};
#endif
