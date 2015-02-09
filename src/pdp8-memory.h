/*  pdp8-memory *  Edward Sayers
 *  ECE 486 Project
 */


#ifndef PDP8_MEMORY_H
#define PDP8_MEMORY_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <bitset>

namespace Pdp8 
{
    typedef std::bitset<12> reg12;

    namespace mem
    {
        const int size = 4096;
        const std::string default_logfile = "mem.dmp";

        enum log_type
        {
            data_read = 0,
            data_write = 1,
            inst_fetch = 2,
        };
    }

    struct Word
    {
        Word();
        reg12 value;
        bool access;
    };

    class Memory
    {
    public:
        Memory(unsigned int size = Pdp8::mem::size);
        ~Memory();

        void store(reg12, reg12);
        reg12 load(reg12);
        reg12 fetch(reg12);

        int dump_memory(std::ostream&);
        int load_from_file(std::string);
    private:
        const int mem_size;
        Pdp8::Word *mem; 

        std::string logfile_name;
        std::ofstream logfile;

        void mem_put(reg12, reg12);
        reg12 mem_get(reg12);
        void log(reg12, Pdp8::mem::log_type);
    };
}

#endif // PDP8_MAIN_MEMORY_H
