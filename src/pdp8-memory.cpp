/*  pdp8-memory.cpp
 *
 *  Edward Sayers
 * ECE 486 Project
 */

#include "pdp8-memory.h"

// Constructor
Pdp8::Memory::Memory(unsigned int size) : mem_size(size)
{
    mem = new Pdp8::Word[mem_size];
    logfile = Pdp8::mem::default_logfile;

    for (int i = 0; i < mem_size; ++i)
    {
        mem[i].access = false;
        mem[i].value = 0;
    }
}

// Destructor
Pdp8::Memory::~Memory()
{
    delete [] mem;
}

int Pdp8::Memory::dump_memory(std::ostream& out)
{
    int count = 0;
    out << std::oct << std::setfill('0') << std::right;

    for (int i = 0; i < mem_size; ++i)
    {
        if (mem[i].access)
        {
            out << std::setw(4) << i << ": ";
            out << std::setw(4) << mem[i].value << std::endl;
            ++count;
        }
    }
    
    return count;
}

int Pdp8::Memory::load_from_file(std::string filename)
{
    std::ifstream file (filename);
    std::string line;
    int count = 0;
    int index = 0;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (line.length())
            {
                if (line.compare(0, 1, "@") == 0)
                {
                    index = std::stoi(line.substr(1), NULL, 16);
                }
                else
                {
                    this->mem_put(index++, std::stoi(line, NULL, 16));
                    ++count;
                }
            }
        }
        file.close();
    }
    
    return count;
}

int Pdp8::Memory::store(unsigned short address, short value)
{
    mem_put(address, value);
    log(address, Pdp8::mem::data_write); 

}

void Pdp8::Memory::mem_put(unsigned short address, short value)
{
    // Check that address is valid
    if (address >= mem_size)
    {
        throw std::out_of_range ("Array out of bounds");
        return;
    }

    // Insert value at address
    mem[address].value = value;
    mem[address].access = true;

    return;
}

short Pdp8::Memory::mem_get(unsigned short address)
{
    if (address >= mem_size)
    {
        throw std::out_of_range ("Array out of bounds");
        return 0;
    }

    return mem[address].value;
}

void Pdp8::Memory::log(unsigned short address, Pdp8::mem::log_type type)
{
    
    std::ofstream file (logfile, std::ios::app);
    if (file.is_open())
    {   
        file << type << " " << std::oct << address << std::endl; 
    }
    file.close();
}
