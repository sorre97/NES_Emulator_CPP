#ifndef MEMORY_RANGES_H
#define MEMORY_RANGES_H

#include <cstdint>

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

#endif