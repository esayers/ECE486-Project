/*  pdp8-memory *  Edward Sayers
 *  ECE 486 Project
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>

#ifndef PDP8_MEMORY_H
#define PDP8_MEMORY_H

namespace Pdp8 {
    namespace mem {
        const int size = 4096;
        const std::string default_logfile = "mem.dmp";

        enum log_type {
            data_read = 0,
            data_write = 1,
            inst_fetch = 2,
        };
    }

    struct Word {
        short value;
        bool access;
    };

    class Memory
    {
    public:
        Memory();
        Memory(unsigned int);
        ~Memory();

        int store(unsigned short, short);
        int load(unsigned short, short);
        int fetch(unsigned short, short);

        int dump_memory(std::ostream&);
        int load_from_file(std::string);
    private:
        const int mem_size;
        Word *mem; 

        std::string logfile;

        void mem_put(unsigned short, short);
        short mem_get(unsigned short);
        void log(unsigned short, Pdp8::mem::log_type);
    };

}



#endif // PDP8_MAIN_MEMORY_H
