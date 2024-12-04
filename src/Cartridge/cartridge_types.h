/**
 * @file cartridge_types.h
 * @brief Defines the iNES ROM header structure for NES cartridges.
 */

#ifndef CARTRIDGE_TYPES_H
#define CARTRIDGE_TYPES_H

#include <cstdint>

/**
 * @struct RomHeaderType
 * @brief Represents the iNES ROM header as defined in the NES file format.
 *
 * This structure contains metadata about the NES cartridge, including ROM sizes,
 * mirroring type, and mapper ID.
 */
struct RomHeaderType {
    char magic[4];        /**< Magic number "NES<EOF>" - Bytes 0-3. */
    uint8_t PRGROM_size;  /**< Size of PRG ROM in 16 KB units - Byte 4. */
    uint8_t CHRROM_size;  /**< Size of CHR ROM in 8 KB units - Byte 5. */
    uint8_t flags6;       /**< Mapper, mirroring, battery, trainer - Byte 6. */
    uint8_t flags7;       /**< Mapper, VS/Playchoice, NES 2.0 - Byte 7. */
    uint8_t flags8;       /**< PRG-RAM size (rarely used extension) - Byte 8. */
    uint8_t flags9;       /**< TV system (rarely used extension) - Byte 9. */
    uint8_t flags10;      /**< TV system, PRG-RAM presence (unofficial) - Byte 10. */
    uint8_t unused[5];    /**< Unused padding (should be zero) - Bytes 11-15. */
} __attribute__((packed));

using RomHeader = struct RomHeaderType;

#endif // CARTRIDGE_TYPES_H
