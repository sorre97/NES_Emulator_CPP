#include "ppu.h"

PPU::PPU() 
    : PPUCTRL(0), PPUMASK(0), PPUSTATUS(0), OAMADDR(0), PPUSCROLL(0), PPUADDR(0), PPUDATA(0) {
    VRAM.resize(2048, 0); // Initialize 2 KB of VRAM
    OAM.resize(256, 0);   // Initialize 256 bytes of OAM
}

void PPU::reset() {
    PPUCTRL = 0;
    PPUMASK = 0;
    PPUSTATUS = 0;
    OAMADDR = 0;
    PPUSCROLL = 0;
    PPUADDR = 0;
    PPUDATA = 0;
}

void PPU::step() {
    // Handle PPU rendering and timing here
}

// TODO: check
uint8_t PPU::readRegister(uint16_t address) {
    uint16_t reg = address & 0x2007; // Handle mirroring within $2000-$2007
    switch (reg) {
        case 0x2002: // PPUSTATUS
            {
                uint8_t status = PPUSTATUS;
                PPUSTATUS &= 0x7F; // Clear the vertical blank flag (bit 7)
                return status;
            }
        case 0x2004: // OAMDATA
            return OAM[OAMADDR]; // Read from OAM at current OAMADDR
        case 0x2007: // PPUDATA
            {
                uint8_t data = VRAM[PPUADDR % 2048]; // Read from VRAM
                PPUADDR += (PPUCTRL & 0x04) ? 32 : 1; // Increment PPUADDR by 1 or 32
                return data;
            }
        default:
            throw std::runtime_error("Unsupported PPU register read.");
    }
}

// TODO: check
void PPU::writeRegister(uint16_t address, uint8_t value) {
    uint16_t reg = address & 0x2007; // Handle mirroring within $2000-$2007
    switch (reg) {
        case 0x2000: // PPUCTRL
            PPUCTRL = value;
            break;
        case 0x2001: // PPUMASK
            PPUMASK = value;
            break;
        case 0x2003: // OAMADDR
            OAMADDR = value;
            break;
        case 0x2004: // OAMDATA
            OAM[OAMADDR++] = value; // Write to OAM and increment OAMADDR
            break;
        case 0x2007: // PPUDATA
            VRAM[PPUADDR % 2048] = value; // Write to VRAM
            PPUADDR += (PPUCTRL & 0x04) ? 32 : 1; // Increment PPUADDR
            break;
        default:
            throw std::runtime_error("Unsupported PPU register write.");
    }
}
