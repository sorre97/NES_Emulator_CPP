#include "mapper.h"
//#include "memory_ranges.h"
#include <stdexcept>

/* Mapper */
Mapper::Mapper(uint8_t nPRGBanks, uint8_t nCHRBanks) 
    : nPRGBanks(nPRGBanks), nCHRBanks(nCHRBanks) {}


/* Mapper000 */
Mapper000::Mapper000(uint8_t nPRGBanks, uint8_t nCHRBanks)
                : Mapper(nPRGBanks, nCHRBanks) {}

uint16_t Mapper000::translatePRGaddr(uint16_t address) const
{
    // normalize address + BANK1 mirroring handle
    uint32_t offset = (address - 0x8000) % (nPRGBanks * 16 * 1024);
    return offset;
}

uint16_t Mapper000::translateCHRaddr(uint16_t address) const
{
    // Normalize the address for CHR-ROM or CHR-RAM
    uint32_t offset = address % (nCHRBanks * 8 * 1024); // CHR-ROM size in bytes
    return offset;
}
