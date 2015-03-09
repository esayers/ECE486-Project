/*  pdp8-simulator.h
 *  Edward Sayers
 *  ECE 486 Project
 */


#ifndef PDP8_SIMULATOR_H
#define PDP8_SIMULATOR_H

#include "pdp8-memory.h"

namespace Pdp8
{
    class Simulator
    {
    public:
        Simulator();
        ~Simulator();

        int load_from_hex(std::string);
        int load_from_oct(std::string);
        void set_tracefile(std::string); 
        int dump_memory(std::ostream& = std::cout) const;

    private:
        Memory *  memory;
        reg12 accum;
        reg12 pc;
    };
};
#endif
