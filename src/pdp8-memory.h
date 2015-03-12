// pdp8-memory.h
// Edward Sayers
// ECE 486: PDP-8 Instruction Set Simulator


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
    typedef std::bitset<9> reg9;

    namespace mem
    {
        const int size = 4096;
        const std::string default_logfile = "tracefile";

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
        Memory();
        ~Memory();

        void store(unsigned short, reg12);
        reg12 load(unsigned short);
        reg12 fetch(unsigned short);

        int dump_memory(std::ostream&) const;
        int load_from_hex(std::string);
        int load_from_oct(std::string);

        void set_tracefile(std::string);
    private:
        const unsigned int mem_size;
        Pdp8::Word *mem;

        std::string logfile_name;
        std::ofstream logfile;

        void mem_put(unsigned short, reg12);
        reg12 mem_get(unsigned short);
        void log(unsigned short, Pdp8::mem::log_type);
    };
}

#endif // PDP8_MAIN_MEMORY_H
