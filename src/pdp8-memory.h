/*  pdp8-main-memory.hpp
 *
 *  Edward Sayers
 *  ECE 486 Project
 */

#ifndef PDP8_MAIN_MEMORY_H
#define PDP8_MAIN_MEMORY_H

class Pdp8MainMemory
{
public:
    Pdp8MainMemory();
    ~Pdp8MainMemory();
private:
    const unsigned int wordSize = 12;
    const unsigned int memSize = 4096;
    unsigned int mem[memSize];
}

#endif // PDP8_MAIN_MEMORY_H
