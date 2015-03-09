/*  pdp8-memory.cpp
 *
 *  Edward Sayers
 * ECE 486 Project
 */

#include "pdp8-memory.h"


//
// Public functions
//

// Constructor for struct Word
Pdp8::Word::Word()
{
    access = false;
}

// Constructor for class Memory
// INPUT: number of memory locations to create
Pdp8::Memory::Memory() : mem_size(Pdp8::mem::size)
{
    mem = new Pdp8::Word[mem_size];

    set_tracefile(Pdp8::mem::default_logfile);
}

// Destructor for class Memory
Pdp8::Memory::~Memory()
{
    delete [] mem;
    logfile.close();
}

// Display all memory locations that have been previously accessed
// INPUT: ostream to display on
// OUTPUT: number of memory locations displayed
int Pdp8::Memory::dump_memory(std::ostream& out) const
{
    int count = 0;  // To count lines displayed

    // Setup stream format
    out << std::oct << std::setfill('0') << std::right;

    for (unsigned int i = 0; i < mem_size; ++i)
    {
        if (mem[i].access)
        {
            out << std::setw(4) << i << ": ";
            out << std::setw(4) << mem[i].value.to_ulong() << std::endl;
            ++count;
        }
    }

    return count;
}


// Load memory from hex file
// INPUT: file name to load from
// OUTPUT: number of memory locations loaded
int Pdp8::Memory::load_from_hex(std::string filename)
{
    std::ifstream file (filename);  // Open filename as file
    std::string line;               // String for getline
    int count = 0;                  // Count of memory locations
    unsigned short address = 0;     // Current address

    Pdp8::Word *new_mem = new Pdp8::Word[mem_size];

    if (file.is_open())
    {
        while (std::getline(file, line))
        {

            if (line.length()) // Ignore blank lines
            {
                // Lines starting with "@" specify a starting address
                if (line.compare(0, 1, "@") == 0)
                {
                    unsigned long conv; // Converted string
                    try
                    {
                        conv = std::stoul(line.substr(1), NULL, 16);
                    }
                    catch (...)
                    {
                        // If conversion fails, delete new_mem and rethrow
                        file.close();
                        delete [] new_mem;
                        throw;
                    }

                    // Check that requested address is valid
                    if (conv < mem_size)
                    {
                        address = conv;
                    }
                    else
                    {
                        file.close();
                        delete [] new_mem;
                        throw std::out_of_range("Array out of bounds");
                    }
                }
                else
                {
                    unsigned long conv;

                    // Check that address is valid
                    if (address >= mem_size)
                    {
                        file.close();
                        delete [] new_mem;
                        throw std::out_of_range ("Array out of bounds");
                    }

                    try
                    {
                        conv = std::stoul(line, NULL, 16);
                    }
                    catch (...)
                    {
                        // If conversion fails, delete new_mem and rethrow
                        file.close();
                        delete [] new_mem;
                        throw;
                    }

                    new_mem[address].value = conv;
                    new_mem[address++].access = true;
                    ++count;
                }
            }
        }
        file.close();
    }

    delete [] mem;
    mem = new_mem;

    return count;
}

// Load memory from octal file
// INPUT: file name to load from
// OUTPUT: number of memory locations loaded
int Pdp8::Memory::load_from_oct(std::string filename)
{
    std::ifstream file (filename);  // Open filename as file
    std::string line1, line2;       // String for getline
    int count = 0;                  // Count of memory locations
    unsigned short address = 0;     // Current address

    Pdp8::Word *new_mem = new Pdp8::Word[mem_size];

    if (file.is_open())
    {
        while (std::getline(file, line1) && std::getline(file, line2))
        {
            unsigned long conv1, conv2;

            try
            {
                conv1 = std::stoul(line1, NULL, 8);
                conv2 = std::stoul(line2, NULL, 8);
            }
            catch (...)
            {
                file.close();
                delete [] new_mem;
                throw;
            }

            bool is_address = conv1 & (1 << 6);

            // remove upper bits
            conv1 &= ~((~0u) << 6);
            conv2 &= ~((~0u) << 6);

            unsigned short value = (conv1 << 6) | conv2;

            if (is_address)
            {
                if (value >= mem_size)
                {
                    file.close();
                    delete [] new_mem;
                    throw std::out_of_range ("Array out of bounds");
                }
                else
                {
                    address = value;
                }
            }
            else
            {
                if (address >= mem_size)
                {
                    file.close();
                    delete [] new_mem;
                    throw std::out_of_range("Array out of bounds");
                }
                else
                {
                    new_mem[address].value = value;
                    new_mem[address++].access = true;
                    ++count;
                }
            }
        }
        file.close();
    }
    delete [] mem;
    mem = new_mem;
    return count;
}



// Store value in memory and log
// INPUT: address and value
// OUTPUT: logged as a write
void Pdp8::Memory::store(unsigned short address, Pdp8::reg12 value)
{
    mem_put(address, value);
    log(address, Pdp8::mem::data_write);
}

// Load value from memory and log
// INPUT: address
// OUTPUT: value returned and logged as a read
Pdp8::reg12 Pdp8::Memory::load(unsigned short address)
{
   Pdp8::reg12 rv = mem_get(address);
   log(address, Pdp8::mem::data_read);
   return rv;
}

// Fetch instruction from memory and log
// INPUT: address
// OUTPUT: instruction returned and logged as a fetch
Pdp8::reg12 Pdp8::Memory::fetch(unsigned short address)
{
    Pdp8::reg12 rv = mem_get(address);
    log(address, Pdp8::mem::inst_fetch);
    return rv;
}

void Pdp8::Memory::set_tracefile(std::string filename)
{
    logfile.close();
    logfile_name = filename;
    logfile.open(filename, std::ios::app);
}

//
// Private functions
//

// Put value into memory
// INPUT: address and value
// OUTPUT: None
void Pdp8::Memory::mem_put(unsigned short address, Pdp8::reg12 value)
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
}

// Get value from memory
// INPUT: address
// OUTPUT: value returned
Pdp8::reg12 Pdp8::Memory::mem_get(unsigned short address)
{
    if (address >= mem_size)
    {
        throw std::out_of_range ("Array out of bounds");
        return 0;
    }

    return mem[address].value.to_ulong();
}

// Log memory access
// INPUT: address and type
// OUTPUT: none
void Pdp8::Memory::log(unsigned short address, Pdp8::mem::log_type type)
{

    if (logfile.is_open())
    {
        logfile << type << " " << std::oct << address << std::endl;
    }
}
