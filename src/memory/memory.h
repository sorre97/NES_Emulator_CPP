#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <vector>
#include "NESROM.h"
#include "mapper.h"
#include "memory_ranges.h"

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

// Forward declaration of PPU
class PPU;

class Memory
{
    public:
        /* Default Constructor */
        Memory(PPU& ppuInstance);

        /* CPU Read/Write operations */
        uint8_t CPUread(uint16_t address) const;
        void CPUwrite(uint16_t address, uint8_t data);

        /* PPU Read/Write operations */
        uint8_t PPUread(uint16_t address) const;
        void PPUwrite(uint16_t address, uint8_t data);

        /* Load Cartridge in PRGROM */
        void loadCartridge(const NESROM& cartridge);

    private:
        std::vector<uint8_t> WRAM;
        std::vector<uint8_t> PRGROM; // PRG-ROM data
        std::vector<uint8_t> CHRROM; // CHR-ROM data

        std::unique_ptr<Mapper> mapper;

        PPU& ppu; // Reference to the PPU
};

#endif // MEMORY_H