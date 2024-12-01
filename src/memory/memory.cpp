#include "memory.h"
#include <iostream>

Memory::Memory() 
    : WRAM(2 * 1024, 0) // 2KB of WRAM
{}

uint8_t Memory::read(uint16_t address) const
{
    /* WRAM access: $0000 - $07FF */
    if (address >= WRAM_STARTADDR && address < WRAM_ENDADDR) {
        return WRAM[address];
    }
    
    /* WRAM mirrored access: $0800 - $1FFF */
    if (address >= WRAM_MIRRORS_STARTADDR && address < WRAM_MIRRORS_ENDADDR) {
        uint16_t mirror_address = address % (WRAM_ENDADDR - WRAM_STARTADDR);
        return WRAM[mirror_address];
    }

    /* PPU register access: $2000 - $2007 */
    if (address >= PPU_REGISTERS_STARTADDR && address < PPU_REGISTERS_ENDADDR) {
        // Placeholder for future PPU implementation
        return 0x00;
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        // Placeholder for future PPU mirrored implementation
        return 0x00;
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        // Placeholder for future APU/IO implementation
        return 0x00;
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        // Placeholder for cartridge handling
        return 0x00;
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        size_t offset = address - CARTRIDGE_ROM_STARTADDR; // rescale for 0-index in vector access
        
        if(PRGROM.size() == (16 * 1024)) // only 16 KB of PRG-ROM
        {
            // BANK2 is mirror of BANK1, rescale access to first bank if needed
            offset %= (16 * 1024);
        }

        return PRGROM[offset];
    }

    /* Out of range read */
    return 0xFF;
}

void Memory::write(uint16_t address, uint8_t value) {
    /* WRAM access: $0000 - $07FF */
    if (address >= WRAM_STARTADDR && address < WRAM_ENDADDR) {
        WRAM[address] = value;
        return;
    }

    /* WRAM mirrored access: $0800 - $1FFF */
    if (address >= WRAM_MIRRORS_STARTADDR && address < WRAM_MIRRORS_ENDADDR) {
        uint16_t mirror_address = address % (WRAM_ENDADDR - WRAM_STARTADDR);
        WRAM[mirror_address] = value;
        return;
    }

    /* PPU register access: $2000 - $2007 */
    if (address >= PPU_REGISTERS_STARTADDR && address < PPU_REGISTERS_ENDADDR) {
        // Placeholder for future PPU implementation
        return;
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        // Placeholder for future PPU mirrored implementation
        return;
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        // Placeholder for future APU/IO implementation
        return;
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        // Placeholder for cartridge handling
        return;
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        // ROM write ignored
        return;
    }
}

void Memory::loadCartridge(const NESROM& cartridge)
{
    PRGROM = cartridge.getPRGROM();
    CHRROM = cartridge.getCHRROM();
}