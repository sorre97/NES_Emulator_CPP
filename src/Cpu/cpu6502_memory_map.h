/**
 * @file cpu6502_memory_map.h
 * @brief Defines constants for the CPU memory map.
 */

#ifndef CPU6502_MEMORY_MAP_H
#define CPU6502_MEMORY_MAP_H

#include <cstdint>

// Memory map constants
constexpr uint16_t WRAM_STARTADDR = 0x0000; /**< Start address of WRAM. */
constexpr uint16_t WRAM_ENDADDR = 0x0800;   /**< End address of WRAM (exclusive). */
constexpr uint16_t WRAM_MIRRORS_STARTADDR = 0x0800; /**< Start address of WRAM mirrors. */
constexpr uint16_t WRAM_MIRRORS_ENDADDR = 0x2000;   /**< End address of WRAM mirrors (exclusive). */

constexpr uint16_t PPU_REGISTERS_STARTADDR = 0x2000; /**< Start address of PPU registers. */
constexpr uint16_t PPU_REGISTERS_ENDADDR = 0x2008;   /**< End address of PPU registers (exclusive). */
constexpr uint16_t PPU_MIRRORS_STARTADDR = 0x2008;   /**< Start address of PPU register mirrors. */
constexpr uint16_t PPU_MIRRORS_ENDADDR = 0x4000;     /**< End address of PPU register mirrors (exclusive). */

constexpr uint16_t APU_IO_STARTADDR = 0x4000; /**< Start address of APU and I/O registers. */
constexpr uint16_t APU_IO_ENDADDR = 0x4020;   /**< End address of APU and I/O registers (exclusive). */

constexpr uint16_t CARTRIDGE_SRAM_STARTADDR = 0x6000; /**< Start address of cartridge SRAM. */
constexpr uint16_t CARTRIDGE_SRAM_ENDADDR = 0x8000;   /**< End address of cartridge SRAM (exclusive). */

constexpr uint16_t CARTRIDGE_ROM_STARTADDR = 0x8000; /**< Start address of cartridge ROM. */
constexpr uint16_t CARTRIDGE_ROM_ENDADDR = 0xFFFF;   /**< End address of cartridge ROM (inclusive). */

#endif // CPU6502_MEMORY_MAP_H
