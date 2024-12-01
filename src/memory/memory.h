#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>
#include "NESROM.h"

/*
 * NES CPU Memory Map
 * 
 * Address Range    Description                       Notes
 * --------------------------------------------------------------------
 * $0000–$07FF      Work RAM (WRAM)                  2 KB of internal RAM
 * $0800–$1FFF      WRAM Mirrors                     Mirrors of $0000–$07FF
 * $2000–$2007      PPU Registers                    Graphics processing
 * $2008–$3FFF      PPU Register Mirrors             Mirrors of $2000–$2007
 * $4000–$401F      APU and I/O Registers            Sound and input handling
 * $4020–$FFFF      Cartridge Space                  PRG-ROM, PRG-RAM, and mapper
 * 
 * - WRAM is mirrored repeatedly from $0800 to $1FFF, allowing the same 
 *   physical memory to be accessed from multiple addresses.
 * - PPU registers are mirrored every 8 bytes from $2000–$3FFF.
 * - The cartridge space ($4020–$FFFF) is controlled by the cartridge's
 *   mapper, which determines how PRG-ROM and PRG-RAM are accessed.
 */

// Memory region constants
constexpr uint16_t WRAM_STARTADDR = 0x0000;
constexpr uint16_t WRAM_ENDADDR = 0x0800; // Exclusive range for easier checks

constexpr uint16_t WRAM_MIRRORS_STARTADDR = 0x0800;
constexpr uint16_t WRAM_MIRRORS_ENDADDR = 0x2000;

constexpr uint16_t PPU_REGISTERS_STARTADDR = 0x2000;
constexpr uint16_t PPU_REGISTERS_ENDADDR = 0x2008;

constexpr uint16_t PPU_MIRRORS_STARTADDR = 0x2008;
constexpr uint16_t PPU_MIRRORS_ENDADDR = 0x4000;

constexpr uint16_t APU_IO_STARTADDR = 0x4000;
constexpr uint16_t APU_IO_ENDADDR = 0x4020;

constexpr uint16_t CARTRIDGE_SRAM_STARTADDR = 0x6000;
constexpr uint16_t CARTRIDGE_SRAM_ENDADDR = 0x8000;

constexpr uint16_t CARTRIDGE_ROM_STARTADDR = 0x8000;
constexpr uint16_t CARTRIDGE_ROM_ENDADDR = 0xFFFF;

class Memory
{
    public:
        /* Default Constructor */
        Memory();

        /* Read/Write operations */
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t data);

        /* Load Cartridge in PRGROM */
        void loadCartridge(const NESROM& cartridge);

    private:
        std::vector<uint8_t> WRAM;
        std::vector<uint8_t> PRGROM; // PRG-ROM data
        std::vector<uint8_t> CHRROM; // CHR-ROM data
};

#endif // MEMORY_H