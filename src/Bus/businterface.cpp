#include "businterface.h"
#include "Cpu/cpu6502_memory_map.h"

BusInterface::BusInterface(std::shared_ptr<Cartridge> cartridge)
    : cartridge(cartridge) {}

uint8_t BusInterface::ppuBusRead(uint16_t address) const
{
    return 0xFF; // TODO:
}

void BusInterface::ppuBusWrite(uint16_t address, uint8_t data)
{
    return; // TODO:
}

uint8_t BusInterface::cpuBusRead(uint16_t address) const
{
    /* PPU register access: $2000 - $2007 */
    if (address >= PPU_REGISTERS_STARTADDR && address < PPU_REGISTERS_ENDADDR) {
        // Placeholder for future PPU implementation
        return 0xFF; //TODO: ppu.readRegister(address);
    }

    /* PPU register mirrored access: $2008 - $3FFF */
    if (address >= PPU_MIRRORS_STARTADDR && address < PPU_MIRRORS_ENDADDR) {
        uint16_t mirroredAddress = PPU_REGISTERS_STARTADDR + (address % 8);
        return 0xFF; //TODO: ppu.readRegister(mirroredAddress);
    }

    /* APU and I/O register access: $4000 - $401F */
    if (address >= APU_IO_STARTADDR && address < APU_IO_ENDADDR) {
        // Placeholder for future APU/IO implementation
        return 0xFF; //TODO: apu.readRegister(address);
    }

    /* Cartridge SRAM space access: $6000 - $7FFF */
    if (address >= CARTRIDGE_SRAM_STARTADDR && address < CARTRIDGE_SRAM_ENDADDR) {
        // Placeholder for cartridge handling
        return 0xFF; //TODO:
    }

    /* Cartridge ROM space access: $8000 - $FFFF */
    if (address >= CARTRIDGE_ROM_STARTADDR && address <= CARTRIDGE_ROM_ENDADDR) {
        return cartridge->readPRGROM(address);
    }

    /* Out of range read */
    return 0xFF;
}

void BusInterface::cpuBusWrite(uint16_t address, uint8_t data)
{
    return; // TODO:
}