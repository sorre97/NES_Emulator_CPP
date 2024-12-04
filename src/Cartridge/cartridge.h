/**
 * @file cartridge.h
 * @brief Defines the Cartridge class for managing NES ROMs.
 */

#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "cartridge_types.h"
#include "mapper.h"
#include <string>
#include <vector>
#include <memory>

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

/**
 * @class Cartridge
 * @brief Represents an NES cartridge and provides access to its PRG and CHR data.
 *
 * This class handles the loading and parsing of iNES-format ROM files.
 */
class Cartridge {
public:
    /**
     * @brief Deleted default constructor.
     */
    Cartridge() = delete;

    /**
     * @brief Destructor.
     */
    ~Cartridge() = default;

    /**
     * @brief Constructs a Cartridge instance from a file path.
     * @param filepath Path to the NES ROM file.
     */
    explicit Cartridge(const std::string& filepath);

    // Metadata accessors
    uint8_t getMapperID() const;
    bool hasBatteryBackedRAM() const;
    bool isFourScreenVRAM() const;
    bool isVerticalMirroring() const;

    uint8_t getPRGBankCount() const;
    uint8_t getCHRBankCount() const;

    // Memory access functions
    uint8_t readPRGROM(uint16_t address) const;
    uint8_t readCHRROM(uint16_t address) const;

private:
    RomHeader RomHeader;               /**< Parsed ROM header. */
    std::vector<uint8_t> PRGROM;       /**< PRG-ROM data. */
    std::vector<uint8_t> CHRROM;       /**< CHR-ROM data. */
    std::vector<uint8_t> trainer;      /**< Trainer data (if present). */
    uint8_t mapperID;                  /**< Mapper ID parsed from the header. */
    std::unique_ptr<Mapper> mapper;    /**< Mapper instance for address translation. */
};

#endif // CARTRIDGE_H