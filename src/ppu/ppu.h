/**
 * @file ppu.h
 * @brief Represents the PPU co-processor used in the NES emulator.
 *
 * This file defines the PPU class, which emulates the PPU,
 * including its internal registers, status flags, and interaction with the system bus.
 */

#ifndef PPU_H
#define PPU_H

#include <cstdint>
#include <vector>
#include <functional>

/**
 * @class PPU
 * @brief Represents the Picture Processing Unit (PPU) of the NES.
 *
 * The PPU is responsible for rendering graphics and managing video memory.
 * It interacts with the CPU via specific memory-mapped registers
 * and provides the necessary functionality to display sprites and backgrounds.
 */
class PPU
{
    public:
        /**
         * @brief Constructs a new PPU object.
         *
         * Initializes internal state and allocates VRAM and OAM memory.
         */
        PPU();

        /**
         * @brief Resets the PPU to its initial state.
         *
         * Clears internal registers and memory, preparing the PPU for a new frame or game.
         */
        void reset();

        /**
         * @brief Executes a single PPU step (cycle).
         *
         * This function progresses the PPU's internal state, emulating
         * the rendering process for each CPU cycle.
         */
        void step();

        /**
         * @brief Reads from a memory-mapped PPU register.
         * 
         * @param address The memory address of the register to read.
         * @return The value read from the specified register.
         */
        uint8_t readRegister(uint16_t address);

        /**
         * @brief Writes to a memory-mapped PPU register.
         * 
         * @param address The memory address of the register to write.
         * @param value The value to write to the specified register.
         */
        void writeRegister(uint16_t address, uint8_t value);

        // Register a callback for triggering NMI
        void setNMICallback(const std::function<void()>& callback);
        void setIRQCallback(const std::function<void()>& callback);

    private:
        std::function<void()> triggerNMI; // NMI callback function
        std::function<void()> triggerIRQ; // IRQ callback function

        // PPU Registers

        /** @brief Control register (PPUCTRL). Manages settings like name table address and NMI enable. */
        uint8_t PPUCTRL;    // $2000

        /** @brief Mask register (PPUMASK). Controls rendering options like grayscale and background visibility. */
        uint8_t PPUMASK;    // $2001

        /** @brief Status register (PPUSTATUS). Provides status information like sprite overflow and vertical blank. */
        uint8_t PPUSTATUS;  // $2002

        /** @brief OAM address register (OAMADDR). Points to the address in OAM for subsequent reads or writes. */
        uint8_t OAMADDR;    // $2003

        /** @brief OAM data register (OAMDATA). Used to access sprite attribute data. */
        uint8_t OAMDATA;    // $2004

        /** @brief Scroll register (PPUSCROLL). Sets the scroll position for the background. */
        uint8_t PPUSCROLL;  // $2005

        /** @brief Address register (PPUADDR). Holds the address for VRAM read/write operations. */
        uint8_t PPUADDR;    // $2006

        /** @brief Data register (PPUDATA). Used to read or write data to/from VRAM. */
        uint8_t PPUDATA;    // $2007

        /** @brief Video RAM (VRAM). 2 KB of memory for storing tile data and other graphics-related data. */
        std::vector<uint8_t> VRAM;

        /** @brief Object Attribute Memory (OAM). 256 bytes for storing sprite attributes. */
        std::vector<uint8_t> OAM;

        uint16_t currentCycle = 0;     // Current cycle in the scanline (0-340)
        uint16_t currentScanline = 0;  // Current scanline (0-260)

        bool writeToggle = false; // Tracks alternating writes to PPUSCROLL/PPUADDR
        uint8_t scrollX = 0;      // Fine X scroll
        uint8_t scrollY = 0;      // Fine Y scroll
};

#endif