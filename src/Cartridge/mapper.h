/**
 * @file mapper.h
 * @brief Defines the Mapper base class and derived mapper implementations for NES cartridges.
 */

#ifndef MAPPER_H
#define MAPPER_H

#include <cstdint>

/**
 * @class Mapper
 * @brief Base class for NES mappers, handling address translation for PRG and CHR data.
 */
class Mapper {
public:
    /**
     * @brief Constructs a Mapper with the given PRG and CHR bank counts.
     * @param nPRGBanks Number of PRG-ROM banks.
     * @param nCHRBanks Number of CHR-ROM banks.
     */
    Mapper(uint8_t nPRGBanks, uint8_t nCHRBanks);

    /**
     * @brief Virtual destructor for the base class.
     */
    virtual ~Mapper() = default;

    /**
     * @brief Translates a PRG-ROM address.
     * @param address The CPU-visible address.
     * @return The mapped address within PRG-ROM.
     */
    virtual uint16_t translatePRGaddr(uint16_t address) const = 0;

    /**
     * @brief Translates a CHR-ROM address.
     * @param address The PPU-visible address.
     * @return The mapped address within CHR-ROM.
     */
    virtual uint16_t translateCHRaddr(uint16_t address) const = 0;

protected:
    uint8_t nPRGBanks; /**< Number of PRG-ROM banks. */
    uint8_t nCHRBanks; /**< Number of CHR-ROM banks. */
};

/**
 * @class Mapper000
 * @brief Implementation of the simplest NES mapper, Mapper 000.
 */
class Mapper000 : public Mapper {
public:
    /**
     * @brief Constructs a Mapper000 instance.
     * @param nPRGBanks Number of PRG-ROM banks.
     * @param nCHRBanks Number of CHR-ROM banks.
     */
    Mapper000(uint8_t nPRGBanks, uint8_t nCHRBanks);

    uint16_t translatePRGaddr(uint16_t address) const override;
    uint16_t translateCHRaddr(uint16_t address) const override;
};

#endif // MAPPER_H
