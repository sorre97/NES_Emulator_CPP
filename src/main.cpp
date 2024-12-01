#include "NESROM.h"
#include "memory.h"
#include "cpu.h"
#include <iostream>
#include <iomanip>
#include "config.h"

int main()
{
    try
    {
        // Load ROM
        //NESROM rom("../roms/Metal Gear.nes");
        NESROM rom("../roms/Super Mario Bros.nes");
        //NESROM rom("../roms/test_lda_immediate.nes");

        std::cout << "Successfully parsed ROM." << std::endl;
        if (DEBUG)
        {
            std::cout << "  > [DEBUG] PRG-ROM size: " << static_cast<int>(rom.getPRGROM().size()) << " bytes" << std::endl;
            std::cout << "  > [DEBUG] CHR-ROM size: " << static_cast<int>(rom.getCHRROM().size()) << " bytes" << std::endl;
            std::cout << "  > [DEBUG] Mapper ID: " << static_cast<int>(rom.getMapperID()) << std::endl;
        }

        // Initialize memory and load the cartridge
        Memory memory;
        memory.loadCartridge(rom);
        std::cout << "Successfully loaded cartridge into memory." << std::endl;

        // Initialize the CPU
        NES::CPU cpu(memory);

        // Reset the CPU (sets PC to reset vector, initializes registers, etc.)
        cpu.reset();
        std::cout << "CPU reset complete." << std::endl;
        if (DEBUG)
        {
            cpu.printCPUState();
        }

        // Fetch and execute a limited number of instructions
        int instructionCount = 30;
        while (instructionCount-- > 0)
        {
            if (DEBUG)
            {
                std::cout << "Executing instruction at PC: 0x" 
                          << std::hex << std::setw(4) << std::setfill('0') << cpu.getProgramCounter() 
                          << std::endl;
            }
            // TODO: remove try catch as it will be catched underneath and return
            try{
                cpu.executeInstruction();
            }catch (const std::exception& e) {
                if (DEBUG)
                {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
            
        }

        std::cout << "Execution of 4 instructions complete." << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
