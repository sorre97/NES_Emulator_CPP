#ifndef PPU_H
#define PPU_H

#include <cstdint>
#include <vector>

class PPU
{
    public:
        PPU();
        void reset();
        void step();

        uint8_t readRegister(uint16_t address);
        void writeRegister(uint16_t address, uint8_t value);

    private:
        // PPU Registers
        uint8_t PPUCTRL;    // $2000
        uint8_t PPUMASK;    // $2001
        uint8_t PPUSTATUS;  // $2002
        uint8_t OAMADDR;    // $2003
        uint8_t OAMDATA;    // $2004
        uint8_t PPUSCROLL;  // $2005
        uint8_t PPUADDR;    // $2006
        uint8_t PPUDATA;    // $2007

        std::vector<uint8_t> VRAM; // PPU's Video RAM (2 KB)
        std::vector<uint8_t> OAM;  // Object Attribute Memory (256 bytes)
};

#endif