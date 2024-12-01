#include "mapper.h"
#include "memory_ranges.h"
#include <stdexcept>

/* Mapper */
Mapper::Mapper(uint8_t nPRGBanks, uint8_t nCHRBanks) 
    : nPRGBanks(nPRGBanks), nCHRBanks(nCHRBanks) {}


/* Mapper000 */
Mapper000::Mapper000(uint8_t nPRGBanks, uint8_t nCHRBanks)
                : Mapper(nPRGBanks, nCHRBanks) {}

uint16_t Mapper000::translatePRGaddr(uint16_t address) const
{
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        // normalize address + BANK1 mirroring handle
        uint32_t offset = (address - 0x8000) % (nPRGBanks * 16 * 1024);
        return offset;
    }
    throw std::out_of_range("Invalid PRG address");
}

uint16_t Mapper000::translateCHRaddr(uint16_t address) const
{
    return 0x00;
}
