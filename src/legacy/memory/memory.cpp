#include "memory.h"
#include <iostream>
#include "ppu.h" // Full PPU definition is needed here

Memory::Memory(PPU& ppuInstance) 
    : WRAM(2 * 1024, 0), ppu(ppuInstance) // 2KB of WRAM
{}

uint8_t Memory::CPUread(uint16_t address) const
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
        return ppu.readRegister(address);
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        return ppu.readRegister(mirroredAddress);
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
        /*size_t offset = address - CARTRIDGE_ROM_STARTADDR; // rescale for 0-index in vector access
        
        if(PRGROM.size() == (16 * 1024)) // only 16 KB of PRG-ROM
        {
            // BANK2 is mirror of BANK1, rescale access to first bank if needed
            offset %= (16 * 1024);
        }*/

        return PRGROM[mapper->translatePRGaddr(address)];
    }

    /* Out of range read */
    return 0xFF;
}

void Memory::CPUwrite(uint16_t address, uint8_t value) {
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
        ppu.writeRegister(address, value);
        return;
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        ppu.writeRegister(mirroredAddress, value);
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

// TODO:
uint8_t Memory::PPUread(uint16_t address) const {
    return 0x00;
}

// TODO:
void Memory::PPUwrite(uint16_t address, uint8_t value) {

}

void Memory::loadCartridge(const NESROM& cartridge)
{
    PRGROM = cartridge.getPRGROM();
    CHRROM = cartridge.getCHRROM();

    uint8_t mapperID = cartridge.getMapperID();
    if (mapperID == 0) { // Mapper 0 (NROM)
        mapper = std::make_unique<Mapper000>(
            cartridge.getPRGBankCount(), // Number of 16 KB PRG banks
            cartridge.getCHRBankCount()  // Number of 8 KB CHR banks
        );
    } else {
        throw std::runtime_error("Unsupported mapper: " + std::to_string(mapperID));
    }
}