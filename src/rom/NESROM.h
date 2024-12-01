#ifndef NESROM_H
#define NESROM_H

#include <string>
#include <vector>

/*
 * NES Cartridge Memory Organization (iNES Format)
 * ------------------------------------------------
 * Note: NES 2.0 format is currently not supported.
 *
 * Address Range    Description
 * --------------------------------------------------------------
 * $4020–$5FFF      Expansion ROM (optional, rarely used)
 * $6000–$7FFF      PRG-RAM (save RAM or work RAM, battery-backed)
 * $8000–$BFFF      PRG-ROM Bank 1 (first 16 KB of program data)
 * $C000–$FFFF      PRG-ROM Bank 2 (second 16 KB or switchable bank)
 *
 * NES ROM Structure (iNES File Format)
 * ------------------------------------
 * Header (16 bytes):
 * --------------------------------------------------------------
 * Offset | Size | Description
 * --------------------------------------------------------------
 * 0-3    | 4    | Magic number "NES<EOF>" (ASCII: 4E 45 53 1A)
 * 4      | 1    | PRG-ROM size in 16 KB units
 * 5      | 1    | CHR-ROM size in 8 KB units (0 if CHR-RAM is used)
 * 6      | 1    | Flags 6:
 *                  - Bit 0: Mirroring
 *                           0 = Vertical mirroring ("horizontal arrangement")
 *                           1 = Horizontal mirroring ("vertical arrangement")
 *                  - Bit 1: Cartridge contains battery-backed PRG-RAM ($6000–$7FFF) or other persistent memory
 *                  - Bit 2: Trainer (512 bytes) present at $7000–$71FF
 *                  - Bit 3: Four-screen VRAM layout
 *                  - Bits 4-7: Lower nibble of Mapper ID
 * 7      | 1    | Flags 7:
 *                  - Bit 0: VS Unisystem (1 = cartridge works with VS Unisystem hardware)
 *                  - Bit 1: PlayChoice-10 (1 = cartridge contains PlayChoice-10 hint data)
 *                  - Bits 2-3: NES 2.0 identifier
 *                           00 = Standard iNES format
 *                           10 = NES 2.0 format
 *                  - Bits 4-7: Upper nibble of Mapper ID
 * 8      | 1    | PRG-RAM size in 8 KB units (0 means 8 KB for compatibility)
 * 9      | 1    | TV System:
 *                  - Bit 0: 0 (NTSC); 1 (PAL)
 *                  - Bits 1-7: Unused (must be 0)
 * 10     | 1    | Flags 10:
 *                  - Bit 0-1: TV system (NTSC/PAL compatibility)
 *                  - Bit 4: PRG-RAM absence (0: present, 1: absent)
 *                  - Bit 5: Bus conflicts (0: no, 1: yes)
 *                  - Bits 2-3, 6-7: Unused (must be 0)
 * 11-15  | 5    | Reserved bytes (must be 0)
 *
 * PRG-ROM: Program data for the CPU, size defined by byte 4.
 * CHR-ROM: Graphics data for the PPU, size defined by byte 5 (if 0, CHR-RAM is used).
 */

class NESROM
{
    public:
        /* Delete default empty constructor */
        NESROM() = delete;
        ~NESROM() = default;

        /* Constructor with rom filepath param */
        explicit NESROM(const std::string& filepath);

        /* Metadata getters */
        uint8_t getMapperID() const;
        bool hasBatteryBackedRAM() const;
        bool isFourScreenVRAM() const;
        bool isVerticalMirroring() const;

        /* Accessor methods for PRG-ROM and CHR-ROM */
        const std::vector<uint8_t>& getPRGROM() const;
        const std::vector<uint8_t>& getCHRROM() const;

    private:
        // Define NESHeader as a typedef for the struct
        struct RomHeaderType {
            char magic[4];         // "NES<EOF>" - Bytes 0-3
            uint8_t PRGROM_size;    // Size of PRG ROM in 16 KB units - Byte 4
            uint8_t CHRROM_size;    // Size of CHR ROM in 8 KB units - Byte 5
            uint8_t flags6;        // Mapper, mirroring, battery, trainer - Byte 6
            uint8_t flags7;        // Mapper, VS/Playchoice, NES 2.0 - Byte 7
            uint8_t flags8;        // PRG-RAM size (rarely used extension) - Byte 8
            uint8_t flags9;        // TV system (rarely used extension) - Byte 9
            uint8_t flags10;       // TV system, PRG-RAM presence (unofficial) - Byte 10
            uint8_t unused[5];     // Unused padding (should be zero) - Bytes 11-15
        } __attribute__((packed));

        /* ROM header */
        RomHeaderType RomHeader;

        /*  PRG and CHR ROM */
        std::vector<uint8_t> PRGROM;     // PRG-ROM data (program code for the CPU)
        std::vector<uint8_t> CHRROM;     // CHR-ROM data (graphics for the PPU)
        std::vector<uint8_t> trainer;    // 

        /* Specific Flags */
        uint8_t mapperID;
};

#endif // NESROM_H